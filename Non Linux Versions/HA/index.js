let socket;
let sort;
let order;
let type;

setInterval(() => {
    location.reload();
}, 300000);

function initializeSocket() {
    socket = io('http://localhost:8080', {
        transports: ['websocket', 'polling']
    });

    socket.on('connect', () => {
        var item = localStorage.getItem('user_id');
        socket.emit('login', item);
    });

    socket.on('message', (message) => {
        handleServerMessage(JSON.parse(message));
    });

    socket.on('disconnect', () => {
        console.log('Disconnected from WebSocket server');
    });
}

function handleServerMessage(message) {

    let type = message.type;
    let data = message.data;
    switch (type) {
        case 'CreateAuctionFull':
            if(data.status !== 'success')
            {
                alert(data.message);
            }
            console.log(message);
            break;
        case 'GetAuctionsFull':
            populate_auctions(data.data);
            break;
        case 'GetUserBids':
            populate_auctions(data.data);
            break;
        case 'GetUserAuctions':
            populate_auctions(data.data);
            break;
        case 'GetAuctionsOne':
            populate_view(data.data);
            break;
        case 'BidOnAuction':
            if(data.status !== "success")
            {
                alert(data.message);
            }
            else
            {
                location.reload();
            }
            break;
        default:
            console.log('Unknown message type:', type);
            break;
    }
}

async function populate_auctions(data) {
    document.getElementById('loading-container').style.display = 'block';
    let listings;
    if (data !== null && data !== undefined) {
        listings = data;
    }
    var list = document.getElementById('house-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function(li) {
        if (li.querySelector('button.plus-button')) {
        }
        else
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }
    if (listings === null || listings === undefined || listings.length === 0) {
        var message = document.createElement('div');
        message.classList.add('empty-message');
        message.style.color = '#EDF5E1';
        message.style.background = '#05386B';
        message.style.fontSize = '50px';
        message.style.marginLeft = '5vw';
        message.style.padding = '1vw';
        message.style.borderRadius = '5px';
        message.style.width = '30vw';
        message.textContent = 'It appears this search is empty, try other options :D';
        list.appendChild(message);
    }
    else
    for (const item of listings) {
        var listItem = document.createElement('li');
        
        var anchor = document.createElement('a');
        anchor.href = 'view.html?id=' + item.auction_id;
        anchor.classList.add('view-button');
    
        var image = document.createElement('img');
        image.classList.add('house-thumbnail');
        image.src = item.image;
        image.alt = "House";
    
        anchor.appendChild(image);

        var Title = document.createElement('h1');
        var Price = document.createElement('div');
        var State = document.createElement('div');
        var Location = document.createElement('div');
        var Bedrooms = document.createElement('div');
        var Bathrooms = document.createElement('div');
    
        Title.textContent = item.title;
        if(item.highest_bid !== null)
        {
            Price.textContent = "Current Bid: R" + item.highest_bid;
        }
        else
        {
            Price.textContent = "Current Bid: None";
        }
        State.textContent = "State: " + item.state;
        Location.textContent = "Location: " + item.location;
        Bedrooms.textContent = "Bedrooms: " + item.bedrooms;
        Bathrooms.textContent = "Bathrooms: " + item.bathrooms;
    
        listItem.appendChild(anchor);
        listItem.appendChild(Title);
        listItem.appendChild(Price);
        listItem.appendChild(State);
        listItem.appendChild(Location);
        listItem.appendChild(Bedrooms);
        listItem.appendChild(Bathrooms);
        list.appendChild(listItem);
    }
    document.getElementById('loading-container').style.display = 'none';
}

async function load_auctions() {

    let user_id = localStorage.getItem('user_id');
    var currentUrl = window.location.href;
    let requestDataAuctions= {};
    if(currentUrl.includes("userauctions.html")) {
        type = 'GetUserAuctions';
    }
    else if(currentUrl.includes("bids.html")) {
        type = 'GetUserBids';
    }
    else if(currentUrl.includes("auctions.html")) {
        type = 'GetAuctionsFull';
    }
    else if(currentUrl.includes("view.html"))
    {
        type = 'GetAuctionsOne';
    }

    if(type !== "GetAuctionsOne")
    {
        requestDataAuctions = get_attributes(type);
    }
    else 
    {
        requestDataAuctions["type"] = type;
    }
    if(type === "GetUserBids" || type === "GetUserAuctions") {
        requestDataAuctions["user_id"] = user_id;
    }
    else if(type === "GetAuctionsOne")
    {
        const urlParams = new URLSearchParams(window.location.search);
        const id = urlParams.get('id');
        requestDataAuctions["auction_id"] = id;
    }
    socket.emit('message', JSON.stringify(requestDataAuctions));
}

async function load_auctions_title()
{
    sort = 'title';
    load_auctions();
}

