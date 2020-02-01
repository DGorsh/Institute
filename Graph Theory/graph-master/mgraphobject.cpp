#include "mgraphobject.h"


void MGraphObject::addVertex(const MVertex Vertex) {
    Vertexs.push_back(Vertex);
    nodes.push_back(QVector<MVertexNode>());
}

void MGraphObject::addVertex(const QPointF &coordinates) {
    MVertex newVertex(id++, coordinates);
    addVertex(newVertex);
}

void MGraphObject::updateVertex(const MVertex oldVertex, const MVertex newVertex) {
    Vertexs.replace(Vertexs.indexOf(oldVertex), newVertex);
}

bool MGraphObject::checkVertex(MVertex *Vertex) {
    return Vertexs.indexOf(*Vertex) != MConstants::not_exists;
}

bool MGraphObject::checkVertex(unsigned vertexId) {
    return getVertexById(vertexId) != nullptr;
}

bool MGraphObject::addNode(MVertex *from, MVertex *to, const int w) {
    int fromIndex = Vertexs.indexOf(*from);

    QPointF center;

    if (from->id == to->id) {
        center = QPointF(int((80 * (pow(-1, rand()%2)))) +
                         (from->point.x()),
                         int((80 * (pow(-1, rand()%2)))) +
                         (from->point.y()));
    } else {
        center = QPointF(int((rand()%80 * (pow(-1, rand()%2)))) +
                         (from->point.x() + to->point.x()) / 2,
                         int((rand()%80 * (pow(-1, rand()%2)))) +
                         (from->point.y() + to->point.y()) / 2);
    }


    if (checkVertex(from) && checkVertex(to)) {
        nodes[fromIndex].push_back(MVertexNode(nid++, from->id, to->id, center, w));
        return true;
    }

    return false;
}

bool MGraphObject::addUNode(MVertex *Vertex1, MVertex *Vertex2, const int w) {

    if (checkVertex(Vertex1) && checkVertex(Vertex2)) {
        return addNode(Vertex1, Vertex2, w) && addNode(Vertex2, Vertex1, w);
    }

    return false;
}

bool MGraphObject::checkNode(MVertex *from, MVertex *to, const int w) {
//    int fromIndex = Vertexs.indexOf(*from);
//    int toIndex = Vertexs.indexOf(*to);

    MVertexNode* node = getNodeById(from->id, to->id, w);

    if (node != nullptr) {
        return true;
    }

    return false;
}

bool MGraphObject::checkUNode(MVertex *Vertex1, MVertex *Vertex2, const int w) {
    return checkNode(Vertex1, Vertex2, w) && checkNode(Vertex2,Vertex1, w);
}

bool MGraphObject::deleteVertex(MVertex *Vertex) {
    if (checkVertex(Vertex)) {
        for (auto &it : nodes) {
            for (auto &dt : it) {
                if (dt.data == Vertex->id) {
                    it.removeOne(dt);
                }
            }
        }

        nodes.remove(Vertexs.indexOf(*Vertex));
        return Vertexs.removeOne(*Vertex);
    }

    return false;
}

bool MGraphObject::deleteNode(MVertex *from, MVertex *to, const int w) {
    int fromIndex = Vertexs.indexOf(*from);
    int toIndex = Vertexs.indexOf(*to);

    if (checkNode(from, to, w)) {
        MVertexNode* node = getNodeById(from->id, to->id, w);
        nodes[Vertexs.indexOf(*getVertexById(from->id))].removeOne(*node);
    }

    return false;
}

bool MGraphObject::deleteUNode(MVertex *Vertex1, MVertex *Vertex2, const int w) {
    return deleteNode(Vertex1, Vertex2, w) && deleteNode(Vertex2, Vertex1, w);
}

bool MGraphObject::reverseNode(MVertex *from, MVertex *to, const int w) {
    if (checkNode(from, to, w)) {
        deleteNode(from, to, w);
        return addNode(to, from, w);
    }

    return false;
}

