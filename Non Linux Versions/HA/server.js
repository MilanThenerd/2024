const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const axios = require('axios');
const readline = require('readline');
const crypto = require('crypto');

const PORT_RANGE = { min: 1024, max: 49151 };
const RESERVED_PORTS = [];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const users = {};
const auctions = {};

const askForPort = () => {
  return new Promise((resolve) => {
    rl.question('Enter a port to run the server on (1024-49151): ', (answer) => {
      const port = parseInt(answer, 10);
      if (port >= PORT_RANGE.min && port <= PORT_RANGE.max && !RESERVED_PORTS.includes(port)) {
        resolve(port);
      } else {
        console.log('Invalid port. Please try again.');
        resolve(askForPort());
      }
    });
  });
};

const startServer = async () => {
  const port = await askForPort();

  const app = express();
  const server = http.createServer(app);
  const io = socketIo(server);

  app.use(express.json());

  const fetchAuctions = async (payload) => {
    const headers = 
    {
      'Content-Type': 'application/json',
      'Authorization': 'Basic ' + Buffer.from('u04948123:3918Milo').toString('base64')
    };

    try 
    {
      const response = await axios.post('https://wheatley.cs.up.ac.za/u04948123/api.php', payload, { headers });
      return response.data;
    } 
    catch (error) 
    {
      console.error('Error during fetchAuctions:', error);
      throw error;
    }
  };

  const generateAuctionId = () => {
    return crypto.randomBytes(5).toString('hex');
  };

  io.on('connection', (socket) => {
    console.log('Client connected:', socket.id);

    socket.on('login', (username) => {
      users[username] = socket.id;
      console.log(`User logged: ${username} with socket ID: ${socket.id}`);
    });

    socket.on('message', async (message) => {
      let parsedMessage;
      try {
        parsedMessage = JSON.parse(message);
        console.log('Received:', parsedMessage);
      } catch (error) {
        console.error('Invalid JSON:', error);
        socket.emit('message', JSON.stringify({ type: 'error', message: 'Invalid JSON format' }));
        return;
      }

      const { type, data } = parsedMessage;

      switch (type) 
      {
        case 'CreateAuctionFull':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            socket.emit('message' , JSON.stringify({ type: 'CreateAuctionFull', data: auctions }));
          } 
          catch (error) 
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
          break;
        case 'GetAuctionListings':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            socket.emit('message' , JSON.stringify({ type: 'GetAuctionListings', data: auctions }));
          } 
          catch (error) 
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
          break;
        case 'GetAuctionsFull':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            socket.emit('message' , JSON.stringify({ type: 'GetAuctionsFull', data: auctions }));
          } 
          catch (error) 
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
          break;
        case 'GetUserBids':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            socket.emit('message' , JSON.stringify({ type: 'GetUserBids', data: auctions }));
          } 
          catch (error) 
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
          break;
        case 'GetUserAuctions':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            socket.emit('message' , JSON.stringify({ type: 'GetUserAuctions', data: auctions }));
          } 
          catch (error)
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
          break;  
        case 'GetAuctionsOne':
            try {
              parsedMessage.type = "GetAuctionsFull"
              const auctions = await fetchAuctions(parsedMessage);
              socket.emit('message' , JSON.stringify({ type: 'GetAuctionsOne', data: auctions }));
            } catch (error) {
              console.error('Error fetching auctions:', error);
              socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
            }
            break;  
        case 'BidOnAuction':
          try 
          {
            const auctions = await fetchAuctions(parsedMessage);
            console.log(auctions);
            socket.emit('message' , JSON.stringify({ type: 'BidOnAuction', data: auctions }));
          } 
          catch (error) 
          {
            console.error('Error fetching auctions:', error);
            socket.emit('message', JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
          }
              break;  
        case 'otherAction':
          break;

        default:
          console.error('Unknown message type:', type);
          socket.emit('message', JSON.stringify({ type: 'error', message: 'Unknown message type' }));
          break;
      }
    });

    socket.on('disconnect', () => {
      console.log('Client disconnected:', socket.id);
      for (const [username, socketId] of Object.entries(users)) {
        if (socketId === socket.id) {
          delete users[username];
          console.log(`User ${username} removed`);
          break;
        }
      }
    });
  });

  const handleCommand = (command) => {
    const parts = command.trim().split(' ');
    const cmd = parts[0];
    const args = parts.slice(1);

    switch (cmd) {
      case 'KILL':
        if (args.length > 0) {
          const username = args[0];
          const socketId = users[username];
          if (socketId) {
            io.sockets.sockets.get(socketId)?.disconnect(true);
            delete users[username];
            console.log(`Disconnected user ${username}`);
          } else {
            console.log('User not found');
          }
        } else {
          console.log('Please provide a username');
        }
        break;

      case 'LIST':
        console.log('Connected users:');
        for (const [username, socketId] of Object.entries(users)) {
          console.log(`Username: ${username}, Socket ID: ${socketId}`);
        }
        break;

      case 'QUIT':
        io.emit('message', JSON.stringify({ type: 'server', message: 'Server is going offline' }));
        setTimeout(() => {
          io.close(() => {
            console.log('Server closed');
            process.exit(0);
          });
        }, 1000);
        break;

      case 'AUCTIONS':
        console.log('Auctions in session:');
        for (const [auctionId, auction] of Object.entries(auctions)) {
          console.log(`Auction ID: ${auctionId}, Auction Name: ${auction.name}, Participants: ${auction.participants.join(', ')}`);
        }
        break;

      default:
        console.log('Unknown command');
        break;
    }
  };

  rl.on('line', handleCommand);

  server.listen(port, () => {
    console.log(`Server is running on port ${port}`);
  });
};

startServer();
