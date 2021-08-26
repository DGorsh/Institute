using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

struct EncodeParams {
    public string FileIn;
    public string FileOut;
    public ulong[] KeyExp;
    public ulong[] KeySpice;
    public int Mode;
    public ulong Initialisaton; };


namespace WindowsFormsApplication3
{
    public partial class Form1 : Form
    {
        private ulong[] SpiceKey;
        private ulong[] ExtKey;
        private ulong Key;

        private long FileProgress;
        private long KeyProgress;

        static object locker = new object();
        static object locker1 = new object();
        static object locker2 = new object();


        public Form1()
        {
            InitializeComponent();
            SpiceKey = new ulong[8];
            ExtKey = new ulong[256];
            Key = 987654321;

            FileProgress = 0;
            KeyProgress = 0;
        }
        private ulong ShiftL(ulong Value, int itr)
        {
            ulong Result = Value;
            for (int i = 0; i < itr; i++)
            {
                ulong ttLastBit = Result & 1;
                Result = (Result << 1) | (ttLastBit);
            }
            return Result;
        }

        private ulong mod(ulong x) {
            return x % 0xFFFFFFFFFFFFFFFF;
        }
        private ulong m_xor(ulong x, ulong y) { return mod(x ^ y); }
        private ulong m_lsh(ulong x, ulong y) { return mod(x << (int)(y % 64)); }
        private ulong m_rsh(ulong x, ulong y) { return mod(x >> (int)(y % 64)); }
        private ulong m_add(ulong x, ulong y) { return mod(x + y); }
        private ulong m_sub(ulong x, ulong y) { return mod(x - y); }
        private ulong m_mul(ulong x, ulong y) { return mod(x * y); }
        private ulong m_or(ulong x, ulong y) { return mod(x | y); }
        private ulong m_and(ulong x, ulong y) { return mod(x & y); }

        /*private ulong m_lsh(ulong x, ulong y)
        {
            ulong Result = x;
            for (int i = 0; i < (int)(y % 64); i++)
            {
                ulong ttLastBit = Result & 1;
                Result = (Result << 1) | (ttLastBit);
            }
            return Result;
        }
        private ulong m_rsh(ulong x, ulong y)
        {
            ulong Result = x;
            for (int i = 0; i < (int)(y%64); i++)
            {
                ulong ttLastBit = Result & 1;
                Result = (Result >> 1) | (ttLastBit << 63);
            }
            return Result;
        }*/

        private ulong ShiftR(ulong Value, int itr)
        {
            ulong Result = Value;
            for (int i = 0; i < itr; i++)
            {
                ulong ttLastBit = Result & 1;
                Result = (Result >> 1) | (ttLastBit << 63);
            }
            return Result;
        }

        private ulong Null(ulong Value)
        {
            return Value & (0xFFFFFFFFFFFFFF00);
        }

        private ulong PlusModule (ulong T1, ulong T2)
        {
            return (T1 + T2) & ((ulong)18446744073709551615);
        }

        private ulong[] KeyExpand(ulong KeyB) {
            ulong[] K = new ulong[256];
            ulong Key = KeyB;
            FileProgress = 0;
            //Этап 1
            K[0] = 14142135623730950488 + 3;
            K[1] = 2718281828459045235 + 64;
            K[2] = ShiftL(14142135623730950488, 3);

            for (int i = 3; i < 256; i++)
            {
                K[i] = K[i - 1] + (K[i - 2] ^ (ShiftR(K[i - 3], 23)) ^ (ShiftL(K[i - 3], 41)));
            }
            FileProgress = 333;
            //Этап 2
            for (int i = 0; i < 128; i++)
            {
                Key = Key ^ K[i];
            }
            FileProgress = 666;
            //Этап 3
            ulong S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7;
            KeyProgress = 0;

            for (int i = 3; i < 256; i++)
            {
                ulong kc_1 = K[i];
                ulong kc_2 = K[(i+83)&255];
                ulong kc_3 = K[Key&255];
                S_0 = K[255]; S_1 = K[254]; S_2 = K[253]; S_3 = K[252]; S_4 = K[251];
                S_5 = K[250]; S_6 = K[249]; S_7 = K[248];
                //1
                S_0 = S_0 ^ (kc_3 + (kc_2 ^ kc_1));
                S_1 = S_1 + S_0;
                S_2 = S_2 + kc_1;
                S_3 = S_3 ^ S_2;
                S_5 = S_5 - S_4;
                S_4 = S_4 ^ (ShiftL(S_1, 11));
                S_7 = S_7 ^ S_6;
                S_6 = S_6 ^ (ShiftR(S_2, 17));
                //2
                S_3 = S_3 + (ShiftR(S_0, 13));
                S_0 = S_0 - (S_6 ^ (ulong)i);
                S_2 = S_2 - S_5;
                S_7 = S_7 | (S_4 + S_3);
                S_4 = S_4 - S_3;
                S_5 = S_5 ^ (ShiftR(S_3, (int)(S_1 & 31)));
                S_1 = S_1 ^ (S_5 + 14142135623730950488);
                S_6 = S_6 ^ S_5;
                //3
                S_0 = S_0 + S_7;
                S_2 = S_2 + ShiftR(S_7, i);
                S_2 = S_2 ^ S_1;
                //4
                K[i] = S_2 + S_6;
                KeyProgress += 4;
            }
            FileProgress = 1000;

            return K;
        }

