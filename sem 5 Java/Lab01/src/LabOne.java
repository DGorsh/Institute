import java.io.*;
import java.util.Stack;
import java.util.Vector;

import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class LabOne {
    private File TextFile;
    private Vector<Character> Scobes;
    private Stack<Integer> TempScopes;

    public LabOne(String pTextFilePath, String pConfigFilePath) throws Exception{
        Scobes = new Vector<Character>(0);
        TempScopes = new Stack<Integer>();
        //файл с текстом
        TextFile = new File(pTextFilePath);
        //файл с настройками
        JSONParser TempJsonParser = new JSONParser();
        JSONObject TempJsonObject;
        JSONArray TempScobesVector;
        Reader reader;
        try {
            reader = new FileReader(pConfigFilePath);
        } catch (FileNotFoundException Exc) {
            System.out.println(Exc.getMessage());
            throw new Exception("Не удалось найти файл");
        }
        try {
            TempJsonObject = (JSONObject) TempJsonParser.parse(reader);
            TempScobesVector = (JSONArray) TempJsonObject.get("bracket");
        } catch (IOException | ParseException Exc) {
            throw new Exception("Ошибка в чтении файла конфигурации");
        }
        for (int i = 0; i < TempScobesVector.size(); i++) {
            JSONObject TempJsonElement = (JSONObject) TempScobesVector.get(i);
            String TempLeftScobe = (String) TempJsonElement.get("left");
            String TempRightScobe = (String) TempJsonElement.get("right");
            if ((TempLeftScobe.length()!=1) || TempRightScobe.length()!=1) {
                throw new Exception("Символ, выступающий в качестве скобки, должен быть одним! Ну или вы просто ничего не ввели. (Тип скобок: " +
                        (i+1) + ");");
            }
            Scobes.add(TempLeftScobe.charAt(0));
            Scobes.add(TempRightScobe.charAt(0));
        }
    }

    public boolean mRun() throws Exception{
        char TempSymbol;
        int TempReaded;
        int TempCurrentPos = 0;
        BufferedReader TextReader;
        try {
            TextReader = new BufferedReader(new FileReader(TextFile));
            while ((TempReaded = TextReader.read()) != -1) {
                TempCurrentPos++;
                TempSymbol = (char) TempReaded;
                if (Scobes.contains(TempSymbol)) {
                    Constants Enum = Constants.values()[pmScobeCheck(Scobes.indexOf(TempSymbol))];
                    switch (Enum) {
                        case SCOBES_CORRECT: {break;}
                        case SCOBES_ERROR: { System.out.println("Неверно расставлены скобки. Позиция:  " + TempCurrentPos + "  , Элемент:  " + TempSymbol);
                            TextReader.close();
                            return false; }
                        case SCOBES_BEGINNING: { System.out.println("Начало скобочной последовательности с закрывающей скобки");
                        TextReader.close();
                        return false; }
                    };
                }
            }
            TextReader.close();
            if (TempScopes.isEmpty()) {
                return true;
            } else {
                System.out.println("Неверно расставлены скобки. Стек не пуст!");
                return false;
            }
        } catch (IOException Exc) {
            System.out.println(Exc.getMessage());
            throw new Exception("Проблемы с считыванием данных из файла");
        }
    }

    private int pmScobeCheck(int pIndex) {
        if ((pIndex % 2 == 0) && (Scobes.get(pIndex) != Scobes.get(pIndex+1))) {
            TempScopes.push(pIndex);
        } else {
            if (!TempScopes.isEmpty()) {
                if (pIndex != Scobes.size()-1) {
                    if (Scobes.get(pIndex) == Scobes.get(pIndex + 1)) {
                        if (TempScopes.peek() == pIndex) {
                            TempScopes.pop();
                            return Constants.SCOBES_CORRECT.ordinal();
                        } else {
                            TempScopes.push(pIndex);
                            return Constants.SCOBES_CORRECT.ordinal();
                        }
                    }
                }
                if (TempScopes.peek() == pIndex - 1) {
                    TempScopes.pop();
                } else {
                    return Constants.SCOBES_ERROR.ordinal();
                }
            } else {
                if (Scobes.get(pIndex) != Scobes.get(pIndex+1)){
                    return Constants.SCOBES_BEGINNING.ordinal();
                } else {
                    TempScopes.push(pIndex);
                }
            }
        }
        return 0;
    }

}
