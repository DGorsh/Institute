#ifndef SOLUTION_3_H
#define SOLUTION_3_H


#include <msolution.h>
#include <mpair.h>
#include <vector>
#include <queue>


typedef QPair<bool, QPair<QVector<int>, QVector<int>>> PairOfBooleanAndPair;
typedef QPair<QVector<int>, QVector<int>> PairOfVectors;
class Solution_3 : public MSolution<QPair<QVector<int>, QVector<int>>>
{
private:
    int fromId;
    MGraphObject graphObject;
    QString result;

public:

    Solution_3(const MGraphObject& graphObject, int fromId);

    Solution_3();

    virtual void run() override;

    virtual ~Solution_3() override;

    //Алгоритм Дейкстры. Находит кратчайшие пути до различных мест
    PairOfVectors Dijkstra(MGraphObject& graph, int fromId);

    PairOfBooleanAndPair BellmanFord(MGraphObject& graph, int fromId);

    PairOfVectors FloydWorshell(MGraphObject& graph, int fromId = -1);

    void Jhonson(MGraphObject& graph, int fromId = -1);
    void relax(MGraphObject& graph, QVector<distance>& dist, QVector<parent>& parent, int fromId, int toId, int w);

    QString getres() {
        return result;

    }
    int min(int a, int b);
};

#endif // SOLUTION_3_H






















//#endif // SOLUTION_3_H
