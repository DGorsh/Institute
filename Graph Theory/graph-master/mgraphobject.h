/*
 * 2019, Maxim Degtyarev
 * MGraphObject class definition
 * */

#include <QPointF>
#include <QColor>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QHash>

#include <qmath.h>


class Scene;

#ifndef MGRAPHOBJECT_H
#define MGRAPHOBJECT_H

namespace MConstants {
const int not_exists = -1;
const int Vertex_diam = 30;
const int point_center = 16;
const bool uncheck_center = false;
const bool check_center = true;
const bool check_w = true;
const bool uncheck_w = false;
const int dont_know = INT_MAX;

const int flag_visited = 1;
const int flag_unvisited = -1;
}

enum MDistribution {
    ITERATIVE,
    UNIFORM,
    PLANAR
};

enum MModes {
    NONE,
    MOVE,
    DESTROY,
    EDIT,
    CREATE,
    CONNECT,
    UCONNECT,
    SELECT_ALG,
    MOVE_CENTER
};

enum MColor {
    CL_SELECTED = 0,
    CL_USED = 1,
    CL_DEFAULT = 2,
    CL_VISITED = 3,
    CL_RED = 4,
    CL_BLUE = 5,
    CL_GREEN = 6,
    CL_GRAY = 7,
    CL_BLACK = 8,
    CL_YELLOW = 9
};

enum MTypes {
    ONE_DIRECTION,
    BIDIRECTION
};

/*
 * Описание основных структур графа
*/


/*
 * Структура вершины. Хранит 3 базовых поля (уникальный ID, точка расположения, цвет)
 * */
struct MVertex {
    int id;
    int flag = MConstants::flag_unvisited;
    QPointF point;
    MColor color;

    int d;
    int last;

    MVertex(const int id, const QPointF point) : id(id), point(point), color(CL_DEFAULT) {}

    MVertex() : color(CL_DEFAULT) {}
    bool operator == (const MVertex& with) const {
        return with.id == this->id && with.point == this->point;
    }

    bool operator == (MVertex& with) const {
        return with.id == this->id && with.point == this->point;
    }

    friend QDebug operator << (QDebug deb, const MVertex& self) {
        deb.nospace() << "Vertex: [id: " << self.id << ", point: " << self.point << "]";
        return deb.maybeSpace();
    }

    void DMoveVertex (const QPointF point) {
        this->point = point;
    }
};

/*
 * Структура ребра. Хранит 3 базовых поля (ID вершины, к которой идёт соединение, вес дуги, связывающую точку ребра)
 * */
struct MVertexNode {
    int id;

    int parent;
    int data;
    int w;
    bool checkCenter;
    bool checkW;

    QPointF center;
    MColor color;

    MVertexNode () {
    }

    MVertexNode(int parent, int data, const int w = 1) : parent(parent), data(data), w(w) {
        checkW = MConstants::check_w;
    }

    MVertexNode(int parent, int data, const QPointF center, const int w = 1, const bool checkCenter = MConstants::check_center, const bool checkW = MConstants::check_w) : parent(parent), data(data), center(center), w(w), checkCenter(checkCenter), checkW(checkW) {
    }

    MVertexNode(int id,int parent, int data, const QPointF center, const int w = 1, const bool checkCenter = MConstants::check_center, const bool checkW = MConstants::check_w) : MVertexNode(parent, data, center, w, checkCenter, checkW) {
        this->id = id;
    }

    bool operator == (const MVertexNode& with) const {
        bool w_in = with.w == this->w;
        bool cen_in = with.center == this->center;

        if (checkCenter && checkW)
            return with.parent == this->parent && with.data == this->data && cen_in && w_in;
        else if (!checkCenter && checkW) {
            return with.parent == this->parent && with.data == this->data && with.w == this->w;
        } else if (checkCenter && !checkW) {
            return with.parent == this->parent && with.data == this->data && with.w == this->w && cen_in;
        } else if (!checkCenter && !checkW) {
            return with.data == this->data && this->parent == with.parent;
        }
    }

    bool operator > (const MVertexNode& with) {
        return (this->data == with.data && this->parent == with.parent) && (this->w > with.w);
    }

    bool operator < (const MVertexNode& with) {
        return (this->data == with.data && this->parent == with.parent) && (this->w < with.w);
    }

    friend QDebug operator << (QDebug dbg, const MVertexNode& self) {
        dbg.nospace() << "node:[parent: " << self.parent  << ", data: " << self.data << ", w: " << self.w << " center: " << self.center << "]";
        return dbg.maybeSpace();
    }

};