        private ulong[] HPCMediumMainEncode(ulong S_0B, ulong S_1B, ulong[] K, ulong[] Spice)
        {
            //ulong lmask = (1 << 64) - 1;
            ulong lmask = 0xFFFFFFFFFFFFFFFF;
            ulong S_0 = m_add(m_add(S_0B, K[128]), 0);
            ulong S_1 = m_add(S_1B, K[128 + 1]) & lmask;
            KeyProgress = 0;
            lock (locker)
            {
                ulong IRN1 = 3141592653589793238;
                ulong IRN2 = 2718281828459045235;
                ulong IRN3 = 14142135623730950488;
                for (ulong i = 0; i < 8; i++)
                {
                    ulong k = K[S_0 % 255];
                    S_1 = m_add(S_1, k) & lmask;
                    S_0 = m_xor(S_0, m_lsh(k, 8));
                    S_1 = m_xor(S_1, S_0) & lmask;
                    S_0 = m_sub(S_0, m_rsh(S_1, 11));
                    S_0 = m_xor(S_0, m_lsh(S_1, 2));
                    S_0 = m_sub(S_0, Spice[i ^ 4]);
                    S_0 = m_add(S_0, m_xor(m_lsh(S_0, 32), m_add(IRN1, 128)));
                    S_0 = m_xor(S_0, m_rsh(S_0, 17));
                    S_0 = m_xor(S_0, m_rsh(S_0, 34));
                    ulong t = Spice[i];
                    S_0 = m_xor(S_0, t);
                    S_0 = m_add(S_0, m_lsh(t, 5));
                    t = m_rsh(t, 4);
                    S_1 = m_add(S_1, t) & lmask;
                    S_0 = m_xor(S_0, t);
                    S_0 = m_add(S_0, m_lsh(S_0, 22 + (S_0 & 31)));
                    S_0 = m_xor(S_0, m_rsh(S_0, 23));
                    S_0 = m_sub(S_0, Spice[i ^ 7]);
                    t = S_0 & 255;
                    k = K[t];
                    ulong kk = K[(t + 3 * i + 1) % 255];
                    S_1 = m_xor(S_1, k) & lmask;
                    S_0 = m_xor(S_0, m_lsh(kk, 8));
                    kk = m_xor(kk, k);
                    S_1 = m_add(S_1, m_rsh(kk, 5)) & lmask;
                    S_0 = m_sub(S_0, m_lsh(kk, 12));
                    S_0 = m_xor(S_0, kk & ~((ulong)255));
                    S_1 = m_add(S_1, S_0) & lmask;
                    S_0 = m_add(S_0, m_lsh(S_1, 3));
                    S_0 = m_xor(S_0, Spice[i ^ 2]);
                    S_0 = m_add(S_0, K[128 + 16 + i]);
                    S_0 = m_add(S_0, m_lsh(S_0, 22));
                    S_0 = m_xor(S_0, m_rsh(S_1, 4));
                    S_0 = m_add(S_0, Spice[i ^ 1]);
                    S_0 = m_xor(S_0, m_rsh(S_0, 33 + i));
                    KeyProgress += 125;
                }
                S_0 = m_add(S_0, K[128 + 8]);
                S_1 = m_add(S_1, K[128 + 9]);
                return new ulong[] { S_0, S_1 };
            }
        }

