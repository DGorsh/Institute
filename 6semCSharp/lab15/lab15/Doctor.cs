using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace lab15
{
    enum DoctorParams
    {
        HelpChance = 20
    }
    class Doctor
    {
        private Pacient prCurrentPacient;
        private int prTimeWork;
        private bool prNeedHelp;
        private int prHelping;
        private bool prGetHelp;

        public Doctor ()
        {
            Random tRand = new Random();
            prCurrentPacient = null;
            prTimeWork = 0;
            prNeedHelp = false;
            prHelping = -1;
            prGetHelp = false;
        }

        public void mNextSecond()
        {
            if (prTimeWork == 0)
            {
                if (prCurrentPacient != null)
                {
                    prCurrentPacient.mSetStatus();
                    prCurrentPacient = null;
                }

                if (mNeedHelp)
                {
                    prNeedHelp = false;
                    prGetHelp = false;
                }
            } else
            {
                if (prCurrentPacient != null)
                {
                    if (prCurrentPacient.mGetType() == (byte)PacientType.AnnoyUnique)
                    {
                        Random tRand = new Random();
                        if (tRand.Next(0, 100) <= (int)DoctorParams.HelpChance)
                        {
                            prNeedHelp = true;
                        }
                    }
                }
                if ((prHelping == -1) && (prGetHelp || !prNeedHelp))
                {
                    prTimeWork--;
                }
            }
        }

        public Pacient mPacient
        {
            set {
                prCurrentPacient = value;
            }
            get
            {
                return prCurrentPacient;
            }
        }

        public bool mIsHelping ()
        {
            if (prHelping != -1)
            {
                return true;
            }
            return false;
        }

        public int Helping
        {
            get
            {
                return prHelping;
            }

            set
            {
                prHelping = value;
            }
        }

        public bool mNeedHelp
        {
            get
            {
                return prNeedHelp;
            }
            set
            {
                prNeedHelp = value;
            }
        }

        public int mTimeWork
        {
            get
            {
                return prTimeWork;
            }
            set
            {
                prTimeWork = value;
            }
        }

        public bool mGetHelp
        {
            set
            {
                prGetHelp = value;
            }
            get
            {
                return prGetHelp;
            }
        }
    }
}
