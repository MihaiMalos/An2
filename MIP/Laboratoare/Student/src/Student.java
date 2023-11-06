public class Student {

    private String firstName;
    private String lastName;
    private String cnp;

    public String getFirstName() {
        return this.firstName;
    }

    public String getLastName()
    {
        return this.lastName;
    }

    public String getCnp() {
        return this.cnp;
    }

    public void setFirstName(String firstName)
    {
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setCnp(String cnp) {
        this.cnp = cnp;
    }

    public Student(String firstName, String lastName, String cnp)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.cnp = cnp;
    }

    public String getHelloMessage()
    {
        StringBuilder sb = new StringBuilder("Hello, ");
        sb.append(this.firstName);
        sb.append(" ");
        sb.append(this.lastName);
        sb.append("!");

        return sb.toString();
    }
}