#ifndef SOLUTION_17_H
#define SOLUTION_17_H

#include <msolution.h>

class Solution_17 : public MSolution<QString>
{
private:
    QVector<int> VectorData;
    QString Result;

public:
    Solution_17(const QVector<int> Data);
    QString ResultReturn();
    virtual void run() override;
};

#endif // SOLUTION_17_H
