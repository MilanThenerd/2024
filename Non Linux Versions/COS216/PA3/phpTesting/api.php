<?php
require_once 'config.php';



class API 
{
    private $conn;

    public function __construct() 
    {
        $this->conn = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
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

        $sql = "INSERT INTO `users` (`name`, `surname`, `email`, `password` , `api`) VALUES (?, ?, ?, ? ,?)";
        $stmt = $this->conn->prepare($sql);


        $apiKey = $this->generateApiKey();

        $salt = bin2hex(random_bytes(16));

        $hashedPassword = password_hash($password, PASSWORD_DEFAULT);
        $combined = $hashedPassword . $salt;

        $stmt->bind_param("sssss", $name, $surname, $email, $combined , $apiKey);
        $stmt-> execute();

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


    private function fetchImagesForListings($listings)
    {
        $images = [];
        foreach ($listings as $listing) 
        {
            $ch = curl_init();
            $url = 'https://wheatley.cs.up.ac.za/api/getimage';
            $params = http_build_query([
                'listing_id' => $listing['id']
            ]);
            $fullUrl = $url . '?' . $params;

            curl_setopt($ch, CURLOPT_URL, $fullUrl);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

            $response = curl_exec($ch);

            if ($response === false) 
            {
                $images[] = ["error" => "Error fetching image for listing ID " . $listing['id']];
            } else {
                $responseData = json_decode($response, true);
                if ($responseData && isset($responseData['status']) && $responseData['status'] === "success" && isset($responseData['data']) && is_array($responseData['data'])) 
                {
                    $imageUrls = [];
                    foreach ($responseData['data'] as $imageUrl) 
                    {
                        $imageUrls[] = $imageUrl;
                    }
                    $images[] = ["id" => $listing['id'], "images" => $imageUrls];
                } 
                else 
                {
                    $images[] = ["error" => "Error parsing image response for listing ID " . $listing['id']];
                }
            }
            curl_close($ch);
        }
        return $images;
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
        $originalReturn = $return;
        if ($return === "*" || (is_array($return) && in_array("images", $return))) 
        {
            $fetchImages = true;
            if ($return === "*") 
            {
                $return = ['id', 'title', 'location', 'price', 'bedrooms', 'bathrooms', 'url', 'parking_spaces', 'amenities', 'description', 'type', 'images'];
            }
            $originalReturn = $return;
            if (is_array($return) && ($key = array_search("images", $return)) !== false) 
            {
                unset($return[$key]);
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
        if ($fetchImages) 
        {
            $dataWithImages = $this->fetchImagesForListings($data);
            foreach ($dataWithImages as $key => $listing) 
            {
                $data[$key]['images'] = $listing['images'];
            }
        }
        if (!in_array('id', $originalReturn))
         {
            foreach ($data as &$listing) 
            {
                unset($listing['id']);
            }
        }
        return $this->generateSuccessListingsResponse($data);
    }
}

$api = new API();
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        $postData = json_decode(file_get_contents("php://input"), true);
        if (isset($postData["type"]) && $postData["type"] == "Register" && isset($postData["name"]) && isset($postData["surname"]) && isset($postData["email"]) && isset($postData["password"])) 
        {
            $response = $api->registerUser($postData["name"], $postData["surname"], $postData["email"], $postData["password"]);

            echo $response;
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
