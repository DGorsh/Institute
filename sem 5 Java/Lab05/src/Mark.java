import java.util.Date;
import java.util.Objects;

public final class Mark {
    private int subject;
    private int puple;

    public String toString() {
        return "Mark{" +
                "subject=" + subject +
                ", puple=" + puple +
                ", value=" + value +
                ", date=[ year:" + date.getYear() + " month:" + date.getMonth() + " day:" + date.getDate() +
                "]}";
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Mark mark = (Mark) o;
        return subject == mark.subject &&
                puple == mark.puple &&
                value == mark.value &&
                Objects.equals(date, mark.date);
    }

    public int hashCode() {
        return Objects.hash(subject, puple, value, date);
    }

    public int getId() {
        return subject;
    }

    public void setId(int subject) {
        this.subject = subject;
    }

    public int getPupleId() {
        return puple;
    }

    public void setPupleId(int puple) {
        this.puple = puple;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Mark(int subject, int puple, int value, Date date) {
        this.subject = subject;
        this.puple = puple;
        this.value = value;
        this.date = date;
    }

    private int value;
    private Date date;
    
}
