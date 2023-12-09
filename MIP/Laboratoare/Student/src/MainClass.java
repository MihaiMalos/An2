import java.util.ArrayList;
import java.util.List;
import java.awt.*;
import javax.swing.*;

public class MainClass {
    public static void main(String[] args)
    {
        JFrame f = new JFrame("Student");
        f.setLocationRelativeTo(null);
        f.setLayout(null);
        f.setSize(1000, 1000);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);

        JMenuBar menuBar = new JMenuBar();

        JMenu menuHome = new JMenu("ACASA");

        JMenu menuStudents = new JMenu("STUDENTI");
        JMenuItem menuShowStudents = new JMenuItem("LISTA_STUDENTI");
        JMenuItem menuAddStudent = new JMenuItem("ADAUGA_STUDENT");
        menuStudents.add(menuShowStudents);
        menuStudents.add(menuAddStudent);

        JMenu menuProfessors = new JMenu("PROFESORI");
        JMenuItem menuShowProfessors = new JMenuItem("LISTA_PROFESORI");
        JMenuItem menuAddProfessor = new JMenuItem("ADAUGA_PROFESOR");
        menuProfessors.add(menuShowProfessors);
        menuProfessors.add(menuAddProfessor);

        menuBar.add(menuHome);
        menuBar.add(menuStudents);
        menuBar.add(menuProfessors);

        menuShowStudents.addActionListener(e->{
            List<Student> students;
            List<String> helloMessages;
            students = new ArrayList<Student>();
            helloMessages = new ArrayList<String>();

            try {
                students = DbUtils.GetAllActiveStudents();
//                helloMessages = Utils.Execute(students);
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
                //log error
            } finally {
                //System.out.println("Mesaj in finally");
            }

            if (helloMessages.isEmpty()) {
                System.out.println("Niciun mesaj trimis, niciun student din lista nu are email.");
            }

            for(Student s : students)
            {
                System.out.println(s.getFirstName());
            }

            for (String helloMessage : helloMessages) {
                System.out.println(helloMessage);
            }
        });

        JLabel lblFirstName = new JLabel("Prenumele: ");
        JTextArea txtFirstName = new JTextArea();

        lblFirstName.setBounds(100,200,80,30);
        txtFirstName.setBounds(200,200,80,30);

        JButton btnOk = new JButton("Ok");
        JButton btnCancel = new JButton("Cancel");

        btnOk.addActionListener(e -> {
            System.out.println("Button Ok clicked");
        });
        btnOk.setBounds(300,200,80,30);

        btnCancel.addActionListener(e -> {
            f.dispose();
        });

        btnCancel.setBounds(400,200,80,30);
        f.setJMenuBar(menuBar);
        f.add(lblFirstName);
        f.add(txtFirstName);
        f.add(btnOk);
        f.add(btnCancel);
        f.pack();
    }
}