bool MGraphObject::reverseNode(MVertexNode *node) {
    return reverseNode(getVertexById(node->parent), getVertexById(node->data), node->w);
}

int MGraphObject::countNodes() {
    int result = 0;

    for (auto &it : nodes)
        result += it.size();

    return result;
}

int MGraphObject::countVertexs() {
    return Vertexs.size();
}

int MGraphObject::size() {
    return countNodes() + countVertexs();
}

MVertex *MGraphObject::getVertexByPos(const QPointF coordinates) {
    for (auto &it : Vertexs) {
        if (abs(it.point.x() - coordinates.x()) < 30 && abs(it.point.y() - coordinates.y()) < 30) {
            return &it;
        }
    }

    return nullptr;
}

MVertex *MGraphObject::getVertexByIndex(const unsigned index) {
    if (index >= Vertexs.size())
        throw MConstants::not_exists;

    return &Vertexs[index];
}

MVertexNode *MGraphObject::getNodeByPos(const QPointF coordinates) {
    for (auto &it : nodes) {
        for (auto &kt : it) {
            if (abs(kt.center.x() - coordinates.x()) < (MConstants::point_center/ 2) && abs(kt.center.y() - coordinates.y()) < (MConstants::point_center/ 2)) {
                return &nodes[nodes.indexOf(it)][nodes[nodes.indexOf(it)].indexOf(kt)];
            }
        }
    }

    return nullptr;
}

MVertexNode *MGraphObject::getMinWNodeById(const int parent, const int data, const int w, const bool checkW) {

    MVertex* Vertex = getVertexById(parent);

    int index = Vertexs.indexOf(*Vertex);

    MVertexNode check_node = MVertexNode(parent, data, QPointF(), w, MConstants::uncheck_center, checkW);

    MVertexNode* result = &check_node;

    for (auto &node : nodes[index]) {
        if (*result > node) {
            result = &node;
        }
    }

    if (result->w != check_node.w)
        return result;
    else {
        return nullptr;
    }
}

MVertex *MGraphObject::getVertexById(const int id) {
    int left = 0;
    int right = Vertexs.size() - 1;

    while(left <= right) {
        int middle = (left + right) / 2;
        if (Vertexs[middle].id == id)
            return &Vertexs[middle];

        if (Vertexs[middle].id < id)
            left = middle + 1;
        else {
            right = middle - 1;
        }
    }

    return nullptr;
}

MVertexNode *MGraphObject::getNodeById(const int parent, const int data, const int w, const bool checkW) {
    MVertex* Vertex = getVertexById(parent);
    int index = Vertexs.indexOf(*Vertex);

    MVertexNode check_node = MVertexNode(parent, data, QPointF(), w, MConstants::uncheck_center, checkW);

    for (auto &node : nodes[index]) {
        if (check_node == node) {
            return &node;
        }
    }

    return nullptr;
}

int MGraphObject::getIndexByVertexId(const int id) {
    MVertex* currentVertex = getVertexById(id);

    if (currentVertex != nullptr) {
        return Vertexs.indexOf(*currentVertex);
    }

    return MConstants::not_exists;
}

QVector<QVector<int> > MGraphObject::toMatrix() {
    QVector<QVector<int>> currentMatrix(Vertexs.size(), QVector<int>(Vertexs.size()));

    for (int i = 0; i < Vertexs.size(); i++) {
        for (auto current_node : nodes[i]) {
            currentMatrix[i][Vertexs.indexOf(*getVertexById(current_node.data))] += current_node.w;
        }
    }

    return currentMatrix;
}

void MGraphObject::clear() {
    id = 0;
    nodes.clear();
    Vertexs.clear();

}

void MGraphObject::DMoveVertex (int id, QPointF point) {
    this->Vertexs[id].DMoveVertex(point);
}


