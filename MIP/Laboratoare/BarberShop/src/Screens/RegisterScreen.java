package Screens;

import Screens.LoginScreen;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;

class RegisterScreen extends JFrame {
    JPanel panel;
    GridBagConstraints gbc;
    private final JTextField usernameField, firstNameField, lastNameField, phoneNumberField;
    private final JPasswordField passwordField, retypePasswordField;

    public RegisterScreen() {
        setTitle("Register");
        setSize(500, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null); // Center the window on the screen

        panel = new JPanel(new GridBagLayout());
        add(panel);

        gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        firstNameField = new JTextField();
        lastNameField = new JTextField();
        usernameField = new JTextField();
        phoneNumberField = new JTextField();
        passwordField = new JPasswordField();
        retypePasswordField = new JPasswordField();

        InitField("First Name", firstNameField, 0);
        InitField("Last Name", lastNameField, 1);
        InitField("Phone", phoneNumberField, 2);
        InitField("Username", usernameField, 3);
        InitField("Password", passwordField, 4);
        InitField("Retype Password", retypePasswordField, 5);

        gbc.gridx = 0;
        gbc.gridy = 6;
        gbc.gridwidth = 2; // Span two columns
        JButton registerButton = new JButton("Register");
        registerButton.setPreferredSize(new Dimension(150, 30));
        panel.add(registerButton, gbc);

        setVisible(true);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(!Arrays.equals(passwordField.getPassword(), retypePasswordField.getPassword()))
                {
                    JOptionPane.showMessageDialog(null, "Passwords don't match");
                }
                else if (!DbUtils.CreateUser(
                        usernameField.getText(),
                        Arrays.toString(passwordField.getPassword()),
                        firstNameField.getText(),
                        lastNameField.getText(),
                        phoneNumberField.getText(),
                        2
                        ))
                {
                    JOptionPane.showMessageDialog(null, "User already exists");
                }
                else
                {
                    dispose();
                    new LoginScreen().setVisible(true);
                }
            }
        });
    }
    private void InitField(String text, Component field, int y) {
        JLabel label = new JLabel(text + ":");
        gbc.gridx = 0;
        gbc.gridy = y;
        panel.add(label, gbc);

        gbc.gridx = 1;
        field.setPreferredSize(new Dimension(200, 25));
        panel.add(field, gbc);
    }
}