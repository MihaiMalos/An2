import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class RegisterPanel extends JPanel {
    private JTextField jcomp1;
    private JLabel jcomp2;
    private JLabel jcomp3;
    private JPasswordField jcomp4;
    private JLabel jcomp5;
    private JPasswordField jcomp6;
    private JButton jcomp7;

    public RegisterPanel() {
        //construct components
        jcomp1 = new JTextField (1);
        jcomp2 = new JLabel ("Username");
        jcomp3 = new JLabel ("Password");
        jcomp4 = new JPasswordField (1);
        jcomp5 = new JLabel ("Confirm");
        jcomp6 = new JPasswordField (1);
        jcomp7 = new JButton ("Register");

        //adjust size and set layout
        setPreferredSize (new Dimension (366, 274));
        setLayout (null);

        //add components
        add (jcomp1);
        add (jcomp2);
        add (jcomp3);
        add (jcomp4);
        add (jcomp5);
        add (jcomp6);
        add (jcomp7);

        //set component bounds (only needed by Absolute Positioning)
        jcomp1.setBounds (125, 35, 165, 25);
        jcomp2.setBounds (60, 35, 65, 25);
        jcomp3.setBounds (60, 85, 60, 25);
        jcomp4.setBounds (125, 85, 165, 25);
        jcomp5.setBounds (70, 130, 55, 25);
        jcomp6.setBounds (125, 130, 165, 25);
        jcomp7.setBounds (60, 195, 260, 45);
    }
}
