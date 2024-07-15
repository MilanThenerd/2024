<?php
require_once 'config.php';


header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

class API 
{
    private $conn;

    public function __construct() 
    {
        $this->conn = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_DATABASE);
        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
        }
    }

    public function registerUser($username, $password , $email , $premium, $url) 
    {
        if(empty($username))
        {
            return $this->generateErrorResponse("Missing Username");
        }

        if(empty($password))
        {
            return $this->generateErrorResponse("Missing Password");
        }

        if(!preg_match('/[a-z]/', $password))
        {
            return $this->generateErrorResponse("Password must contain atleast one lowercase");
        }
        if(!preg_match('/[A-Z]/', $password))
        {
            return $this->generateErrorResponse("Password must contain atleast one uppercase");
        }
        if (!preg_match('/\d/', $password)) 
        {
            return $this->generateErrorResponse("Password must contain atleast one digit");
        }
        if (!preg_match('/[^\w\d\s]/', $password)) 
        {
            return $this->generateErrorResponse("Password must contain atleast one symbol");
        }
        if (strlen($password) < 8) 
        {
            return $this->generateErrorResponse("Password must be at least 8 characters long");
        }

        $stmt = $this->conn->prepare("SELECT * FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            return $this->generateErrorResponse("Username already exists");
        }

        $sql = "INSERT INTO `users` (`username`, `password` , `email` , `premium` , `URL`) VALUES (?, ? ,? ,? ,?)";
        $stmt = $this->conn->prepare($sql);
        if(!$stmt)
        {
            return $this->generateErrorResponse("Failed to execute statement: " . $this->conn->error);
        }
        $stmt->bind_param("sssss", $username, $password , $email , $premium, $url);
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse("Registered user successfully");
    }

    public function loginUser($username , $password)
    {
        $sql = "SELECT * FROM users WHERE username = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s",$username);
        $stmt->execute();
        $result = $stmt->get_result();
        if ($result->num_rows > 0) 
        {
            while ($row = $result->fetch_assoc()) 
            {

                if($password === $row["password"])
                {
                    return $this->generateSuccessResponse($row["userID"]);
                }
            }
        }
        return $this->generateErrorResponse("Username or password incorrect");
    }

    public function GetUserImage($user_id)
    {
        $sql = "SELECT * FROM users WHERE userID = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s",$user_id);

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();
        return $this->generateSuccessArrayResponse($data);
    }

    public function getMovie($movie_id , $title , $releaseDate , $length , $genre , $rating , $ageRating , $summary)
    {
        $sql = "SELECT * FROM movies";
        $conditions = [];
        $params = [];

        if ($movie_id !== null) 
        {
            $conditions[] = "MediaID = ?";
            $params[] = $movie_id;
        }
        if ($title !== null) 
        {
            $conditions[] = "Title LIKE ?";
            $params[] = "%" . $title . "%";
        }
        if ($releaseDate !== null) 
        {
            $conditions[] = "ReleaseDate = ?";
            $params[] = $releaseDate;
        }
        if ($length!== null) 
        {
            $conditions[] = "Length = ?";
            $params[] = $length;
        }
        if ($genre !== null) 
        {
            $conditions[] = "Genre LIKE ?";
            $params[] = "%" . $genre . "%";
        }
        if ($rating !== null) 
        {
            $conditions[] = "Rating = ?";
            $params[] = $rating;
        }
        if ($ageRating !== null) 
        {
            $conditions[] = "AgeRating = ?";
            $params[] = $ageRating;
        }
        if ($summary !== null) 
        {
            $conditions[] = "Summary Like ?";
            $params[] = "%" . $summary . "%";
        }

        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessArrayResponse($data);
    }

    public function addMovie($title , $release_date , $length , $genre , $rating , $age_rating , $summary, $url)
    {
        $sql = "INSERT INTO `movies` (`Title`, `ReleaseDate` , `Length` , `Genre` , `Rating` , `AgeRating` , `Summary` , `URL`) VALUES (?, ? , ? , ? , ? , ? , ? , ?)";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ssssssss" , $title , $release_date , $length , $genre , $rating , $age_rating , $summary, $url);
        $stmt->execute();

        return $this->generateSuccessResponse("Successfully added Movie");
    }

    public function updateMovie($movie_id , $title , $releaseDate , $length , $genre , $rating , $ageRating , $summary , $url)
    {
        $sql = "UPDATE movies";
        $conditions = [];
        $params = [];

        if ($title !== null) 
        {
            $conditions[] = "Title = ?";
            $params[] = $title;
        }
        if ($releaseDate !== null) 
        {
            $conditions[] = "ReleaseDate = ?";
            $params[] = $releaseDate;
        }
        if ($length!== null) 
        {
            $conditions[] = "Length = ?";
            $params[] = $length;
        }
        if ($genre !== null) 
        {
            $conditions[] = "Genre = ?";
            $params[] = $genre;
        }
        if ($rating !== null) 
        {
            $conditions[] = "Rating = ?";
            $params[] = $rating;
        }
        if ($ageRating !== null) 
        {
            $conditions[] = "AgeRating = ?";
            $params[] = $ageRating;
        }
        if ($summary !== null) 
        {
            $conditions[] = "Summary = ?";
            $params[] = $summary;
        }
        if($url !== null)
        {
            $conditions[] = "URL = ?";
            $params[] = $url;
        }

        if (count($conditions) > 0) 
        {
            $sql .= " SET " . implode(" , ", $conditions);
        }
        else
        {
            return $this->generateErrorResponse("Must update atleast 1 column");
        }
        $sql .= " WHERE MediaID = ?";
        $params[] = $movie_id;

        $stmt = $this->conn->prepare($sql);
        
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $stmt->close();

        return $this->generateSuccessResponse("Succesfully update Movie");
    }

    public function deleteMovie($movie_id)
    {
        $sql = "DELETE FROM `movies` WHERE `MediaID` = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s", $movie_id);
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse("Succesfully deleted Movie");
    }

    public function getShow($show_id , $title , $season , $releaseDate , $length , $genre , $rating , $ageRating , $summary)
    {
        $sql = "SELECT * FROM tvshows";
        $conditions = [];
        $params = [];

        if ($show_id !== null) 
        {
            $conditions[] = "MediaID = ?";
            $params[] = $show_id;
        }
        if ($title !== null) 
        {
            $conditions[] = "Title LIKE ?";
            $params[] = "%" . $title . "%";
        }
        if ($season !== null) 
        {
            $conditions[] = "Season = ?";
            $params[] = $title;
        }
        if ($releaseDate !== null) 
        {
            $conditions[] = "ReleaseDate = ?";
            $params[] = $releaseDate;
        }
        if ($length!== null) 
        {
            $conditions[] = "Length = ?";
            $params[] = $length;
        }
        if ($genre !== null) 
        {
            $conditions[] = "Genre Like ?";
            $params[] = "%" . $genre . "%";
        }
        if ($rating !== null) 
        {
            $conditions[] = "Rating = ?";
            $params[] = $rating;
        }
        if ($ageRating !== null) 
        {
            $conditions[] = "AgeRating = ?";
            $params[] = $ageRating;
        }
        if ($summary !== null) 
        {
            $conditions[] = "Summary = ?";
            $params[] = $summary;
        }

        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessArrayResponse($data);
    }

    public function addShow($title , $season , $releaseDate , $length , $genre , $rating , $ageRating , $summary , $url)
    {
        $sql = "INSERT INTO `TVShows` (`Title`, `Season`, `ReleaseDate` , `Length` , `Genre` , `Rating` , `AgeRating` , `Summary` , `URL`) VALUES (?, ? , ? , ? , ? , ? , ? , ?, ?)";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ssssssss" , $title , $season , $releaseDate , $length , $genre , $rating , $ageRating , $summary , $url);
        $stmt->execute();

        return $this->generateSuccessResponse("Successfully added Show");
    }

    public function updateShow($show_id , $title , $season , $releaseDate , $length , $genre , $rating , $ageRating , $summary, $url)
    {
        $sql = "UPDATE movies";
        $conditions = [];
        $params = [];

        if ($title !== null) 
        {
            $conditions[] = "Title = ?";
            $params[] = $title;
        }
        if ($season !== null) 
        {
            $conditions[] = "Season = ?";
            $params[] = $season;
        }
        if ($releaseDate !== null) 
        {
            $conditions[] = "ReleaseDate = ?";
            $params[] = $releaseDate;
        }
        if ($length!== null) 
        {
            $conditions[] = "Length = ?";
            $params[] = $length;
        }
        if ($genre !== null) 
        {
            $conditions[] = "Genre = ?";
            $params[] = $genre;
        }
        if ($rating !== null) 
        {
            $conditions[] = "Rating = ?";
            $params[] = $rating;
        }
        if ($ageRating !== null) 
        {
            $conditions[] = "AgeRating = ?";
            $params[] = $ageRating;
        }
        if ($summary !== null) 
        {
            $conditions[] = "Summary = ?";
            $params[] = $summary;
        }
        if ($url !== null) 
        {
            $conditions[] = "URL = ?";
            $params[] = $url;
        }

        if (count($conditions) > 0) 
        {
            $sql .= " SET " . implode(" , ", $conditions);
        }
        else
        {
            return $this->generateErrorResponse("Must update atleast 1 column");
        }
        $sql .= " WHERE MediaID = ?";
        $params[] = $show_id;

        $stmt = $this->conn->prepare($sql);
        
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $stmt->close();

        return $this->generateSuccessResponse("Succesfully update Movie");
    }

    public function deleteShow($show_id)
    {
        $sql = "DELETE FROM `TVShows` WHERE `MediaID` = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s", $show_id);
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse("Succesfully deleted Show");
    }

    public function addReview($rating , $summary , $movie_id , $show_id)
    {
        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        $type = "";
        $mediaID = "";
        if($movie_id !== null)
        {
            $sql = "INSERT INTO `reviews` (`rating`, `summary`, `movieid` , `type`) VALUES (?, ? , ? , ?)";
            $type = "movie";
            $mediaID = $movie_id;
        }
        else if($show_id !== null)
        {
            $sql = "INSERT INTO `reviews` (`rating`, `summary`, `tvshowid`, `type`) VALUES (?, ? , ? , ?)";
            $type = "tvshow";
            $mediaID = $show_id;
        }
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ssss" , $rating , $summary , $mediaID, $type);
        $stmt->execute();

        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }

        return $this->generateSuccessResponse("Successfully added Review");
    }

    public function getReview($movie_id , $show_id)
    {
        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        $sql = "SELECT * FROM reviews";
        $conditions = [];
        $params = [];
        $type = null;
        if ($movie_id !== null) 
        {
            $conditions[] = "movieid = ?";
            $params[] = $movie_id;
        }
        if ($show_id !== null) 
        {
            $conditions[] = "tvshowid = ?";
            $params[] = $show_id;
        }
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessArrayResponse($data);
    }

    public function getAverageReview($movie_id , $show_id)
    {
        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        $sql = "SELECT AVG(rating) AS rating FROM reviews";
        $conditions = [];
        $params = [];
        $type = null;
        if ($movie_id !== null) 
        {
            $conditions[] = "movieid = ?";
            $params[] = $movie_id;
        }
        if ($show_id !== null) 
        {
            $conditions[] = "tvshowid = ?";
            $params[] = $show_id;
        }
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessArrayResponse($data);
    }

    public function addWatchlist($user_id , $movie_id , $show_id)
    {
        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        if($movie_id !== null)
        {
            $type = "Movie";
            $media = $movie_id;
        }
        else if($show_id !== null)
        {
            $type = "Show";
            $media = $show_id;
        }

        $stmt = $this->conn->prepare("SELECT * FROM watchlist WHERE userID = ? AND mediaID = ?" );
        $stmt->bind_param("ss", $user_id , $media);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            return $this->generateErrorResponse("Movie or TvShow already in watchlist");
        }

        $sql = "INSERT INTO `Watchlist` (`userID`, `MediaID`, `type`) VALUES (?, ?, ?)";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("sss" , $user_id , $media, $type);
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse("Added to watchlist");
    }

    public function getWatchList($user_id)
    {
        $sql = "SELECT * FROM Watchlist WHERE userID = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s" , $user_id);
        $stmt->execute();

        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);
        $stmt->close();
        return $this->generateSuccessArrayResponse($data);
    }

    public function deleteWatchlist($user_id , $movie_id , $show_id)
    {
        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        if($movie_id !== null)
        {
            $sql = "DELETE FROM `TVShows` WHERE `user_id` = ? AND `MediaID` = ? AND `type` = 'Movie'";
            $stmt = $this->conn->prepare($sql);
            $stmt->bind_param("ss", $user_id , $movie_id);
        }
        else if($show_id !== null)
        {
            $sql = "DELETE FROM `TVShows` WHERE `user_id` = ? AND `MediaID` = ? AND `type` = 'Show'";
            $stmt = $this->conn->prepare($sql);
            $stmt->bind_param("ss", $user_id , $show_id);
        }
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse("Succesfully deleted Watchlist");
    }

    public function getCast($cast_id , $lead_actor , $secondary_actor , $director , $backstage , $movie_id , $show_id)
    {
        $sql = "SELECT * FROM cast";
        $conditions = [];
        $params = [];

        if($movie_id === null && $show_id === null)
        {
            return $this->generateErrorResponse("movieID or showID must be specified");
        }
        if($movie_id !== null && $show_id !== null)
        {
            return $this->generateErrorResponse("You can only specify movieID or showID , one at a time");
        }
        if($movie_id !== null)
        {
            $conditions[] = "movie_id = ?";
            $params[] = $movie_id;
        }
        else if($show_id !== null)
        {
            $conditions[] = "tv_id = ?";
            $params[] = $show_id;
        }
        if ($cast_id !== null) 
        {
            $conditions[] = "cast_id = ?";
            $params[] = $cast_id;
        }
        if ($lead_actor !== null) 
        {
            $conditions[] = "lead_actor LIKE ?";
            $params[] = "%" . $lead_actor . "%";
        }
        if ($secondary_actor !== null) 
        {
            $conditions[] = "secondary LIKE ?";
            $params[] = "%" . $secondary_actor . "%";
        }
        if ($director !== null) 
        {
            $conditions[] = "director LIKE ?";
            $params[] = "%" . $director . "%";
        }
        if($backstage !== null)
        {
            $conditions[] = "backstage LIKE ?";
            $params[] = "%" . $backstage . "%";
        }
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessArrayResponse($data);
    }

    private function generateSuccessResponse($message) 
    {
        $response = array(
            "status" => "success",
            "message" => $message
        );
        return json_encode($response);
    }

    public function generateErrorResponse($message) 
    {
        $response = array(
            "status" => "error",
            "message" => $message
        );
        return json_encode($response);
    }

    private function generateSuccessArrayResponse($array)
    {
        $response = array(
            "status" => "success",
            "timestamp" => time(),
            "data" => $array
        );
        return json_encode($response);
    }
}


