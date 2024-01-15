package Screens.AdminScreens;

import Models.Barber;
import Models.Service;
import Models.User;
import Screens.DbUtils;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

enum EEntity {
    USER,
    BARBER,
    SERVICE,
}

interface EntityListCallback {
    void EntityUpdated();
}

public class EntityListScreen extends JPanel {
    private JTable table;
    private final EEntity entityType;
    private ViewEntityScreen entityViewScreen;
    private EntityListCallback callback;


    public EntityListScreen(EEntity entityType) {
        super(new BorderLayout());
        this.entityType = entityType;

        entityViewScreen = new ViewEntityScreen(null);
        RefreshTable();
        JScrollPane scrollPane = new JScrollPane(table);
        table.setFillsViewportHeight(true);
        table.putClientProperty("terminateEditOnFocusLost", Boolean.TRUE);

        // Create buttons and add action listeners
        JButton addButton = new JButton("Add");
        JButton deleteButton = new JButton("Delete");

        // Create a panel for buttons and set layout
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
        buttonPanel.add(addButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(10, 0)));
        buttonPanel.add(deleteButton);

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                UpdateEntity();
                updateUI();
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DeleteEntity();
                updateUI();
            }
        });

        // Add components to the main panel
        add(buttonPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(entityViewScreen, BorderLayout.SOUTH);
    }

    List<String> GetColumnNames() {
        List<String> list = new ArrayList<String>();
        switch (entityType) {
            case USER -> list = User.GetUserListColumns();
            case BARBER -> list = Barber.GetBarberListColumns();
            case SERVICE -> list = Service.GetServiceListColumns();
        }
        return list;
    }

    private void UpdateEntity() {
        if (entityType == EEntity.USER) {
            remove(entityViewScreen);
            User currentUser = new User();

            if (table.getSelectedRowCount() > 0) {
                String selectedRowUsername = table.getValueAt(table.getSelectedRow(), 0).toString();

                for (User user : DbUtils.GetAllUsers(true)) {
                    if (selectedRowUsername.equals(user.getUsername()))
                        currentUser = user;
                }
            }

            entityViewScreen = new ViewEntityScreen(currentUser);
            add(entityViewScreen, BorderLayout.SOUTH);

            entityViewScreen.SetCallback(new ViewEntityCallback() {
                @Override
                public void PanelEnded() {
                    remove(entityViewScreen);
                    callback.EntityUpdated();
                    updateUI();
                }
            });
        }
    }

    private void DeleteEntity() {
        if (table.getSelectedRowCount() > 0) {
            List<String> selectedRowsUsers = new ArrayList<>();

            for (int row : table.getSelectedRows())
            {
                String rowUser = table.getValueAt(row, 0).toString();
                for (User user : DbUtils.GetAllUsers(true)) {
                    if (rowUser.equals(user.getUsername())) {
                        DbUtils.DeleteUser(user.GetId());
                        break;
                    }
                }
            }
            callback.EntityUpdated();
        }
    }
    public void RefreshTable() {
        List<String> columnNames = GetColumnNames();
        List<List<String>> data = GetTableData();

        // Create the table
        int numRows = data.size();
        int numColumns = data.get(0).size();
        Object[][] tableData = new Object[numRows][numColumns];

        for (int row = 0; row < numRows; row++) {
            List<String> rowList = data.get(row);
            for (int column = 0; column < numColumns; column++) {
                tableData[row][column] = rowList.get(column);
            }
        }

        DefaultTableModel model = new DefaultTableModel(tableData, columnNames.toArray());
        table = new JTable(model) {
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
    }

    private List<List<String>> GetTableData() {
        List<List<String>> tableData = new ArrayList<List<String>>();
        switch (entityType) {

            case USER -> {
                for (User user : DbUtils.GetAllUsers(true)) {
                    List<String> currentUser = new ArrayList<String>();
                    currentUser.add(user.getUsername());
                    currentUser.add(user.getFirstName());
                    currentUser.add(user.getLastName());
                    currentUser.add(user.getPhoneNumber());
                    currentUser.add(user.getRole().getRoleName());
                    tableData.add(currentUser);
                }
            }
            case BARBER -> {
                for (Barber barber : DbUtils.GetAllBarbers(true)) {
                    List<String> currentBarber = new ArrayList<String>();
                    currentBarber.add(barber.getFirstName());
                    currentBarber.add(barber.getLastName());
                    currentBarber.add(String.valueOf(barber.getPhoneNumber()));
                    tableData.add(currentBarber);
                }
            }
            case SERVICE -> {

                for (Service service : DbUtils.GetAllServices(true)) {
                    List<String> currentUser = new ArrayList<String>();
                    currentUser.add(service.getServiceName());
                    currentUser.add(String.valueOf(service.getPrice()));
                    tableData.add(currentUser);
                }
            }
        }
        return tableData;
    }

    public void SetCallback(EntityListCallback callback) {
        this.callback = callback;
    }

}