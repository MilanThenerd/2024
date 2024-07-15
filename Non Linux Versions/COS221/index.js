async function populate_Media(data)
{
    document.getElementById('loading-container').style.display = 'block';
    let movies;
    if (data !== null && data !== undefined) {
        movies = data;
    }
    var list = document.getElementById('movie-list');
    var elements = list.querySelectorAll('li');
    elements.forEach(function(li) 
    {
        li.parentNode.removeChild(li);
    });
    var existingMessage = list.querySelector('.empty-message');
    if (existingMessage) {
        list.removeChild(existingMessage);
    }
    if (movies === null || movies === undefined || movies.length === 0) {
        var message = document.createElement('div');
        message.classList.add('empty-message');
        message.style.color = '#EDF5E1';
        message.style.background = '#272727';
        message.style.fontSize = '50px';
        message.style.marginLeft = '5vw';
        message.style.padding = '1vw';
        message.style.borderRadius = '5px';
        message.style.width = '30vw';
        message.textContent = 'It appears this search is empty, try other options :D';
        list.appendChild(message);
    }
    else
    for (const item of movies) {
        var listItem = document.createElement('li');
        
        var anchor = document.createElement('a');
        if(item.Season !== undefined && item.Season !== null)
        {
            anchor.href = 'view.html?id=' + item.MediaID + "&type=" + "Show";
        }
        else
        {
            anchor.href = 'view.html?id=' + item.MediaID + "&type=" + "Movie";
        }
        anchor.classList.add('view-button');
    
        var image = document.createElement('img');
        image.src = item.URL;
        image.alt = "Image";
    
        anchor.appendChild(image);

        var Title = document.createElement('h1');
        var Genre = document.createElement('div');
        var ReleaseDate = document.createElement('div');

        var button = document.createElement('button');
        button.className = 'watchlist';
        button.textContent = 'Add to watchlist';

        button.addEventListener('click', function() {
            addWatchlist(item.MediaID , "Movie");
        });

        Title.textContent = "Title : " + item.Title;
        Genre.textContent = "Genre : " + item.Genre;
        ReleaseDate.textContent = "Release Data : "+item.ReleaseDate;

        listItem.appendChild(anchor);
        listItem.appendChild(Title);
        listItem.appendChild(Genre);
        listItem.appendChild(ReleaseDate);

        if(item.Season !== undefined && item.Season !== null)
        {
            var Season = document.createElement('div');
            Season.textContent = "Seasons : " + item.Season;
            listItem.appendChild(Season);
        }

        listItem.appendChild(button);
        list.appendChild(listItem);
    }
    document.getElementById('loading-container').style.display = 'none';
}

async function getMedia()
{
    var currentUrl = window.location.href;
    if(!currentUrl.includes("view.html"))
    {
        var profile = document.getElementById('profilePic');
        let image = document.createElement('img');
        image.style.width = "150px";
        image.style.borderRadius = "100px";
        let user_id = localStorage.getItem('userID');
        let userdata = {
            type : "GetUserImage",
            user_id : user_id
        }
        let userProf = await fetchMedia(userdata);
    
        image.alt = "Image";
        image.src = userProf.data[0].URL;
    
        profile.appendChild(image);
    
        let data = await get_attributes("GetMovie");
        let movies = await fetchMedia(data);
        data = await get_attributes("GetShow");
        let show = await fetchMedia(data);   
        let mergedMedia = show.data.concat(movies.data);
        mergedMedia.sort((a, b) => {
            const titleA = a.Title.toUpperCase();
            const titleB = b.Title.toUpperCase();
            if (titleA < titleB) {
                return -1;
            }
            if (titleA > titleB) {
                return 1;
            }
            return 0;
        });
    
        populate_Media(mergedMedia);
    }
    else
    {
        const queryString = window.location.search;
        const urlParams = new URLSearchParams(queryString);

        const id = urlParams.get('id');
        const type = urlParams.get('type');
        get_view(id , type);
    }

}

async function get_view(id , type)
{
    let data = {}
    if(type === "Movie")
    {
        data.type = "GetMovie";
        data.movie_id = id;
    }
    if(type === "Show")
    {
        data.type = "GetShow";
        data.show_id = id;
    }
    let media = await fetchMedia(data);
    data = {}
    if(type === "Movie")
    {
        data.type = "GetCast";
        data.movie_id = id;
    }
    else if(type === "Show")
    {
        data.type = "GetCast";
        data.show_id = id;
    }
    let cast = await fetchMedia(data);

    data = {}
    if(type === "Movie")
    {
        data.type = "GetReview";
        data.movie_id = id;
    }
    else if(type === "Show")
    {
        data.type = "GetReview";
        data.show_id = id;
    }
    let reviews = await fetchMedia(data);

    data = {}
    if(type === "Movie")
        {
            data.type = "GetAverageReview";
            data.movie_id = id;
        }
        else if(type === "Show")
        {
            data.type = "GetAverageReview";
            data.show_id = id;
        }
    let rating = await fetchMedia(data);
    await populate_view(media.data[0], cast);
    await populate_reviews(reviews.data , rating.data);
}

