import java.io.FileWriter;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.locks.Lock;

public class Statistic extends Thread {
    private int MaxLines;
    private int ReadedLines;
    private int LinesPrevReaded;
    private int TimePrevReaded;
    private int TimeCurrentReaded;
    private int FindedLines;
    private int TempMillis;

    public Statistic(int pLines) throws Exception{
        MaxLines = pLines;
        ReadedLines = 0;
        TimePrevReaded = 0;
        TimeCurrentReaded = 0;
        TempMillis = 0;
        start();
    }

    public void mLineReaded(){
        ReadedLines++;
    }

    public void mLineFinded() {
        FindedLines++;
    }

    public void mFileEnd() {
        System.out.println("Прогресс: [100%], Прочтено: " + ReadedLines + "/" + MaxLines + " строк, " + "Времени прошло: " +
                TimeCurrentReaded + "." + TempMillis + "c., Времени осталось (примерно): 0 с., " + "Совпадений найдено: " + FindedLines);
    }

    public void start(){
        Timer CurrentTimer = new Timer();
        CurrentTimer.schedule(new cTimerTask(), 0, 10);
    }

    private class cTimerTask extends TimerTask {
        public void run() {
            int WorkPercent = (ReadedLines * 100) / MaxLines;
            if (ReadedLines != MaxLines) {
                int TimeToEnd = 0;
                //подсчитать среднее
                if ((ReadedLines != 0) && ((TimeCurrentReaded*1000+TempMillis) != 0)) {
                    TimeToEnd = ((MaxLines-ReadedLines)) / (ReadedLines/(TimeCurrentReaded*1000+TempMillis));
                    TimePrevReaded = TimeToEnd;
                } else {
                    TimeToEnd = TimePrevReaded;
                }
                StringBuffer TempString = new StringBuffer("Прогресс: [");
                TempString.append(WorkPercent).append("%], Прочтено: ").append(ReadedLines).append("/");
                TempString.append(MaxLines).append(" строк, Времени прошло: ").append(TimeCurrentReaded).append(".");
                TempString.append(TempMillis).append("c., Времени осталось (примерно): ").append(TimeToEnd/1000);
                TempString.append("с., Совпадений найдено: ").append(FindedLines);
                System.out.println(TempString);
                LinesPrevReaded = ReadedLines;
                if (TempMillis == 1000) {
                    TempMillis = 0;
                    TimeCurrentReaded++;
                } else {
                    TempMillis += 10;
                }
            } else {
                cancel();
            }
        }
    }
}