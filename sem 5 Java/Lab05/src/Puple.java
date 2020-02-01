public final class Puple {
    public int id;
    public String fio;


    public Puple(int id, String fio) {
        this.id = id;
        this.fio = fio;
    }

    @Override
    public String toString() {
        return "Puple{" +
                "id=" + id +
                ", fio='" + fio + '\'' +
                '}';
    }

    public boolean equals(Puple puple) {
        return (id == puple.id);
    }

}
