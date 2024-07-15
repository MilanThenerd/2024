const socket = io('http://localhost:8080');

const requestDataAuctions= {
    type: 'GetAuctionsFull',
    limit: 30,
    sort: 'id',
    order: 'ASC',
    title: '',
    location: '',
    price_min: '0',
    price_max: '100000000',
    bedrooms: '2',
    bathrooms: '2',
    parking_spaces: '2',
    amenities: '',
    type: 'sale',
};

socket.on('connect', () => {
    console.log('Connected to Socket.IO Server');
});

socket.on('message', (data) => {
    console.log(data);
});

socket.on('disconnect', () => {
    console.log('Disconnected from Socket.IO Server');
});


function load_auctions() {
    socket.send(JSON.stringify(requestDataAuctions));
}
