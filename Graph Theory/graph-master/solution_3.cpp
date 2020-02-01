#include "solution_3.h"

Solution_3::Solution_3(const MGraphObject &graphObject, int fromId) : graphObject(graphObject), fromId(fromId) {

}

Solution_3::Solution_3() {}

void Solution_3::run() {
    Dijkstra(graphObject, fromId);
}

Solution_3::~Solution_3() {}

PairOfVectors Solution_3::Dijkstra(MGraphObject &graph, int fromId) {

    /*
     * Будет использоваться очередь с приоритетами из STL
     *
     * */

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

        result.append("\nВектор дистанций\n");
        for (int i = 0; i < distances.size(); ++i) {
            result.append("До вершины ").append(QString::number(i)).append(" Дистанция: ").append(QString::number(distances[i])).append('\n');
        }

        result.append("\nВектор родителей\n");
        for (int i = 0; i < parents.size(); ++i) {
            result.append(QString::number(i)).append(" есть родитель ").append(" ").append(QString::number(parents[i])).append('\n');
        }

        return QPair<QVector<int>, QVector<int>>(distances, parents);

    } else {
        throw MUncorrectInput();
    }
}

/*
 * Беллман форд - возвращает true, если нет циклов с отрицательным весом
 * false, иначе
 * */
PairOfBooleanAndPair Solution_3::BellmanFord(MGraphObject &graph, int fromId) {
    //Инициализация

    if (graph.checkVertex(fromId)) {

        QVector<distance> distances(graph.countVertexs(), INF);
        QVector<parent> parents(graph.countVertexs(), MConstants::not_exists);

        distances[graph.getIndexByVertexId(fromId)] = 0;

        //Оптимизация
        graph.generateLinearVector();

        //Теперь сам алгоритм

        for (int i = 0; i < graph.countVertexs()-1; i++) {
            for (auto& it: graph.getLinearNodeVector_link()) {
                relax(graph, distances, parents, it.parent, it.data, it.w); //Релаксация
            }
        }



        for (auto& node : graph.getLinearNodeVector_link()) {

            int fromIndex = graph.getIndexByVertexId(node.parent);
            int toIndex = graph.getIndexByVertexId(node.data);

            if (distances[toIndex] > distances[fromIndex] + node.w) {
                result.append("\nВектор дистанций\n");
                for (int i = 0; i < distances.size(); ++i) {
                    result.append("До вершины ").append(QString::number(i)).append(" Дистанция: ").append(QString::number(distances[i])).append('\n');
                }

                result.append("\nВектор родителей\n");
                for (int i = 0; i < parents.size(); ++i) {
                    result.append(QString::number(i)).append(" есть родитель ").append(" ").append(QString::number(parents[i])).append('\n');
                }

                result.append("\nНасчёт циклов\n");
                result.append("false");
                return PairOfBooleanAndPair(false, PairOfVectors(distances, parents));
            }
        }


        result.append("\nВектор дистанций\n");
        for (int i = 0; i < distances.size(); ++i) {
            result.append("До вершины ").append(QString::number(i)).append(" Дистанция: ").append(QString::number(distances[i])).append('\n');
        }

        result.append("\nВектор родителей\n");
        for (int i = 0; i < parents.size(); ++i) {
            result.append(QString::number(i)).append(" есть родитель ").append(" ").append(QString::number(parents[i])).append('\n');
        }

        result.append("\nНасчёт циклов\n");
        result.append("true");
        return PairOfBooleanAndPair(true, PairOfVectors(distances, parents));
    } else {
        throw MUncorrectInput();
    }
}

PairOfVectors Solution_3::FloydWorshell(MGraphObject &graph, int fromId) {

    MMatrix d = graph.toMatrix();
    int n = d.size();

    for (int i = 0; i < d.size(); ++i) {
        for (int j = 0; j < d.size(); ++j) {
            if (d[i][j] == 0) {
                d[i][j] = INF;
            }
        }
    }



    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min (d[i][j], d[i][k] + d[k][j]);


    for (int i = 0; i < d.size(); ++i) {
        for (int j = 0; j < d.size(); ++j) {
            if (i == j) {
                d[i][j] = -1;
            } else {
                   result.append("\nРасстояние от вершины").append(QString::number(i)).append(" до ").append(QString::number(j)).append(" : ").append(QString::number(d[i][j]));
            }
        }
    }

    return PairOfVectors(QPair<QVector<int>, QVector<int>>());
}

void Solution_3::Jhonson(MGraphObject &graph, int fromId) {

    qDebug() << "Исполяется Джонсон для поиска расстониями между парами";
    MMatrix d = graph.toMatrix();
    int n = d.size();

    for (int i = 0; i < d.size(); ++i) {
        for (int j = 0; j < d.size(); ++j) {
            if (d[i][j] == 0) {
                d[i][j] = INF;
            }
        }
    }



    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min (d[i][j], d[i][k] + d[k][j]);


    QVector<int> iused;
    QVector<int> jused;

    for (int i = 0; i < d.size(); ++i) {
        for (int j = 0; j < d.size(); ++j) {
            if (i == j) {
                d[i][j] = -1;
            } else{
                   result.append("\nРасстояние от вершины ").append(QString::number(i)).append(" до ").append(QString::number(j)).append(" : ").append(QString::number(d[i][j]));
            }
        }
    }
}

void Solution_3::relax(MGraphObject &graph, QVector<distance> &dist, QVector<parent> &parent, int fromId, int toId, int w) {
    int fromIndex = graph.getIndexByVertexId(fromId);
    int toIndex = graph.getIndexByVertexId(toId);

    if (dist[toIndex] > dist[fromIndex] + w) {
        dist[toIndex] = dist[fromIndex] + w;
        parent[toIndex] = fromId;

    }

}

int Solution_3::min(int a, int b) {
    return a > b ? b : a;
}

