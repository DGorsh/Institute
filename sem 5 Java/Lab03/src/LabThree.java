import java.io.*;
import java.util.Vector;


public class LabThree {
    private String TextFilePath;
    private String TextFileFind;
    private int LinesCount;
    private int Founded;
    private File CurrentFile;

    public LabThree(String pTextFilePath, String pTextFinding, int pTextLinesCount) throws Exception {
        TextFilePath = pTextFilePath;
        TextFileFind = pTextFinding;
        LinesCount = pTextLinesCount;
        CurrentFile = new File(pTextFilePath);
    }

    public String mRun() throws Exception {
        int FileLines;
        int CurrentPosition = 0;
        //количество строк в файлe
        BufferedReader FileReaderStream;
        try {
            FileReaderStream = new BufferedReader( new FileReader(CurrentFile));
        } catch (FileNotFoundException Exc) {
            throw new Exception("Не удалось открыть файл!");
        }
        try {FileReaderStream.mark(0);} catch (IOException Exc) {throw new Exception("Не удалось поставить метку на начало файла!");}
        int LinesCounter = 0;
        try {
            while (FileReaderStream.readLine() != null) {
                LinesCounter++;
            }
        } catch (IOException Exc) {
            throw new Exception("Не удалось прочесть строку!");
        }
        FileLines = LinesCounter;
        //чтеие файла
        try {
            FileReaderStream.close();
            FileReaderStream = new BufferedReader( new FileReader(CurrentFile));
        } catch (FileNotFoundException Exc) {
            throw new Exception("Не удалось открыть файл! Файл куда-то потерялся");
        } catch (IOException Exc) {
            throw new Exception("Не удалось открыть файл!");
        }
        TextWritter TextWritingThread;
        Statistic StatThread;
        try {
            TextWritingThread = new TextWritter(TextFilePath);
            StatThread = new Statistic(FileLines);
        } catch (Exception Exc) {
            throw new Exception("Не удалось создать потоки для записи или счетчика!");
        }
        Vector<String> TempStringVector = new Vector<String>(0);
        String TempString;
        while ((TempString = FileReaderStream.readLine()) != null) {
            TempStringVector.add(TempString);
            if (TempString.contains(TextFileFind) ) {
                StatThread.mLineFinded();
                int CurVectorSize = TempStringVector.size();
                try {
                    FileReaderStream.mark(CurrentPosition);
                } catch (IOException Exc) {
                    throw new Exception("Не удалось поставить метку!");
                }
                for (int i = 0; i < LinesCount; i++) {
                    String TempStr;
                    try {
                        if ((TempStr = FileReaderStream.readLine()) != null) {
                            TempStringVector.add(TempStr);
                        }
                    } catch (IOException Exc) {
                        throw new Exception("Не удалось считать файл!");
                    }
                }
                TextWritingThread.mWrite(TempStringVector);
                for (int i = LinesCount; i > 0; i--) {
                    if (TempStringVector.size() == CurVectorSize + i) {
                        TempStringVector.remove(TempStringVector.size() - 1);
                    }
                }
                try{ FileReaderStream.reset(); } catch (IOException Exc) { throw new Exception("Не удалось поставить метку!"); }
                Founded++;
            }
            if (TempStringVector.size() == LinesCount + 1) {
                TempStringVector.remove(0);
            }
            CurrentPosition += TempString.length();
            StatThread.mLineReaded();
        }
        StatThread.mFileEnd();
        if (Founded != 0) {
            return "Совпадения найдены!";
        }
        return "Ничего не найдено";
    }
}
