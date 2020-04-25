using System;
using System.Collections.Generic;
using System.Text;

namespace lab11
{
    class VectorException : Exception
    {
        public VectorException(string message)
            : base(message)
        { }
    }

    class Vector<T>: IComparable, IComparable<Vector<T>> where T : IComparable, new()
    {

        // Переменныe
        List<T> prElements;

        // Конструкторы
        public Vector(int ppElement)
        {
            prElements = new List<T>(new T[ppElement]);
        }

        public Vector(List<T> ppVector)
        {
            prElements = new List<T>(new T[ppVector.Count]);
            for (int i = 0; i < ppVector.Count; i++)
            {
                prElements[i] = ppVector[i];
            }
        }

        public Vector(T[] ppVector)
        {
            prElements = new List<T>(new T[ppVector.Length]);
            for (int i = 0; i < ppVector.Length; i++)
            {
                prElements[i] = ppVector[i];
            }
        }

        public Vector()
        {
            prElements = new List<T>(0);
        }

        //Перегрузки операторов
        //Оператор сложения
        public static Vector<T> operator +(Vector<T> ppElementA, Vector<T> ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            if (tSize != ppElementB.mVectorSize)
            {
                throw new VectorException("Размеры векторов не совпадают");
            }
            Vector<T> tResultVector = new Vector<T>(tSize);
            for (int i = 0; i < tSize; i++)
            {
                tResultVector.prElements[i] = (dynamic)ppElementA.prElements[i] + ppElementB.prElements[i];
            }
            return tResultVector;
        }
        //Оператор вычитания
        public static Vector<T> operator -(Vector<T> ppElementA, Vector<T> ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            if (tSize != ppElementB.mVectorSize)
            {
                throw new VectorException("Размеры векторов не совпадают");
            }
            Vector<T> tResultVector = new Vector<T>(tSize);
            for (int i = 0; i < tSize; i++)
            {
                tResultVector.prElements[i] = (dynamic)ppElementA.prElements[i] - ppElementB.prElements[i];
            }
            return tResultVector;
        }
        //Оператор умножения (скалярное произведение)

        public static T operator *(Vector<T> ppElementA, Vector<T> ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            if (tSize != ppElementB.mVectorSize)
            {
                throw new VectorException("Размеры векторов не совпадают");
            }
            T tResult = new T();
            for (int i = 0; i < tSize; i++)
            {
                if (i == 0)
                {
                    tResult = (dynamic)ppElementA.prElements[i] * ppElementB.prElements[i];
                }
                else
                {
                    tResult += (dynamic)ppElementA.prElements[i] * ppElementB.prElements[i];
                }
            }
            return tResult;
        }
        //Оператор умножения (на число)
        public static Vector<T> operator *(Vector<T> ppElementA, T ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            Vector<T> tResultVector = new Vector<T>(tSize);
            for (int i = 0; i < tSize; i++)
            {
                tResultVector.prElements[i] = (dynamic)ppElementA.prElements[i] * ppElementB;
            }
            return tResultVector;
        }
        //Оператор деления на число
        public static Vector<T> operator /(Vector<T> ppElementA, T ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            Vector<T> tResultVector = new Vector<T>(tSize);
            for (int i = 0; i < tSize; i++)
            {
                tResultVector.prElements[i] = (dynamic)ppElementA.prElements[i] / ppElementB;
            }
            return tResultVector;
        }

        //методы
        //сравнение
        public int CompareTo(object ppObject)
        {
            if (!(ppObject is Vector<T>))
            {
                return 0;
            }
            return CompareTo((Vector<T>)ppObject);
        }
        public int CompareTo(Vector<T> ppVectorA)
        {
            double tModA = this.mModule();
            double tModB = ppVectorA.mModule();
            return tModA.CompareTo(tModB);
        }

        //ортогонализация
        //Алгоритм Грама-Шмидта
        public static Vector<T>[] mOrtogonalize(Vector<T>[] ppSystem)
        {
            int tSize = ppSystem.Length;
            if (tSize == 0)
            {
                throw new VectorException("Передана пустая система.");
            }
            //проверка на размеры векторов
            int tVectorSize = ppSystem[0].mVectorSize;
            for (int i = 1; i < tSize; i++)
            {
                if (ppSystem[i].mVectorSize != tVectorSize)
                {
                    throw new VectorException("Размеры векторов не совпадают");
                }
            }
            //Алгоритм Грама-Шмидта
            Vector<T>[] tResult = new Vector<T>[tSize];
            for (int i = 0; i < tSize; i++)
            {
                tResult[i] = ppSystem[i];
                for (int j = 0; j < i; j++)
                {
                    tResult[i] -= mpProjection(ppSystem[i], ppSystem[j]);
                }
            }
            return tResult;
        }
        //проекция (для Г-Ш)
        private static Vector<T> mpProjection (Vector<T> ppElementA, Vector<T> ppElementB)
        {
            int tSize = ppElementA.mVectorSize;
            if (tSize != ppElementB.mVectorSize)
            {
                throw new VectorException("Размеры векторов не совпадают");
            }
            Vector<T> tResultVector = new Vector<T>(tSize);
            tResultVector = ppElementB * (((dynamic)ppElementA * ppElementB)/ ((ppElementB * ppElementB)));
            /// (ppElementB * ppElementB))*ppElementB
            return tResultVector;
        }
        //модуль
        public double mModule()
        {
            int tSize = mVectorSize;
            double tResult = 0;
            if (typeof(T).Name.Equals("Complex")) {
                for (int i = 0; i < tSize; i++)
                {
                    double tComplexModule = ((Complex)(Object)prElements[i]).Module();
                    tComplexModule *= tComplexModule;
                    if (i == 0)
                    {
                        tResult = tComplexModule;
                    }
                    else
                    {
                        tResult += tComplexModule;
                    }
                }
                return Math.Sqrt(tResult);
            }
            else
            {
                for (int i = 0; i < tSize; i++)
                {
                    if (i == 0)
                    {
                        tResult = (dynamic)prElements[i] * prElements[i];
                    }
                    else
                    {
                        tResult += (dynamic)prElements[i] * prElements[i];
                    }
                }
                return Math.Sqrt(tResult);
            }
        }
        //преобразование в массив
        public T[] mArrayIn ()
        {
            T[] tResult = new T[mVectorSize];
            for (int i = 0; i < mVectorSize; i++)
            {
                tResult[i] = prElements[i];
            }
            return tResult;
        }
        //преобразование из массива
        public void mArrayIn(T[] tArray)
        {
            prElements = new List<T>(new T[tArray.Length]);
            for (int i = 0; i < tArray.Length; i++)
            {
                prElements[i] = tArray[i];
            }
        }

        //размер вектора
        public int mVectorSize
        {
            get {
                return prElements.Count;
            }
        }

        //Вывод
        public override string ToString()
        {
            StringBuilder tResult = new StringBuilder("(  ");
            for (int i = 0; i < mVectorSize; i++)
            {
                tResult.Append(prElements[i]).Append("  ");
            }
            tResult.Append(")");
            return tResult.ToString();
        }
    }
}
