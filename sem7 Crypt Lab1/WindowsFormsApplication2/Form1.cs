using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //==================================================
        //   Лабораторная работа 1
        //==================================================
        private bool SampleTest (int i)
        {
            if (i % 2 == 0 && i != 2) return false;
            int maxI = (int)Math.Truncate(Math.Sqrt(i));
            int j = 3;
            while (j <= maxI)
            {
                if ((i % j) == 0)
                {
                    return false;
                }
                j += 2;
            }
            return true;
        } 

        private void Lab1Button_Click(object sender, EventArgs e)
        {
            Lab1Result.Items.Clear();
            int tValueM = Convert.ToInt32(Lab1TextM.Text);
            for (int i = 2; i <= tValueM; i++)
            {
                if (SampleTest(i)) Lab1Result.Items.Add(i);
            }
        }

        //==================================================
        //   Лабораторная работа 2
        //==================================================


        private int PowModule (int a, int b, int mod)
        {
            return (int)Math.Pow(a, b) % mod;
        }

        private void Lab2Button_Click(object sender, EventArgs e)
        {
            Lab2Result.Items.Clear();
            int tValueM = Convert.ToInt32(Lab2TextM.Text);
            int tEulerValue = 2;
            for (int i = 2; i <= tValueM; i++)
            {
                if (SampleTest(i)) tEulerValue++;
            }

            int tRoot = 1;
            for (int i = 2; i <= tValueM; i++)
            {
                bool tResult = true;
                //a ^ euler = 1 (mod)
                if ((int)Math.Pow(i, tEulerValue) % tValueM != 1)
                {
                    tResult = false;
                }

                //a ^ l = 1 (mod)
                if (tResult)
                {
                    for (int j = 1; j < tEulerValue; j++)
                    {
                        if ((int)Math.Pow(i, j) % tValueM == 1)
                        {
                            tResult = false;
                        }
                    }
                }

                if (tResult)
                {
                    tRoot = i;
                    break;
                }        
            }

            for (int i = 0; i < tEulerValue; i++)
            {
                int tTemp = (int)Math.Pow(tRoot, i) % tValueM;
                Lab2Result.Items.Add(tTemp);
            }
        }

        //==================================================
        //   Лабораторная работа 3
        //==================================================
        private void Lab3Button_Click(object sender, EventArgs e)
        {
            int tValueM = Convert.ToInt32(Lab3TextM.Text);
            int tEulerValue = 0;
            if (tValueM >= 2) tEulerValue = 2; else tEulerValue = tValueM+1;
            for (int i = 2; i <= tValueM; i++)
            {
                if (SampleTest(i)) tEulerValue++;
            }
            Lab3Result.Text = tEulerValue.ToString();
        }

        //==================================================
        //   Лабораторная работа 4
        //==================================================
        private void Lab4Button_Click(object sender, EventArgs e)
        {

            Lab4Result.Items.Clear();
            int tValueM = Convert.ToInt32(Lab4TextM.Text);
            Dictionary<int, int> tResultList = new Dictionary<int, int>();
            int tDivider = 2;
            while (tValueM != 1)
            {
                if (tValueM % tDivider == 0)
                {
                    tValueM /= tDivider;
                    if (tResultList.Keys.Contains(tDivider))
                    {
                        tResultList[tDivider] = tResultList[tDivider] + 1;
                    }
                    else
                    {
                        tResultList.Add(tDivider, 1);
                    }
                } else
                {
                    tDivider++;
                }       
            }

            foreach (int tKey in tResultList.Keys)
            {
                Lab4Result.Items.Add(tKey.ToString() + " ^ " + tResultList[tKey].ToString());
            }
        }

        //==================================================
        //   Лабораторная работа 5
        //==================================================
        private void Lab5Button_Click(object sender, EventArgs e)
        {
            uint tValueM = (uint)Convert.ToInt32(Lab5TextM.Text);
            uint tValueA = (uint)Convert.ToInt32(Lab5TextA.Text);
            uint tValueN = (uint)Convert.ToInt32(Lab5TextN.Text);

            uint tResult = 1;
            while (tValueN != 0)
            {
                if ((tValueN & 1) != 0)
                   tResult *= tValueA;
                tValueA *= tValueA;
                tValueN >>= 1;
            }
            tResult %= tValueM;
            Lab5Result.Text = tResult.ToString();
        }
    }
}
