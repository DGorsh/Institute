using System;

namespace lab12
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Лабораторная работа № 12: Обработка файлв\nВведите: (1) - выполнить, (2) - о программе, (0) - выход");
            string pInput;
            while (!(pInput = Console.ReadLine()).Equals("0"))
            {
                switch (pInput)
                {
                    case "1":
                        {
                            try
                            {
                                Console.WriteLine("Введите название файла");
                                string prFilename = Console.ReadLine();
                                Console.WriteLine("Введите слово для поиска");
                                string prStringFind = Console.ReadLine();
                                ProgClass Solution = new ProgClass(prFilename, prStringFind);
                                Console.WriteLine(Solution.mSolution());
                            }
                            catch (Exception Ex)
                            {
                                Console.WriteLine("Ошибка при выполнении программы:");
                                Console.WriteLine(Ex.ToString());
                                Console.ReadLine();
                                Environment.Exit(1);
                            }
                            break;
                        }
                    case "2":
                        {
                            Console.WriteLine("Лабораторная работа № 10: Матрица и полином\nАвтор: Горшков Д.С. (Группа М8О-312Б)\n");
                            break;
                        }
                }
            }
        }
    }
}
