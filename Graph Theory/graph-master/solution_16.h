#ifndef SOLUTION_16_H
#define SOLUTION_16_H

#include <msolution.h>

class Solution_16 : public MSolution<QString>
{
    QVector<int> vertexs;
    QVector<int> nodes;

public:
    Solution_16() {

    }

    Solution_16(const QVector<int>& vertexs, const QVector<int>& nodes) : vertexs(vertexs), nodes(nodes) {

    }
};

#endif // SOLUTION_16_H
