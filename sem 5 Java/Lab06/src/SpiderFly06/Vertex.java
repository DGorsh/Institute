package SpiderFly06;

public class Vertex {
    private int x;
    private int y;
    private State state = State.Empty;

//    public Vertex(){}

//    public Vertex(Vertex vertex) {
//        x = vertex.x;
//        y = vertex.y;
//        state = vertex.state;
//    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public State getState() {
        return state;
    }

    public Vertex copy() {
        Vertex v = new Vertex();
        v.x = x;
        v.y = y;
        v.state = state;
        return v;
    }

    public void setState(State state) {
        this.state = state;
    }

    @Override
    public boolean equals(Object obj) {
        if (super.equals(obj))
            return true;
        if (obj.getClass() != Vertex.class)
            return false;
        Vertex v = (Vertex)obj;
        return x == v.x && y == v.y;
    }
}
