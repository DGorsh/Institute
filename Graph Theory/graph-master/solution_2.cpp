#include "solution_2.h"

Solution_2::Solution_2(const MGraphObject& graphObject, int fromId, int toId, int MODE) : graphObject(graphObject), fromId(fromId), toId(toId), MODE(MODE) {
}

Solution_2::Solution_2() {
    this->graphObject = MGraphObject();
}

void Solution_2::run() {
    QPair<QVector<int>, QVector<int>> res;

    if (MODE == 0){
        res = BFSFind(graphObject, fromId, toId);
    }
    if (MODE == 1) {
        res = A_star(graphObject, fromId, toId);
    }

    int indexfrom = graphObject.getIndexByVertexId(fromId);
    int indexto = graphObject.getIndexByVertexId(toId);

    if (res.first[indexto] != MConstants::flag_unvisited) {
        QVector<int> path;

        for (int v = indexto; v != -1; v= graphObject.getIndexByVertexId(res.first[v])) {
            path.push_back(v);
        }

        savedResult = MAnswer<QPair<QVector<int>, int>>(QPair<QVector<int>, int>(path, res.second[indexto]));

    } else {
        throw MSolutionNotFound();
    }


}

Solution_2::~Solution_2() {}

QPair<QVector<int>, QVector<int>> Solution_2::BFSFind(MGraphObject &graph, int fromId, int toId) {

    if (graph.checkVertex(fromId) && graph.checkVertex(toId)) {

        QQueue<int> Q;
        QVector<int> p(graph.getVertexs_link().size(), MConstants::flag_unvisited);
        QVector<int> w(graph.getVertexs_link().size(), 0);

        graph.getVertexById(fromId)->flag = MConstants::flag_visited;

        Q.push_back(fromId);

        while(!Q.isEmpty()) {
            unsigned v = Q.front();
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
                    int k = graph.getIndexByVertexId(minNode->data);
                    w[k] += w[index] + minNode->w;
                    p[k] = v;
                }

            }
        }

        return QPair<QVector<int>, QVector<int>>(p,w);

    } else {
        throw MUncorrectInput();
    }

}

QPair<QVector<int>, QVector<int> > Solution_2::A_star(MGraphObject &graph, int fromId, int toId) {
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
