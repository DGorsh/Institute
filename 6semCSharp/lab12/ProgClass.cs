using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace lab12
{
    class ProgClass
    {
        FileStream prFile;
        string prFindText;
        public ProgClass (string ppFileName, string ppFindText)
        {
            if (!File.Exists(ppFileName))
            {
                throw new Exception("Файл отсутствует");
            }
            prFile = File.OpenRead(ppFileName);
            prFindText = ppFindText;
        }

        public StringBuilder mSolution ()
        {
            SortedDictionary<string, int> ppWords = new SortedDictionary<string, int>();
            StringBuilder tResult = new StringBuilder("Результат: \n");
            StreamReader sr = new StreamReader(prFile);
            StringBuilder tWord = new StringBuilder("");
            while (true)
            {
                char tChar = ' ';
                if ((!sr.EndOfStream))
                {
                    tChar = (char)sr.Read();
                }
                if (!tChar.Equals(' ') || !sr.EndOfStream)
                {
                    tWord.Append(tChar);
                }
                else
                {
                    //если символ - пробел
                    string tTempWord = tWord.ToString();
                    //если есть запись
                    if (ppWords.ContainsKey(tTempWord))
                    {
                        ppWords[tTempWord]++;
                        tWord.Clear();
                    }
                    else
                    {
                        //если записи нет
                        ppWords.Add(tTempWord, 1);
                        tWord.Clear();
                    }
                    if (sr.EndOfStream)
                    {
                        break;
                    }
                }
            }
            //слова
            foreach (var tValue in ppWords)
            {
                tResult.Append(string.Format("Слово: \"{0}\", встретилось: {1} раз(а)\n", tValue.Key, tValue.Value));
            }
            //наиболее часто встречающееся слово
            var result = ppWords.Where(s => s.Value.Equals(ppWords.Max(s => s.Value))).Select(s => s.Key).ToList();
            for (int i = 0; i < result.Count; i++)
            {
                tResult.Append(string.Format("Наиболее часто встречается слово \"{0}\"", result[i]));
            }
            if (ppWords.ContainsKey(prFindText))
            {
                tResult.Append(string.Format("\nНайдено слово \"{0}\"\n Встречается {1} раз(а)",prFindText, ppWords[prFindText]));
            } else
            {
                tResult.Append(string.Format("\nЗаданное слово не обнаружено!"));
            }
            return tResult;
        }
    }
}
