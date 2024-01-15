package Screens.AdminScreens;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

interface EntityActionListener {
    void onDelete(List<List<String>> data);
    void onAdd(int[] data);
}


public class EntityListScreen<E> extends JPanel {
    private EntityActionListener entityActionListener;
    private final JTable table;
    private List<E> entities;

    public EntityListScreen(List<String> columnNames, List<List<String>> data) {
        super(new BorderLayout());

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
                // Add your logic for the "Add" button action here
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (table.getSelectedRowCount() != 0)
                    entityActionListener.onDelete(getSelectedRowsData());
            }
        });

        // Add components to the main panel
        add(buttonPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    public void addEntityActionListener(EntityActionListener listener) {
        this.entityActionListener = listener;
    }

    private List<List<String>> getSelectedRowsData() {
        int[] selectedRows = table.getSelectedRows();
        List<List<String>> selectedRowsData = new ArrayList<>();

        for (int selectedRow : selectedRows) {
            List<String> rowData = new ArrayList<>();

            for (int col = 0; col < table.getColumnCount(); col++) {
                Object cellValue = table.getValueAt(selectedRow, col);
                rowData.add(String.valueOf(cellValue));
            }

            selectedRowsData.add(rowData);
        }

        return selectedRowsData;
    }
}