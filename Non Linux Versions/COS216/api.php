<?php
require_once 'config.php';

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");
class API 
{
    private $conn, $conn_auctions;

    public function __construct() 
    {
        $this->conn = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_LISTINGS);
        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
        }
        $this->conn_auctions = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_AUCTIONS);
        if ($this->conn_auctions->connect_error) {
            die("Connection failed: " . $this->conn_auctions->connect_error);
        }
    }

    public function registerUser($name, $surname, $email, $password) 
    {
        if(empty($name))
        {
            return $this->generateErrorResponse("Missing Name");
        }
        if(empty($surname))
        {
            return $this->generateErrorResponse("Missing Surname");
        }

        if(empty($email))
        {
            return $this->generateErrorResponse("Missing Email");
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

        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) 
        {
            return $this->generateErrorResponse("Invalid email format");
        }

        $stmt = $this->conn->prepare("SELECT * FROM users WHERE email = ?");
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            return $this->generateErrorResponse("User already exists");
        }

        $sql = "INSERT INTO `users` (`name`, `surname`, `email`, `password` , `api` , `theme`) VALUES (?, ?, ?, ? ,?,'light')";
        $stmt = $this->conn->prepare($sql);
        $apiKey = $this->generateApiKey();

        $salt = $this->generateSalt($email);
        $salt_pass = $password.$salt;
        $hashedPassword = password_hash($salt_pass, PASSWORD_DEFAULT);
        $stmt->bind_param("sssss", $name, $surname, $email, $hashedPassword , $apiKey);
        $stmt->execute();

        return $this->generateSuccessResponse($apiKey);
    }

    private function generateSuccessResponse($apiKey) 
    {
        $response = array(
            "status" => "success",
            "timestamp" => time(),
            "data" => array(
                "apikey" => $apiKey
            )
        );
        return json_encode($response);
    }

    private function generateSalt($input) {
        $hash = hash('sha256', $input);
        
        $salt = substr($hash, 0, 16);
        
        return $salt;
    }

    private function generateSuccessListingsResponse($array)
    {
        $response = array(
            "status" => "success",
            "timestamp" => time(),
            "data" => $array
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

    private function generateApiKey() 
    {
        return bin2hex(random_bytes(16));
    }

    public function getListings($api ,$type, $limit , $sort, $order , $fuzzy , $search , $return)
    {
        if (empty($api) || empty($type)) 
        {
            return $this->generateErrorResponse("Post parameters are missing");
        }

        if (!in_array(strtoupper($order), array('ASC', 'DESC'))) 
        {
            return $this->generateErrorResponse("Invalid order parameter. Order must be 'ASC' or 'DESC'");
        }
        if(!empty($limit))
        {
            if($limit <= 1)
            {
                $limit = 1;
            }
            if($limit >= 500)
            {   
                $limit = 500;
            }
        }
        $fetchImages = false;
        if ($return === "*" || (is_array($return) && in_array("images", $return))) 
        {
            $fetchImages = true;
            if ($return === "*") 
            {
                $return = ['id', 'title', 'location', 'price', 'bedrooms', 'bathrooms', 'url', 'parking_spaces', 'amenities', 'description', 'type', 'images'];
            }
        }
        
        $sql = "SELECT ";
        if (!in_array('id', $return)) 
        {
            $return[] = 'id';
        }
        if (empty($return)) 
        {
            $sql .= "*";
        } 
        else if (is_array($return)) 
        {
            $sql .= implode(", ", array_map(function($column) 
            {
                return "`$column`";
            }, $return));
        } 
        else
        {
            $sql .= $return;
        }

        $sql .= " FROM listings";
        if (!empty($search) && is_array($search)) 
        {
            $conditions = [];
            foreach ($search as $column => $term) 
            {
                if (!empty($term) && in_array($column, ['id', 'title', 'location', 'bedrooms', 'bathrooms', 'parking_spaces', 'amenities', 'type' , 'price_min' , 'price_max']))
                {
                    if ($column === 'location' || $column === 'type') 
                    {
                        $term = addslashes($term);
                    }
                    if ($column === 'bedrooms' || $column === 'bathrooms' || $column === 'parking_spaces') 
                    {
                        $conditions[] = "$column = '$term'";
                    } 
                    else if ($column === 'price_min') 
                    {
                        $conditions[] = "price >= $term";
                    } 
                    else if ($column === 'price_max') 
                    {
                        $conditions[] = "price <= $term";
                    } 
                    else if ($column === 'type') 
                    {
                        $conditions[] = "type = '$term'";
                    } 
                    else 
                    {
                        if ($fuzzy) 
                        {
    
                            $term = '%' . addslashes($term) . '%';
                            $conditions[] = "$column LIKE '$term'";
                        } 
                        else 
                        {
                            $conditions[] = "$column = '$term'";
                        }
                    }
                }
            }
            if (!empty($conditions)) {
                $sql .= " WHERE " . implode(" AND ", $conditions);
            }
        }
    

        if(isset($sort) && isset($order)) 
        {
            $sql .= " ORDER BY $sort $order";
        }
        if(isset($limit)) {
            $sql .= " LIMIT " . (int)$limit;
        }
        $stmt = $this->conn->prepare($sql);
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);
        return $this->generateSuccessListingsResponse($data);
    }

    public function getAgents($limit=10)
    {
        $sql = "SELECT * FROM agencies LIMIT ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s", $limit);
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        return $this->generateSuccessListingsResponse($data);
    }

    public function loginUser($email , $password)
    {
        $sql = "SELECT * FROM users WHERE email = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s",$email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            while ($row = $result->fetch_assoc()) 
            {
                $salt = $this->generateSalt($email);
                $saltedPassword = $password.$salt;

                if(password_verify($saltedPassword , $row['password']))
                {
                    return $this->generateSuccessResponse($row['api']);
                }
            }
        }

        return $this->generateErrorResponse("Email not in database or password incorrect");

    }

    public function addFavourite($api , $item_id)
    {
        $sql = "INSERT IGNORE INTO `favourites` (`fav_id`, `listings_id`, `user_api`) VALUES (NULL, ?, ?);";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ss", $item_id, $api);
        $stmt->execute();

        return $this->generateSuccessResponse($api);
    }

    public function removeFavourite($item_id, $api)
    {
        $sql = "DELETE FROM favourites WHERE `listings_id` = ? AND `user_api` = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ss", $item_id, $api);
        $stmt->execute();
        if ($stmt->error) {
            return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
        }
        return $this->generateSuccessResponse($api);
    }

    public function getFavourites($api , $limit , $sort, $order , $fuzzy ,  $return , $search )
    {
        if (empty($api)) 
        {
            return $this->generateErrorResponse("Post parameters are missing");
        }

        if (!in_array(strtoupper($order), array('ASC', 'DESC'))) 
        {
            return $this->generateErrorResponse("Invalid order parameter. Order must be 'ASC' or 'DESC'");
        }
        if(!empty($limit))
        {
            if($limit <= 1)
            {
                $limit = 1;
            }
            if($limit >= 500)
            {   
                $limit = 500;
            }
        }
        $fetchImages = false;
        if ($return === "*" || (is_array($return) && in_array("images", $return))) 
        {
            $fetchImages = true;
            if ($return === "*") 
            {
                $return = ['id', 'title', 'location', 'price', 'bedrooms', 'bathrooms', 'url', 'parking_spaces', 'amenities', 'description', 'type', 'images'];
            }
        }
        
        $sql = "SELECT ";
        if (!in_array('id', $return)) 
        {
            $return[] = 'id';
        }
        if (empty($return)) 
        {
            $sql .= "*";
        } 
        else if (is_array($return)) 
        {
            $sql .= implode(", ", array_map(function($column) 
            {
                return "`$column`";
            }, $return));
        } 
        else
        {
            $sql .= $return;
        }

        $sql .= " FROM favourites JOIN listings ON `listings_id` = `id` WHERE `user_api` = '{$api}'";
        if (!empty($search) && is_array($search)) 
        {
            $conditions = [];
            foreach ($search as $column => $term) 
            {
                if (!empty($term) && in_array($column, ['id', 'title', 'location', 'bedrooms', 'bathrooms', 'parking_spaces', 'amenities', 'type' , 'price_min' , 'price_max']))
                {
                    if ($column === 'location' || $column === 'type') 
                    {
                        $term = addslashes($term);
                    }
                    if ($column === 'bedrooms' || $column === 'bathrooms' || $column === 'parking_spaces') 
                    {
                        $conditions[] = "$column = '$term'";
                    } 
                    else if ($column === 'price_min') 
                    {
                        $conditions[] = "price >= $term";
                    } 
                    else if ($column === 'price_max') 
                    {
                        $conditions[] = "price <= $term";
                    } 
                    else if ($column === 'type') 
                    {
                        $conditions[] = "type = '$term'";
                    } 
                    else 
                    {
                        if ($fuzzy) 
                        {
    
                            $term = '%' . addslashes($term) . '%';
                            $conditions[] = "$column LIKE '$term'";
                        } 
                        else 
                        {
                            $conditions[] = "$column = '$term'";
                        }
                    }
                }
            }
            if (!empty($conditions)) {
                $sql .= " AND " . implode(" AND ", $conditions);
            }
        }
    

        if(isset($sort) && isset($order)) 
        {
            $sql .= " ORDER BY $sort $order";
        }
        if(isset($limit)) {
            $sql .= " LIMIT " . (int)$limit;
        }
        $stmt = $this->conn->prepare($sql);
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);
        return $this->generateSuccessListingsResponse($data);
    }

    public function getTheme($api)
    {
        $sql = "SELECT `theme` FROM users WHERE `api` = ?;";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s", $api);
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        return $this->generateSuccessListingsResponse($data);
    }

    public function setTheme($api, $theme)
    {
        $sql = "UPDATE `users` SET `theme` = ? WHERE `api` = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("ss",$theme ,$api);
        $stmt->execute();

        return $this->generateSuccessListingsResponse($api);
    }

    public function getPreferences($api)
    {
        $sql = "SELECT preferences FROM users WHERE `api` = ?";
        $stmt = $this->conn->prepare($sql);
        $stmt->bind_param("s", $api);
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        
        $preferences = $data[0]["preferences"];
        preg_match_all('/\[[^\]]*\]|[^,]+/', $preferences, $matches);

        $limit = trim($matches[0][0], ',');
        $sort = trim($matches[0][1], ',');
        $order = trim($matches[0][2], ',');
        $return = $matches[0][3];
        $search = $matches[0][4];
        
        $return_list = explode(',', trim($return, '[]'));
        $return = $return_list;
        $filters = array(
            "limit" => $limit,
            "sort" => $sort,
            "order" => $order,
            "return" => $return,
            "search" => $search
        );
        

        return $this->generateSuccessListingsResponse($filters);
    }
    public function setPreferences($api , $limit , $sort, $order , $return, $search)
    {
        $sql = "UPDATE `users` SET `preferences` = ? WHERE `api` = ?";
        $stmt = $this->conn->prepare($sql);
        $search = "[".implode(',', $search)."]";
        if($search == "[]")
        {
            $search = "[,,,,,,,,]";
        }
        if ($return == "*" || $return == "[*]") 
        {
            $return = ['id', 'title', 'location', 'price', 'bedrooms', 'bathrooms', 'url', 'parking_spaces', 'amenities', 'description', 'type', 'images'];
        }
        $return = "[".implode(',' , $return)."]";
        $string = $limit.",".$sort.",".$order.",".$return.",".$search;
        $stmt->bind_param("ss", $string,$api);
        $stmt->execute();
        return $this->generateSuccessResponse($api);
    }

    public function getAuctions($name, $start, $end, $state)
    {
        $sql = "SELECT * FROM auctions";
        $conditions = [];
        $params = [];

        if ($name !== null) 
        {
            $conditions[] = "auction_name LIKE ?";
            $params[] = "%" . $name . "%";
        }
        if ($start !== null) 
        {
            $conditions[] = "start_date = ?";
            $params[] = $start;
        }
        if ($end !== null) 
        {
            $conditions[] = "end_date = ?";
            $params[] = $end;
        }
        if ($state !== null) 
        {
            $conditions[] = "state = ?";
            $params[] = $state;
        }

        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn_auctions->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessListingsResponse($data);
    }

    public function createAuction($name  , $start , $end , $listing_id , $state , $seller_id)
    {
        if(!($state === "Wating" || $state === "Ongoing"))
        {
            return $this->generateErrorResponse("State must be either Waiting or Ongoing");
        }
        $sql = "INSERT IGNORE INTO `auctions` (`auction_id`, `auction_name`, `start_date`, `end_date`, `listing_id`, `highest_bid`, `state`, `buyer_id`, `seller_id`) 
        VALUES (NULL, ? , ? , ? , ? , NULL , ? , NULL , ?)";
        $stmt = $this->conn_auctions->prepare($sql);
        $stmt->bind_param("ssssss",$name , $start , $end , $listing_id , $state , $seller_id);
        $stmt->execute();

        return $this->generateSuccessResponse("Successfully created auction");
    }

    public function createAuctionFull($title, $location, $bedrooms, $bathrooms, $parking, $amenities, $description, $images, $name, $start, $end, $state, $seller_id)
    {
        $this->conn_auctions->begin_transaction();

        try {
            $stmt = $this->conn_auctions->prepare("SELECT 1 FROM listings WHERE title = ?");
            $stmt->bind_param("s", $title);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows > 0) {
                $stmt->close();
                $this->conn_auctions->rollback();
                return $this->generateErrorResponse("Listing title already exists");
            }
            $stmt->close();

            $sql = "INSERT INTO listings (title, location, bedrooms, bathrooms, parking_spaces, amenities, description, image) 
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            $stmt = $this->conn_auctions->prepare($sql);
            $stmt->bind_param("ssssssss", $title, $location, $bedrooms, $bathrooms, $parking, $amenities, $description, $images);

            if (!$stmt->execute()) {
                $stmt->close();
                $this->conn_auctions->rollback();
                return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
            }

            $listing_id = $this->conn_auctions->insert_id;
            $stmt->close();

            $stmt = $this->conn_auctions->prepare("SELECT 1 FROM auctions WHERE auction_name = ?");
            $stmt->bind_param("s", $name);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows > 0) {
                $stmt->close();
                $this->conn_auctions->rollback();
                return $this->generateErrorResponse("Auction name already exists");
            }
            $stmt->close();

            if (!($state === "Waiting" || $state === "Ongoing")) {
                return $this->generateErrorResponse("State must be either Waiting or Ongoing");
            }

            $sql = "INSERT INTO auctions (auction_name, start_date, end_date, listing_id, highest_bid, state, buyer_id, seller_id) 
                    VALUES (?, ?, ?, ?, NULL, ?, NULL, ?)";
            $stmt = $this->conn_auctions->prepare($sql);
            $stmt->bind_param("ssssss", $name, $start, $end, $listing_id, $state, $seller_id);

            if (!$stmt->execute()) {
                $this->conn_auctions->rollback();
                return $this->generateErrorResponse("Failed to execute statement: " . $stmt->error);
            }
            $stmt->close();

            $this->conn_auctions->commit();

            return $this->generateSuccessResponse("Successfully created Auction");
            
        } catch (Exception $e) {
            $this->conn_auctions->rollback();
            return $this->generateErrorResponse("Transaction failed: " . $e->getMessage());
        }
    }

    public function updateAuction($listing_id, $name, $start, $end, $seller_id, $buyer_id, $state)
    {
        $sql = "UPDATE auctions";
        $conditions = [];
        $params = [];
        $types = '';

        if ($name !== null) 
        {
            $conditions[] = "auction_name = ?";
            $params[] = $name;
            $types .= 's';
        }
        if ($start !== null) 
        {
            $conditions[] = "start_date = ?";
            $params[] = $start;
            $types .= 's';
        }
        if ($end !== null) 
        {
            $conditions[] = "end_date = ?";
            $params[] = $end;
            $types .= 's';
        }
        if ($state !== null) 
        {
            $conditions[] = "state = ?";
            $params[] = $state;
            $types .= 's';
        }
        if ($seller_id !== null) 
        {
            $conditions[] = "seller_id = ?";
            $params[] = $seller_id;
            $types .= 's';
        }
        if ($buyer_id !== null) 
        {
            $conditions[] = "buyer_id = ?";
            $params[] = $buyer_id;
            $types .= 's';
        }

        if (count($conditions) > 0) 
        {
            $sql .= " SET " . implode(", ", $conditions);
        }
        $sql .= " WHERE listing_id = ?";
        $params[] = $listing_id;
        $types .= 's';

        $stmt = $this->conn_auctions->prepare($sql);
        if ($stmt === false) 
        {
            return $this->generateErrorResponse("Failed to prepare statement: " . $this->conn_auctions->error);
        }

        $stmt->bind_param($types, ...$params);

        if ($stmt->execute()) 
        {
            return $this->generateSuccessResponse("Successfully updated auctions");
        } 
        else 
        {
            return $this->generateErrorResponse("Failed to update auctions: " . $stmt->error);
        }
    }

    public function getAuctionListings($title , $min_price , $max_price, $location , $bedrooms , $bathrooms , $parking , $amenities)
    {
        $sql = "SELECT * FROM listings";
        $conditions = [];
        $params = [];

        if ($title !== null) 
        {
            $conditions[] = "title LIKE ?";
            $params[] = "%" . $title . "%";
        }
        if ($min_price !== null) 
        {
            $conditions[] = "price >= ?";
            $params[] = $min_price;
        }
        if ($max_price !== null) 
        {
            $conditions[] = "price >= ?";
            $params[] = $max_price;
        }
        if ($location !== null) 
        {
            $conditions[] = "location LIKE ?";
            $params[] = "%" . $location . "%";
        }
        if ($bedrooms !== null) 
        {
            $conditions[] = "bedrooms = ?";
            $params[] = $bedrooms;
        }
        if ($bathrooms !== null) 
        {
            $conditions[] = "bathrooms = ?";
            $params[] = $bathrooms;
        }
        if ($parking !== null) 
        {
            $conditions[] = "parking_spaces = ?";
            $params[] = $parking;
        }
        if ($amenities !== null) 
        {
            $conditions[] = "amenities LIKE ?";
            $params[] = "%" . $amenities . "%";
        }

        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        $stmt = $this->conn_auctions->prepare($sql);
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessListingsResponse($data);
    }

    public function getAuctionFull($name, $start, $end, $state , $title , $min_price , $max_price, $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order , $auction_id)
    {
        $sql = "SELECT * FROM auctions JOIN listings ON listings.listing_id = auctions.listing_id ";
        $conditions = [];
        $params = [];

        if ($name !== null || $title !== null || $location !== null) {
            $orConditions = [];
            if ($name !== null) {
                $orConditions[] = "auction_name LIKE ?";
                $params[] = "%" . $name . "%";
            }
            if ($title !== null) {
                $orConditions[] = "title LIKE ?";
                $params[] = "%" . $title . "%";
            }
            if ($location !== null) {
                $orConditions[] = "location LIKE ?";
                $params[] = "%" . $location . "%";
            }
            if ($amenities !== null) {
                $orConditions[] = "amenities LIKE ?";
                $params[] = "%" . $amenities . "%";
            }
            $conditions[] = "(" . implode(" OR ", $orConditions) . ")";
        }
        if ($start !== null) 
        {
            $conditions[] = "start_date = ?";
            $params[] = $start;
        }
        if ($end !== null) 
        {
            $conditions[] = "end_date = ?";
            $params[] = $end;
        }
        if ($state !== null) 
        {
            $conditions[] = "state = ?";
            $params[] = $state;
        }
        if ($min_price !== null) 
        {
            $conditions[] = "highest_bid >= ?";
            $params[] = $min_price;
        }
        if ($max_price !== null) 
        {
            $conditions[] = "highest_bid <= ?";
            $params[] = $max_price;
        }
        if ($bedrooms !== null) 
        {
            $conditions[] = "bedrooms = ?";
            $params[] = $bedrooms;
        }
        if ($bathrooms !== null) 
        {
            $conditions[] = "bathrooms = ?";
            $params[] = $bathrooms;
        }
        if ($parking !== null) 
        {
            $conditions[] = "parking_spaces = ?";
            $params[] = $parking;
        }
        if ($auction_id !== null) 
        {
            $conditions[] = "auction_id = ?";
            $params[] = $auction_id;
        }
        
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        if ($sort !== null) {
            $allowedSortFields = ['auction_name', 'start_date', 'end_date', 'highest_bid', 'title', 'location'];
            if (in_array($sort, $allowedSortFields)) {
                $sql .= " ORDER BY " . $sort;
                if ($order !== null && ($order === 'ASC' || $order === 'DESC')) {
                    $sql .= " " . $order;
                }
            }
        }
        if($limit !== null)
        {
            $sql .= " LIMIT ?";
            $params[] = $limit;
        }
        $stmt = $this->conn_auctions->prepare($sql);
        
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessListingsResponse($data);
    }

    public function getUserBids($user_id , $name, $start, $end, $state , $title , $min_price , $max_price, $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order)
    {
        $sql = "SELECT * FROM auctions JOIN listings ON listings.listing_id = auctions.listing_id ";
        $conditions = [];
        $params = [];

        if ($name !== null || $title !== null || $location !== null) {
            $orConditions = [];
            if ($name !== null) {
                $orConditions[] = "auction_name LIKE ?";
                $params[] = "%" . $name . "%";
            }
            if ($title !== null) {
                $orConditions[] = "title LIKE ?";
                $params[] = "%" . $title . "%";
            }
            if ($location !== null) {
                $orConditions[] = "location LIKE ?";
                $params[] = "%" . $location . "%";
            }
            if ($amenities !== null) {
                $orConditions[] = "amenities LIKE ?";
                $params[] = "%" . $amenities . "%";
            }
            $conditions[] = "(" . implode(" OR ", $orConditions) . ")";
        }
        if($user_id !== null)
        {
            $conditions[] = "buyer_id = ?";
            $params[] = $user_id;
        }
        if ($start !== null) 
        {
            $conditions[] = "start_date = ?";
            $params[] = $start;
        }
        if ($end !== null) 
        {
            $conditions[] = "end_date = ?";
            $params[] = $end;
        }
        if ($state !== null) 
        {
            $conditions[] = "state = ?";
            $params[] = $state;
        }
        if ($min_price !== null) 
        {
            $conditions[] = "highest_bid >= ?";
            $params[] = $min_price;
        }
        if ($max_price !== null) 
        {
            $conditions[] = "highest_bid <= ?";
            $params[] = $max_price;
        }
        if ($bedrooms !== null) 
        {
            $conditions[] = "bedrooms = ?";
            $params[] = $bedrooms;
        }
        if ($bathrooms !== null) 
        {
            $conditions[] = "bathrooms = ?";
            $params[] = $bathrooms;
        }
        if ($parking !== null) 
        {
            $conditions[] = "parking_spaces = ?";
            $params[] = $parking;
        }
        
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        if ($sort !== null) {
            $allowedSortFields = ['auction_name', 'start_date', 'end_date', 'highest_bid', 'title', 'location'];
            if (in_array($sort, $allowedSortFields)) {
                $sql .= " ORDER BY " . $sort;
                if ($order !== null && ($order === 'ASC' || $order === 'DESC')) {
                    $sql .= " " . $order;
                }
            }
        }
        if($limit !== null)
        {
            $sql .= " LIMIT ?";
            $params[] = $limit;
        }
        $stmt = $this->conn_auctions->prepare($sql);
        
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessListingsResponse($data);
    }

    public function getUserAuctions($user_id , $name, $start, $end, $state , $title , $min_price , $max_price, $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order)
    {
        $sql = "SELECT * FROM auctions JOIN listings ON listings.listing_id = auctions.listing_id ";
        $conditions = [];
        $params = [];

        if ($name !== null || $title !== null || $location !== null) {
            $orConditions = [];
            if ($name !== null) {
                $orConditions[] = "auction_name LIKE ?";
                $params[] = "%" . $name . "%";
            }
            if ($title !== null) {
                $orConditions[] = "title LIKE ?";
                $params[] = "%" . $title . "%";
            }
            if ($location !== null) {
                $orConditions[] = "location LIKE ?";
                $params[] = "%" . $location . "%";
            }
            if ($amenities !== null) {
                $orConditions[] = "amenities LIKE ?";
                $params[] = "%" . $amenities . "%";
            }
            $conditions[] = "(" . implode(" OR ", $orConditions) . ")";
        }
        if($user_id !== null)
        {
            $conditions[] = "seller_id = ?";
            $params[] = $user_id;
        }
        if ($start !== null) 
        {
            $conditions[] = "start_date = ?";
            $params[] = $start;
        }
        if ($end !== null) 
        {
            $conditions[] = "end_date = ?";
            $params[] = $end;
        }
        if ($state !== null) 
        {
            $conditions[] = "state = ?";
            $params[] = $state;
        }
        if ($min_price !== null) 
        {
            $conditions[] = "highest_bid >= ?";
            $params[] = $min_price;
        }
        if ($max_price !== null) 
        {
            $conditions[] = "highest_bid <= ?";
            $params[] = $max_price;
        }
        if ($bedrooms !== null) 
        {
            $conditions[] = "bedrooms = ?";
            $params[] = $bedrooms;
        }
        if ($bathrooms !== null) 
        {
            $conditions[] = "bathrooms = ?";
            $params[] = $bathrooms;
        }
        if ($parking !== null) 
        {
            $conditions[] = "parking_spaces = ?";
            $params[] = $parking;
        }
        
        if (count($conditions) > 0) 
        {
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
        if ($sort !== null) {
            $allowedSortFields = ['auction_name', 'start_date', 'end_date', 'highest_bid', 'title', 'location'];
            if (in_array($sort, $allowedSortFields)) {
                $sql .= " ORDER BY " . $sort;
                if ($order !== null && ($order === 'ASC' || $order === 'DESC')) {
                    $sql .= " " . $order;
                }
            }
        }
        if($limit !== null)
        {
            $sql .= " LIMIT ?";
            $params[] = $limit;
        }
        $stmt = $this->conn_auctions->prepare($sql);
        
        if (!empty($params)) 
        {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }
        $stmt->execute();
        $result = $stmt->get_result();
        $data = $result->fetch_all(MYSQLI_ASSOC);

        $stmt->close();

        return $this->generateSuccessListingsResponse($data);
    }

    public function createAuctionListings($title , $price , $location , $bedrooms , $bathrooms , $parking , $amenities , $description , $images)
    {
        $stmt = $this->conn_auctions->prepare("SELECT * FROM listings WHERE title = ?");
        $stmt->bind_param("s", $title);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            return $this->generateErrorResponse("Listing title already exists");
        }

        $sql = "INSERT IGNORE INTO `listings` (`listing_id`, `title`, `price`, `location`, `bedrooms`, `bathrooms`, `parking_spaces`, `amenities`, `description`, `image`) 
        VALUES (NULL , ? , ? , ? , ? , ? , ? , ? , ? , ?);";
        $stmt = $this->conn_auctions->prepare($sql);
        $stmt->bind_param("sssssssss",$title , $price , $location , $bedrooms , $bathrooms , $parking , $amenities , $description , $images);
        $stmt->execute();

        return $this->generateSuccessResponse("Successfully created listing");
    }

    public function auctionRegister($name , $surname , $email , $password)
    {
        if(empty($name))
        {
            return $this->generateErrorResponse("Missing Name");
        }
        if(empty($surname))
        {
            return $this->generateErrorResponse("Missing Surname");
        }

        if(empty($email))
        {
            return $this->generateErrorResponse("Missing Email");
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

        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) 
        {
            return $this->generateErrorResponse("Invalid email format");
        }

        $stmt = $this->conn_auctions->prepare("SELECT * FROM users WHERE email = ?");
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            return $this->generateErrorResponse("User already exists");
        }

        $sql = "INSERT INTO `users` (`name`, `surname`, `email`, `password`) VALUES (?, ?, ?, ? )";
        $stmt = $this->conn_auctions->prepare($sql);
        $apiKey = $this->generateApiKey();

        $salt = $this->generateSalt($email);
        $salt_pass = $password.$salt;
        $hashedPassword = password_hash($salt_pass, PASSWORD_DEFAULT);
        $stmt->bind_param("ssss", $name, $surname, $email, $hashedPassword);
        $stmt->execute();

        return $this->generateSuccessResponse("User registered");
    }

    public function auctionLogin($email , $password)
    {
        $sql = "SELECT * FROM users WHERE email = ?";
        $stmt = $this->conn_auctions->prepare($sql);
        $stmt->bind_param("s",$email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            while ($row = $result->fetch_assoc()) 
            {
                $salt = $this->generateSalt($email);
                $saltedPassword = $password.$salt;
                if(password_verify($saltedPassword , $row['password']))
                {
                    return $this->generateSuccessResponse($row['user_id']);
                }
                return $this->generateErrorResponse("Password incorrect");
            }
        }

        return $this->generateErrorResponse("Email does not exist");
    }

    public function bidOnAuction($auction_id , $user_id , $bid)
    {
        $stmt = $this->conn_auctions->prepare("SELECT * FROM auctions WHERE auction_id = ?");
        $stmt->bind_param("s", $auction_id);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) 
        {
            while ($row = $result->fetch_assoc()) 
            {
                if($row['state'] == "Waiting" || $row['state'] == "Done")
                {
                    return $this->generateErrorResponse("Can't bid on this auction");
                }
                if($row['highest_bid'] >= $bid)
                {
                    return $this->generateErrorResponse("Must bid higher than current bid");
                }
                $stmt = $this->conn_auctions->prepare("UPDATE auctions SET buyer_id = ? , highest_bid = ? WHERE auction_id = ?");
                $stmt->bind_param("sss", $user_id , $bid , $auction_id);
                $stmt->execute();
                return $this->generateSuccessListingsResponse("Correctly bid on auction");
            }
        }
        return $this->generateErrorResponse("Auction doesn't exist");
    }
}


