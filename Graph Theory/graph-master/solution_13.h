#ifndef SOLUTION_13_H
#define SOLUTION_13_H

#include <QDebug>
#include <QStack>
#include "graph.h"
#include <QQueue>
#include <QVector>
#include <msolution.h>

class Solution_13 {
public:
    Solution_13 () = default;
    ~Solution_13() = default;

    QStack<int> BFS(MGraphObject& graph, int fromId) {
        if (graph.checkVertex(fromId)) {

            QQueue<int> Q;
            QStack<int> component;

            graph.getVertexById(fromId)->flag = MConstants::flag_visited;

            Q.push_back(fromId);
            component.push(fromId);

            while(!Q.isEmpty()) {
                int v = Q.front();
                Q.pop_front();
                int index = graph.getIndexByVertexId(v);

                if (index == MConstants::not_exists)
                    throw MUncorrectInput();

                for (auto& node : graph.getNodes_link()[index]) {
                    /*
                     * Здесь будет браться меньший элемент
                     * */
                    MVertexNode* minNode = graph.getMinWNodeById(node.parent, node.data);

                    MVertex* vertex = nullptr;

                    if ((vertex = graph.getVertexById(minNode->data))->flag != MConstants::flag_visited) {
                        vertex->flag = MConstants::flag_visited;
                        Q.push_back(vertex->id);
                        component.push(vertex->id);
                    }

                }
            }

            return component;

        } else {
            throw MUncorrectInput();
        }
    }


    QVector<QVector<int>> getComponents(MGraphObject& graph) {

        QVector<QStack<int> > componentsVec;
        bool oriented = true;

        for (auto& it : graph.getVertexs_link()) {
            if (it.flag != MConstants::flag_visited)
                componentsVec.push_back(BFS(graph, it.id));
        }

        if (componentsVec.size() == 1) {
        } else if (componentsVec.size() > 1 && oriented) {
            //Проверяем граф на слабую связность

            graph.generateLinearVector();

            for (auto& it : graph.getLinearNodeVector_link()) {
                if (graph.checkNode(graph.getVertexById(it.parent), graph.getVertexById(it.data)) && !graph.checkNode(graph.getVertexById(it.data), graph.getVertexById(it.parent))) {
                    graph.addNode(graph.getVertexById(it.data), graph.getVertexById(it.parent));
                }
            }

            QVector<QStack<int> >  newComponents;

            for (auto& it : graph.getVertexs_link()) { //Снова всё непосещено
                it.flag = MConstants::flag_unvisited;
            }

            for (auto& it : graph.getVertexs_link()) {
                if (it.flag != MConstants::flag_visited)
                    newComponents.push_back(BFS(graph, it.id));
            }
        }
        QVector<QVector<int>> ResultVector(componentsVec.size());
        for (int i = 0; i < componentsVec.size(); i++) {
            while (componentsVec[i].size() != 0) {
                ResultVector[i].push_back(componentsVec[i].top());
                componentsVec[i].pop();
            }
        }
        return ResultVector;
    }

    QVector<int> Cycle_wideWalk(QVector<QVector<int>> g, int s)
    {
        QVector<int> cycle;
        QQueue<int> q;
        q.push_back(s);
        QVector<bool> used (g.size());
        QVector<int> p (g.size());
        used[s] = true;
        p[s] = -1;
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();

            for (int i=0; i < g.size(); ++i) {
                if(!g[v][i]) continue;

                if (!used[i])
                {
                    used[i] = true;
                    q.push_back(i);
                    p[i] = v;
                }
                else if(i != p[v] && used[i])
                {
                    for (; v!=-1; v=p[v])
                        cycle.push_back(v);
                    for (v=i; v!=-1; v=p[v])
                        cycle.push_back(v);

                    return cycle;
                }

            }
        }

