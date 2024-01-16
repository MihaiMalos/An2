package Screens.AdminScreens;

import Models.*;
import Screens.AdminScreens.Interfaces.ViewEntityCallback;
import Screens.DbUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class ViewEntityScreen extends JPanel {
    private Entity entity;
    private GridBagConstraints gbc;
    private ViewEntityCallback callback;


    public ViewEntityScreen(Entity entity) {
        super(new GridBagLayout());
        this.entity = entity;

        gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        AddFields();

    }
    private void AddFields() {
        if (entity instanceof User) { AddUserFields(); }
        else if (entity instanceof Barber) {AddBarberFields();}
        else if (entity instanceof Service) {AddServiceFields();}
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

        InitField("Username", username, 0);
        InitField("First Name", firstName, 1);
        InitField("Last Name", lastName, 2);
        InitField("Phone Number", phoneNumber, 3);
        InitField("Role", roles, 4);
        InitButtons(update, cancel, 6);



        if (user.GetId() != 0) {
            username.setText(user.getUsername());
            firstName.setText(user.getFirstName());
            lastName.setText(user.getLastName());
            phoneNumber.setText(user.getPhoneNumber());
            roles.setSelectedItem(user.getRole().getRoleName());
        } else {
            InitField("Password", password, 5);
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

    private void AddBarberFields() {
        Barber barber = (Barber) entity;

        JTextField firstName = new JTextField();
        JTextField lastName = new JTextField();
        JTextField phoneNumber = new JTextField();
        JButton update = new JButton("Update");
        JButton cancel = new JButton("Cancel");

        InitField("First Name", firstName, 1);
        InitField("Last Name", lastName, 2);
        InitField("Phone Number", phoneNumber, 3);
        InitButtons(update, cancel, 4);



        if (barber.GetId() != 0) {
            firstName.setText(barber.getFirstName());
            lastName.setText(barber.getLastName());
            phoneNumber.setText(barber.getPhoneNumber());
        }

        update.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                barber.setFirstName(firstName.getText());
                barber.setLastName(lastName.getText());
                barber.setPhoneNumber(phoneNumber.getText());

                if (barber.GetId() != 0) {
                    DbUtils.UpdateBarber(barber);
                }
                else {
                    if (!DbUtils.CreateBarber(
                            firstName.getText(),
                            lastName.getText(),
                            phoneNumber.getText()
                    ))
                    {
                        JOptionPane.showMessageDialog(null, "Barber already exists");
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

    private void AddServiceFields() {
        Service service = (Service) entity;

        JTextField serviceName = new JTextField();
        JTextField price = new JTextField();
        JButton update = new JButton("Update");
        JButton cancel = new JButton("Cancel");

        InitField("Service Name", serviceName, 1);
        InitField("Price", price, 2);
        InitButtons(update, cancel, 3);

        if (service.GetId() != 0) {
            serviceName.setText(service.getServiceName());
            price.setText(Double.toString(service.getPrice()));
        }

        update.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                service.setServiceName(serviceName.getText());
                service.setPrice(Double.parseDouble(price.getText()));

                if (service.GetId() != 0) {
                    DbUtils.UpdateService(service);
                }
                else {
                    if (!DbUtils.CreateService(
                            serviceName.getText(),
                            Double.parseDouble(price.getText())
                    ))
                    {
                        JOptionPane.showMessageDialog(null, "Service already exists");
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

    private void InitField(String text, Component field, int y) {
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