        private ulong[] HPCMediumMainDecode(ulong S_0B, ulong S_1B, ulong[] K, ulong[] Spice)
        {
            ulong IRN1 = 3141592653589793238;
            ulong IRN2 = 2718281828459045235;
            ulong IRN3 = 14142135623730950488;
            //ulong lmask = (1 << 64) - 1;
            ulong lmask = 0xFFFFFFFFFFFFFFFF;
            ulong S_0 = m_sub(S_0B, K[128 + 8]);
            ulong S_1 = m_sub(S_1B, K[128 + 9]) & lmask;
            KeyProgress = 0;
            lock (locker)
            {
                int i = 7;
                while (i >= 0) {
                    ulong t = S_0;
                    t = m_rsh(t, (ulong)(33 + i));
                    S_0 = m_xor(S_0, t);
                    S_0 = m_sub(S_0, Spice[i ^ 1]);
                    t = S_1;
                    t = m_rsh(t, 4);
                    S_0 = m_xor(S_0, t);
                    ulong k = S_0;
                    k = m_lsh(k, 22);
                    t = S_0;
                    t = m_sub(t, k);
                    t = m_lsh(t, 22);
                    S_0 = m_sub(S_0, t);
                    S_0 = m_sub(S_0, K[128 + 16 + i]);
                    S_0 = m_xor(S_0, Spice[i ^ 2]);
                    t = S_1;
                    t = m_lsh(t, 3);
                    S_0 = m_sub(S_0, t);
                    S_1 = m_sub(S_1, S_0) & lmask;
                    ulong tt = S_0 & 255;
                    k = K[tt];
                    tt += (ulong)(3 * i + 1);
                    ulong kk = K[tt%255];
                    kk = m_xor(kk, k);
                    t = kk & ~((ulong)255);
                    S_0 = m_xor(S_0, t);
                    t = kk;
                    t = m_lsh(t, 12);
                    S_0 = m_add(S_0, t);
                    t = kk;
                    t = m_rsh(t, 5);
                    S_1 = m_sub(S_1, t) & lmask;
                    kk = K[tt&255];
                    kk = m_lsh(kk, 8);
                    S_0 = m_xor(S_0, kk);
                    S_1 = m_xor(S_1, k) & lmask;
                    S_0 = m_add(S_0, Spice[i ^ 7]);
                    t = S_0;
                    t = m_rsh(t, 23);
                    S_0 = m_xor(S_0, t);
                    t = S_0;
                    t = m_rsh(t, 46);
                    S_0 = m_xor(S_0, t);
                    tt = 22 + (S_0 & 31);
                    t = S_0;
                    t = m_lsh(t, tt);
                    kk = S_0;
                    kk = m_sub(kk, t);
                    kk = m_lsh(kk, tt);
                    S_0 = m_sub(S_0, kk);
                    kk = Spice[i];
                    t = kk;
                    kk = m_rsh(kk, 4);
                    S_0 = m_xor(S_0, kk);
                    S_1 = m_sub(S_1, kk) & lmask;
                    k = t;
                    k = m_lsh(k, 5);
                    S_0 = m_sub(S_0, k);
                    S_0 = m_xor(S_0, t);
                    t = S_0;
                    t = m_rsh(t, 17);
                    S_0 = m_xor(S_0, t);
                    t = IRN1 + 128;
                    k = S_0;
                    k = m_sub(k, t);
                    k = m_lsh(k, 32);
                    t = m_xor(t, k);
                    S_0 = m_sub(S_0, t);
                    S_0 = m_add(S_0, Spice[i ^ 4]);
                    t = S_1;
                    t = m_lsh(t, 2);
                    S_0 = m_xor(S_0, t);
                    t = S_1;
                    t = m_rsh(t, 11);
                    S_0 = m_add(S_0, t);
                    S_1 = m_xor(S_1, S_0) & lmask;
                    tt = S_0 & 255;
                    k = K[tt];
                    t = k;
                    t = m_lsh(t, 8);
                    S_0 = m_xor(S_0, t);
                    S_1 = m_sub(S_1, k) & lmask;
                    i--;
                    KeyProgress += 125;
                }

                S_0 = m_sub(m_sub(S_0, K[128]), 0);
                S_1 = m_sub(S_1, K[128 + 1]) & lmask;

            }

            return new ulong[] { S_0, S_1 };
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Thread tm = new Thread(BarUpdater);
            tm.Start();
        }

        private void buttonAddKey_Click(object sender, EventArgs e)
        {
            Random tRand = new Random();
            for (int i = 0; i < 8; i++)
            {
                SpiceKey[i] = (ulong)tRand.Next();
                listAddKey.Items[i] = SpiceKey[i].ToString();
            }
        }

        private void buttonExtendKey_Click(object sender, EventArgs e)
        {
            Key = Convert.ToUInt64(textBoxKey.Text);
            ExtKey = KeyExpand(Key);
        }

        private void BarUpdater()
        {
            for (;;)
            {
                MethodInvoker m = new MethodInvoker(() => progressFile.Value = (int)FileProgress);
                progressFile.Invoke(m);
            }
        }

