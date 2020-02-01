#ifndef SOLUTION_0_H
#define SOLUTION_0_H

#include <msolution.h>

/*
 * Reverse graph
 * */
class Solution_0 : public MSolution<QString>
{
public:
    Solution_0(QVector<MGraphObject>& graphVector);

    Solution_0();

    virtual void run() override;

    virtual ~Solution_0() override;
};

#endif // SOLUTION_0_H
