#ifndef SOLUTION_4_H
#define SOLUTION_4_H


#include<algorithm>
#include <msolution.h>
#include <limits>

/*
 * Reverse graph
 * */
class Solution_4 : public MSolution<QString>
{
    MGraphObject graphObject;
    bool SaveFile;
    QString GlobalAnswer;

public:
    Solution_4(const MGraphObject& graphObject);

    Solution_4() {}

    virtual void run() override;

    virtual ~Solution_4() override;

    int min_value (int pFirst, int pSecond);

    int max_value (int pFirst, int pSecond);

    QString GetAnswer();
};

#endif // SOLUTION_0_H
