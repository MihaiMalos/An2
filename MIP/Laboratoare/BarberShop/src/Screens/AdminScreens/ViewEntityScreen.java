package Screens.AdminScreens;

import Models.Entity;
import Models.Role;
import Models.User;
import Screens.DbUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

interface ViewEntityCallback {
    void PanelEnded();
}

public class ViewEntityScreen extends JPanel {
    private Entity entity;
    private GridBagConstraints gbc;
    private ViewEntityCallback callback;


    ViewEntityScreen(Entity entity) {
        super(new GridBagLayout());
        this.entity = entity;

        gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        if (entity instanceof User) { AddUserFields(); }

    }

    private void AddUserFields() {
        User user = (User) entity;

        JTextField username = new JTextField();
        JTextField firstName = new JTextField();
        JTextField lastName = new JTextField();
        JTextField phoneNumber = new JTextField();
        JTextField password = new JTextField();
        JButton update = new JButton("Update");
        JButton cancel = new JButton("Cancel");

        List<String> rolesName = new ArrayList<String>();
        for (Role role : DbUtils.GetAllRoles()) { rolesName.add(role.getRoleName()); }
        String[] finalRoles = rolesName.toArray(new String[0]);
        JComboBox<String> roles = new JComboBox<>(finalRoles);

        InitTextField("Username", username, 0);
        InitTextField("First Name", firstName, 1);
        InitTextField("Last Name", lastName, 2);
        InitTextField("Phone Number", phoneNumber, 3);
        InitComboboxField("Role", roles, 4);
        InitButtons(update, cancel, 6);



        if (user.GetId() != 0) {
            username.setText(user.getUsername());
            firstName.setText(user.getFirstName());
            lastName.setText(user.getLastName());
            phoneNumber.setText(user.getPhoneNumber());
            roles.setSelectedItem(user.getRole().getRoleName());
        } else {
            InitTextField("Password", password, 5);
        }

        update.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                    user.setUsername(username.getText());
                    user.setFirstName(firstName.getText());
                    user.setLastName(lastName.getText());
                    user.setPhoneNumber(phoneNumber.getText());

                    for (Role role : DbUtils.GetAllRoles()) {
                        if (roles.getSelectedItem().equals(role.getRoleName())) {
                            user.setRole(role);
                        }
                    }

                if (user.GetId() != 0) {
                    DbUtils.UpdateUser(user);
                }
                else {
                    if (!DbUtils.CreateUser(
                            username.getText(),
                            password.getText(),
                            firstName.getText(),
                            lastName.getText(),
                            phoneNumber.getText(),
                            user.getRole().GetId()
                            ))
                        {
                            JOptionPane.showMessageDialog(null, "User already exists");
                        }
                }
                callback.PanelEnded();
            }
        });

        cancel.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                callback.PanelEnded();
            }
        });

    }

    private void InitTextField(String text, JTextField field, int y) {
        JLabel label = new JLabel(text + ":");
        gbc.gridx = 0;
        gbc.gridy = y;
        add(label, gbc);

        gbc.gridx = 1;
        field.setPreferredSize(new Dimension(200, 25));
        add(field, gbc);
    }
    private void InitComboboxField(String text, JComboBox<String> field, int y) {
        JLabel label = new JLabel(text + ":");
        gbc.gridx = 0;
        gbc.gridy = y;
        add(label, gbc);

        gbc.gridx = 1;
        field.setPreferredSize(new Dimension(200, 25));
        add(field, gbc);
    }
    private void InitButtons(JButton firstButton, JButton secondButton, int y) {
        firstButton.setPreferredSize(new Dimension(200, 25));
        secondButton.setPreferredSize(new Dimension(200, 25));

        gbc.gridx = 0;
        gbc.gridy = y;
        add(firstButton, gbc);

        gbc.gridx = 1;
        add(secondButton, gbc);
    }

    public void SetCallback(ViewEntityCallback callback) {
        this.callback = callback;
    }


}
