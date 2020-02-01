import java.io.*;
import java.util.Collections;
import java.util.Vector;

import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class LabTwo {
    private Vector<Integer> MoneyNominals;
    private Vector<Integer> MoneyCount;
    private int MoneyValue;
    boolean Result;

    public LabTwo(int pMoneyValue, String pConfigFilePath) throws Exception  {
        MoneyNominals = new Vector<Integer>(0);
        MoneyCount = new Vector<Integer>(0);
        MoneyValue = pMoneyValue;
        Result = false;

        //файл с настройками
        JSONParser TempJsonParser = new JSONParser();
        JSONObject TempJsonObject;
        try (Reader reader = new FileReader(pConfigFilePath)) {
            TempJsonObject = (JSONObject) TempJsonParser.parse(reader);
            JSONArray TempNomVector = (JSONArray) TempJsonObject.get("nominal");
            for (int i = 0; i < TempNomVector.size(); i++) {
                int TempJsonElement = ((Long) TempNomVector.get(i)).intValue();
                MoneyNominals.add(TempJsonElement);
                MoneyCount.add(0);
            }
        } catch (ParseException Exc) {
            System.out.println(Exc.getMessage());
            throw new Exception("Проблемы со считыванием данных из файла конфигураций");
        } catch (FileNotFoundException Exc) {
            throw new Exception("Файл конфигураций не найден");
        }
        Collections.sort(MoneyNominals);
    }

    public boolean mRun() throws Exception {
        mLab(MoneyValue, MoneyNominals.size()-1);
        if (Result) {
            return true;
        } else {
            return false;
        }
    }

    public void mLab(int pMoneyValue, int pMoneyNominalId) throws Exception{
        if (pMoneyValue == 0) {
            StringBuilder TempText = new StringBuilder(MoneyValue);
            TempText.append(" -> ");
            for (int i = 0; i < MoneyNominals.size(); i++) {
                TempText.append("["); TempText.append(MoneyNominals.elementAt(i)); TempText.append("] = ");
                        TempText.append(MoneyCount.elementAt(i)); TempText.append("; ");
            }
            System.out.println(TempText);
            Result = true;
            return;
        }
        if (pMoneyValue >= MoneyNominals.elementAt(pMoneyNominalId)) {
            MoneyCount.set(pMoneyNominalId, (MoneyCount.elementAt(pMoneyNominalId) + 1)) ;
            mLab(pMoneyValue - MoneyNominals.elementAt(pMoneyNominalId), pMoneyNominalId);
            MoneyCount.set(pMoneyNominalId, (MoneyCount.elementAt(pMoneyNominalId) - 1)) ;
        }
        if (pMoneyNominalId != 0) {
            mLab(pMoneyValue, pMoneyNominalId - 1);
        }
    }
}
