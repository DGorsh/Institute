#ifndef SOLUTION_6_H
#define SOLUTION_6_H

#include <msolution.h>
#include <QQueue>
#include <QStack>

class Solution_6 : MSolution<QString>
{
    MGraphObject graph;
    bool oriented = false;
    QString result = "";

public:
    Solution_6(MGraphObject& graph, bool oriented = false) : graph(graph), oriented(oriented) {

    }

    Solution_6() {

    }

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

    QString getComponents(MGraphObject& graph) {

        QVector<QStack<int> > componentsVec;

        for (auto& it : graph.getVertexs_link()) {
            if (it.flag != MConstants::flag_visited)
                componentsVec.push_back(BFS(graph, it.id));
        }

        if (componentsVec.size() == 1) {
            if (!oriented)
                result.append("\nГраф является связным (содержит одну компоненту связноти)\n");
            else {
                result.append("\nГраф является сильно связным (содержит одну компоненту связности)\n");
            }
        } else if (componentsVec.size() > 1 && oriented) {
            //Проверяем граф на слабую связность

            graph.generateLinearVector();

            for (auto& it : graph.getLinearNodeVector_link()) {
                if (graph.checkNode(graph.getVertexById(it.parent), graph.getVertexById(it.data)) && !graph.checkNode(graph.getVertexById(it.data), graph.getVertexById(it.parent))) {
                    result.append("\nДополнили: " + QString::number(it.parent)).append(" к " + QString::number(it.data));
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

            if (newComponents.size() == 1) {
                result.append("\nГраф является слабо связным\n");
            } else {
                result.append("\nГраф является несвязным\n");
            }

        } else if (componentsVec.size() > 1 && !oriented) {
            result.append("Граф является несвязным\n");
        }

        result.append("\n Компоненты связности: \n");
        for (auto& it : componentsVec) {
            for (auto& jt : it) {
                result.append(QString::number(jt)).append(" -> ");

            }
            result.append('\n');
        }

        if (!oriented) {
            find_bridges(graph);
        }


        return result;
    }


    int min (int a, int b) {
         return a > b ? b : a;
    }

    void dfs (MGraphObject& graph, QVector<bool>& used, QVector<int>& tin, QVector<int>& fup, int& timer, int v, int p = MConstants::not_exists) {
        int v_index = graph.getIndexByVertexId(v);

        used[v_index] = true;
        tin[v_index] = fup[v_index] = timer++;

        for (auto& it : graph.getNodes_link()[v_index]) {
            int toIndex= graph.getIndexByVertexId(it.data);
            if (it.data == p) continue;

            if (used[toIndex]) {
                fup[v_index] = min(fup[v_index], tin[toIndex]);
            } else {
                dfs(graph, used, tin, fup, timer, it.data, v);
                fup[v_index] = min(fup[v_index], fup[toIndex]);
                if (fup[toIndex] > tin[v_index])
                    result.append(QString::number(it.parent)).append(" ").append(QString::number(it.data)).append('\n');
            }
        }
    }

    void find_bridges(MGraphObject& graph) {
        int timer = 0;
        QVector<int> tin(graph.countVertexs(), 0);
        QVector<int> fup(graph.countVertexs(), 0);
        QVector<bool> used(graph.countVertexs(), false);
        result.append("\nМосты (и, соотв, шарниры):\n");
        for (auto& it : graph.getVertexs_link()) {
            if (!used[graph.getIndexByVertexId(it.id)]) {
                dfs(graph, used, tin, fup, timer, it.id);
            }
        }

    }


};

#endif // SOLUTION_6_H
