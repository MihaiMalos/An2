import java.sql.*;

public class DbUtils {

    public static int isWorking()
    {
        if(getConnection()==null)
        {
            return 0;
        }

        return 1;
    }

    public static Connection getConnection()
    {
        Connection conn;

        String connectionUrl;

        //connectionUrl = ApplicationProperties.getProperties().getProperty(Constants.CONNECTION_STRING);
        connectionUrl = "jdbc:sqlserver://localhost:1433;database=Musify;user=sa1;password=1q2w3e;encrypt=true;trustServerCertificate=true";

        try
        {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            conn = DriverManager.getConnection(connectionUrl);

            if(conn==null)
            {
                return null;
            }

            Statement statement = conn.createStatement();

            ResultSet resultSet = statement.executeQuery("exec selectAllUsers");
            while (resultSet.next())
            {
                System.out.println(resultSet.getString(2) + " " + resultSet.getString(3));
            }

        }
        catch(Exception ex)
        {
            System.out.println(ex.getMessage());
            return null;
        }
        return conn;
    }

}