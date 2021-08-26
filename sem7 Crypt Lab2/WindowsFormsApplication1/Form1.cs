using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //==========================================
        //Laboratory Work 1
        //==========================================
        private void Lab1TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab1TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab1TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab1TextInputResult.Text = "Error!";
                return;
            }
            Lab1TextInputResult.Text = Convert.ToInt32(Lab1TextCurValue.Text, 2).ToString();
        }

        // Step 1
        private void Lab1TextButtonA_Click(object sender, EventArgs e)
        {
            if (!Lab1TextInputResult.Text.Equals("Error!"))
            {
                StringBuilder tBeforeText = new StringBuilder(Lab1TextInputResult.Text);
                tBeforeText.Append(" (10),     ").Append(Lab1TextCurValue.Text).Append(" (2)     ");
                tBeforeText.Append(Lab1TextInputK.Value.ToString()).Append(" (k)");
                Lab1TextBefore.Text = tBeforeText.ToString();
                int tValue = Convert.ToInt32(Lab1TextInputResult.Text, 10);
                int tPower = 1 << ((int)Lab1TextInputK.Value-1);
                tValue = (tValue & tPower) >> ((int)Lab1TextInputK.Value-1);
                Lab1TextAfter.Text = tValue.ToString();
            } else
            {
                Lab1TextBefore.Text = "Error";
                Lab1TextAfter.Text = "Error";
            }
        }

        //Step 2
        private void Lab1TextButtonB_Click(object sender, EventArgs e)
        {
            if (!Lab1TextInputResult.Text.Equals("Error!"))
            {
                StringBuilder tText = new StringBuilder(Lab1TextInputResult.Text);
                tText.Append(" (10),     ").Append(Lab1TextCurValue.Text).Append(" (2)     ");
                tText.Append(Lab1TextInputK.Value.ToString()).Append(" (k)");
                Lab1TextBefore.Text = tText.ToString();
                int tValue = Convert.ToInt32(Lab1TextInputResult.Text, 10);
                int tPower = 1 << ((int)Lab1TextInputK.Value - 1);
                tValue = tValue ^ tPower;

                tText.Clear();
                tText.Append(tValue.ToString()).Append(" (10),     ");
                tText.Append(Convert.ToString(tValue, 2)).Append(" (2)     ");
                Lab1TextAfter.Text = tText.ToString();

                Lab1TextCurValue.Text = Convert.ToString(tValue, 2);
            }
            else
            {
                Lab1TextBefore.Text = "Error";
                Lab1TextAfter.Text = "Error";
            }
        }

        //Step 3
        private void Lab1TextButtonC_Click(object sender, EventArgs e)
        {
            if (!Lab1TextInputResult.Text.Equals("Error!") || Lab1TextInputI.Value == Lab1TextInputJ.Value)
            {
                StringBuilder tText = new StringBuilder(Lab1TextInputResult.Text);
                tText.Append(" (10),     ").Append(Lab1TextCurValue.Text).Append(" (2)     ");
                tText.Append(Lab1TextInputI.Value.ToString()).Append(" (i)     ");
                tText.Append(Lab1TextInputJ.Value.ToString()).Append(" (j)     ");
                Lab1TextBefore.Text = tText.ToString();
                int tValue = Convert.ToInt32(Lab1TextInputResult.Text, 10);
                int tPowerI = 1 << ((int)Lab1TextInputI.Value - 1);
                int tPowerJ = 1 << ((int)Lab1TextInputJ.Value - 1);
                int tResultI = (tValue & tPowerI) >> ((int)Lab1TextInputI.Value - 1);
                int tResultJ = (tValue & tPowerJ) >> ((int)Lab1TextInputJ.Value - 1);
                //I Value
                if (tResultJ == 1)
                {
                    tValue = tValue | (1 << ((int)Lab1TextInputI.Value - 1));
                } else
                {
                    tValue = tValue & ~(1 << ((int)Lab1TextInputI.Value - 1));
                }
                //J Value
                if (tResultI == 1)
                {
                    tValue = tValue | (1 << ((int)Lab1TextInputJ.Value - 1));
                }
                else
                {
                    tValue = tValue & ~(1 << ((int)Lab1TextInputJ.Value - 1));
                }
                tText.Clear();
                tText.Append(tValue.ToString()).Append(" (10),     ");
                tText.Append(Convert.ToString(tValue, 2)).Append(" (2)     ");
                Lab1TextAfter.Text = tText.ToString();
                //Lab1TextAfter.Text = Convert.ToString(~(1 << ((int)Lab1TextInputI.Value - 1)), 2);
                Lab1TextCurValue.Text = Convert.ToString(tValue, 2);
            }
            else
            {
                Lab1TextBefore.Text = "Error";
                Lab1TextAfter.Text = "Error";
            }
        }

        //Step 4
        private void Lab1TextButtonD_Click(object sender, EventArgs e)
        {
            if (!Lab1TextInputResult.Text.Equals("Error!"))
            {
                StringBuilder tText = new StringBuilder(Lab1TextInputResult.Text);
                tText.Append(" (10),     ").Append(Lab1TextCurValue.Text).Append(" (2)     ");
                tText.Append(Lab1TextInputK.Value.ToString()).Append(" (k)");
                Lab1TextBefore.Text = tText.ToString();
                int tValue = Convert.ToInt32(Lab1TextInputResult.Text, 10);
                int tMinus = 0;

                for (int i = 0; i < Lab1TextInputM.Value; i++)
                {
                    tMinus |= (1 << i);
                }
                tValue &= ~tMinus;

                tText.Clear();
                tText.Append(tValue.ToString()).Append(" (10),     ");
                tText.Append(Convert.ToString(tValue, 2)).Append(" (2)     ");
                Lab1TextAfter.Text = tText.ToString();
                //Lab1TextAfter.Text = tMinus.ToString();

                Lab1TextCurValue.Text = Convert.ToString(tValue, 2);
            }
            else
            {
                Lab1TextBefore.Text = "Error";
                Lab1TextAfter.Text = "Error";
            }
        }

        //==========================================
        //Laboratory Work 3
        //==========================================
        private void Lab3TextButtonC_Click(object sender, EventArgs e)
        {
            if (!Lab3TextInputResult.Text.Equals("Error!") || Lab3TextInputI.Value == Lab3TextInputJ.Value)
            {
                StringBuilder tText = new StringBuilder(Lab3TextInputResult.Text);
                tText.Append(" (10),     ").Append(Lab3TextCurValue.Text).Append(" (2)     ");
                tText.Append(Lab3TextInputI.Value.ToString()).Append(" (i)     ");
                tText.Append(Lab3TextInputJ.Value.ToString()).Append(" (j)     ");
                Lab3TextBefore.Text = tText.ToString();
                int tValue = Convert.ToInt32(Lab3TextInputResult.Text, 10);
                int tPowerI = 255 << (((int)Lab3TextInputI.Value - 1)*8);
                int tPowerJ = 255 << (((int)Lab3TextInputJ.Value - 1)*8);
                int tResultI = (tValue & tPowerI) >> (((int)Lab3TextInputI.Value - 1)*8);
                int tResultJ = (tValue & tPowerJ) >> (((int)Lab3TextInputJ.Value - 1)*8);
                //I Value 10101011000000001111111100000000
                for (int i = 0; i < 8; i++)
                {
                    int tRes = (tResultJ & (1 << i)) >> i;
                    if (tRes == 1)
                    {
                        tValue = tValue | (1 << (((int)Lab3TextInputI.Value - 1)) * 8 + i);
                    }
                    else
                    {
                        tValue = tValue & ~(1 << (((int)Lab3TextInputI.Value - 1)) * 8 + i);
                    }
                }
                //J Value
                for (int i = 0; i < 8; i++)
                {
                    int tRes = (tResultI & (1 << i)) >> i;
                    if (tRes == 1)
                    {
                        tValue = tValue | (1 << (((int)Lab3TextInputJ.Value - 1)) * 8 + i);
                    }
                    else
                    {
                        tValue = tValue & ~(1 << (((int)Lab3TextInputJ.Value - 1)) * 8 + i);
                    }
                }
                tText.Clear();
                tText.Append(tValue.ToString()).Append(" (10),     ");
                tText.Append(Convert.ToString(tValue, 2)).Append(" (2)     ");
                Lab3TextAfter.Text = tText.ToString();
                //Lab3TextAfter.Text = Convert.ToString(~(1 << ((int)Lab3TextInputI.Value - 1)), 2);
                Lab3TextCurValue.Text = Convert.ToString(tValue, 2);
            }
            else
            {
                Lab3TextBefore.Text = "Error";
                Lab3TextAfter.Text = "Error";
            }
        }

        private void Lab3TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab3TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab3TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab3TextInputResult.Text = "Error!";
                return;
            }
            Lab3TextInputResult.Text = Convert.ToInt32(Lab3TextCurValue.Text, 2).ToString();
        }

        //==========================================
        //Laboratory Work 8
        //==========================================
        private void Lab8TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab8TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab8TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab8TextInputResult.Text = "Error!";
                return;
            }
            Lab8TextInputResult.Text = Convert.ToInt32(Lab8TextCurValue.Text, 2).ToString();
        }

        private void Lab8ButtonTrans_Click(object sender, EventArgs e)
        {
            int[] tTransformArray = new int[Lab8TextCurValue.Text.Count()];
            string tValueString = Lab8TextCurTrans.Text;
            string[] tTempTextArray = tValueString.Split(' ');
            for (int i = 0; i < tTempTextArray.Count(); i++)
            {
                try
                {
                    tTransformArray[i] = Convert.ToInt32(tTempTextArray[i], 10);
                } catch (Exception)
                {
                    Lab8TextInputResult.Text = "Error!";
                    return;
                }
            }

            int tResultValue = 0;
            int tInputValue = Convert.ToInt32(Lab8TextInputResult.Text, 10);
            for (int i = tTransformArray.Count() - 1; i >= 0 ; i--)
            {
                int tValue = tInputValue;
                int tPower = 1 << (tTransformArray[i]);
                tValue = (tValue & tPower) >> (tTransformArray[i]);

                tResultValue |= (tValue) << (tTransformArray.Count() - 1 - i);
            }

            Lab8TextBefore.Text = Lab8TextCurValue.Text;
            Lab8TextAfter.Text = Convert.ToString(tResultValue, 2);
        }

        //==========================================
        //Laboratory Work 6
        //==========================================
        private void Lab6Button_Click(object sender, EventArgs e)
        {
            int tResult = 0;
            string tTempInput = Lab6TextCurValue.Text;
            int tInputValue = Convert.ToInt32(Lab6TextInputResult.Text, 10);
            for (int i = 0; i < Lab6TextCurValue.Text.Count(); i++)
            {
                int tValue = tInputValue;
                int tPower = 1 << i;
                tValue = (tValue & tPower) >> i;

                if (i==0)
                {
                    tResult = tValue;
                } else
                {
                    tResult ^= tValue;
                }
            }
            Lab6TextBefore.Text = Lab6TextCurValue.Text;
            Lab6TextAfter.Text = Convert.ToString(tResult, 2);
        }

        private void Lab6TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab6TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab6TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab6TextInputResult.Text = "Error!";
                return;
            }
            Lab6TextInputResult.Text = Convert.ToInt32(Lab6TextCurValue.Text, 2).ToString();
        }

        //==========================================
        //Laboratory Work 2
        //==========================================
        private void Lab2TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab2TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab2TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab2TextInputResult.Text = "Error!";
                return;
            }
            Lab2TextInputResult.Text = Convert.ToInt32(Lab2TextCurValue.Text, 2).ToString();
        }

        private void Lab2TextButtonB_Click(object sender, EventArgs e)
        {
            //Bit Mask
            //i bites
            int tIValue = (int)Math.Pow(2, (double)Lab2TextInputI.Value) - 1;
            //bit mask
            //int tMainMask = ((0 | tIValue) >> (int)Lab2TextInputI.Value) | tIValue;
            string tValueString = Lab2TextCurValue.Text;
            int tMainMask = ((0 | tIValue) << (tValueString.Count() - (int)Lab2TextInputI.Value)) | tIValue;
            Lab2TextBefore.Text = Convert.ToString(tMainMask, 2);

            //Inverse mask
            tMainMask = ~(tMainMask);
            //Main
            int tInputValue = Convert.ToInt32(Lab2TextInputResult.Text, 10);
            tInputValue = (tInputValue & tMainMask) >> (int)Lab2TextInputI.Value;

            Lab2TextBefore.Text = Lab2TextCurValue.Text;
            tValueString = Convert.ToString(tInputValue, 2);
            if (tValueString.Count() < (Lab2TextCurValue.Text.Count() - 2 * (int)Lab2TextInputI.Value))
            {
                int tZeros = (Lab2TextCurValue.Text.Count() - 2 * (int)Lab2TextInputI.Value) - tValueString.Count();
                StringBuilder tZeroString = new StringBuilder();
                for (int i = 0; i < tZeros; i++)
                {
                    tZeroString.Append("0");
                }
                tValueString = tValueString.Insert(0, tZeroString.ToString());
            }
            Lab2TextAfter.Text = tValueString;
        }

        private void Lab2TextButtonA_Click(object sender, EventArgs e)
        {
            int tInputValue = Convert.ToInt32(Lab2TextInputResult.Text, 10);
            //Bit Mask
            //i bites
            int tIValue = (int)Math.Pow(2, (double)Lab2TextInputI.Value) - 1;
            //bit mask
            //int tMainMask = ((0 | tIValue) >> (int)Lab2TextInputI.Value) | tIValue;
            string tValueString = Lab2TextCurValue.Text;
            //low bites
            int tValue = 0 | (tIValue & tInputValue);
            //high bites
            int tMainMask = (((tIValue) << (tValueString.Count() - (int)Lab2TextInputI.Value))& tInputValue) >> (tValueString.Count() - 2 * (int)Lab2TextInputI.Value);
            tValue |= tMainMask;


            Lab2TextBefore.Text = Lab2TextCurValue.Text;
            tValueString = Convert.ToString(tValue, 2);
            if (tValueString.Count() < (2 * (int)Lab2TextInputI.Value))
            {
                int tZeros = (2 * (int)Lab2TextInputI.Value) - tValueString.Count();
                StringBuilder tZeroString = new StringBuilder();
                for (int i = 0; i < tZeros; i++)
                {
                    tZeroString.Append("0");
                }
                tValueString = tValueString.Insert(0, tZeroString.ToString());
            }
            Lab2TextAfter.Text = tValueString;
        }

        //==========================================
        //Laboratory Work 4
        //==========================================
        private void Lab4Button_Click(object sender, EventArgs e)
        {
            int tInputValue = Convert.ToInt32(Lab4TextInputResult.Text, 10);
            if (tInputValue == 0)
            {
                Lab4TextBefore.Text = tInputValue.ToString();
                Lab4TextAfter.Text = "Any";
                return;
            };

            int tMaxPower = (int)Math.Log(tInputValue & -tInputValue, 2);
            Lab4TextBefore.Text = tInputValue.ToString();
            Lab4TextAfter.Text = tMaxPower.ToString();
        }

        private void Lab4TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab4TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab4TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab4TextInputResult.Text = "Error!";
                return;
            }
            Lab4TextInputResult.Text = Convert.ToInt32(Lab4TextCurValue.Text, 2).ToString();
        }

        //==========================================
        //Laboratory Work 7
        //==========================================
        private void Lab7TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab7TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab7TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab7TextInputResult.Text = "Error!";
                return;
            }
            Lab7TextInputResult.Text = Convert.ToInt32(Lab7TextCurValue.Text, 2).ToString();
        }

        private void Lab7TextButtonA_Click(object sender, EventArgs e)
        {
            //last bit
            int tInputValue = Convert.ToInt32(Lab7TextInputResult.Text, 10);
            //size
            string tValueString = Lab7TextCurValue.Text;
            int tInputSize = tValueString.Count();
            //shift >>
            for (int i = 0; i < Lab7TextInputI.Value; i++)
            {
                int ttLastBit = tInputValue & 1;
                tInputValue = (tInputValue >> 1) | (ttLastBit << (tInputSize - 1));
            }

            Lab7TextBefore.Text = Lab7TextCurValue.Text;
            tValueString = Convert.ToString(tInputValue, 2);
            if (tValueString.Count() < tInputSize)
            {
                int tZeros = (tInputSize - tValueString.Count());
                StringBuilder tZeroString = new StringBuilder();
                for (int i = 0; i < tZeros; i++)
                {
                    tZeroString.Append("0");
                }
                tValueString = tValueString.Insert(0, tZeroString.ToString());
            }
            Lab7TextAfter.Text = tValueString;
            Lab7TextCurValue.Text = tValueString;
        }

        private void Lab7TextButtonB_Click(object sender, EventArgs e)
        {
            //last bit
            int tInputValue = Convert.ToInt32(Lab7TextInputResult.Text, 10);
            //size
            string tValueString = Lab7TextCurValue.Text;
            int tInputSize = tValueString.Count();
            //shift >>
            for (int i = 0; i < Lab7TextInputI.Value; i++)
            {
                int ttLastBit = tInputValue & 1;
                tInputValue = (tInputValue << 1) | (ttLastBit >> (tInputSize - 1));
            }

            Lab7TextBefore.Text = Lab7TextCurValue.Text;
            tValueString = Convert.ToString(tInputValue, 2);
            if (tValueString.Count() < tInputSize)
            {
                int tZeros = (tInputSize - tValueString.Count());
                StringBuilder tZeroString = new StringBuilder();
                for (int i = 0; i < tZeros; i++)
                {
                    tZeroString.Append("0");
                }
                tValueString = tValueString.Insert(0, tZeroString.ToString());
            }
            Lab7TextAfter.Text = tValueString;
            Lab7TextCurValue.Text = tValueString;
        }

        //==========================================
        //Laboratory Work 5
        //==========================================
        private void Lab5TextCurValue_TextChanged(object sender, EventArgs e)
        {
            //Check
            string tValueString = Lab5TextCurValue.Text;
            if (tValueString.Count() > 32 || tValueString.Count() == 0)
            {
                Lab5TextInputResult.Text = "Error!";
                return;
            }
            tValueString = tValueString.Replace("1", "");
            tValueString = tValueString.Replace("0", "");
            if (tValueString.Count() != 0)
            {
                Lab5TextInputResult.Text = "Error!";
                return;
            }
            Lab5TextInputResult.Text = Convert.ToInt32(Lab5TextCurValue.Text, 2).ToString();
        }

        private void Lab5Button_Click(object sender, EventArgs e)
        {
            int tInputValue = Convert.ToInt32(Lab5TextInputResult.Text, 10);
            float tPower = (float)Math.Log(tInputValue, 2);
            Lab5TextBefore.Text = tInputValue.ToString();
            StringBuilder tResult = new StringBuilder("p = ");
            tResult.Append(Math.Floor(tPower)).Append("   2^p = ").Append(Math.Pow(2, Math.Floor(tPower)));
            tResult.Append("   2^(p+1) = ").Append(Math.Pow(2, Math.Floor(tPower)+1));
            Lab5TextAfter.Text = tResult.ToString();
        }

        //==========================================
        //Laboratory Work 9
        //==========================================
        private void Lab9ButtonCode_Click(object sender, EventArgs e)
        {
            if (Lab9TextCodeFile.Text == "")
            {
                Lab9TextCurKey.Text = "Error";
                return;
            }

            ASCIIEncoding tAscii = new ASCIIEncoding();
            byte[] tKey = tAscii.GetBytes(Lab9TextCurKey.Text);
            BinaryReader tFileReader = new BinaryReader(File.Open(Lab9TextCodeFile.Text, FileMode.Open));
            FileStream tFileWritter = new FileStream(Lab9TextCodeFile.Text + "out", FileMode.Append);
            byte tSymbol = 0;
            int tKeyLength = tKey.Count();
            int tKeyPosition = 0;

            //Если нет файла с ключом
            if (Lab9TextKeyFile.Text == "")
            {
               if (Lab9TextCurKey.Text == "")
                {
                    Lab9TextCurKey.Text = "Error";
                    return;
                }
                while (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length)
                {
                    tSymbol = tFileReader.ReadByte();
                    byte tEncoded = 0;
                    tEncoded = (byte)(tSymbol ^ tKey[tKeyPosition]);

                    tFileWritter.WriteByte(tEncoded);
                    if (tKeyPosition == tKeyLength - 1)
                        {
                        tKeyPosition = 0;
                        } else
                        {
                            tKeyPosition++;
                        }
                }
            } else
            {
                BinaryReader tKeyReader = new BinaryReader(new FileStream(Lab9TextKeyFile.Text, FileMode.Open));
                byte tKeySymbol = 0;
                while (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length && tKeyReader.BaseStream.Position != tKeyReader.BaseStream.Length)
                {
                    tSymbol = tFileReader.ReadByte();
                    tKeySymbol = tKeyReader.ReadByte();
                    byte tEncoded = 0;
                    tEncoded = (byte)(tSymbol ^ tKeySymbol);
                    tFileWritter.WriteByte(tEncoded);
                }
                tKeyReader.Close();
            }
            tFileReader.Close();
            tFileWritter.Close();
        }

        private void Lab9ButtonFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog tDialog = new OpenFileDialog();
            if (tDialog.ShowDialog() == DialogResult.OK)
            {
                Lab9TextCodeFile.Text = tDialog.FileName;
            }
        }

        private void Lab9ButtonKey_Click(object sender, EventArgs e)
        {
            OpenFileDialog tDialog = new OpenFileDialog();
            if (tDialog.ShowDialog() == DialogResult.OK)
            {
                Lab9TextKeyFile.Text = tDialog.FileName;
            }
        }

        //==========================================
        //Laboratory Work 11
        //==========================================
    }
}