        return cycle;
    }

    QVector<int> minCycle(MGraphObject& graph)
    {
        QVector<QVector<int>> g = graph.toMatrix();
        QVector<int> ans;
        ans = Cycle_wideWalk(g, 0);
        int minCyc = ans.size();
        QVector<QVector<int>> comps = getComponents(graph);
        for(auto it : comps)
        {
            if(Cycle_wideWalk(g, it[0]).size() < minCyc && Cycle_wideWalk(g, it[0]).size() != 0)
            {
                ans = Cycle_wideWalk(g, it[0]);
                minCyc = ans.size();
            }
        }

        return ans;
    }

    int min_value (int pFirst, int pSecond) {
        if (pFirst > pSecond) {
            return pSecond;
        } else {
            return pFirst;
        }
    }

    int max_value (int pFirst, int pSecond) {
        if (pFirst < pSecond) {
            return pSecond;
        } else {
            return pFirst;
        }
    }

    QString centerVer(MGraphObject& graph)
    {
        QVector<int> answer;

        //Нахождение радиуса и диаметра при помощи алгоритма Флойда-Уоршелла
        const int N = graph.countVertexs(); // Количество вершин в графе
        QVector<QVector<int>> TempAdjMatrix = graph.toMatrix();
        QVector<QVector<int>> d; // Дистанции в графе
        d.resize(N);
        for (int i = 0; i < d.size(); i++){
            d[i].resize(N);
        }
        for (int i = 0; i < d.size(); i++) {
            for (int j = 0; j < d.size(); j++) {
                d[i][j] = TempAdjMatrix[i][j];
                if (d[i][j] == 0) {
                    d[i][j] = 100000000;
                }
            }
        }
        QVector<int> e(N); // Эксцентриситет вершин
        int rad = INT_MAX; // Радиус графа
        int diam = 0; // Диаметр графа

        // Алгоритм Флойда-Уоршелла
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (i == j) {
                        d[i][j] = 0;
                    } else {
                        d[i][j] = min_value(d[i][j], d[i][k] + d[k][j]);
                    }
                }
            }
        }

        // Нахождение эксцентриситета
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                e[i] = max_value(e[i], d[i][j]);
            }
        }

        int CenterVertex=0;
        // Нахождение центра
        for (int i = 0; i < N; i++) {
            int temprad = rad;
            rad = min_value(rad, e[i]);
            if (temprad!=rad) {
                CenterVertex=i;
            }
        }
        QString TempAnswer = "Центр = " + QString::number(CenterVertex);
        TempAnswer += "\nГлубина = " + QString::number(e[CenterVertex]);
        return TempAnswer;
    }

    QVector<int> parentt, degree;
    QVector<QVector<int>> g;

    void dfs (int v) {
        for (size_t i=0; i<g.size(); ++i) {
            if(!g[v][i]) continue;
            int to = i;
            if (to != parentt[v]) {
                parentt[to] = v;
                dfs (to);
            }
        }
    }
    QString Prufer(MGraphObject& gr)
    {
        QVector<QVector<int>> graph = gr.toMatrix();
            QVector<int> vec1(graph.size()), vec2(graph.size());
            parentt = vec1;
            degree = vec2;
            g = graph;

            parentt[graph.size()-1] = -1;
            dfs (graph.size()-1);

            int ptr = -1;
            for (int i=0; i<graph.size(); ++i) {
                for(auto it : graph[i])
                    if(it) degree[i]++;
                if (degree[i] == 1 && ptr == -1)
                    ptr = i;
            }

            QVector<int> result;
            int leaf = ptr;
            for (int iter=0; iter<graph.size()-2; ++iter) {
                int next = parentt[leaf];
                result.push_back (next);
                --degree[next];
                if (degree[next] == 1 && next < ptr)
                    leaf = next;
                else {
                    ++ptr;
                    while (ptr<graph.size() && degree[ptr] != 1)
                        ++ptr;
                    leaf = ptr;
                }
            }
            QString TempAnswer = "Код Прюфера = (";
            for (int i=0; i<result.size(); i++) {
                TempAnswer += QString::number(result[i]) + " ";
            }
            return TempAnswer;
      }
};
#endif // SOLUTION_13_H
