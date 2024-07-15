//Milan Kruger
//u04948123

const api = 'c4afad33b0c3275bc75e563c1ea7ea05';
const url = 'https://wheatley.cs.up.ac.za/api/';
const studentnum = 'u04948123';

const requestDataListings = {
    studentnum: studentnum,
    apikey: api,
    type: 'GetAllListings',
    limit: 30,
    sort: 'id',
    order: 'ASC',
    return: '*',
    search: {
        title: '',
        location: '',
        price_min: '0',
        price_max: '100000000',
        bedrooms: '2',
        bathrooms: '2',
        parking_spaces: '2',
        amenities: '',
        type: 'sale',
    },
    search_on: 0,
};
async function fetchListings() 
{
    return new Promise((resolve) => 
    {
        let xml = new XMLHttpRequest();
        xml.open('POST', url, true);
        xml.setRequestHeader('Content-Type', 'application/json');

        xml.onreadystatechange = function () 
        {
            if (xml.readyState === 4 && xml.status === 200) 
            {
                let response = JSON.parse(xml.responseText);
                resolve(response);
            }
        };
        xml.send(JSON.stringify(requestDataListings));
    });
}
async function fetchImages(type) {
    return new Promise((resolve, reject) => 
    {
        const api = 'c4afad33b0c3275bc75e563c1ea7ea05';
        const url = 'https://wheatley.cs.up.ac.za/api/getimage';

        var queryString;
        var requestUrl;
       
        if(!isNaN(type))
        {
            queryString = `listing_id=${type}`;
            requestUrl = `${url}?${queryString}`;
        }
        else
        {
            queryString = `agency=${type}`;
            requestUrl = `${url}?${queryString}`;
        }
        
        let xml = new XMLHttpRequest();
        xml.open('GET', requestUrl, true);

        xml.onreadystatechange = function () {
            if (xml.readyState === 4) {
                if (xml.status === 200) {
                    let response = JSON.parse(xml.responseText);
                    resolve(response);
                } else {
                    reject('Request failed with status: ' + xml.status);
                }
            }
        };

        xml.send();
    });
}
async function load_listings() 
{
    document.getElementById('loading-container').style.display = 'block';
    let listings = await fetchListings();
    listings = listings.data;
    var list = document.getElementById('house-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function(li) {
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }

    if(listings.length === 0) {
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
    
    for (const item of listings) {
        var listItem = document.createElement('li');
        
        let images = await fetchImages(item.id);
        var anchor = document.createElement('a');
        anchor.href = 'view.html?id=' + item.id;
        anchor.classList.add('view-button');
    
        var image = document.createElement('img');
        image.classList.add('house-thumbnail');
        image.src = images.data[0];
        image.alt = "House";
    
        anchor.appendChild(image);

        var houseInteractButtonsDiv = document.createElement('div');
        houseInteractButtonsDiv.id = item.id;
        houseInteractButtonsDiv.classList.add('house-interact-buttons');
        houseInteractButtonsDiv.id = "interactButton-"+item.id;
        var heartButton = document.createElement('button');
        heartButton.classList.add('fav-button');
        var heartIcon = document.createElement('i');
        heartIcon.classList.add('fa', 'fa-heart');
        heartButton.appendChild(heartIcon);

        const storedValue = localStorage.getItem(item.id);

        if (storedValue && Object.keys(storedValue).length > 0) {
            heartButton.style.color = "RED";
        } else {
            heartButton.style.color = "WHITE";
        }
        


        var contactButton = document.createElement('button');
        contactButton.classList.add('contact-button');
        var phoneIcon = document.createElement('i');
        phoneIcon.classList.add('fa', 'fa-phone');
        contactButton.appendChild(phoneIcon);




        contactButton.addEventListener('click', function() {
            window.location.href = item.url;
        });

        heartButton.addEventListener('click', async function() {
            try {
                const result = await write_to_fav(item);
                if (result === false) {
                    heartButton.style.color = 'WHITE';
                } else {
                    heartButton.style.color = "RED";
                }
                load_listings();
            } catch (error) {
                console.error('Error occurred:', error);

            }
        });


        houseInteractButtonsDiv.appendChild(heartButton);
        houseInteractButtonsDiv.appendChild(contactButton);
        var Title = document.createElement('h1');
        var Price = document.createElement('div');
        var Location = document.createElement('div');
        var Bedrooms = document.createElement('div');
        var Bathrooms = document.createElement('div');
    
        Title.textContent = item.title;
        if(requestDataListings.search.type === 'sale') {
            Price.textContent = "Price: R" + item.price;
        } else {
            Price.textContent = "Price: R" + item.price + " per month";
        }
        Location.textContent = "Location: " + item.location;
        Bedrooms.textContent = "Bedrooms: " + item.bedrooms;
        Bathrooms.textContent = "Bathrooms " + item.bathrooms;
    
        listItem.appendChild(anchor);
        listItem.appendChild(Title);
        listItem.appendChild(Price);
        listItem.appendChild(Location);
        listItem.appendChild(Bedrooms);
        listItem.appendChild(Bathrooms);
        listItem.appendChild(houseInteractButtonsDiv);
        list.appendChild(listItem);
    }
    document.getElementById('loading-container').style.display = 'none';
}
async function load_listings_title()
{
    requestDataListings.sort = 'title';
    load_listings();
}
async function load_listings_loc()
{
    requestDataListings.sort = 'location';
    load_listings();
}
async function load_listings_price()
{
    requestDataListings.sort = 'price';
    load_listings();
}
async function load_listings_bed()
{
    requestDataListings.sort = 'bedrooms';
    load_listings();
}
async function load_listings_bath()
{
    requestDataListings.sort = 'bathrooms';
    load_listings();
}
async function load_listings_park()
{
    requestDataListings.sort = 'parking_spaces';
    load_listings();
}
async function load_listings_buy()
{
    requestDataListings.search.type = 'sale';
    load_listings();
}
async function load_listings_rent()
{
    requestDataListings.search.type = 'rent';
    load_listings();
}
async function load_listings_bedrooms()
{
    const bed = document.getElementById('bedrooms').value;
    requestDataListings.search.bedrooms = bed;
    load_listings();
}
async function load_listings_bathrooms()
{
    const bath = document.getElementById('bathrooms').value;
    requestDataListings.search.bathrooms = bath;
    load_listings();
}
async function load_listings_max()
{
    const max = document.getElementById('price-max').value;
    requestDataListings.search.price_max = max;
    load_listings();
}
async function load_listings_min()
{
    const min = document.getElementById('price-min').value;
    requestDataListings.search.price_min = min;
    load_listings();
}
async function load_listings_search()
{
    const searchText = document.getElementById('search-input');
    const searchValue = searchText.value;
    requestDataListings.search.title = searchValue;
    load_listings(searchValue);
}
async function load_listings_parkingspaces()
{
    const spaces = parseInt(document.getElementById('parkingspaces').value);
    requestDataListings.search.parking_spaces = spaces ;
    load_listings();
}
async function load_listings_limit()
{
    let limittext = parseInt(document.getElementById('limits').value);
    if(limittext >= 500)
    {
        limittext = 500;
    }
    if(limittext <= 1)
    {
        limittext = 1;
    }
    requestDataListings.limit = limittext;
    
    load_listings();
}
async function load_listings_asc_desc()
{
    const icon = document.getElementById('asc-desc-icon');
    if(icon.classList.contains("fa-angle-down"))
    {
        icon.classList.remove("fa-angle-down");
        icon.classList.add("fa-angle-up");
        requestDataListings.order = "DESC";
    }
    else {
        icon.classList.remove("fa-angle-up");
        icon.classList.add("fa-angle-down");
        requestDataListings.order = "ASC";
    }
    load_listings();
}
async function load_listings_reset_filters()
{
    let newsearch = {
        type: requestDataListings.search.type,
    }
    requestDataListings.search = newsearch;
    load_listings();
}

const requestDataAgents = {
    studentnum: studentnum,
    apikey: api,
    type: 'GetAllAgents',
    limit: 10,
};
async function fetchAgents() 
{
    return new Promise((resolve) => 
    {
        let xml = new XMLHttpRequest();
        xml.open('POST', url, true);
        xml.setRequestHeader('Content-Type', 'application/json');

        xml.onreadystatechange = function () {
            if (xml.readyState === 4 && xml.status === 200) 
            {
                let response = JSON.parse(xml.responseText);
                resolve(response);
            }
        };
        xml.send(JSON.stringify(requestDataAgents));
    });
}
async function load_agents(l)
{
    document.getElementById('loading-container').style.display = 'block';
    let agents = await fetchAgents();
    var list = document.getElementById('agent-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function(li) {
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }
    agents.data.forEach(async function(item) {
        var listItem = document.createElement('li');
        
        let images = await fetchImages(item.name);
        var anchor = document.createElement('a');
        anchor.href = item.url;
        anchor.classList.add('view-button');

        var image = document.createElement('img');
        image.classList.add('house-thumbnail');
        image.src = images.data;
        image.alt = "House";

        anchor.appendChild(image);
        
        var Name = document.createElement('h1');
        var Description = document.createElement('div');


        Name.textContent = item.name;
        Description.textContent = "Description: "+item.description;


        listItem.appendChild(anchor);
        listItem.appendChild(Name);
        listItem.appendChild(Description);
        list.appendChild(listItem);
      });
      document.getElementById('loading-container').style.display = 'none';
}
async function load_agents_limit()
{
    const limittext = parseInt(document.getElementById('limits').value);
    requestDataAgents.limit = limittext;
    load_agents();
}

async function load_view()
{
    document.getElementById('loading-container').style.display = 'block';
    var urlParams = new URLSearchParams(window.location.search);

    var itemId = urlParams.get('id');
    requestDataListings.search = {
        id: itemId,
    }

    let item = await fetchListings();
    let itemImages = await fetchImages(itemId);
    item = item.data;
    itemImages = itemImages.data;

    const carousel = document.querySelector('.carousel');
    const slides = document.querySelector('.slides');

    function createImage(src) {
        const img = document.createElement('img');
        img.src = src;
        img.alt = 'Image';
        return img;
    }

    if (itemImages.length > 0) 
    {
        itemImages.forEach(imageUrl => {
            const img = createImage(imageUrl);
            slides.appendChild(img);
        });

        const images = document.querySelectorAll('.slides img');

        const prevBtn = document.createElement('button');
        prevBtn.textContent = '<';
        const nextBtn = document.createElement('button');
        prevBtn.classList.add("prev");
        nextBtn.textContent = '>';
        nextBtn.classList.add("next");
        carousel.appendChild(prevBtn);
        carousel.appendChild(nextBtn);

        let currentIndex = 0;

        let length = images.length-2;
        function showSlide(index) {
            images.forEach(image => {
                image.style.display = 'none';
            });
            images[index].style.display = 'block';
        }

        function prevSlide() 
        {
            currentIndex--;
            if(currentIndex < 0)
            {
                currentIndex = length;
            }
            showSlide(currentIndex);
        }

        function nextSlide() 
        {
            currentIndex++;
            if (currentIndex > length) {

                currentIndex = 0;
            }
            showSlide(currentIndex);
        }
        
        showSlide(currentIndex);

        prevBtn.addEventListener('click', prevSlide);
        nextBtn.addEventListener('click', nextSlide);
    } else 
    {
        console.error('No images found for the item.');
    }

    const header = document.querySelector(".listing-details h1");
    header.textContent = item[0].title;


    const info = document.querySelector(".listing-details .listing-info");

    const description = document.createElement('div');
    let text = item[0].description.replace(/,/g, '');
    description.textContent = text;
    description.style.fontSize = '30px';


    const price = document.createElement('div');
    price.textContent = "Price: R"+item[0].price;

    const location = document.createElement('div');
    location.textContent = "Location: " + item[0].location;

    const bedrooms = document.createElement('div');
    bedrooms.textContent = "Bedrooms: "+ item[0].bedrooms;

    const bathrooms = document.createElement('div');
    bathrooms.textContent = "Bedrooms: "+ item[0].bathrooms;


    const amenities = document.createElement('div');
    text = item[0].amenities.replace(/,/g, '');
    if(text.length === 0)
    {
        text = "None";
    }
    amenities.textContent = "Amenities: " + text;
    amenities.style.fontSize = '40px';



    const call = document.createElement('button');
    const callbutton = document.createElement('i');

    callbutton.classList.add('call-button');

        
    callbutton.classList.add("fa", "fa-phone"); 

    call.style.fontSize = '50px';
    call.style.background = 'transparent';
    call.style.border = 'none';

    call.addEventListener('click', function() {

        window.location.href = item[0].url;
    });

    
    call.appendChild(callbutton);
    info.appendChild(call);
    info.appendChild(price);
    info.appendChild(location);
    info.appendChild(bedrooms);
    info.appendChild(bathrooms);
    info.appendChild(amenities);
    info.appendChild(description);

    


    document.getElementById('loading-container').style.display = 'none';
    
}

async function write_to_fav(item)
{
    try {
        const existingData = localStorage.getItem(item.id);
        let parsedData = {};
        if (existingData) {
            parsedData = JSON.parse(existingData);
            if (item.id in parsedData)
            {
                localStorage.removeItem(item.id);
                return false;
            }
        } 
        parsedData[item.id] = item;
        localStorage.setItem(item.id, JSON.stringify(parsedData));
        return true;
    } catch (error) {
        console.error('Error occurred while writing to localStorage:', error);
        return false;
    }
}
function listAllItemsFromLocalStorage() {
    const allItems = [];
    for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i);
        const value = localStorage.getItem(key);
        let parsedValue;
        try {
            parsedValue = JSON.parse(value);
        } catch (error) {
            parsedValue = null;
        }
        allItems.push({ key, value: parsedValue });
    }

    let items =[];

    allItems.forEach(async function(item){
        let key = item.key;
        if(key != 'debug')
        {
            let value = item.value[key];
            if (value !== undefined && value !== null) 
            {
                items.push(value);
            }
        }
    });
    return items;
}
const favouritesData = {
    limit: 10,
    sort: 'id',
    order: 'ASC',
    return: '*',
    search: {
        title: '',
        location: '',
        price_min: '0',
        price_max: '100000000',
        bedrooms: '2',
        bathrooms: '2',
        parking_spaces: '2',
        amenities: '',
        type: 'sale',
    },
}
function getFilteredArray()
{
    let array = listAllItemsFromLocalStorage();
    let sortedArray = [];

    array.forEach(element => {

        if(favouritesData.search.title === '')
        {
            if (
                element.bedrooms === parseInt(favouritesData.search.bedrooms) &&
                element.bathrooms === parseInt(favouritesData.search.bathrooms) &&
                parseFloat(element.price) >= parseFloat(favouritesData.search.price_min) &&
                parseFloat(element.price) <= parseFloat(favouritesData.search.price_max) &&
                element.type === favouritesData.search.type
            ) 
            {
                sortedArray.push(element);
            }
        }
        else if (element.title.toLowerCase().includes(favouritesData.search.title.toLowerCase()) &&
            element.bedrooms === parseInt(favouritesData.search.bedrooms) &&
            element.bathrooms === parseInt(favouritesData.search.bathrooms) &&
            parseFloat(element.price) >= parseFloat(favouritesData.search.price_min) &&
            parseFloat(element.price) <= parseFloat(favouritesData.search.price_max) &&
            element.type === favouritesData.search.type
        ) 
        {
            sortedArray.push(element);
        }
    });
    return sortedArray;
}
async function load_favourites()
{
    document.getElementById('loading-container').style.display = 'block';
    
    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'id');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return parseFloat(a.id) - parseFloat(b.id);
        } else {
            return parseFloat(b.id) - parseFloat(a.id);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_title()
{
    document.getElementById('loading-container').style.display = 'block';

    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'title');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);


    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return a.title.localeCompare(b.title);
        } else {
            return b.title.localeCompare(a.title);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_location()
{
    document.getElementById('loading-container').style.display = 'block';

    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'loc');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return a.location.localeCompare(b.location);
        } else {
            return b.location.localeCompare(a.location);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_price() {
    document.getElementById('loading-container').style.display = 'block';

    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'price');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return parseFloat(a.price) - parseFloat(b.price);
        } else {
            return parseFloat(b.price) - parseFloat(a.price);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_bed() {
    document.getElementById('loading-container').style.display = 'block';

    
    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'bed');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return parseFloat(a.bedrooms) - parseFloat(b.bedrooms);
        } else {
            return parseFloat(b.bedrooms) - parseFloat(a.bedrooms);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_bath() {
    document.getElementById('loading-container').style.display = 'block';

    
    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'bath');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return parseFloat(a.bathroom) - parseFloat(b.bathroom);
        } else {
            return parseFloat(b.bathroom) - parseFloat(a.bathroom);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_park() {
    document.getElementById('loading-container').style.display = 'block';

    
    const urlParams = new URLSearchParams(window.location.search);
    urlParams.set('sort', 'park');
    const newURL = window.location.pathname + '?' + urlParams.toString();
    history.pushState({}, '', newURL);

    let sortedArray = getFilteredArray();
    sortedArray.sort((a, b) => {
        if (favouritesData.order === 'ASC') {
            return parseFloat(a.parking_spaces) - parseFloat(b.parking_spaces);
        } else {
            return parseFloat(b.parking_spaces) - parseFloat(a.parking_spaces);
        }
    });
    let counter = 0;
    sortedArray = sortedArray.filter((item) => {
        counter++;
        return counter <= favouritesData.limit;
    });
    load_favourites_default(sortedArray);
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_default(listing) 
{
    let listings = listing;
    var list = document.getElementById('house-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function (li) {
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }
    if (listings.length === 0) {
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

    for (const item of listings) {
        var listItem = document.createElement('li');

        let images = await fetchImages(item.id);
        var anchor = document.createElement('a');
        anchor.href = 'view.html?id=' + item.id;
        anchor.classList.add('view-button');

        var image = document.createElement('img');
        image.classList.add('house-thumbnail');
        image.src = images.data[0];
        image.alt = "House";

        anchor.appendChild(image);

        var houseInteractButtonsDiv = document.createElement('div');
        houseInteractButtonsDiv.id = item.id;
        houseInteractButtonsDiv.classList.add('house-interact-buttons');
        var XButton = document.createElement('button');
        XButton.classList.add('add-button');
        var XIcon = document.createElement('i');
        XIcon.classList.add('fa', 'fa-close');
        XButton.appendChild(XIcon);

        XButton.addEventListener('click', function () {
            write_to_fav(item);
            load_favourites();
        });


        var contactButton = document.createElement('button');
        contactButton.classList.add('contact-button');
        var phoneIcon = document.createElement('i');
        phoneIcon.classList.add('fa', 'fa-phone');
        contactButton.appendChild(phoneIcon);
        contactButton.addEventListener('click', function () {
            window.location.href = item.url;
        });

        houseInteractButtonsDiv.appendChild(XButton);
        houseInteractButtonsDiv.appendChild(contactButton);
        var Title = document.createElement('h1');
        var Price = document.createElement('div');
        var Location = document.createElement('div');
        var Bedrooms = document.createElement('div');
        var Bathrooms = document.createElement('div');

        Title.textContent = item.title;
        if (requestDataListings.search.type === 'sale') {
            Price.textContent = "Price: R" + item.price;
        } else {
            Price.textContent = "Price: R" + item.price + " per month";
        }
        Location.textContent = "Location: " + item.location;
        Bedrooms.textContent = "Bedrooms: " + item.bedrooms;
        Bathrooms.textContent = "Bathrooms " + item.bathrooms;

        listItem.appendChild(anchor);
        listItem.appendChild(Title);
        listItem.appendChild(Price);
        listItem.appendChild(Location);
        listItem.appendChild(Bedrooms);
        listItem.appendChild(Bathrooms);
        listItem.appendChild(houseInteractButtonsDiv);
        await list.appendChild(listItem);
    }
}
async function load_fav_url()
{
    const urlParams = new URLSearchParams(window.location.search);
    const parameters = {};
    for (const [key, value] of urlParams.entries()) {
        parameters[key] = value;
    }
    if(parameters.sort === 'id')
    {
        load_favourites();
    }
    if(parameters.sort === 'title')
    {
        load_favourites_title();
    }
    if(parameters.sort === 'location')
    {
        load_favourites_location();
    }
    if(parameters.sort === 'price')
    {
        load_favourites_price();
    }
    if(parameters.sort === 'bed')
    {
        load_favourites_bed();
    }
    if(parameters.sort === 'bath')
    {
        load_favourites_bath();
    }
    if(parameters.sort === 'park')
    {
        load_favourites_park();
    }
}
async function load_favourites_buy()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.type = 'sale'
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_rent()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.type = 'rent'
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_min()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.price_min = document.getElementById('price-min').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_max()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.price_max = document.getElementById('price-max').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_bedrooms()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.bedrooms = document.getElementById('bedrooms').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_bathrooms()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.bathrooms = document.getElementById('bathrooms').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_parkingspaces()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.parking_spaces = document.getElementById('parkingspaces').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_limit()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.limit = parseInt(document.getElementById('limits').value);
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_search()
{
    document.getElementById('loading-container').style.display = 'block';
    favouritesData.search.title = document.getElementById('search-input').value;
    load_fav_url();
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_reset_filters()
{
    document.getElementById('loading-container').style.display = 'block';
    load_favourites_default_no_filter(listAllItemsFromLocalStorage());
    document.getElementById('loading-container').style.display = 'none';
}
async function load_favourites_default_no_filter(listing) 
{
    let listings = listing;
    var list = document.getElementById('house-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function (li) {
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }
    if (listings.length === 0) {
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

    for (const item of listings) {
        var listItem = document.createElement('li');

        let images = await fetchImages(item.id);
        var anchor = document.createElement('a');
        anchor.href = 'view.html?id=' + item.id;
        anchor.classList.add('view-button');

        var image = document.createElement('img');
        image.classList.add('house-thumbnail');
        image.src = images.data[0];
        image.alt = "House";

        anchor.appendChild(image);

        var houseInteractButtonsDiv = document.createElement('div');
        houseInteractButtonsDiv.id = item.id;
        houseInteractButtonsDiv.classList.add('house-interact-buttons');
        var XButton = document.createElement('button');
        XButton.classList.add('add-button');
        var XIcon = document.createElement('i');
        XIcon.classList.add('fa', 'fa-close');
        XButton.appendChild(XIcon);

        XButton.addEventListener('click', function () {
            write_to_fav(item);
            load_favourites_default_no_filter(listAllItemsFromLocalStorage());
        });


        var contactButton = document.createElement('button');
        contactButton.classList.add('contact-button');
        var phoneIcon = document.createElement('i');
        phoneIcon.classList.add('fa', 'fa-phone');
        contactButton.appendChild(phoneIcon);
        contactButton.addEventListener('click', function () {
            window.location.href = item.url;
        });

        houseInteractButtonsDiv.appendChild(XButton);
        houseInteractButtonsDiv.appendChild(contactButton);
        var Title = document.createElement('h1');
        var Price = document.createElement('div');
        var Location = document.createElement('div');
        var Bedrooms = document.createElement('div');
        var Bathrooms = document.createElement('div');

        Title.textContent = item.title;
        if (requestDataListings.search.type === 'sale') {
            Price.textContent = "Price: R" + item.price;
        } else {
            Price.textContent = "Price: R" + item.price + " per month";
        }
        Location.textContent = "Location: " + item.location;
        Bedrooms.textContent = "Bedrooms: " + item.bedrooms;
        Bathrooms.textContent = "Bathrooms " + item.bathrooms;

        listItem.appendChild(anchor);
        listItem.appendChild(Title);
        listItem.appendChild(Price);
        listItem.appendChild(Location);
        listItem.appendChild(Bedrooms);
        listItem.appendChild(Bathrooms);
        listItem.appendChild(houseInteractButtonsDiv);
        await list.appendChild(listItem);
    }
}
