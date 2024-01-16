package Screens;

import Models.Barber;
import Models.Role;
import Models.Service;
import Models.User;
import Screens.AdminScreens.Enums.EEntity;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DbUtils {

    private static String connectionUrl = "jdbc:sqlserver://localhost:1433;database=dbBarberShop;user=sa1;password=1q2w3e;encrypt=true;trustServerCertificate=true";
    static {
        // Load the SQL Server JDBC driver
        try {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection GetConnection() throws SQLException {
        return DriverManager.getConnection(connectionUrl);
    }

    public static void CloseConnection(Connection connection) {
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static boolean CreateUser(String username, String password, String firstName, String lastName, String phoneNumber, int roleId) {
        Connection connection = null;
        boolean result = true;
        String storedProcedureCall = "{CALL sp_RegisterUser(?, ?, ?, ?, ?, ?)}";
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setInt(1, roleId);
            callableStatement.setString(2, username);
            callableStatement.setString(3, password);
            callableStatement.setString(4, firstName);
            callableStatement.setString(5, lastName);
            callableStatement.setString(6, phoneNumber);

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
        return result;
    }

    public static boolean CreateBarber(String firstName, String lastName, String phoneNumber) {
        Connection connection = null;
        String storedProcedureCall = "{CALL sp_RegisterBarber(?, ?, ?)}";
        boolean result = true;
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setString(1, firstName);
            callableStatement.setString(2, lastName);
            callableStatement.setString(3, phoneNumber);

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
        return result;
    }

    public static boolean CreateService(String serviceName, Double price) {
        Connection connection = null;
        String storedProcedureCall = "{CALL sp_RegisterService(?, ?)}";
        boolean result = true;
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setString(1, serviceName);
            callableStatement.setDouble(2, price);

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
        return result;
    }

    public static void UpdateUser(User user) {
        Connection connection = null;
        boolean result = true;
        String storedProcedureCall = "{CALL sp_UpdateUser(?, ?, ?, ?, ?, ?)}";
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setInt(1, user.GetId());
            callableStatement.setInt(2, user.getRole().GetId());
            callableStatement.setString(3, user.getUsername());
            callableStatement.setString(4, user.getFirstName());
            callableStatement.setString(5, user.getLastName());
            callableStatement.setString(6, user.getPhoneNumber());

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
    }

    public static void UpdateBarber(Barber barber) {
        Connection connection = null;
        boolean result = true;
        String storedProcedureCall = "{CALL sp_UpdateBarber(?, ?, ?, ?)}";
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setInt(1, barber.GetId());
            callableStatement.setString(2, barber.getFirstName());
            callableStatement.setString(3, barber.getLastName());
            callableStatement.setString(4, barber.getPhoneNumber());

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
    }

    public static void UpdateService(Service service) {
        Connection connection = null;
        boolean result = true;
        String storedProcedureCall = "{CALL sp_UpdateService(?, ?, ?)}";
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setInt(1, service.GetId());
            callableStatement.setString(2, service.getServiceName());
            callableStatement.setDouble(3, service.getPrice());

            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
    }

    public static void DeleteEntity(int id, EEntity entityType) {
        Connection connection = null;
        boolean result = true;
        String storedProcedureCall = switch (entityType) {
            case USER -> "{CALL sp_DeleteUser(?)}";
            case BARBER ->  "{CALL sp_DeleteBarber(?)}";
            case SERVICE -> "{CALL sp_DeleteService(?)}";
        };
        try {
            connection = GetConnection();
            CallableStatement callableStatement = connection.prepareCall(storedProcedureCall);

            callableStatement.setInt(1, id);
            callableStatement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            result = false;
        } finally {
            CloseConnection(connection);
        }
    }

    public static User GetAuthenticatedUser(String username, String password)
    {
        List<User> userList = GetAllUsers(true);
        for (User user : userList)
        {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }
    public static List<Role> GetAllRoles()
    {
        List<Role> roleList = new ArrayList<>();
        Connection connection = null;
        try {
            connection = GetConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("sp_SelectAllRoles");

            while (resultSet.next()) {
                    Role role = new Role(
                            resultSet.getInt("RoleId"),
                            resultSet.getString("RoleName")
                    );
                    roleList.add(role);
            }

        } catch(SQLException e) {
            e.printStackTrace();
        }
        return roleList;
    }
    public static List<User> GetAllUsers(boolean activeOnly)
    {
        List<User> userList = new ArrayList<>();
        Connection connection = null;
        try {
            connection = GetConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("sp_SelectAllUsers");

            while (resultSet.next()) {
                if (resultSet.getBoolean("Active") || !activeOnly) {
                    Role userRole;
                    for (Role role : GetAllRoles())
                    {
                        if (role.GetId() == resultSet.getInt("RoleId"))
                        {
                            User user = new User(
                                    resultSet.getInt("UserId"),
                                    role,
                                    resultSet.getString("Username"),
                                    resultSet.getString("Password"),
                                    resultSet.getString("FirstName"),
                                    resultSet.getString("LastName"),
                                    resultSet.getString("PhoneNumber"),
                                    resultSet.getBoolean("Active")
                            );
                            userList.add(user);
                        }
                    }
                }
            }

        } catch(SQLException e) {
            e.printStackTrace();
        }
        return userList;
    }
    public static List<Service> GetAllServices(boolean activeOnly)
    {
        List<Service> serviceList = new ArrayList<>();
        Connection connection = null;
        try {
            connection = GetConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("sp_SelectAllServices");

            while (resultSet.next()) {
                if (resultSet.getBoolean("Active") || !activeOnly) {
                    Service service = new Service(
                            resultSet.getInt("ServiceId"),
                            resultSet.getString("ServiceName"),
                            resultSet.getDouble("Price"),
                            resultSet.getBoolean("Active")
                    );
                    serviceList.add(service);
                }
            }

        } catch(SQLException e) {
            e.printStackTrace();
        }
        return serviceList;
    }

    public static List<Barber> GetAllBarbers(boolean activeOnly)
    {
        List<Barber> barberList = new ArrayList<>();
        Connection connection = null;
        try {
            connection = GetConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("sp_SelectAllBarbers");

            while (resultSet.next()) {
                if (resultSet.getBoolean("Active") || !activeOnly) {
                    Barber barber = new Barber(
                            resultSet.getInt("BarberId"),
                            resultSet.getString("FirstName"),
                            resultSet.getString("LastName"),
                            resultSet.getString("PhoneNumber"),
                            resultSet.getBoolean("Active")
                    );
                    barberList.add(barber);
                }
            }

        } catch(SQLException e) {
            e.printStackTrace();
        }
        return barberList;
    }

}