using System;
using System.Collections.Generic;
using System.Text;

namespace lab11
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Лабораторная работа № 11: Вектор комплексных чисел\nВведите: (1) - выполнить, (2) - о программе, (0) - выход");
            string pInput;
            while (!(pInput = Console.ReadLine()).Equals("0"))
            {
                switch (pInput)
                {
                    case "1":
                        {
                            try
                            {
                                Complex prComplexA = new Complex(5, 3);
                                Complex prComplexB = new Complex(2, 4);
                                Complex prComplexC = new Complex(0, 3);
                                Complex prComplexD = new Complex(2, 4);

                                Vector<Complex> prVectorA = new Vector<Complex>(new Complex[]{
                                    prComplexA, prComplexC, prComplexB
                                });

                                Vector<Complex> prVectorB = new Vector<Complex>(new Complex[]{
                                    prComplexB, prComplexC, new Complex(1, 11)
                                });

                                Vector<Complex> prVectorC = new Vector<Complex>(new Complex[]{
                                    new Complex(3, 1),  new Complex(0, 5),  new Complex(2, 6)
                                });

                                var intv = prVectorC.mModule();
                                //комплексы
                                Console.WriteLine(String.Format("A = {0}, B = {1}, C = {2}, D = {3}", prComplexA, prComplexB, prComplexC, prComplexD));
                                Console.WriteLine(String.Format("Сложение = {0}", prComplexA + prComplexB));
                                Console.WriteLine(String.Format("Вычитание = {0}", prComplexA - prComplexB));
                                Console.WriteLine(String.Format("Умножение = {0}", prComplexA * prComplexB));
                                Console.WriteLine(String.Format("Деление = {0}", prComplexA / prComplexB));
                                Console.WriteLine(String.Format("A^15 = {0}", prComplexA.Pow(15)));
                                List<Complex> t = prComplexA.Root(4);
                                Console.WriteLine(String.Format("A^(1/4)=\n{0}, \n{1}, \n{2}, \n{3}",t[0],t[1],t[2],t[3]));

                                Console.WriteLine(String.Format("A = {0}, \nB = {1}, \nC = {2}", prVectorA, prVectorB, prVectorC));
                                var temp = Vector<Complex>.mOrtogonalize(new Vector<Complex>[]{ prVectorA, prVectorB, prVectorC});
                                Console.WriteLine(String.Format("Ortogonalize A \n{0}, \n{1}, \n{2}", temp[0], temp[1], temp[2]));
                                Console.WriteLine(String.Format("Module A = {0}", prVectorA.mModule()));
                                Console.WriteLine(String.Format("Compare A with B = {0}", prVectorA.CompareTo(prVectorB)));

                            }
                            catch (Exception Ex)
                            {
                                Console.WriteLine("Ошибка при выполнении программы:");
                                Console.WriteLine(Ex.Message);
                                Console.ReadLine();
                                Environment.Exit(1);
                            }
                            break;
                        }
                    case "2":
                        {
                            Console.WriteLine("Лабораторная работа № 11: Комплекс и вектор\nАвтор: Горшков Д.С. (Группа М8О-312Б)\n");
                            break;
                        }
                }
            }
        }
    }
}
