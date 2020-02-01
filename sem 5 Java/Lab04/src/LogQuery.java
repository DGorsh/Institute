import java.time.LocalDateTime;
import java.time.ZoneOffset;

public class LogQuery {
    private int QueryId;
    private long TimeStart;
    private long Duration;

    public LogQuery(int pId, String pTime) throws Exception {
        QueryId = pId;
        Duration = 0;
        try {
            TimeStart = LocalDateTime.parse(pTime).atZone(ZoneOffset.UTC).toEpochSecond();
        } catch (Exception ex) {
            throw new Exception("Ошибка записи даты! Некорректный формат.");
        }
    }

    public void SetEnd(String pTime) throws Exception {
        try {
            Duration = LocalDateTime.parse(pTime).atZone(ZoneOffset.UTC).toEpochSecond() - TimeStart;
        } catch (Exception ex) {
            throw new Exception("Ошибка записи даты! Некорректный формат.");
        }
        if (Duration < 0) {
            throw new Exception("Ошибка записи даты! Окончание произошло раньше начала.");
        }
    }

    public int GetId() {
        return QueryId;
    }

    public long GetDuration()
    {
        return Duration;
    }
}