        private void buttonSelect_Click(object sender, EventArgs e)
        {
            OpenFileDialog tDialog = new OpenFileDialog();
            if (tDialog.ShowDialog() == DialogResult.OK)
            {
                labelFile.Text = tDialog.FileName;
            }
        }

        private ulong[] buttonOFBEncode(ulong[] Encode0, ulong[] tKey, ulong[] tSpice, ulong[] Initialisaton)
        {
            ulong[] Encode1 = HPCMediumMainEncode(Initialisaton[0], Initialisaton[1], tKey, tSpice);
            return new ulong[4] { Encode1[0] ^ Encode0[0], Encode1[1] ^ Encode0[1], Encode1[0], Encode1[1] };
        }

        private ulong[] buttonCBCEncode(ulong[] Encode0, ulong[] tKey, ulong[] tSpice, ulong[] Initialisaton)
        {
            ulong[] Encode1 = new ulong[2] { Encode0[0] ^ Initialisaton[0], Encode0[1] ^ Initialisaton[1] };
            return HPCMediumMainEncode(Encode1[0], Encode1[1], tKey, tSpice);
        }

        private ulong[] buttonCFBEncode(ulong[] Encode0, ulong[] tKey, ulong[] tSpice, ulong[] Initialisaton)
        {
            ulong[] Encode1 = HPCMediumMainEncode(Initialisaton[0], Initialisaton[1], tKey, tSpice);
            return new ulong[2] { Encode0[0] ^ Encode1[0], Encode0[1] ^ Encode1[1] };
        }


        private ulong[] buttonCFBCBCDecode(ulong[] Encode0, ulong[] tKey, ulong[] tSpice, ulong[] Initialisaton)
        {
            ulong[] Encode1 = HPCMediumMainDecode(Encode0[0], Encode0[1], tKey, tSpice);
            return new ulong[2] { Encode1[0] ^ Initialisaton[0], Encode1[1] ^ Initialisaton[1] };
        }


        private void buttonEncode_Click(object sender, EventArgs e)
        {
            EncodeParams EncodeData = new EncodeParams();
            EncodeData.FileIn = labelFile.Text;
            EncodeData.FileOut = EncodeData.FileIn + "enc";
            EncodeData.KeyExp = ExtKey;
            EncodeData.KeySpice = SpiceKey;
            EncodeData.Mode = listMode.SelectedIndex;
            EncodeData.Initialisaton = Convert.ToUInt64(textBoxInit.Text);
            Thread myThread = new Thread(new ParameterizedThreadStart(EncodingThreat));
            myThread.Start(EncodeData);
            //EncodingThreat(EncodeData);
        }

        private void EncodingThreat (Object tParams)
        {
            EncodeParams tParam = (EncodeParams)tParams;
            BinaryReader tFileReader = new BinaryReader(File.Open(tParam.FileIn, FileMode.Open));
            FileStream tFileWritter = new FileStream(tParam.FileOut, FileMode.Append);
            int Counter = 16;
            ulong Word1 = 0;
            ulong Word2 = 0;
            ulong[] InitVector = new ulong[2] { tParam.Initialisaton, tParam.Initialisaton };
            while (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length || Counter != -1)
            {
                long CurPosition = tFileReader.BaseStream.Position / tFileReader.BaseStream.Length;
                FileProgress = CurPosition * 1000;
                if (Counter == -1)
                {
                    Word1 = 0;
                    Word2 = 0;
                    Counter = 16;
                }
                if (Counter == 0)
                {
                    ulong[] Coded = new ulong[2];
                    switch (tParam.Mode)
                    {
                        case 0:
                            Coded = HPCMediumMainEncode(Word1, Word2, tParam.KeyExp, tParam.KeySpice);
                            Word1 = Coded[0];
                            Word2 = Coded[1];
                            break;
                        case 1:
                            Coded = buttonCBCEncode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                            Word1 = Coded[0];
                            Word2 = Coded[1];
                            InitVector[0] = Coded[0];
                            InitVector[1] = Coded[1];
                            break;
                        case 2:
                            Coded = buttonCFBEncode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                            Word1 = Coded[0];
                            Word2 = Coded[1];
                            InitVector[0] = Coded[0];
                            InitVector[1] = Coded[1];
                            break;
                        case 3:
                            Coded = buttonOFBEncode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                            Word1 = Coded[0];
                            Word2 = Coded[1];
                            InitVector[0] = Coded[2];
                            InitVector[1] = Coded[3];
                            break;
                        default: break;
                    }

                    
                    byte[] Cur = BitConverter.GetBytes(Word1);
                    for (int i = 7; i >= 0; i--)
                    {
                        tFileWritter.WriteByte(Cur[i]);
                    }

                    Cur = BitConverter.GetBytes(Word2);
                    for (int i = 7; i >= 0; i--)
                    {
                        tFileWritter.WriteByte(Cur[i]);
                    }
                    Counter = -1;
                }

                if (Counter > 8)
                {
                    if (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length) {
                        Word1 += (ulong)(tFileReader.ReadByte()) << ((Counter - 9) * 8);
                    }
                    Counter--;
                } else if (Counter > 0 && Counter <= 8)
                {
                    if (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length)
                    {
                        Word2 += (ulong)(tFileReader.ReadByte()) << ((Counter - 1) * 8);
                    }
                    Counter--;
                }
            }
            tFileWritter.Close();
            tFileReader.Close();
        }

