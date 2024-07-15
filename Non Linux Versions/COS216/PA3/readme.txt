---------------------------------------------------
|       Using WEBSITE COS 216 u04948123           |
---------------------------------------------------

Post to url: https://wheatley.cs.up.ac.za/u04948123/api.php
use wheatly login details in your authorization headers.


The JSON object:
For users

type-Required-"Register"
name-Required
surname-Required
email-Required
password-Required


email must be correct format
password must be atleast 8 letters, contain uppercase and lowercase , and atleast 1 symbol.
Mixing the password with uppercase and lowercase with symbols with atleast 8 letters will make the password 
much harder to crack since when its hashed it will be alot longer and complex

This is password would be hashed so even if someone finds the password in the the database they cant hack other websites with your login detail.
The password was hashed and then added a salt variable to make it harder to crack.

$salt = bin2hex(random_bytes(16));
$hashedPassword = password_hash($password, PASSWORD_DEFAULT);
$combined = $hashedPassword . $salt;

API would be psuedo random
private function generateApiKey() 
{
    return bin2hex(random_bytes(16));
}



The JSON object:
for Listings

apikey-Required- Registered user's API
type-Required- "GetAllListings"
limit-optional- Between 1 and 500
sort-optional- choose column [’id’, ’title’, ’location’, ’price’, ’bedrooms’, ’bathrooms’, ’parking spaces’]
order-optional- ASC or DESC
fuzzy-optional- fuzzy search should be used or not , default is true
search-optional-JSON object with [’id’, ’title’, ’location’, ’price min’, ’price max’, ’bedrooms’, ’bathrooms’, ’parking spaces’, ’amenities’, ’type’] attributes, type being sale or return
return-Required-Determines which columns to return , all = "*" or [’id’, ’title’, ’location’, ’price’, ’bedrooms’, ’bathrooms’, ’url’, ’parking spaces’, ’amenities’, ’description’, ’type’, ’images’]


