#ifndef SOLUTION_2_H
#define SOLUTION_2_H

#include <msolution.h>
#include <queue>
#include <QQueue>
#include <QPair>

#include <mpair.h>

typedef int distance;
typedef int parent;

class Solution_2 : public MSolution<QPair<QVector<int>, int>>
{
private:
    int fromId;
    int toId;
    int MODE;
    MGraphObject graphObject;

    QString result;

public:

    Solution_2(const MGraphObject& graphObject, int fromId, int toId, int MODE=0);

    Solution_2();

    virtual void run() override;

    virtual ~Solution_2() override;

    QPair<QVector<int>, QVector<int>> BFSFind(MGraphObject& graph, int fromId, int toId);

    QPair<QVector<int>, QVector<int>> A_star(MGraphObject& graph, int fromId, int toId);

    QPair<QVector<int>, QVector<int>> IterativeDeepingA_star(MGraphObject& graph, int fromId, int toId) {
        if (graph.checkVertex(fromId)) {

            std::priority_queue<MPair<int, int>, std::vector<MPair<int,int>>, std::greater<MPair<int,int>>> Q;

            QVector<distance> distances(graph.countVertexs(), INF);
            QVector<parent> parents(graph.countVertexs(), MConstants::not_exists);

            distances[graph.getIndexByVertexId(fromId)] = 0;

            graph.generateLinearVector();

            for (auto& it : graph.getLinearNodeVector_link()) {
                if (it.w < 0) {
                    throw MUncorrectInput();
                }
            }

            //Произведём инициализацию:
            for (auto& it : graph.getVertexs_link()) {
                if (it.id != fromId)
                    Q.push(MPair<distance, int>(INF, it.id));
            }

            //Растояние от начальной вершины до неё ZIRO
            Q.push(MPair<distance, int>(0, fromId));
            QSet<int> S;

            while(!Q.empty()) {
                MPair<distance, int> pair = Q.top();
                Q.pop();
                S.insert(pair.getValue());

                //Теперь нужно пройтись по вершинам, которые соединены с вершиной S

                for (auto& it : graph.getNodes()[graph.getIndexByVertexId(pair.getValue())]) {
                    relax(graph, distances, parents, it.parent, it.data, it.w);
                }
            }


            return QPair<QVector<int>, QVector<int>>(parents, distances);

        } else {
            throw MUncorrectInput();
        }
    }


    void relax(MGraphObject& graph, QVector<distance>& dist, QVector<parent>& parent, int fromId, int toId, int w) {
        int fromIndex = graph.getIndexByVertexId(fromId);
        int toIndex = graph.getIndexByVertexId(toId);

        if (dist[toIndex] > dist[fromIndex] + w) {
            dist[toIndex] = dist[fromIndex] + w;
            parent[toIndex] = fromId;

        }
    }

    MAnswer<QPair<QVector<int>, int>> res() {
        return savedResult;
    }



};

#endif // SOLUTION_2_H