        private void buttonDecode_Click(object sender, EventArgs e)
        {
            EncodeParams EncodeData = new EncodeParams();
            EncodeData.FileIn = labelFile.Text;
            EncodeData.FileOut = EncodeData.FileIn + "dec";
            EncodeData.KeyExp = ExtKey;
            EncodeData.KeySpice = SpiceKey;
            EncodeData.Mode = listMode.SelectedIndex;
            EncodeData.Initialisaton = Convert.ToUInt64(textBoxInit.Text);
            Thread myThread = new Thread(new ParameterizedThreadStart(DecodingThreat));
            myThread.Start(EncodeData);
            //DecodingThreat(EncodeData);
        }

        private void DecodingThreat(Object tParams)
        {
            lock (locker2)
            {
                EncodeParams tParam = (EncodeParams)tParams;
                BinaryReader tFileReader = new BinaryReader(File.Open(tParam.FileIn, FileMode.Open));
                FileStream tFileWritter = new FileStream(tParam.FileOut, FileMode.Append);
                int Counter = 16;
                ulong Word1 = 0;
                ulong Word2 = 0;
                ulong[] InitVector = new ulong[2] { tParam.Initialisaton, tParam.Initialisaton };
                while (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length || Counter != -1)
                {
                    long CurPosition = tFileReader.BaseStream.Position / tFileReader.BaseStream.Length;
                    FileProgress = CurPosition * 1000;
                    if (Counter == -1)
                    {
                        Word1 = 0;
                        Word2 = 0;
                        Counter = 16;
                    }
                    if (Counter == 0)
                    {
                        ulong[] Coded = new ulong[2];
                        switch (tParam.Mode)
                        {
                            case 0:
                                Coded = HPCMediumMainDecode(Word1, Word2, tParam.KeyExp, tParam.KeySpice);
                                Word1 = Coded[0];
                                Word2 = Coded[1];
                                break;
                            case 1:
                                Coded = buttonCFBCBCDecode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                                Word1 = Coded[0];
                                Word2 = Coded[1];
                                InitVector[0] = Coded[0];
                                InitVector[1] = Coded[1];
                                break;
                            case 2:
                                Coded = buttonCFBEncode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                                InitVector[0] = Word1;
                                InitVector[1] = Word2;
                                Word1 = Coded[0];
                                Word2 = Coded[1];
                                break;
                            case 3:
                                Coded = buttonOFBEncode(new ulong[2] { Word1, Word2 }, tParam.KeyExp, tParam.KeySpice, InitVector);
                                Word1 = Coded[0];
                                Word2 = Coded[1];
                                InitVector[0] = Coded[2];
                                InitVector[1] = Coded[3];
                                break;
                            default: break;
                        }

                        byte[] Cur = BitConverter.GetBytes(Word1);
                        for (int i = 7; i >= 0; i--)
                        {
                            tFileWritter.WriteByte(Cur[i]);
                        }

                        Cur = BitConverter.GetBytes(Word2);
                        for (int i = 7; i >= 0; i--)
                        {
                            tFileWritter.WriteByte(Cur[i]);
                        }
                        Counter = -1;
                    }

                    if (Counter > 8)
                    {
                        if (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length)
                        {
                            Word1 += (ulong)(tFileReader.ReadByte()) << ((Counter - 9) * 8);
                        }
                        Counter--;
                    }
                    else if (Counter > 0 && Counter <= 8)
                    {
                        if (tFileReader.BaseStream.Position != tFileReader.BaseStream.Length)
                        {
                            Word2 += (ulong)(tFileReader.ReadByte()) << ((Counter - 1) * 8);
                        }
                        Counter--;
                    }
                }
                tFileWritter.Close();
                tFileReader.Close();
            }
        }
    }
}
