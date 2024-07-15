import java.sql.*;

public class main 
{
    public static void main(String[] args) throws ClassNotFoundException, SQLException
    {
        Class.forName("org.mariadb.jdbc.Driver");
        String url = "jdbc:mariadb://localhost:3306/u04948123_sakila";
        String username = "root";
        String password = "mysql_native_password";

        Connection connection = DriverManager.getConnection(url, username, password);
        
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM actor LIMIT 5");

        while(resultSet.next()) {
            System.out.println(resultSet.getString("first_name"));
        }
    }
}
