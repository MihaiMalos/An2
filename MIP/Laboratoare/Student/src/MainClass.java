import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.awt.*;
import javax.swing.*;

public class MainClass {
    public static void main(String[] args) {

        JFrame f = new JFrame("Student");
        f.setLayout(new FlowLayout());

        JLabel lblFirstName = new JLabel("Prenumele: ");
        JTextArea txtFirstName = new JTextArea();

        //txtFirstName.setText("Andreea");

        JButton btnOk = new JButton("Ok");
        JButton btnCancel = new JButton("Cancel");

        btnOk.addActionListener(e -> {
            String helloMessage;
            Student s1 = new Student(txtFirstName.getText(), "Popescu", "2788888881231");
            s1.setLastName("Duca");
            Student s2 = new Student(txtFirstName.getText(), "Ionescu", "2888888881231");

            //calcul
            helloMessage = "";
            try {
                int a, b;
                b = 0;
                //a= 3/b;
                //helloMessage = Utils.Execute(s1, s2);

                List<Student> students = new ArrayList<Student>();
                students.add(s1);
                students.add(s2);

                helloMessage = Utils.Execute(students);

            }
            catch(ArithmeticException ex1)
            {
                System.out.println(ex1.getMessage());
            }
            catch(Exception ex)
            {
                System.out.println(ex.getMessage());
                //log error
            }
            finally
            {
                System.out.println("Mesaj in finally");
            }
            System.out.println(helloMessage);

        });

        btnCancel.addActionListener(e -> {
            f.dispose();
        });

        f.add(lblFirstName);
        f.add(txtFirstName);
        f.add(btnOk);
        f.add(btnCancel);
        f.pack();

        f.setLocationRelativeTo(null);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);

    }
}