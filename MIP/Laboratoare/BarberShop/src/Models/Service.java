package Models;

import Screens.AdminScreens.EntityListScreen;
import Screens.DbUtils;

import java.util.ArrayList;
import java.util.List;

public class Service implements Entity {
    private int serviceId;
    private String serviceName;
    private double price;
    private boolean active;

    public static List<String> GetServiceListColumns() {
        List<String> columns = new ArrayList<String>();
        columns.add("Service");
        columns.add("Price");

        return columns;
    }
    public Service() {}
    public Service(int serviceId, String serviceName, double price, boolean active) {
        this.serviceId = serviceId;
        this.serviceName = serviceName;
        this.price = price;
        this.active = active;
    }

    public int GetId() {
        return serviceId;
    }

    public void setServiceId(int serviceId) {
        this.serviceId = serviceId;
    }

    public String getServiceName() {
        return serviceName;
    }

    public void setServiceName(String serviceName) {
        this.serviceName = serviceName;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}
