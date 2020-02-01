#ifndef SOLUTION_19_H
#define SOLUTION_19_H

#include <msolution.h>

using namespace std;

class Solution_19
{

    QString result;

public:
    Solution_19() {
//        MMatrix matrix = {{-444, 5, 11, 9},
//                          {10, -444, 8, 7},
//                          {7, 14, -444, 8},
//                          {12, 6, 15, -444}};

//        solveMe(matrix);
    }

    void solve(MGraphObject& graph) {
        MMatrix matrix = graph.toMatrix();
        for (int i = 0; i < matrix.size(); ++i) {
            matrix[i][i] = -444;
        }
        solveMe(matrix);
    }


    void removeCity(MMatrix& matr, int cityIndex) {
        MMatrix newMatrix(matr.size()-1, QVector<int>(matr.size()-1, 0));

        int newI = 0;
        int newJ = 0;

        for (int i = 0; i < matr.size(); ++i) {
            if (i != cityIndex) {
                newJ = 0;
                for (int j = 0; j < matr.size(); ++j) {
                    if (j != cityIndex) {
                        newMatrix[newI][newJ] = matr[i][j];
                        newJ++;
                    }
                }
                newI++;
            }

        }

    }


    void solveMe(MMatrix& matr)
    {
        int uz[50][50];
        int vich[50][50];
        int mstr[50];
        int msto[50];
        int kp[50];
        int msh[50][50];
        int mshstr[50][50];
        int mshsto[50][50];
        int d[50][2], c[50];
        int g[50][2];
        int k[50][2];
        int m[50][2];
        int a, b, e, f;
        int h;
        int n;
        int sp = 0;
        int r;
        int i, j;

        //Vvod razmera matrici
        r = matr.size();

        //prisv diag elm znach -444
        for (i = 0; i <= (r - 1); i++)
        {
            uz[i][i] = -444;
        }

        //vvod elem matrizi
        for (i = 0; i <= (r - 1); i++)
        {
            for (j = 0; j <= (r - 1); j++)
            {
                if (uz[i][j] != -444) {
                    uz[i][j] = matr[i][j];
                };
            }
        }



        //prisv perv znach matr g[][]
        for (j = 0; j <= (r - 1); j++)
        {
            g[j][0] = j + 1;
            g[j][1] = j + 1;
        }


        //prisv znach matr vich
        for (i = 0; i <= (r - 1); i++)
        {
            for (j = 0; j <= (r - 1); j++)
            {
                vich[i][j] = uz[i][j];
            }
        }

        //prisv perv znach 0 matr m[][]
        for (j = 0; j <= (r - 2); j++)
        {
            m[j][0] = 0;
            m[j][1] = 0;
        }

        //nachalo zikla shsaga zadachi
        for (h = 1; h <= matr.size(); h++)
        {

            //vichisl min elem strok
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (vich[i][j] != -444) { mstr[i] = vich[i][j]; break; }
                }
            }
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (vich[i][j] != -444)
                    {
                        if (mstr[i] > vich[i][j])mstr[i] = vich[i][j];
                    }
                }
            }


            //vichit min elem strok
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (vich[i][j] != -444)vich[i][j] = vich[i][j] - mstr[i];
                }
            }


            //vichisl min elem stolbc
            for (j = 0; j <= (r - h); j++)
            {
                for (i = 0; i <= (r - h); i++)
                {
                    if (vich[i][j] != -444) { msto[j] = vich[i][j]; break; }
                }
            }

            for (j = 0; j <= (r - h); j++)
            {
                for (i = 0; i <= (r - h); i++)
                {
                    if (vich[i][j] != -444)
                    {
                        if (msto[j] > vich[i][j])msto[j] = vich[i][j];
                    }
                }
            }


            //vichit min elem stolb
            for (j = 0; j <= (r - h); j++)
            {
                for (i = 0; i <= (r - h); i++)
                {
                    if (vich[i][j] != -444)vich[i][j] = vich[i][j] - msto[j];
                }
            }



            //zapom sum konst priv na shage
            for (i = 0; i <= (r - h); i++)
            {
                kp[h - 1] = kp[h - 1] + mstr[i] + msto[i];
            }


            //perech na shage poslednem
            if (h == r - 1)goto e;

            //prisv msh -111
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    msh[i][j] = -111;
                }
            }

            //vich min shtr u nuley v stolb i strokah
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (vich[i][j] == 0)
                    {
                        //vich shtr v str
                        for (a = 0; a <= (r - h); a++)
                        {
                            if (vich[i][a] != -444)
                            {
                                if (a != j)
                                {
                                    mshstr[i][j] = vich[i][a]; goto A;
                                }
                            }
                        }

                    A:
                        for (a = 0; a <= (r - h); a++)
                        {
                            if (vich[i][a] != -444)
                            {
                                if (a != j)
                                {
                                    if (mshstr[i][j] > vich[i][a])mshstr[i][j] = vich[i][a];
                                }
                            }
                        }

                        //vich shtr v stolb u nuley
                        for (b = 0; b <= (r - h); b++)
                        {
                            if (vich[b][j] != -444)
                            {
                                if (b != i)
                                {
                                    mshsto[i][j] = vich[b][j]; goto B;
                                }
                            }
                        }
                    B:
                        for (b = 0; b <= (r - h); b++)
                        {
                            if (vich[b][j] != -444)
                            {
                                if (b != i)
                                {
                                    if (mshsto[i][j] > vich[b][j])mshsto[i][j] = vich[b][j];
                                }
                            }
                        }


                        //vich shtrafa
                        msh[i][j] = mshstr[i][j] + mshsto[i][j];

                    }
                }
            }


            //nahoz perv strafa maks
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (msh[i][j] != -111)
                    {
                        c[h - 1] = msh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j; goto C;
                    }
                }
            }
        C:
            for (i = 0; i <= (r - h); i++)
            {
                for (j = 0; j <= (r - h); j++)
                {
                    if (msh[i][j] != 111)
                    {
                        if (msh[i][j] > c[h - 1])
                        {
                            c[h - 1] = msh[i][j]; d[h - 1][0] = i; d[h - 1][1] = j;
                        }
                    }
                }
            }


            //prisv matr k znach na shage
            k[h - 1][0] = g[d[h - 1][0]][0];
            k[h - 1][1] = g[d[h - 1][1]][1];

            //uresanie stroki matrizi
            for (i = 0; i <= (r - h - 1); i++)
            {
                if (i == d[h - 1][0])
                {
                    for (e = i; e <= (r - h - 1); e++)
                    {
                        for (f = 0; f <= (r - h); f++)
                        {
                            vich[e][f] = vich[e + 1][f];
                        }
                    }
                }
            }


            //uresanie stolbza matrizi
            for (j = 0; j <= (r - h - 1); j++)
            {
                if (j == d[h - 1][1])
                {
                    for (e = j; e <= (r - h - 1); e++)
                    {
                        for (f = 0; f <= (r - h - 1); f++)
                        {
                            vich[f][e] = vich[f][e + 1];
                        }
                    }
                }
            }


            //prisv matr g nomerov strok i stolbzov
            for (i = d[h - 1][0]; i <= (r - h - 1); i++)
                g[i][0] = g[i + 1][0];
            for (i = d[h - 1][1]; i <= (r - h - 1); i++)
                g[i][1] = g[i + 1][1];


            //proverka est li protiv elem, esli est prisv beskonechn
            for (i = 0; i <= (r - h - 1); i++)
            {
                for (j = 0; j <= (r - h - 1); j++)
                {
                    if (k[h - 1][0] == g[j][1] && k[h - 1][1] == g[i][0])
                    {
                        vich[i][j] = -444; goto D;
                    }
                }
            }

            //nahoz vseh zepey(prisoed dugi v nachale)
            for (i = 0; i < (h - 1); i++)
            {
                if (k[h - 1][0] == k[i][1])
                {
                    m[h - 1][0] = k[i][0]; m[h - 1][1] = k[h - 1][1];
                }
            }

            //nahoz vseh zepey(prisoed dugi v konce)
            for (i = 0; i < (h - 1); i++)
            {
                if (k[h - 1][1] == k[i][0])
                {
                    if (m[h - 1][0] == 0)
                    {
                        m[h - 1][0] = k[h - 1][0]; m[h - 1][1] = k[i][1];
                    }
                    else m[h - 1][1] = k[i][1];
                }
            }

            //proverka mozno prisoedinit zepi i prisoedinenie
            for (i = 0; i < h - 1; i++)
            {
                if (m[i][0] != 0)
                {
                    if (k[h - 1][0] == m[i][1])
                    {
                        m[h - 1][0] = m[i][0];
                    }
                }
            }
            for (i = 0; i < h - 1; i++)
            {
                if (m[i][0] != 0)
                {
                    if (k[h - 1][1] == m[i][0])
                    {
                        m[h - 1][1] = m[i][1];
                    }
                }
            }

            //zapret zepi na shage - prisv -444

            for (i = 0; i <= (r - h - 1); i++)
            {
                for (j = 0; j <= (r - h - 1); j++)
                {
                    if (m[h - 1][0] == g[j][1] && m[h - 1][1] == g[i][0])
                    {
                        vich[i][j] = -444;
                    }
                }
            }

        D:
            int a = 0;
        }

    e:

        //prisv dvuch posl strok v mass k
        int l = 2;
        for (i = 0; i <= 1; i++)
        {
            for (j = 0; j <= 1; j++)
            {
                if (vich[i][j] == 0)
                {
                    k[r - l][0] = g[i][0]; k[r - l][1] = g[j][1]; l = l - 1;
                }

            }
        }

        //rasch stoim proezda
        for (i = 0; i <= r - 1; i++)
        {
            sp = sp + uz[k[i][0] - 1][k[i][1] - 1];
        }

        result.append("\nСтоимость пути: ").append(QString::number(sp));

        //Теперь перейдём к путям
        //vivod matrizi k

        result.append("\nПути: ");
        for (i = 0; i <= (r - 1); i++)
        {
            for (j = 0; j <= 0; j++)
            {
                result.append(QString::number(k[i][j])).append(" ");
            }
        }



    }

    QString getResult() {
        return result;
    }
};

#endif // SOLUTION_19_H
