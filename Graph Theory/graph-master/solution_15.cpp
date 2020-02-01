#include "solution_15.h"

void Solution_15::run() {
    QString result("");
    if (isDual(graphObject, left, rigth)) {
        result.append("Граф является двудольным с указанными долями;\n");
        QVector<int> pairv = pairs(graphObject);

        for (auto& it : graphObject.getVertexs_link()) {
            result.append("Из: ").append(QString::number(it.id)).append(" В: ").append(QString::number(pairv[graphObject.getIndexByVertexId(it.id)])).append("\n");
        }


    } else {
        result.append("Граф не является двудольным");
    }

    savedResult = MAnswer<QString>(result);

}

MAnswer<QString> Solution_15::res() const {
    return savedResult;
}

bool Solution_15::isDual(MGraphObject &graph, QVector<int> &left, QVector<int> &right) {

    this->left = left;
    //Подзадача 1 - проверяем, является ли выделенные доли графа двудольными

    //O(N^2)
    for (int i = 0; i < left.size(); ++i) {
        //Проверяем связи между вершинами левых долей
        for (int j = 0; j < left.size(); j++) {
            if (i != j) {
                if (graph.checkNode(graph.getVertexById(left[i]), graph.getVertexById(left[j])))
                {
                    return false;
                }
            }
        }

    }


    for (int i = 0; i < right.size(); ++i) {
        for (int j = 0; j < right.size(); ++j) {
            if (i != j) {
                if (graph.checkNode(
                            graph.getVertexById(right[i]), graph.getVertexById(right[j]))) {
                    return false;
                }
            }
        }
    }


    return true;
}

void Solution_15::meclear(MGraphObject &graph) {
    for (auto& it : graph.getVertexs_link()) {
        it.flag = MConstants::flag_unvisited;
    }
}

QVector<int> Solution_15::pairs(MGraphObject &graph) {
    QVector<int> match(graph.countVertexs(), MConstants::not_exists);
    QVector<bool> used(graph.countVertexs(), false);

    MMatrix matrix = graph.toMinMatrix();

    for (auto& it : left) {
        meclear(graph);
        dfs(graph, match, it);
    }

    return match;
}

bool Solution_15::dfs(MGraphObject &graph, QVector<int> &matching, int vertexId) {
    MVertex* vertex = graph.getVertexById(vertexId);

    if (vertex->flag == MConstants::flag_visited) {
        return false;
    }

    vertex->flag = MConstants::flag_visited;

    for (auto& it : graph.getNodes_link()[graph.getIndexByVertexId(vertexId)]) {
        if (matching[graph.getIndexByVertexId(it.data)] == MConstants::not_exists || dfs(graph, matching, matching[graph.getIndexByVertexId(it.data)])) {
            matching[graph.getIndexByVertexId(it.data)] = vertexId;
            return true;
        }
    }

    return false;
}
