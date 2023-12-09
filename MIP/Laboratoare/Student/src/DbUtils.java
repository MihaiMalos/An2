import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DbUtils {

    public static Connection getConnection()
    {
        Connection conn;

        String connectionUrl;

        //connectionUrl = ApplicationProperties.getProperties().getProperty(Constants.CONNECTION_STRING);
        connectionUrl = "jdbc:sqlserver://localhost:1433;database=dbStudentMM;user=sa1;password=1q2w3e;encrypt=true;trustServerCertificate=true";

        try
        {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            conn = DriverManager.getConnection(connectionUrl);

            if(conn==null)
            {
                System.out.println("Failed - conn is null");
                return null;
            }
        }
        catch(Exception ex)
        {
            System.out.println(ex.getMessage());
            return null;
        }
        return conn;
    }

    public static List<Student> GetAllActiveStudents()
    {
        Connection conn = getConnection();

        if(conn==null)
        {
            return null;
        }

        List<Student> students = new ArrayList<Student>();

        try
        {
            Statement statement = conn.createStatement();

            ResultSet rs = statement.executeQuery("spStudentSelectAllActive");

            while (rs.next())
            {
                int studentId = rs.getInt("StudentId");
                String firstName = rs.getString("FirstName");
                String lastName = rs.getString("LastName");
                String cnp = rs.getString("Cnp");
                Student student = new Student(firstName, lastName, cnp);
                students.add(student);
            }
        }
        catch(Exception ex)
        {
            System.out.println(ex.getMessage());
            return null;
        }

        return students;
    }


}