typedef QVector<QVector<MVertexNode>> nodeVector;
typedef QVector<MVertex> vertexVector;

class MGraphObject
{
    friend Scene;

private:
    MVertexNode* activeNode;
    QVector<MVertex> Vertexs;

    nodeVector nodes;
    QVector<MVertexNode> linearNodeVector; //Линейный вариант всех вершин в случае, если нужно пройтись по всем вершинам не за квадрат

    int last_operation_num;

    int id;
    int nid;

    int bufw;

public:

    explicit MGraphObject() {
        id = 0;
        nid = 0;
    }


    /*
     * Graph model methods
     * */
public:

    /*
     * Убирает у графа есть статус мультиграфа.
     * Оставляет минимальные рёбра
     * */


    void addVertex(const MVertex Vertex);

    void addVertex(const QPointF& coordinates);

    void updateVertex(const MVertex oldVertex, const MVertex newVertex);

    void generateLinearVector() {
        linearNodeVector.clear();

        for (auto& it : nodes) {
            for (auto& jt : it) {
                linearNodeVector.push_back(jt);
            }
        }
    }

    int getVertexDegreeById(int id) {
        if (checkVertex(id)) {
            return nodes[getIndexByVertexId(id)].size();
        }

        return MConstants::not_exists;
    }


    bool checkVertex(MVertex* Vertex);

    bool checkVertex(unsigned vertexId);

    bool addNode(MVertex* from, MVertex* to, const int w = 1);

    bool addUNode(MVertex* Vertex1, MVertex* Vertex2, const int w = 1);

    bool checkNode(MVertex* from, MVertex* to, const int w = 1);

    bool checkUNode(MVertex* Vertex1, MVertex* Vertex2, const int w = 1);

    bool deleteVertex(MVertex* Vertex);

    bool deleteNode(MVertex* from, MVertex* to, const int w);

    bool deleteUNode(MVertex* Vertex1, MVertex* Vertex2, const int w);

    bool reverseNode(MVertex* from, MVertex* to, const int w);

    bool reverseNode(MVertexNode* node);

    int countNodes();

    int countVertexs();

    int size();

    MVertex *getVertexByPos(const QPointF coordinates);

    MVertex *getVertexByIndex(const unsigned index);

    MVertexNode* getNodeByPos(const QPointF coordinates);

    MVertexNode* getMinWNodeById(const int parent, const int data, const int w = MConstants::dont_know, const bool checkW = MConstants::uncheck_w);

    MVertex *getVertexById(const int id);

    MVertexNode *getNodeById(const int parent, const int data, const int w = MConstants::dont_know, const bool checkW = MConstants::uncheck_w);

    int getIndexByVertexId(const int id);

    void clearColor() {
        for (auto& it : Vertexs) {
            it.color = CL_DEFAULT;
        }
    }

    QVector<QVector<int>> toMatrix();

    //Получает матрицу меньших рёбер в случае мультиграфа
    QVector<QVector<int>> toMinMatrix() {
        QVector<QVector<int>> currentMatrix(Vertexs.size(), QVector<int>(Vertexs.size()));
        for (auto& it : nodes) {
            for (auto& jt : it) {
                currentMatrix[getIndexByVertexId(jt.parent)][getIndexByVertexId(jt.data)] = getMinWNodeById(jt.parent, jt.data)->w;
            }
        }

        return currentMatrix;
    }

    /*
    void fromMatrix(QVector<QVector<int>> inMatrix) {
        clear();
    }
    */

    void clear();

    void DMoveVertex (int id, QPointF point);

    nodeVector getNodes() {
        return nodes;
    }

    nodeVector* getNodes_ptr() {
        return &nodes;
    }

    nodeVector& getNodes_link() {
        return nodes;
    }

    vertexVector getVertexs() {
        return Vertexs;
    }

    vertexVector* getVertexs_ptr() {
        return &Vertexs;
    }

    vertexVector& getVertexs_link() {
        return Vertexs;
    }

    QVector<MVertexNode> getLinearNodeVector() {
        return linearNodeVector;
    }

    QVector<MVertexNode>& getLinearNodeVector_link() {
        return linearNodeVector;
    }

    QVector<MVertexNode>* getLinearNodeVector_ptr() {
        return &linearNodeVector;
    }
};


#endif // MGRAPHOBJECT_H
