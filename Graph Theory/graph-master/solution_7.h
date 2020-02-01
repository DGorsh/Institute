#ifndef SOLUTION_7_H
#define SOLUTION_7_H

#include <msolution.h>

class Solution_7 : MSolution<MAnswer<QPair<MGraphObject, QString>>>
{
private:
    MGraphObject graphObject;
public:
    Solution_7(MGraphObject& object);

    Solution_7();

    virtual void run() override;

    virtual ~Solution_7() override;

    MAnswer<QPair<MGraphObject, QString>> inv(MGraphObject& object);
};

#endif // SOLUTION_7_H
