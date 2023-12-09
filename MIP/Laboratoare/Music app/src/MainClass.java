import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainClass {
    public static void main (String[] args) {
        DbUtils.getConnection();
        JFrame frame = new JFrame ("Musify");

        LoginPanel loginPanel = new LoginPanel();
        RegisterPanel registerPanel = new RegisterPanel();

        frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(loginPanel);

        frame.pack();
        frame.setVisible (true);
        frame.setLocationRelativeTo(null);

        loginPanel.getRegisterButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                loginPanel.setVisible(false);
                frame.setContentPane(registerPanel);
                frame.pack();
            }
        });
    }
}
