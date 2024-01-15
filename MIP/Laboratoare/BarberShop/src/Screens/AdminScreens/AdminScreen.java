package Screens.AdminScreens;

import Models.Barber;
import Models.Service;
import Models.User;
import Screens.DbUtils;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.util.ArrayList;
import java.util.List;

public class AdminScreen extends JFrame {
    private EntityListScreen userListScreen, barberListScreen, serviceListScreen;
    public AdminScreen() {
        setTitle("BarberShop Admin");
        setSize(1000, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();

        List<String> columnNames = new ArrayList<String>();

        userListScreen = User.GetUserListScreen(DbUtils.GetAllUsers(true));
        barberListScreen = Barber.GetBarberListScreen(DbUtils.GetAllBarbers(true));
        serviceListScreen = Service.GetServiceListScreen(DbUtils.GetAllServices(true));

        tabbedPane.addTab("Users", userListScreen);
        tabbedPane.addTab("Barbers", barberListScreen);
        tabbedPane.addTab("Services", serviceListScreen);
        tabbedPane.addTab("Appointments", null);

        ChangeListener changeListener = changeEvent -> {
            JTabbedPane sourceTabbedPane = (JTabbedPane) changeEvent.getSource();
            int index = sourceTabbedPane.getSelectedIndex();
                switch (index) {
                case 0 -> userListScreen = User.GetUserListScreen(DbUtils.GetAllUsers(true));
                case 1 -> barberListScreen = Barber.GetBarberListScreen(DbUtils.GetAllBarbers(true));
                case 2 -> serviceListScreen = Service.GetServiceListScreen(DbUtils.GetAllServices(true));
            };
        };
        tabbedPane.addChangeListener(changeListener);
        add(tabbedPane);

        SetListeners();


        setVisible(true);
    }

    private void SetListeners() {
        userListScreen.addEntityActionListener(new EntityActionListener() {
            @Override
            public void onDelete(List<List<String>> data) {
                System.out.println(data);
            }

            @Override
            public void onAdd(int[] data) {

            }
        });

        barberListScreen.addEntityActionListener(new EntityActionListener() {
            @Override
            public void onDelete(List<List<String>> data) {
                System.out.println(data);
            }

            @Override
            public void onAdd(int[] data) {

            }
        });

        serviceListScreen.addEntityActionListener(new EntityActionListener() {
            @Override
            public void onDelete(List<List<String>> data) {
                System.out.println(data);
            }

            @Override
            public void onAdd(int[] data) {

            }
        });
    }
}