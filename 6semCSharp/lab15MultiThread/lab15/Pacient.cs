using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;

namespace lab15
{
    enum PacientType
    {
        //состояния здоровья
        StatusNormal = 0,
        StatusAnnoy = 1,

        //случай
        AnnoyNormal = 0,
        AnnoyUnique = 1,

        //рандом
        DiseaseChance = 35, //шанс того, что пациент болен
        UniqueChance = 25, //шанс того, что пациент имеет уникальный случай
    }
    class Pacient
    {
        private byte prHealth; //здоровье
        private byte prAnnoyType; //тип случая
        private int prIncubationTime;
        private bool prFDoctor;

        public Pacient ()
        {
            Random tRand = new Random();
            prHealth = tRand.Next(0, 100) <= (int)PacientType.DiseaseChance ?
                (byte)PacientType.StatusAnnoy : (byte)PacientType.StatusNormal;
            prAnnoyType = tRand.Next(0, 100) <= (int)PacientType.UniqueChance ?
                (byte)PacientType.AnnoyUnique : (byte)PacientType.AnnoyNormal;
            prIncubationTime = tRand.Next(1,(int)HospitalParams.Incubation);
        }

        public void mSetStatus (bool ppDiseased = false)
        {
            prHealth = ppDiseased ?
                (byte)PacientType.StatusAnnoy : (byte)PacientType.StatusNormal;
            if (ppDiseased)
            {
                Random tRand = new Random();
                prAnnoyType = tRand.Next(0, 100) <= (int)PacientType.UniqueChance ?
                    (byte)PacientType.AnnoyUnique : (byte)PacientType.AnnoyNormal;
            }
        }

        public byte mGetType()
        {
            return prAnnoyType;
        }

        public byte mGetStatus()
        {
            return prHealth;
        }

        public void mNextTick ()
        {
            if (prIncubationTime != 0 && prHealth == (byte)PacientType.StatusAnnoy)
            {
                prIncubationTime--;
            }
        }

        public int mIncubation
        {
            set
            {
                prIncubationTime = value;
            }
            get
            {
                return prIncubationTime;
            }
        }

        public bool mDoctor
        {
            set
            {
                prFDoctor = value;
            }
            get
            {
                return prFDoctor;
            }
        }
    }
}
