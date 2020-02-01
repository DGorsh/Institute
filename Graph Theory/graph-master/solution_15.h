#ifndef SOLUTION_15_H
#define SOLUTION_15_H

#include <msolution.h>
#include <QQueue>

const int none = -1;
const int first = 1;
const int second = 2;

class Solution_15 : public MSolution<QString>
{

private:
    MGraphObject graphObject;
    QVector<int> left;
    QVector<int> rigth;
public:
    Solution_15(MGraphObject& object, QVector<int>& left, QVector<int>& rigth) : graphObject(object), left(left), rigth(rigth){

    }

    Solution_15() {

    }

    virtual void run() override;

    virtual ~Solution_15() override {

    }

    MAnswer<QString> res() const;

    //Проверяет на двудольность графа
    bool isDual(MGraphObject& graph, QVector<int>& left, QVector<int>& right);

    void meclear(MGraphObject& graph);

    QVector<int> pairs(MGraphObject &graph);

    bool dfs(MGraphObject& graph, QVector<int>& matching, int vertexId);

//    bool dfs(MMatrix& matrix, QVector<int>& matching, QVector<bool>  used, int vertex) {
//        if (used[vertex])
//            return false;
//        used[vertex] = true;

//        for (int to : matrix[vertex]) {
//            if (matching[to] == -1 || dfs(matrix, matching, used, matching[to])) {
//                matching[to] = vertex;
//                return true;
//            }
//        }
//        return false;
//    }

//    bool isDual(MGraphObject& graph, int startId) {

//        QHash<int, int> doles;

//        QQueue<int> Q;

//        for (auto& it : graph.getVertexs_link()) { //Пока никакая из вершин никчемная
//            doles.insert(it.id, none);
//        }

//        Q.push_back(startId);

//        while(!Q.isEmpty()) {
//            int v = Q.front();
//            Q.pop_front();

//            if (doles[v] == none)
//                doles[v] = first;

//            int index = graph.getIndexByVertexId(v);

//            if (index == MConstants::not_exists)
//                throw MUncorrectInput();

//            for (auto& node : graph.getNodes_link()[index]) {

//                MVertexNode* minNode = graph.getMinWNodeById(node.parent, node.data);
//                MVertex* vertex = graph.getVertexById(minNode->data);

//                //Если вершина не посещена, то выполняем следующие действия
//                if (doles[(vertex)->id] == none) {
//                    if (doles[v] == first)
//                        doles[vertex->id] = second;
//                    else {
//                        doles[vertex->id] = first;
//                    }
//                } else { //Если вершина посещена, то необходимо убедиться в том, что исходная и та вершина, которую мы посетили находятся в разных долях
//                    if (doles[v] == doles[vertex->id]) {
//                        return false;
//                    }

//                }


//                Q.push_back(vertex->id);
//            }
//        }


//        qDebug() << doles;

//        return true;

//    }
};

#endif // SOLUTION_15_H
