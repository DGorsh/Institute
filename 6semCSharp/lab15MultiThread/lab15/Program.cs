using System;

namespace lab15
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Лабораторная работа № 15: Инфекционное отделение\nВведите: (1) - выполнить, (2) - о программе, (0) - выход");
            string pInput;
            while (!(pInput = Console.ReadLine()).Equals("0"))
            {
                switch (pInput)
                {
                    case "1":
                        {
                            try
                            {
                                ProgClass Solution = new ProgClass();
                                Solution.mSolution();
                            }
                            catch (Exception Ex)
                            {
                                Console.ResetColor();
                                Console.WriteLine("Ошибка при выполнении программы:");
                                Console.WriteLine(Ex.ToString());
                                Console.ReadLine();           
                                Environment.Exit(1);
                            }
                            break;
                        }
                    case "2":
                        {
                            Console.WriteLine("Лабораторная работа № 15: Симулятор чумы\nАвтор: Горшков Д.С. (Группа М8О-312Б)\n");
                            break;
                        }
                }
            }
        }
    }
}
