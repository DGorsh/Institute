using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace lab15
{
    enum HospitalParams
    {
        //параметры
        HospitalPacientCount = 20, //количество мест в смотровой
        HospitalDoctorCount = 5, //количество врачей
        MaxPacients = 100, //всего возможно пациентов
        ShowTime = 20, //время осмотра
        //рандом
        PandemicChance = 50, //шанс заразить отдельного человека  (%)
        Incubation = 10, //время на заражение (макс)
        NewPacientChance = 60 //шанс появления нового пациента за ед. времени
    }
    class ProgClass
    {
        private Doctor[] prDoctors;
        private Stack<int> prNeedHelp;
        private Pacient[] prPacient;
        private int prCurrentPacient;
        private List<int> prPacientOut;
        private List<int> prPacientHospital;
        private Random tRand;
        static object locker = new object();

        private bool prFNewPacient, prFPandemic;
        private Stack<int> prFDisease;

        public ProgClass()
        {
            tRand = new Random();
            prDoctors = new Doctor[(int)HospitalParams.HospitalDoctorCount];
            prPacient = new Pacient[(int)HospitalParams.MaxPacients];
            prPacientOut = new List<int>();
            prPacientHospital = new List<int>();
            prFDisease = new Stack<int>();
            prNeedHelp = new Stack<int>();
            prCurrentPacient = 0;
            prFNewPacient = false;
            prFPandemic = false;

            for (int i = 0; i < prDoctors.Length; i++)
            {
                prDoctors[i] = new Doctor();
            }

            for (int i = 0; i < prPacient.Length; i++)
            {
                prPacient[i] = new Pacient();
            }
        }

        public void mSolution()
        {
            StringBuilder tResult = new StringBuilder();
            Thread tNewPacient = new Thread(mNewPacient); tNewPacient.Start();
            Thread tSetPacientInHospital = new Thread(mSetPacientInHospital); tSetPacientInHospital.Start();
            Thread tPandemic = new Thread(mPandemic); tPandemic.Start();
            for (int i = 0; i < (int)HospitalParams.HospitalDoctorCount; i++)
            {
                ThreadPool.QueueUserWorkItem(mDoctorWork, i);
            }

            for (int i = 0; i < (int)HospitalParams.MaxPacients; i++)
            {
                ThreadPool.QueueUserWorkItem(mPacientLife, i);
            }

            while (prPacientOut.Count != 0 || prPacientHospital.Count != 0 || prCurrentPacient < (int)HospitalParams.MaxPacients - 1)
            {
                Console.Clear();

                for (int i = 0; i < prDoctors.Length; i++)
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.Write("Чумной доктор [{0}]: \n", i);
                    Console.ResetColor();
                    if (prDoctors[i].mIsHelping())
                    {
                        Console.Write("Помогает доктору {0}\n", prDoctors[i].Helping);
                    }
                    else
                    {
                        if (prDoctors[i].mPacient != null)
                        {
                            Console.Write("Работает с больным {0}, с которым осталось возиться {1} c.\n", Array.IndexOf(prPacient, prDoctors[i].mPacient),
                                prDoctors[i].mTimeWork);
                            if (prDoctors[i].mNeedHelp)
                            {
                                Console.Write("Пациент боится делать прививку! Врачу нужна помощь!!!\n");
                            }
                        }
                        else
                        {
                            Console.Write("Ничего не делает...\n");
                        }

                    }

                }

                if (prFNewPacient)
                {
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("В очереди новый пациент!");
                    Console.ResetColor();
                    prFNewPacient = false;
                    Console.ResetColor();
                }

                if (prFPandemic)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Обнаружен зараженный пациент!");
                    while (prFDisease.Count!=0)
                    {
                         Console.WriteLine("Пациент [{0}], кажется, чихнул...", prFDisease.Pop());
                    }
                    Console.ResetColor();
                    prFPandemic = false;
                }

                Console.ResetColor();
                Console.WriteLine("Пациенты в смотровой:\n");
                foreach (var tPacient in prPacientHospital)
                {
                    Console.Write("[{0}] = {1}  ", tPacient,
                        prPacient[tPacient].mGetStatus() == (byte)PacientType.StatusAnnoy ? "Б" : "З");
                }

                Console.Write("\nПациенты в очереди:\n");
                foreach (var tPacient in prPacientOut)
                {
                    Console.Write("[{0}] = {1}  ", tPacient,
                        prPacient[tPacient].mGetStatus() == (byte)PacientType.StatusAnnoy ? "Б" : "З");
                }

                Thread.Sleep(500);
            }

        }

        private void mSetPacientInHospital()
        {
            while (prPacientOut.Count != 0 || prPacientHospital.Count != 0 || prCurrentPacient < (int)HospitalParams.MaxPacients - 1)
            {
                lock (locker)
                {
                    if (prPacientHospital.Count < (int)HospitalParams.HospitalPacientCount)
                    {
                        if (prPacientOut.Count != 0)
                        {
                            bool tDiseased = false;

                            foreach (var tPacient in prPacientHospital)
                            {
                                if (prPacient[tPacient].mGetStatus() == (byte)PacientType.StatusAnnoy)
                                {
                                    tDiseased = true;
                                }
                            }
                            if ((!tDiseased && (prPacient[prPacientOut[0]].mGetStatus() != (byte)PacientType.StatusAnnoy)) ||
                                (prPacientHospital.Count == 0) || (tDiseased && (prPacient[prPacientOut[0]].mGetStatus() != (byte)PacientType.StatusNormal)))
                            {
                                prPacientHospital.Add(prPacientOut[0]);
                                prPacientOut.RemoveAt(0);
                            }
                        }
                    }
                }
                Thread.Sleep(1000);
            }
        }

        private void mNewPacient ()
        {
            while (prPacientOut.Count != 0 || prPacientHospital.Count != 0 || prCurrentPacient < (int)HospitalParams.MaxPacients - 1)
            {
                if (tRand.Next(0, 100) <= (int)HospitalParams.NewPacientChance)
                {
                    if (prCurrentPacient < (int)HospitalParams.MaxPacients)
                    {
                        prPacientOut.Add(prCurrentPacient++);
                        prFNewPacient = true;
                    }
                }
                Thread.Sleep(1000);
            }
        }

        private void mPandemic ()
        {
            while (prPacientOut.Count != 0 || prPacientHospital.Count != 0 || prCurrentPacient < (int)HospitalParams.MaxPacients - 1)
            {
                bool tPandemic = false;
                lock (locker)
                {
                    foreach (var tPacient in prPacientOut)
                    {
                        if (prPacient[tPacient].mGetStatus() == (byte)PacientType.StatusAnnoy &&
                            prPacient[tPacient].mIncubation == 0)
                        {
                            tPandemic = true;
                        }
                    }

                    if (tPandemic)
                    {
                        foreach (var tPacient in prPacientOut)
                        {
                            if (tRand.Next(1, 100) <= (int)HospitalParams.PandemicChance)
                            {
                                if (prPacient[tPacient].mGetStatus() != (byte)PacientType.StatusAnnoy)
                                {
                                    prPacient[tPacient].mSetStatus(true);
                                    prFDisease.Push(tPacient);
                                }
                            }
                        }
                        prFPandemic = true;
                    }
                }
                Thread.Sleep(1000);
            }
        }

        private void mDoctorWork(Object threadContext)
        {
            Doctor tDoctor = prDoctors[(int)threadContext];
            while (prPacientOut.Count != 0 || prPacientHospital.Count != 0 || prCurrentPacient < (int)HospitalParams.MaxPacients - 1)
            {
                lock (locker)
                {
                    if (tDoctor.mIsHelping())
                    {
                        if (!prDoctors[tDoctor.Helping].mNeedHelp || prDoctors[tDoctor.Helping].mIsHelping())
                        {
                            tDoctor.Helping = -1;
                        }
                    }
                    tDoctor.mNextSecond();
                    if (tDoctor.mPacient == null)
                    {
                        if (prNeedHelp.Count != 0)
                        {
                            if (!tDoctor.mIsHelping())
                            {
                                tDoctor.Helping = prNeedHelp.Peek();
                                tDoctor.mTimeWork = tRand.Next(1, (int)HospitalParams.ShowTime);
                                prDoctors[prNeedHelp.Peek()].mTimeWork += tDoctor.mTimeWork;
                                prDoctors[prNeedHelp.Pop()].mGetHelp = true;
                            }
                        }
                        else
                        {
                            if (tDoctor.mNeedHelp)
                            {
                                prNeedHelp.Push(Array.IndexOf(prDoctors, tDoctor));
                                tDoctor.mNeedHelp = false;
                            }
                            else
                            {
                                if (prPacientHospital.Count != 0)
                                {
                                    if (!prPacient[prPacientHospital[0]].mDoctor)
                                    {
                                        prPacient[prPacientHospital[0]].mDoctor = true;
                                        tDoctor.mPacient = prPacient[prPacientHospital[0]];
                                        tDoctor.mTimeWork = tRand.Next(1, (int)HospitalParams.ShowTime);
                                        prPacientHospital.RemoveAt(0);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (tDoctor.mNeedHelp && !tDoctor.mGetHelp)
                        {
                            if (!prNeedHelp.Contains(Array.IndexOf(prDoctors, tDoctor)))
                            {
                                prNeedHelp.Push(Array.IndexOf(prDoctors, tDoctor));
                            }
                        }
                    }
                }
                Thread.Sleep(1000);
            }
        }

        private void mPacientLife (Object threadContext)
        {
            Pacient tPacient = prPacient[(int)threadContext];
            tPacient.mNextTick();
        }
    }
}
