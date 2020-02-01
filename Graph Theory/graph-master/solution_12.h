#ifndef SOLUTION_12_H
#define SOLUTION_12_H

#include <msolution.h>
#include <QPair>
#include <QStack>
class Solution_12 : public MSolution<QString>
{
    MGraphObject graphObject;
    bool SaveFile;
    QString GlobalAnswer;

public:
    Solution_12(const MGraphObject& graphObject);

    Solution_12() {}

    QString Prim();
    QString Kruskal();
    QString Boruvki();

    virtual void run() override;

    virtual ~Solution_12() override;

    int min_value (QVector<int> Vector);

    int max_value (int pFirst, int pSecond);

    QString GetAnswer();
};

#endif // SOLUTION_12_H
