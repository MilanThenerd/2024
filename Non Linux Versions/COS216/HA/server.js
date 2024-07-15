const WebSocket = require('ws');
const axios = require('axios');

const wss = new WebSocket.Server({ port: 8080 });

wss.on('connection', function connection(ws)
{
    console.log('Client connected');

    ws.on('message', async function incoming(message) {
        
    
        let parsedMessage; 
        try {
            parsedMessage = JSON.parse(message);
            console.log('Received:', parsedMessage);
        } catch (error) 
        {
            console.error('Invalid JSON:', error);
            if (ws.readyState === ws.OPEN) {
                ws.send(JSON.stringify({ type: 'error', message: 'Invalid JSON format' }));
            }
            return;
        }
    
        const { type, data } = parsedMessage;
    
        switch (type) {
            case 'GetAuctionsFull':
                try 
                {
                    const auctions = await fetchAuctions();
                    if (ws.readyState === ws.OPEN) 
                    {
                        ws.send(JSON.stringify({ type: 'auctions', data: auctions }));
                    }
                } catch (error) 
                {
                    console.error('Error fetching auctions:', error);
                    if (ws.readyState === ws.OPEN) 
                    {
                        ws.send(JSON.stringify({ type: 'error', message: 'Error fetching auctions' }));
                    }
                }
                break;
    
            // Add more cases here for different types of messages
            case 'otherAction':
                // Perform some other action
                break;
    
            default:
                console.error('Unknown message type:', type);
                if (ws.readyState === ws.OPEN) {
                    ws.send(JSON.stringify({ type: 'error', message: 'Unknown message type' }));
                }
                break;
        }
    });
    
    

    ws.on('close', function () {
        console.log('Client disconnected');
    });
});

async function fetchAuctions() {
    const payload = 
    {
        type: "GetAuctionsFull"
    };

    const headers = {
        'Content-Type': 'application/json',
        // 'Authorization': 'Basic ' + Buffer.from('u04948123:3918Milo').toString('base64')
    };

    try {
        const response = await axios.post('http://localhost:3000/COS216/HA/api.php', payload, {
            headers: headers
        });
        return response.data;
    } catch (error) {
        console.error('Error during fetchListings:', error);
        throw error;
    }
}
