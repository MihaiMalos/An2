import java.awt.*;
import javax.swing.*;

public class LoginPanel extends JPanel {
    private JPasswordField passwordField;
    private JTextField usernameField;
    private JLabel jcomp3;
    private JLabel jcomp4;
    private JLabel jcomp5;
    private JButton registerButton;
    private JButton loginButton;

    public LoginPanel() {
        //construct components
        passwordField = new JPasswordField (1);
        usernameField = new JTextField (1);
        jcomp3 = new JLabel ("Login");
        jcomp4 = new JLabel ("Username");
        jcomp5 = new JLabel ("Password");
        registerButton = new JButton ("Register");
        loginButton = new JButton ("Login");

        //adjust size and set layout
        setPreferredSize (new Dimension (453, 220));
        setLayout (null);

        //add components
        add (passwordField);
        add (usernameField);
        add (jcomp3);
        add (jcomp4);
        add (jcomp5);
        add (registerButton);
        add (loginButton);

        //set component bounds (only needed by Absolute Positioning)
        passwordField.setBounds (90, 110, 280, 25);
        usernameField.setBounds (90, 70, 280, 25);
        jcomp3.setBounds (210, 30, 35, 30);
        jcomp4.setBounds (25, 70, 60, 25);
        jcomp5.setBounds (25, 110, 65, 25);
        registerButton.setBounds (240, 155, 95, 25);
        loginButton.setBounds (120, 155, 95, 25);
    }

    public JButton getRegisterButton() {
        return registerButton;
    }

    public void setRegisterButton(JButton registerButton) {
        this.registerButton = registerButton;
    }

    public JButton getLoginButton() {
        return loginButton;
    }

    public void setLoginButton(JButton loginButton) {
        this.loginButton = loginButton;
    }
}
