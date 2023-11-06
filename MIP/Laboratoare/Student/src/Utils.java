import java.util.List;

public class Utils {

    public static String Execute(Student s1, Student s2)
    {
        if (s1.getFirstName().equals(s2.getFirstName()))
        {
            return s1.getHelloMessage();
        }
        return s2.getHelloMessage();
    }

    public static String Execute(List<Student> list)
    {
        if (list.size() == 0)
        {
            return "Lista de studenti este goala";
        }
        if (list.get(0).getFirstName().equals(list.get(1).getFirstName()))
        {
            return list.get(0).getHelloMessage();
        }
        return list.get(1).getHelloMessage();
    }
}