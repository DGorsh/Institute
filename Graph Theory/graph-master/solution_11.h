#ifndef SOLUTION_11_H
#define SOLUTION_11_H

#include <msolution.h>

class Solution_11 : public MSolution<QString>
{
    MGraphObject graph_1, graph_2;
    QVector<int> bases;
    int n = 0;
public:
    Solution_11(const QVector<int>& base);

    Solution_11();

    virtual void run() override;

    MGraphObject baseToGraph(QVector<int>& base, int number = 0);
};

#endif // SOLUTION_11_H