async function load_auctions_loc()
{
    sort = 'location';
    load_auctions();
}

async function load_auctions_price()
{
    sort = 'highest_bid';
    load_auctions();
}

async function load_auctions_bed()
{
    sort = 'bedrooms';
    load_auctions();
}

async function load_auctions_bath()
{
    sort = 'bathrooms';
    load_auctions();
}

async function load_auctions_park()
{
    sort = 'parking_spaces';
    load_auctions();
}

async function load_auctions_asc_desc()
{
    const icon = document.getElementById('asc-desc-icon');
    if(icon.classList.contains("fa-angle-down"))
    {
        icon.classList.remove("fa-angle-down");
        icon.classList.add("fa-angle-up");
        order = 'DESC';
    }
    else {
        icon.classList.remove("fa-angle-up");
        icon.classList.add("fa-angle-down");
        order = 'ASC';
    }
    load_auctions();
}

function get_attributes(type) {
    
    var price_min_str = document.getElementById("price-min").value.trim();
    var price_max_str = document.getElementById("price-max").value.trim();
    var bedrooms = document.getElementById("bedrooms").value.trim();
    var bathrooms = document.getElementById("bathrooms").value.trim();
    var parking_spaces = document.getElementById("parkingspaces").value.trim();
    var limit = document.getElementById("limits").value.trim();
    var search = document.getElementById("search-input").value.trim();

    var price_min = price_min_str !== "" ? parseFloat(price_min_str) : null;
    var price_max = price_max_str !== "" ? parseFloat(price_max_str) : null;

    var data = {
        "type": type,
        "sort" : sort,
        "order" : order
    };
    if (search !== "") {
        data["title"] = search;
        data["location"] = search;
        data["name"] = search;
        data["amenities"] = search;
    }
    if (price_min !== null) {
        data["min_price"] = price_min;
    }
    if (price_max !== null) {
        data["max_price"] = price_max;
    }
    if (bedrooms !== "") {
        data["bedrooms"] = bedrooms;
    }
    if (bathrooms !== "") {
        data["bathrooms"] = bathrooms;
    }
    if (parking_spaces !== "") {
        data["parking_spaces"] = parking_spaces;
    }
    if (limit !== "") {
        data["limit"] = limit;
    }

    return data;
}

function setTheme() {
    var element = document.body;
    element.classList.toggle("dark-mode");
}

function logout()
{
    localStorage.clear('user_id');
    window.location.href = "login.html";
}

async function load_view()
{
    load_auctions();
}

async function populate_view(item)
{
    document.getElementById('loading-container').style.display = 'block';

    item = item[0];

    const img = document.createElement('img');
    img.src = item.image;
    img.alt = 'Image';

    const header = document.querySelector(".listing-details h1");
    header.textContent = item.title;


    const info = document.querySelector(".listing-details .listing-info");

    const description = document.createElement('div');
    let text = item.description.replace(/,/g, '');
    description.textContent = text;
    description.style.fontSize = '30px';


    const price = document.createElement('div');
    price.textContent = "Bid: R"+item.highest_bid;

    const location = document.createElement('div');
    location.textContent = "Location: " + item.location;

    const bedrooms = document.createElement('div');
    bedrooms.textContent = "Bedrooms: "+ item.bedrooms;

    const bathrooms = document.createElement('div');
    bathrooms.textContent = "Bedrooms: "+ item.bathrooms;

    const state = document.createElement('div');
    state.textContent = "State: " + item.state;
    const amenities = document.createElement('div');
    text = item.amenities.replace(/,/g, '');
    if(text.length === 0)
    {
        text = "None";
    }
    amenities.textContent = "Amenities: " + text;
    amenities.style.fontSize = '40px';
    

    const numberField = document.createElement('input');
    numberField.setAttribute('type', 'number');
    numberField.setAttribute('placeholder', 'Enter a number');
    numberField.style.fontSize = '40px';

    const button = document.createElement('button');
    button.textContent = 'Bid';
    button.setAttribute('type', 'button');
    button.addEventListener('click', () => 
        {
            const urlParams = new URLSearchParams(window.location.search);
            const id = urlParams.get('id');
            const user_id = localStorage.getItem('user_id');
            let payload = {
                "type" : "BidOnAuction",
                "auction_id" : id,
                "user_id" : user_id,
                "bid_amount" : numberField.value,
            }
            socket.emit('message', JSON.stringify(payload));

    });


    info.append(img);
    info.appendChild(price);
    info.appendChild(state);
    info.appendChild(location);
    info.appendChild(bedrooms);
    info.appendChild(bathrooms);
    info.appendChild(amenities);
    info.appendChild(description);
    info.appendChild(numberField);
    info.appendChild(button);

    


    document.getElementById('loading-container').style.display = 'none';
    
}

async function create_auction(data)
{
    socket.emit('message' , JSON.stringify(data));
}
