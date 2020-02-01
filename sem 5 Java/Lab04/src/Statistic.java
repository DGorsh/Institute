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
                TimeCurrentReaded + "." + TempMillis + "c., Времени осталось (примерно): 0 с.");
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
                System.out.println("Прогресс: [" + WorkPercent + "%], Прочтено: " + ReadedLines + "/" + MaxLines + " строк, " + "Времени прошло: " +
                        TimeCurrentReaded + "." + TempMillis + "c., Времени осталось (примерно): " +
                        TimeToEnd/1000 + "с.");
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