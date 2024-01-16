package Screens.AdminScreens;

import Screens.AdminScreens.Enums.EEntity;
import Screens.AdminScreens.Interfaces.EntityListCallback;

import javax.swing.*;
import javax.swing.event.ChangeListener;
import java.util.ArrayList;
import java.util.List;

public class AdminScreen extends JFrame {
    private EntityListScreen userListScreen, barberListScreen, serviceListScreen;
    private final JTabbedPane tabbedPane;
    public AdminScreen() {
        setTitle("BarberShop Admin");
        setSize(1000, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        tabbedPane = new JTabbedPane();

        List<String> columnNames = new ArrayList<String>();

        userListScreen = new EntityListScreen(EEntity.USER);
        barberListScreen = new EntityListScreen(EEntity.BARBER);
        serviceListScreen = new EntityListScreen(EEntity.SERVICE);

        tabbedPane.addTab("Users", userListScreen);
        tabbedPane.addTab("Barbers", barberListScreen);
        tabbedPane.addTab("Services", serviceListScreen);
        tabbedPane.addTab("Appointments", null);

        SetCallbacks();
        ChangeListener changeListener = changeEvent -> {
            JTabbedPane sourceTabbedPane = (JTabbedPane) changeEvent.getSource();
            UpdatePane(sourceTabbedPane);

        };
        tabbedPane.addChangeListener(changeListener);
        add(tabbedPane);

        setVisible(true);
    }

    void UpdatePane(JTabbedPane pane) {
        int index = pane.getSelectedIndex();
        switch (index) {
            case 0 -> {
                userListScreen = new EntityListScreen(EEntity.USER);
                pane.setComponentAt(index, userListScreen);
            }
            case 1 -> {
                barberListScreen = new EntityListScreen(EEntity.BARBER);
                pane.setComponentAt(index, barberListScreen);
            }
            case 2 -> {
                serviceListScreen = new EntityListScreen(EEntity.SERVICE);
                pane.setComponentAt(index, serviceListScreen);
            }
        };
        SetCallbacks();
    }

    void SetCallbacks() {
        userListScreen.SetCallback(new EntityListCallback() {
            @Override
            public void EntityUpdated() {
                UpdatePane(tabbedPane);
            }
        });

        barberListScreen.SetCallback(new EntityListCallback() {
            @Override
            public void EntityUpdated() {
                UpdatePane(tabbedPane);
            }
        });

        serviceListScreen.SetCallback(new EntityListCallback() {
            @Override
            public void EntityUpdated() {
                UpdatePane(tabbedPane);
            }
        });
    }

}