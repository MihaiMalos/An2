package Models;

import java.util.ArrayList;
import java.util.List;

public class Role implements Entity {
    private int roleId;
    private String roleName;

    public Role(int roleId, String roleName) {
        this.roleId = roleId;
        this.roleName = roleName;
    }
    public static List<String> GetRoleListColumns() {
        List<String> columns = new ArrayList<String>();
        columns.add("Role Name");

        return columns;
    }
    public int GetId() {
        return roleId;
    }

    public void setRoleId(int roleId) {
        this.roleId = roleId;
    }

    public String getRoleName() {
        return roleName;
    }

    public void setRoleName(String roleName) {
        this.roleName = roleName;
    }
    public String toString() { return roleName; }
}
