import java.io.*;
import java.util.Vector;


public class LabFour {
    private String TextFilePath;
    private long TextDifference;
    private File CurrentFile;

    public LabFour(String pTextFilePath, long pTextDifference) {
        TextFilePath = pTextFilePath;
        TextDifference = pTextDifference;
        CurrentFile = new File(pTextFilePath);
    }

    public void mRun() throws Exception{
        int FileLines;
        int CurrentPosition = 0;
        //количество строк в файлe
        BufferedReader FileReaderStream;
        try {
            FileReaderStream = new BufferedReader( new FileReader(CurrentFile));
            FileReaderStream.mark(0);
        } catch (FileNotFoundException Exc) {
            throw new Exception("Не удалось открыть файл!");
        } catch (IOException Exc) {
            throw new Exception("Не удалось поставить метку!");
        }
        int LinesCounter = 0;
        while (FileReaderStream.readLine() != null) {
            LinesCounter++;
        }
        FileLines = LinesCounter;
        //чтеие файла
        try {
            FileReaderStream.close();
            FileReaderStream = new BufferedReader( new FileReader(CurrentFile));
        } catch (IOException ex) {
            throw new Exception("Не удалось открыть файл!");
        }
        String TempString;
        Statistic StatThread;
        try {
            StatThread = new Statistic(FileLines);
        }catch (Exception ex) {
            System.out.println(ex.getMessage());
            throw new Exception("Ошибка при обработке статистики");
        }
        int Currentline = 1;
        long QueryTime = 0;
        Vector<LogQuery> QueryVector = new Vector<LogQuery>(0);


        while ((TempString = FileReaderStream.readLine()) != null) {
            String[] TempQueryData = TempString.split(" / ");
            if (TempQueryData.length != 3) {
                throw new Exception("Ошибка в вводе запроса! Формат должен иметь вид Дата/Запрос/номер запроса. Строка = " + Currentline);
            }
            int TempQueryId = 0;
            try {
                TempQueryId = Integer.parseInt(TempQueryData[2]);
            } catch (NumberFormatException ex) {
                throw new Exception("Что-то пошло не так при переводе строки в число. Строка = " + Currentline);
            }
            switch (TempQueryData[1]) {
                case "QUERY": {
                    boolean IdUsed = false;
                    for (int i = 0; i < QueryVector.size(); i++) {
                        if (QueryVector.elementAt(i).GetId() == TempQueryId) {
                            throw new Exception("Данный ID уже встречался. Строка = " + Currentline);
                        }
                    }
                    QueryVector.add(new LogQuery(TempQueryId, TempQueryData[0]));
                    break;
                }
                case "RESULT": {
                    for (int i = 0; i < QueryVector.size(); i++) {
                        if (QueryVector.elementAt(i).GetId() == TempQueryId) {
                            QueryVector.elementAt(i).SetEnd(TempQueryData[0]);
                        }
                    }
                    break;
                }
                default: {
                    throw new Exception("Ошибка в вводе запроса! Формат должен иметь вид Дата/Запрос/номер запроса. Строка = " + Currentline);
                }
            }
            StatThread.mLineFinded();
            CurrentPosition += TempString.length();
            StatThread.mLineReaded();
            Currentline++;
        }
        StatThread.mFileEnd();

        if (TextDifference != 0) {
            for (int i = 0; i <  QueryVector.size(); i++) {
                if ( QueryVector.elementAt(i).GetDuration() > TextDifference) {
                    StringBuilder Temp = new StringBuilder("Найден аномальный запрос: ");
                    Temp.append(QueryVector.elementAt(i).GetId()).append(" (Время = ").append(QueryVector.elementAt(i).GetDuration()).append("c.)");
                    System.out.println(Temp);
                }
            }
        } else {
            long MiddleDuration = 0;
            for (int i = 0; i < QueryVector.size(); i++) {
                MiddleDuration +=  QueryVector.elementAt(i).GetDuration();
            }
            MiddleDuration /=  QueryVector.size();
            StringBuilder Temp = new StringBuilder("Среднее время выполнения: ");
            Temp.append(MiddleDuration).append("с.)");
            System.out.println(Temp);
            MiddleDuration *= 1.25;
            for (int i = 0; i <  QueryVector.size(); i++) {
                if ( QueryVector.elementAt(i).GetDuration() > MiddleDuration) {
                    Temp.setLength(0);
                    Temp.append("Найден аномальный запрос:") ;
                    Temp.append(QueryVector.elementAt(i).GetId()).append(" (Время = ").append(QueryVector.elementAt(i).GetDuration()).append("c.)");
                    System.out.println(Temp);
                }
            }
        }
    }
}