async function populate_view(data , cast)
{   
    let castItems = cast.data;
    document.getElementById('loading-container').style.display = 'block';
    var media = document.getElementById('media-container');

    var castContainer = document.createElement('ul');
    const item = castItems;
    var lead_actor = item[0].lead_actor;
    var secondary_actor = item[0].secondary_actor;
    var director = item[0].director;
    var backstage = item[0].backstage;

    let lead = document.createElement('div');
    lead.textContent = "Lead : " + lead_actor;

    let secondary = document.createElement('div');
    secondary.textContent = "Secondary : " + secondary_actor;

    let dir = document.createElement('div');
    dir.textContent = "Director : " + director;

    let back = document.createElement('div');
    back.textContent = "Backstage : " + backstage;

    let list = document.createElement('li');
    list.appendChild(lead);
    list.appendChild(secondary);
    list.appendChild(dir);
    list.appendChild(back);
    castContainer.appendChild(list);

    
    var imageContainer = document.createElement('divs');
    var image = document.createElement('img');
    image.src = data.URL;
    image.alt = "Media";
    
    imageContainer.appendChild(image);

    var Title = document.createElement('h1');
    Title.textContent = data.Title;

    var Genre = document.createElement('div');
    Genre.textContent = data.Genre;

    var AgeRating = document.createElement('div');
    AgeRating.textContent = data.AgeRating;

    var Length = document.createElement('div');
    Length.textContent = data.Length;

    var ReleaseDate = document.createElement('div');
    ReleaseDate .textContent = data.ReleaseDate ;

    var Summary = document.createElement('div');
    Summary.textContent = data.Summary;

    media.appendChild(imageContainer);
    media.appendChild(Title);
    media.appendChild(AgeRating);
    media.appendChild(Genre);
    media.appendChild(Length);
    media.appendChild(ReleaseDate);
    media.appendChild(Summary);
    media.appendChild(castContainer);
    document.getElementById('loading-container').style.display = 'none';
}


async function addReview()
{
    const queryString = window.location.search;
    const urlParams = new URLSearchParams(queryString);

    const id = urlParams.get('id');
    const type = urlParams.get('type');
    
    const reviewText = document.getElementById("ReviewText").value.trim();
    const ratingNumber = document.getElementById("RatingNumber").value;

    let data = {
        type : "AddReview",
        rating : ratingNumber,
        summary : reviewText
    }
    if(type === "Movie")
    {
       data["movie_id"] = id;
    }
    else
    {
        data["show_id"] = id;
    }
    await fetchMedia(data);
    location.reload();
}

function roundToDecimals(num, decimals) {
    let factor = Math.pow(10, decimals);
    return Math.round(num * factor) / factor;
}


async function populate_reviews(data , rating)
{
    let items = data;
    var review = document.getElementById('reviews');

    var ratingElement = document.getElementById('Rating');
    
    var ratingAverage = document.createElement('div');
    ratingAverage.textContent = "Movie Rating: " + roundToDecimals(rating[0].rating,2);
    ratingElement.appendChild(ratingAverage);
    for (const item of items) {
        var listItem = document.createElement('li');

        var contents = document.createElement('span');
        var Rating = document.createElement('span');
        var Summary = document.createElement('div');

        Rating.textContent = "Rating : " + item.rating;
        Summary.textContent = "Summary : " + item.summary;

        contents.appendChild(Rating);
        contents.appendChild(Summary);
        listItem.appendChild(contents);
        review.appendChild(listItem);
    }

}

async function get_attributes(type) {
    
    var genre = document.getElementById("genreFilter").value;
    var search = document.getElementById("searchBar").value;
    var data = {
        "type": type
    };
    if (search !== "") {
        data["title"] = search;
        data["genre"] = search;
        data["summar"] = search;
    }
    if(genre !== null && genre !== undefined)
    {
        data["genre"] = genre;
    }

    return data;
}

async function fetchMedia(data) 
{
    return new Promise((resolve) => 
    {
        let url = 'http://localhost:3000/COS221/api.php';
        let xml = new XMLHttpRequest();
        xml.open('POST', url, true);
        xml.setRequestHeader('Content-Type', 'application/json');

        // const auth = 'Basic ' + btoa('u04948123' + ':' + '3918Milo');

        // const username = 'u04948123';
        // const password = '3918Milo';
        // const auth = 'Basic ' + btoa(username + ':' + password);
        // xml.setRequestHeader('Authorization', auth);

        xml.onreadystatechange = function () 
        {
            if (xml.readyState === 4 && xml.status === 200) 
            {
                let response = JSON.parse(xml.responseText);
                resolve(response);
            }
        };
        xml.send(JSON.stringify(data));
    });
}

async function addWatchlist(MediaID , type)
{
    let userID = localStorage.getItem('userID');
    let data = {
        type : "AddWatchlist",
        user_id : userID
    }
    if(type === "Movie")
    {
        data["movie_id"] = MediaID;
    }
    else
    {
        data["show_id"] = MediaID;
    }
    let url = 'http://localhost:3000/COS221/api.php';
    let xml = new XMLHttpRequest();
    xml.open('POST', url, true);
    xml.setRequestHeader('Content-Type', 'application/json');
       
    // const auth = 'Basic ' + btoa(username + ':' + password);
    // xml.setRequestHeader('Authorization', auth);
    
    xml.onreadystatechange = function () 
    {
        if (xml.readyState === 4 && xml.status === 200) 
        {
            let response = JSON.parse(xml.responseText);
        }
    };
    xml.send(JSON.stringify(data));
}