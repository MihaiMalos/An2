package Screens;

import Models.User;
import Screens.AdminScreens.AdminScreen;
import Screens.UserScreens.UserScreen;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;

public class LoginScreen extends JFrame {
    private final JTextField usernameField;
    private final JPasswordField passwordField;

    public LoginScreen() {
        setLayout(new BorderLayout());
        setTitle("Login");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(3, 2, 10, 10));
        add(panel);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setHorizontalAlignment(JLabel.CENTER);
        usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setHorizontalAlignment(JLabel.CENTER);
        passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        JButton registerButton = new JButton("Register");

        panel.add(usernameLabel, BorderLayout.CENTER);
        panel.add(usernameField, BorderLayout.CENTER);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton, BorderLayout.CENTER);
        panel.add(registerButton);

        setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = Arrays.toString(passwordField.getPassword());
                User user = DbUtils.GetAuthenticatedUser(username, password);
                if (user != null) {
                    if (user.getRole().GetId() == 1) {
                        dispose();
                        new AdminScreen();
                    }
                    else if(user.getRole().GetId() == 2) {
                        dispose();
                        new UserScreen();
                    }

                }
                else {
                    JOptionPane.showMessageDialog(null, "Invalid username or password");
                }
            }
        });

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                new RegisterScreen();
            }
        });
    }
}