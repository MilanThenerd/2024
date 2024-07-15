var request = new XMLHttpRequest();

function GetMovie() {
    var genre = document.getElementById("genreFilter").value;

    jsonObj = {
        type : "GetMovie",
        title : null,
        release_date : null,
        length : null,
        genre : genre,
        rating : null,
        age_rating : null,
        summary : null
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            var mediaDiv = document.getElementById("media");

            if (response.status == "success") {
                mediaDiv.hidden = response["movieID"];
                mediaDiv.innerHTML = "<h2 class = 'title'>"+ response["Title"] +"</h2>" +
                                    "<p class = 'description'>"+ response["Summary"] +"</p>" +
                                    "<p class='genre'>"+ response["Genre"] +"</p>" +
                                    "<p class ='ageRating'>"+ response["AgeRating"] +"</p>" +
                                    "<button class='watchlist'>Add to watchlist</button>";
            } else {
                window.alert("Something went wrong. Please reload the page");
            } 
        }
    }
} 

function AddMovie() {
    //change ids to match html doc
    var title = document.getElementById("inTitle").value;
    var release = document.getElementById("inRelease").value;
    var length = document.getElementById("inLength").value;
    var genre = document.getElementById("inGenre").value;
    var rating = document.getElementById("inRating").value;
    var age = document.getElementById("inAge").value;
    var sum = document.getElementById("inSum").value;

    jsonObj = {
        type : "AddMovie",
        title : title,
        release_date : release,
        length : length,
        genre : genre,
        rating : rating,
        age_rating : age,
        summary : sum
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of header in div containing movie from html doc
            var head = document.getElementById("headerOfDivContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } else {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } 
        }
    }
}

function UpdateMovie() {
    //change ids to match html doc
    var title = document.getElementById("inTitle").value;
    var release = document.getElementById("inRelease").value;
    var length = document.getElementById("inLength").value;
    var genre = document.getElementById("inGenre").value;
    var rating = document.getElementById("inRating").value;
    var age = document.getElementById("inAge").value;
    var sum = document.getElementById("inSum").value;

    //default values for input fields in html must be null
    jsonObj = {
        type : "UpdateMovie",
        title : title,
        release_date : release,
        length : length,
        genre : genre,
        rating : rating,
        age_rating : age,
        summary : sum
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of header in div containing movie from html doc
            var head = document.getElementById("headerOfDivContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } else {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } 
        }
    }
}

function DeleteMovie() {
    //change to match element id from html
    var id = document.getElementById("divContainingMovie").hidden;

    jsonObj = {
        type : "DeleteMovie",
        movie_id : id
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of div containing movie from html doc
            var divMov = document.getElementById("divContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                divMov.innerHTML = "<div id='divContainingMovie'>" + response.message + "</div>";
            } else {
                //change to fit html element
                divMov.innerHTML = "<div id='divContainingMovie'>" + response.message + "</div>";
            } 
        }
    }
}

function GetShow() {
    //change ids to match html doc
    var title = document.getElementById("inTitle").value;
    var season = document.getElementById("inSeason").value;
    var length = document.getElementById("inLength").value;
    var genre = document.getElementById("inGenre").value;
    var rating = document.getElementById("inRating").value;
    var age = document.getElementById("inAge").value;
    var sum = document.getElementById("inSum").value;

    jsonObj = {
        type : "GetShow",
        title : title,
        season : season,
        length : length,
        genre : genre,
        rating : rating,
        age_rating : age,
        summary : sum
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of header in div containing tv show from html doc
            var head = document.getElementById("headerOfDivContainingMovie");

            if (response.status == "success") {
                //change this when have html formatting
                head.hidden = response["show_id"];
                head.innerHTML = "";
                //items response["Rating"] / ["Season"] / ["Summary"] / ["Length"] / ["AgeRating"] / ["Title"] / ["Genre"]
            } else {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>Something went wrong. Please reload the page</h3>";
            } 
        }
    }
}

function AddShow() {
    //change ids to match html doc
    var title = document.getElementById("inTitle").value;
    var season = document.getElementById("inSeason").value;
    var length = document.getElementById("inLength").value;
    var genre = document.getElementById("inGenre").value;
    var rating = document.getElementById("inRating").value;
    var age = document.getElementById("inAge").value;
    var sum = document.getElementById("inSum").value;

    jsonObj = {
        type : "AddShow",
        title : title,
        season : season,
        length : length,
        genre : genre,
        rating : rating,
        age_rating : age,
        summary : sum
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of header in div containing tv show from html doc
            var head = document.getElementById("headerOfDivContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } else {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } 
        }
    }
}

function UpdateShow() {
    //change ids to match html doc
    var title = document.getElementById("inTitle").value;
    var season = document.getElementById("inSeason").value;
    var length = document.getElementById("inLength").value;
    var genre = document.getElementById("inGenre").value;
    var rating = document.getElementById("inRating").value;
    var age = document.getElementById("inAge").value;
    var sum = document.getElementById("inSum").value;

    //default values for input fields in html must be null
    jsonObj = {
        type : "UpdateShow",
        title : title,
        season : season,
        length : length,
        genre : genre,
        rating : rating,
        age_rating : age,
        summary : sum
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of header in div containing tv show from html doc
            var head = document.getElementById("headerOfDivContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } else {
                //change to fit html element
                head.innerHTML = "<h3 id='headerOfDivContainingMovie'>" + response.message + "</h3>";
            } 
        }
    }
}

function DeleteShow() {
    //change to match element id from html
    var id = document.getElementById("divContainingMovie").hidden;

    jsonObj = {
        type : "DeleteShow",
        movie_id : id
    }

    //insert url for api below
    request.open('POST', 'https://wheatley.cs.up.ac.za/u23586312/api.php')
    request.setRequestHeader('Content-Type', 'application/json')
    request.send(JSON.stringify(jsonObj))

    request.onload = () => {
        if (request.status >= 200 && request.status < 300) {
            var response = JSON.parse(request.responseText);

            //get name of div containing tv show from html doc
            var divMov = document.getElementById("divContainingMovie");

            if (response.status == "success") {
                //change to fit html element
                divMov.innerHTML = "<div id='divContainingMovie'>" + response.message + "</div>";
            } else {
                //change to fit html element
                divMov.innerHTML = "<div id='divContainingMovie'>" + response.message + "</div>";
            } 
        }
    }
}

function Addfave() {
    //needs to be coded according to method used to get favourites
}
