
import java.util.LinkedList;

public final class Group {
    private int id;
    private String name;

    private LinkedList<Puple> pupleLinkedList = new LinkedList<>();

    public Group(int id, String groupName) {
        this.id = id;
        this.name = groupName;
    }

    public void placePuple(Puple puple) {
        pupleLinkedList.add(puple);
    }




}