$api = new API();
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        $postData = json_decode(file_get_contents("php://input"), true);
        if (isset($postData["type"]) && $postData["type"] == "Register" && isset($postData["username"]) && isset($postData["password"]) && isset($postData["url"])) 
        {
            $email = isset($postData["email"]) ? $postData["email"] : null;
            $premium = isset($postData["premium"]) ? $postData["premium"] : null;
            $response = $api->registerUser($postData["username"], $postData["password"] , $email , $premium , $postData["url"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "Login" && isset($postData["username"]) && isset($postData["password"])) 
        {
            $response = $api->loginUser($postData["username"], $postData["password"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetUserImage" && isset($postData["user_id"]))
        {
            $response = $api->GetUserImage($postData["user_id"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "GetMovie")
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $release_date = isset($postData["release_date"]) ? $postData["release_date"] : null;
            $length  = isset($postData["length"]) ? $postData["length"] : null;
            $genre  = isset($postData["genre"]) ? $postData["genre"] : null;
            $rating = isset($postData["rating"]) ? $postData["rating"] : null;
            $age_rating = isset($postData["age_rating"]) ? $postData["age_rating"] : null;
            $summary = isset($postData["summary"]) ? $postData["summary"] : null;

            $response = $api->getMovie($movie_id , $title, $release_date, $length , $genre , $rating , $age_rating , $summary);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "AddMovie" && isset($postData["title"]) && isset($postData["release_date"]) && isset($postData["length"]) && isset($postData["genre"]) && isset($postData["summary"]) && isset($postData["url"]))
        {
            $response = $api->addMovie($postData["title"], $postData["release_date"] , $postData["length"] , $postData["genre"] , $postData["rating"] , $postData["age_rating"] , $postData["summary"], $postData["url"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "UpdateMovie" && isset($postData["movie_id"]))
        {
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $release_date = isset($postData["release_date"]) ? $postData["release_date"] : null;
            $length  = isset($postData["length"]) ? $postData["length"] : null;
            $genre  = isset($postData["genre"]) ? $postData["genre"] : null;
            $rating = isset($postData["rating"]) ? $postData["rating"] : null;
            $age_rating = isset($postData["age_rating"]) ? $postData["age_rating"] : null;
            $summary = isset($postData["summary"]) ? $postData["summary"] : null;
            $url = isset($postData["url"]) ? $postData["url"] : null;
            $response = $api->updateMovie($postData["movie_id"], $title, $release_date, $length , $genre , $rating , $age_rating , $summary, $url);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "DeleteMovie" && isset($postData["movie_id"]) )
        {
            $response = $api->deleteMovie($postData["movie_id"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "GetShow")
        {
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $season = isset($postData["season"]) ? $postData["season"] : null;
            $release_date = isset($postData["release_date"]) ? $postData["release_date"] : null;
            $length  = isset($postData["length"]) ? $postData["length"] : null;
            $genre  = isset($postData["genre"]) ? $postData["genre"] : null;
            $rating = isset($postData["rating"]) ? $postData["rating"] : null;
            $age_rating = isset($postData["age_rating"]) ? $postData["age_rating"] : null;
            $summary = isset($postData["summary"]) ? $postData["summary"] : null;

            $response = $api->getShow($show_id ,$title, $season , $release_date, $length , $genre , $rating , $age_rating , $summary);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "AddShow" && isset($postData["title"]) && isset($postData["season"]) && isset($postData["release_date"]) && isset($postData["length"]) && isset($postData["genre"]) && isset($postData["summary"]) && isset($postData["url"]))
        {
            $response = $api->addShow($postData["title"], $postData["season"] , $postData["release_date"] , $postData["length"] , $postData["genre"] , $postData["rating"] , $postData["age_rating"] , $postData["summary"] , $postData["url"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "UpdateShow" && isset($postData["show_id"]))
        {
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $season = isset($postData["season"]) ? $postData["season"] : null;
            $release_date = isset($postData["release_date"]) ? $postData["release_date"] : null;
            $length  = isset($postData["length"]) ? $postData["length"] : null;
            $genre  = isset($postData["genre"]) ? $postData["genre"] : null;
            $rating = isset($postData["rating"]) ? $postData["rating"] : null;
            $age_rating = isset($postData["age_rating"]) ? $postData["age_rating"] : null;
            $summary = isset($postData["summary"]) ? $postData["summary"] : null;
            $url = isset($postData["url"]) ? $postData["url"] : null;
            $response = $api->updateShow($postData["movie_id"], $title, $season , $release_date, $length , $genre , $rating , $age_rating , $summary , $url);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "DeleteShow" && isset($postData["show_id"]) )
        {
            $response = $api->deleteShow($postData["show_id"]);

            echo($response);
        }
        else if (isset($postData["type"]) && $postData["type"] == "AddReview" && isset($postData["rating"]) && isset($postData["summary"]))
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->addReview($postData["rating"] , $postData["summary"], $movie_id , $show_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetReview")
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->getReview($movie_id , $show_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAverageReview")
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->getAverageReview($movie_id , $show_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetWatchlist" && isset($postData["user_id"]))
        {
            $response = $api->getWatchList($postData["user_id"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "AddWatchlist" && isset($postData["user_id"]))
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->addWatchList($postData["user_id"] , $movie_id , $show_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "RemoveWatchlist" && isset($postData["user_id"]))
        {
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->deleteWatchlist($postData["user_id"] , $movie_id , $show_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetCast")
        {
            $cast_id = isset($postData["cast_id"]) ? $postData["cast_id"] : null;
            $lead_actor = isset($postData["lead_actor"]) ? $postData["lead_actor"] : null;
            $secondary_actor = isset($postData["secondary_actor"]) ? $postData["secondary_actor"] : null;
            $director = isset($postData["director"]) ? $postData["director"] : null;
            $backstage = isset($postData["backstage"]) ? $postData["backstage"] : null;
            $movie_id = isset($postData["movie_id"]) ? $postData["movie_id"] : null;
            $show_id = isset($postData["show_id"]) ? $postData["show_id"] : null;
            $response = $api->getCast($cast_id , $lead_actor , $secondary_actor , $director , $backstage , $movie_id , $show_id);

            echo($response);
        }
        else 
        {
            echo $api->generateErrorResponse("Invalid request");
        }
    }
    else 
    {
        echo $api->generateErrorResponse("Invalid request method");
    }


?>