$api = new API();
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        $postData = json_decode(file_get_contents("php://input"), true);
        if (isset($postData["type"]) && $postData["type"] == "Register" && isset($postData["name"]) && isset($postData["surname"]) && isset($postData["email"]) && isset($postData["password"])) 
        {
            $response = $api->registerUser($postData["name"], $postData["surname"], $postData["email"], $postData["password"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "Login")
        {
            $response = $api->loginUser($postData["email"] , $postData["password"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAllAgents")
        {
            $response = $api->getAgents($postData["limit"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAllListings")
        {
            $limit = isset($postData["limit"]) ? $postData["limit"] : 10;
            $sort = isset($postData["sort"]) ? $postData["sort"] : 'id';
            $order = isset($postData["order"]) ? $postData["order"] : 'ASC';
            $fuzzy = isset($postData["fuzzy"]) ? $postData["fuzzy"] : true;
            $search = isset($postData["search"]) ? $postData["search"] : '';
            $return = isset($postData["return"]) ? $postData["return"] : '*';
            $response = $api->getListings($postData["apikey"], $postData["type"], $limit, $sort, $order, $fuzzy, $search, $return);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetFavourites")
        {
            $limit = isset($postData["limit"]) ? $postData["limit"] : 10;
            $sort = isset($postData["sort"]) ? $postData["sort"] : 'id';
            $order = isset($postData["order"]) ? $postData["order"] : 'ASC';
            $fuzzy = isset($postData["fuzzy"]) ? $postData["fuzzy"] : true;
            $search = isset($postData["search"]) ? $postData["search"] : '';
            $return = isset($postData["return"]) ? $postData["return"] : '*';
            $response = $api->getFavourites($postData["apikey"], $limit, $sort, $order, $fuzzy, $return, $search);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "AddFavourites" && isset($postData["apikey"]) && isset($postData["listings_id"]))
        {
            $response = $api->addFavourite($postData["apikey"], $postData["listings_id"]);
            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "RemoveFavourites" && isset($postData["apikey"]) && isset($postData["listings_id"]))
        {
            $response = $api->removeFavourite($postData["listings_id"], $postData["apikey"]);
            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetTheme" && isset($postData["apikey"]))
        {
            $response = $api->getTheme($postData["apikey"]);
            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "SetTheme" && isset($postData["theme"]))
        {
            $response = $api->setTheme($postData["apikey"] , $postData["theme"]);
            echo($response);
        } 
        else if(isset($postData["type"]) && $postData["type"] == "GetPreferences" && isset($postData["apikey"]))
        {
            $response = $api->getPreferences($postData["apikey"]);
            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "SetPreferences" && isset($postData["apikey"]))
        {
            $limit = isset($postData["limit"]) ? $postData["limit"] : 10;
            $sort = isset($postData["sort"]) ? $postData["sort"] : 'id';
            $order = isset($postData["order"]) ? $postData["order"] : 'ASC';
            $search = isset($postData["search"]) ? $postData["search"] : '';
            $return = isset($postData["return"]) ? $postData["return"] : '*';
            $fuzzy = isset($postData["fuzzy"]) ? $postData["fuzzy"] : true;
            $response = $api->SetPreferences($postData["apikey"],$limit,$sort,$order,$return,$search);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAuctions")
        {
            $name = isset($postData["name"]) ? $postData["name"] : null;
            $start = isset($postData["startDate"]) ? $postData["startDate"] : null;
            $end = isset($postData["endDate"]) ? $postData["endDate"] : null;
            $state = isset($postData["state"]) ? $postData["state"] : null;
            $response = $api->getAuctions($name , $start , $end , $state);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "CreateAuctions" && isset($postData["name"]) && isset($postData["startDate"]) && isset($postData["endDate"]) && isset($postData["state"]) && isset($postData["listingID"]) && isset($postData["sellerID"]))
        {
            $response = $api->createAuction($postData["name"] , $postData["startDate"] , $postData["endDate"], $postData["listingID"] , $postData["state"] , $postData["sellerID"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "CreateAuctionFull" && isset($postData["title"]) && isset($postData["location"]) && isset($postData["bedrooms"]) && isset($postData["bathrooms"]) && isset($postData["parking_spaces"]) && isset($postData["amenities"]) && isset($postData["description"]) && isset($postData["image"]) && isset($postData["name"]) && isset($postData["startDate"]) && isset($postData["endDate"]) && isset($postData["state"]) && isset($postData["sellerID"]))
        {
            $response = $api->createAuctionFull($postData["title"] , $postData["location"] , $postData["bedrooms"] , $postData["bathrooms"] , $postData["parking_spaces"] , $postData["amenities"], $postData["description"] , $postData["image"] , $postData["name"],$postData["startDate"] , $postData["endDate"],$postData["state"] , $postData["sellerID"]);
            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "UpdateAuctions" && isset($postData["listingID"]))
        {
            $name = isset($postData["name"]) ? $postData["name"] : null;
            $start = isset($postData["startDate"]) ? $postData["startDate"] : null;
            $end = isset($postData["endDate"]) ? $postData["endDate"] : null;
            $seller = isset($postData["sellerID"]) ? $postData["sellerID"] : null;
            $buyer = isset($postData["buyerID"]) ? $postData["buyerID"] : null;
            $state = isset($postData["state"]) ? $postData["state"] : null;
            $response = $api->updateAuction($postData["listingID"] , $name, $start , $end , $seller, $buyer,  $state );

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAuctionListings")
        {
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $min_price = isset($postData["min_price"]) ? $postData["min_price"] : null;
            $max_price = isset($postData["max_price"]) ? $postData["max_price"] : null;
            $location = isset($postData["location"]) ? $postData["location"] : null;
            $bedrooms = isset($postData["bedrooms"]) ? $postData["bedrooms"] : null;
            $bathrooms = isset($postData["bathrooms"]) ? $postData["bathrooms"] : null;
            $parking = isset($postData["parking_spaces"]) ? $postData["parking_spaces"] : null;
            $amenities = isset($postData["amenities"]) ? $postData["amenities"] : null;

            $response = $api->getAuctionListings($title , $min_price , $max_price , $location , $bedrooms , $bathrooms , $parking , $amenities );

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetUserBids" && isset($postData["user_id"]))
        {
            $name = isset($postData["name"]) ? $postData["name"] : null;
            $start = isset($postData["startDate"]) ? $postData["startDate"] : null;
            $end = isset($postData["endDate"]) ? $postData["endDate"] : null;
            $state = isset($postData["state"]) ? $postData["state"] : null;
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $min_price = isset($postData["min_price"]) ? $postData["min_price"] : null;
            $max_price = isset($postData["max_price"]) ? $postData["max_price"] : null;
            $location = isset($postData["location"]) ? $postData["location"] : null;
            $bedrooms = isset($postData["bedrooms"]) ? $postData["bedrooms"] : null;
            $bathrooms = isset($postData["bathrooms"]) ? $postData["bathrooms"] : null;
            $parking = isset($postData["parking_spaces"]) ? $postData["parking_spaces"] : null;
            $amenities = isset($postData["amenities"]) ? $postData["amenities"] : null;
            $limit = isset($postData["limit"]) ? $postData["limit"] : null;
            $sort = isset($postData["sort"]) ? $postData["sort"] : null;
            $order = isset($postData["order"]) ? $postData["order"] : null;
            $response = $api->getUserBids($postData["user_id"] , $name , $start , $end , $state , $title , $min_price , $max_price , $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetUserAuctions" && isset($postData["user_id"]))
        {
            $name = isset($postData["name"]) ? $postData["name"] : null;
            $start = isset($postData["startDate"]) ? $postData["startDate"] : null;
            $end = isset($postData["endDate"]) ? $postData["endDate"] : null;
            $state = isset($postData["state"]) ? $postData["state"] : null;
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $min_price = isset($postData["min_price"]) ? $postData["min_price"] : null;
            $max_price = isset($postData["max_price"]) ? $postData["max_price"] : null;
            $location = isset($postData["location"]) ? $postData["location"] : null;
            $bedrooms = isset($postData["bedrooms"]) ? $postData["bedrooms"] : null;
            $bathrooms = isset($postData["bathrooms"]) ? $postData["bathrooms"] : null;
            $parking = isset($postData["parking_spaces"]) ? $postData["parking_spaces"] : null;
            $amenities = isset($postData["amenities"]) ? $postData["amenities"] : null;
            $limit = isset($postData["limit"]) ? $postData["limit"] : null;
            $sort = isset($postData["sort"]) ? $postData["sort"] : null;
            $order = isset($postData["order"]) ? $postData["order"] : null;
            $response = $api->getUserAuctions($postData["user_id"] , $name , $start , $end , $state , $title , $min_price , $max_price , $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "GetAuctionsFull")
        {
            $name = isset($postData["name"]) ? $postData["name"] : null;
            $start = isset($postData["startDate"]) ? $postData["startDate"] : null;
            $end = isset($postData["endDate"]) ? $postData["endDate"] : null;
            $state = isset($postData["state"]) ? $postData["state"] : null;
            $title = isset($postData["title"]) ? $postData["title"] : null;
            $min_price = isset($postData["min_price"]) ? $postData["min_price"] : null;
            $max_price = isset($postData["max_price"]) ? $postData["max_price"] : null;
            $location = isset($postData["location"]) ? $postData["location"] : null;
            $bedrooms = isset($postData["bedrooms"]) ? $postData["bedrooms"] : null;
            $bathrooms = isset($postData["bathrooms"]) ? $postData["bathrooms"] : null;
            $parking = isset($postData["parking_spaces"]) ? $postData["parking_spaces"] : null;
            $amenities = isset($postData["amenities"]) ? $postData["amenities"] : null;
            $limit = isset($postData["limit"]) ? $postData["limit"] : null;
            $sort = isset($postData["sort"]) ? $postData["sort"] : null;
            $order = isset($postData["order"]) ? $postData["order"] : null;
            $auction_id = isset($postData["auction_id"]) ? $postData["auction_id"] : null;

            $response = $api->getAuctionFull($name , $start , $end , $state , $title , $min_price , $max_price , $location , $bedrooms , $bathrooms , $parking , $amenities , $limit , $sort , $order , $auction_id);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "CreateAuctionListings" && isset($postData["title"]) && isset($postData["price"]) && isset($postData["location"]) && isset($postData["bedrooms"]) && isset($postData["bathrooms"]) && isset($postData["parking_spaces"]) && isset($postData["amenities"]) && isset($postData["description"]) && isset($postData["image"]))
        {
            $response = $api->createAuctionListings($postData["title"], $postData["price"] , $postData["location"] , $postData["bedrooms"] ,$postData["bathrooms"] , $postData["parking_spaces"] , $postData["amenities"] , $postData["description"] , $postData["image"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "AuctionRegister" && isset($postData["name"]) && isset($postData["surname"]) && isset($postData["email"]) && isset($postData["password"]))
        {
            $response = $api->auctionRegister($postData["name"], $postData["surname"] , $postData["email"] , $postData["password"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "AuctionLogin" && isset($postData["email"]) && isset($postData["password"]))
        {
            $response = $api->auctionLogin($postData["email"] , $postData["password"]);

            echo($response);
        }
        else if(isset($postData["type"]) && $postData["type"] == "BidOnAuction" && isset($postData["auction_id"]) && isset($postData["user_id"]) && isset($postData["bid_amount"]))
        {
            $response = $api->bidOnAuction($postData["auction_id"] , $postData["user_id"] , $postData["bid_amount"]);

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
