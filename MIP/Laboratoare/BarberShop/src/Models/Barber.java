package Models;

import Screens.AdminScreens.EntityListScreen;

import java.util.ArrayList;
import java.util.List;

public class Barber implements Entity {
    private int barberId;
    private String firstName, lastName, phoneNumber;
    private boolean active;

    public Barber() {}
    public Barber(int barberId, String firstName, String lastName, String phoneNumber, boolean active) {
        this.barberId = barberId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
        this.active = active;
    }

    public static List<String> GetBarberListColumns() {
        List<String> columns = new ArrayList<String>();
        columns.add("First Name");
        columns.add("Last Name");
        columns.add("Phone Number");

        return columns;
    }

    public int GetId() {
        return barberId;
    }

    public void setBarberId(int barberId) {
        this.barberId = barberId;
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

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}
