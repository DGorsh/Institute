#ifndef SOLUTION_5_H
#define SOLUTION_5_H


#include<algorithm>
#include <msolution.h>
#include <limits>
#include <QDebug>

/*
 * Reverse graph
 * */
class Solution_5 : public MSolution<QString>
{
    MGraphObject graphObjectA;
    MGraphObject graphObjectB;
    bool SaveFile;
    QString GlobalAnswer;

public:
    Solution_5(const MGraphObject& graphObjectA, const MGraphObject& graphObjectB);

    Solution_5() {}

    virtual void run() override;

    virtual ~Solution_5() override;

    void UllmanAlgorithm (QVector<QVector<int>> AdjMatrixA, QVector<QVector<int>> AdjMatrixB, QVector<QVector<int>> PermMatrix, int Counter);

    QVector<QVector<int>> Transpose(const QVector<QVector<int>> &Matrix);
    QVector<QVector<int>> Multiple(const QVector<QVector<int>> &MatrixA, const QVector<QVector<int>> &MatrixB);

    QString GetAnswer ();

};

#endif // SOLUTION_5_H
