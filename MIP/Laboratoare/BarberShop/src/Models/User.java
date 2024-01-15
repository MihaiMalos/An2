package Models;

import Screens.AdminScreens.EntityListScreen;

import java.util.ArrayList;
import java.util.List;

public class User implements Entity{
    private int userId;
    private Role role;
    private String username, password, firstName, lastName, phoneNumber;
    private boolean active;
    public User() {}
    public User(int userId, Role role, String username, String password, String firstName, String lastName, String phoneNumber, boolean active) {
        this.userId = userId;
        this.role = role;
        this.username = username;
        this.password = password;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
        this.active = active;
    }


    public static List<String> GetUserListColumns() {
        List<String> columns = new ArrayList<String>();
        columns.add("Username");
        columns.add("First Name");
        columns.add("Last Name");
        columns.add("Phone Number");
        columns.add("Role");

        return columns;
    }
    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public Role getRole() {return role;}

    public void setRole(Role role) {
        this.role = role;
    }

    public int GetId() {return userId;}

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

}
