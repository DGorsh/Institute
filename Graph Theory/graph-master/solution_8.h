#ifndef SOLUTION_8_H
#define SOLUTION_8_H
#include <msolution.h>

class Solution_8 : public MSolution<QString>
{
    MGraphObject graphObjectA;
    MGraphObject graphObjectB;
    QVector<QVector<int>> TransportAnswer;

public:
    Solution_8(const MGraphObject& graphObjectA, const MGraphObject& graphObjectB);

    Solution_8() {}

    virtual void run() override;

    virtual ~Solution_8() override;


    QVector<QVector<int>> Conjuction();
    QVector<QVector<int>> Disjuction();
    QVector<QVector<int>> Substraction(bool bAsubB);
    QVector<QVector<int>> Implication(bool bAsubB);
    QVector<QVector<int>> Coimplication(bool bAsubB);
    QVector<QVector<int>> XOR();
    QVector<QVector<int>> Equivalence();
    QVector<QVector<int>> Sheffer();
    QVector<QVector<int>> Pirs();



private:
    QVector<QVector<int>> Retranslate(const QVector<QVector<int>> &);
    //перестановки
    void UllmanAlgorithm (QVector<QVector<int>> AdjMatrixA, QVector<QVector<int>> AdjMatrixB, QVector<QVector<int>> PermMatrix, int Counter);
    QVector<QVector<int>> Transpose(const QVector<QVector<int>> &Matrix);
    QVector<QVector<int>> Multiple(const QVector<QVector<int>> &MatrixA, const QVector<QVector<int>> &MatrixB);

};

#endif // SOLUTION_8_H
