using System;
using System.Collections.Generic;
using System.Text;

namespace lab11
{
    class ComplexEvent : EventArgs
    {
        private string msg;
        public ComplexEvent (string s)
        {
            msg = s;
        }
        public string Message
        {
            get { return msg; }
            set
            {
                msg = value;
            }
        }
    }


    class Complex : IComparable, IComparable<Complex>
    {
        // Переменныe
        private double prRelative;
        private double prImaginate;

        public delegate void ComplexEventHandler(object ppSender, ComplexEvent ppComplexEvent);
        public event ComplexEventHandler RaiseCustomEvent;

        // Конструкторы
        public Complex(double ppRelative, double ppImaginate = 0.0)
        {
            prRelative = ppRelative;
            prImaginate = ppImaginate;
        }

        public Complex(Complex ppComplex)
        {
            prImaginate = ppComplex.prImaginate;
            prRelative = ppComplex.prRelative;
        }

        public Complex()
        {
            prRelative = 1;
            prImaginate = 0;
        }

        //Перегрузки операторов
        //Оператор сложения
        public static Complex operator +(Complex ppElementA, Complex ppElementB)
        {
            Complex tResultComplex = new Complex();
            tResultComplex.prRelative = ppElementA.prRelative + ppElementB.prRelative;
            tResultComplex.prImaginate = ppElementA.prImaginate + ppElementA.prImaginate;
            return new Complex(tResultComplex);
        }
        //Оператор вычитания
        public static Complex operator -(Complex ppElementA, Complex ppElementB)
        {
            Complex tResultComplex = new Complex();
            tResultComplex.prRelative = ppElementA.prRelative - ppElementB.prRelative;
            tResultComplex.prImaginate = ppElementA.prImaginate - ppElementB.prImaginate;
            return new Complex(tResultComplex);
        }


        //Оператор деления
        public static Complex operator /(Complex ppElementA, Complex ppElementB)
        {
            Complex tResultComplex = new Complex();
            double tZnam = ppElementB.prRelative * ppElementB.prRelative + ppElementB.prImaginate * ppElementB.prImaginate;
            if (tZnam.Equals(0))
            {
                tResultComplex.eDivide();
            }
            tResultComplex.prRelative = ppElementA.prRelative * ppElementB.prRelative + ppElementA.prImaginate * ppElementB.prImaginate; //числитель у а
            tResultComplex.prRelative /= tZnam; //знаменатель у а
            tResultComplex.prImaginate = ppElementB.prRelative * ppElementA.prImaginate - ppElementA.prRelative * ppElementB.prImaginate; //числитель у б
            tResultComplex.prImaginate /= tZnam; //знаменатель у б
            return new Complex(tResultComplex);
        }

        //Оператор умножения
        public static Complex operator *(Complex ppElementA, double ppElementB)
        {
            Complex tResultComplex = new Complex();
            tResultComplex = ppElementA * (new Complex(ppElementB));
            return new Complex(tResultComplex);
        }

        public static Complex operator *(Complex ppElementA, Complex ppElementB)
        {
            Complex tResultComplex = new Complex();
            tResultComplex.prRelative = ppElementA.prRelative * ppElementB.prRelative - ppElementA.prImaginate * ppElementB.prImaginate;
            tResultComplex.prImaginate = ppElementA.prRelative * ppElementB.prImaginate + ppElementB.prRelative * ppElementA.prImaginate;
            return new Complex(tResultComplex);
        }
        //Методы
        //Модуль
        public double Module()
        {
            return Math.Sqrt(prRelative * prRelative + prImaginate * prImaginate);
        }

        //Аргумент
        public double Argument()
        {
            if (prRelative == 0) {
                eDivide();
            }
            double tArgument = prRelative > 0 ? Math.Atan(prImaginate / prRelative) : Math.Atan(prImaginate / prRelative + Math.PI);
            return tArgument;
        }

        //Возведение в степень
        public Complex Pow(int ppValue)
        {
            Complex tResultComplex = new Complex();
            double tModule = this.Module();
            double tArgument = this.Argument();
            //Формула Муавра: z^n = |z|^n*(cos(nf) + sin(nf)i)
            tResultComplex.prRelative = Math.Cos(tArgument * ppValue);
            tResultComplex.prImaginate = Math.Sin(tArgument * ppValue);
            tResultComplex *= Math.Pow(tModule, ppValue);
            return tResultComplex;
        }
        //Излечение корня
        public List<Complex> Root(int ppValue)
        {
            if (ppValue == 0)
            {
                eDivide();
            }
            List<Complex> tResultComplex = new List<Complex>(ppValue);
            double tModule = Math.Pow(this.Module(), 1/(double)ppValue);
            double tArgument = this.Argument();
            //Формула Муавра: z^n = |z|^n*(cos(nf) + sin(nf)i)
            for (int i = 0; i < ppValue; i++)
            {
                tResultComplex.Add(new Complex());
                tResultComplex[i].prRelative = Math.Cos((tArgument + 2 * Math.PI * i) / ppValue);
                tResultComplex[i].prImaginate = Math.Sin((tArgument + 2 * Math.PI * i) / ppValue);
                tResultComplex[i] *= tModule;
            }
            return tResultComplex;
        }
        //Вывод
        public override string ToString()
        {
            return String.Format("({0} + {1}i)", prRelative, prImaginate);
        }

        //события
        public void eDivide()
        {
            RaiseCustomEvent = OnRaiseCustomEvent;
            ComplexEventHandler handler = RaiseCustomEvent;
            handler(this, new ComplexEvent("Divide by zero!"));
        }

        protected virtual void OnRaiseCustomEvent(object Sender, ComplexEvent e)
        {
                e.Message += $" at {DateTime.Now}";
                Console.WriteLine(e.Message);
                throw new Exception("Деление на ноль!");
        }

        public int CompareTo(Complex ppComplexA)
        {
            double tModA = this.Module();
            double tModB = ppComplexA.Module();
            return tModA.CompareTo(tModB);
        }

        public int CompareTo(object ppObject)
        {
            if (!(ppObject is Complex))
            {
                return 0;
            }
            return CompareTo((Complex)ppObject);
        }
    }
}