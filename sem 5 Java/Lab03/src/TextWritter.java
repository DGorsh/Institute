import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;
import java.util.concurrent.locks.Lock;

public class TextWritter extends Thread {
    private String TextFilename;
    private Vector<String> LineMessage;
    private boolean ThreadStop = false;
    private Lock lock;
    private FileWriter OutputFile;

    public TextWritter(String pTextFileName) throws Exception {
        LineMessage = new Vector<String>(0);
        ThreadStop = true;
        TextFilename = "ResultFileof_" + pTextFileName;
        try {
            OutputFile = new FileWriter(TextFilename, false);
            OutputFile.close();
        } catch (IOException Exc) {
            throw new Exception("Программа не смогла создать файл!");
        }
        start();
    }

    public void mWrite(Vector<String> pMessage){
        LineMessage = pMessage;
        ThreadStop = false;
        start();
    }

    public void start(){
        if (!this.ThreadStop){
            try {
                OutputFile = new FileWriter(TextFilename, true);
                for (int i = 0; i < LineMessage.size(); i++) {
                    StringBuilder Temp = new StringBuilder(LineMessage.elementAt(i)).append('\n');
                    OutputFile.append(Temp);
                }
                OutputFile.flush();
            } catch (IOException Exc){
                System.out.println("Ошибка записи в файл. [File] = \'" + OutputFile + "\'; [String] = " + LineMessage);
                System.exit(1);
            };
        }
        this.ThreadStop = true;
        stop();
    }
}
