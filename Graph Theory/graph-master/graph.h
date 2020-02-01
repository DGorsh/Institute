///*
// * Граф, который будет являться основным хранилищем данных для графического отображения
// * Не реализует основные алгоритмы, но реализует храние данных для отображения
//*/

//#ifndef GRAPH_H
//#define GRAPH_H

//#include <QVector>
//#include <QDebug>
//#include <QPointF>
//#include <QMap>
//#include <QString>

//enum states {
//    none = -999,
//    oriented = -1000
//};

//enum e_codes {
//    uncorrect_size = 0x01,
//    uncorrect_value = 0x02,
//    not_exists = -0x01
//};


//struct edge { //Описание вершины. Она должна содержать свой код, координату
//    int code;
//    QPointF point;

//    edge() {}
//    edge(const int code, const QPointF point) : code(code), point(point) {
//    }
//};

//template<typename T>
//struct node {
//    T data; //Сами данные вершины
//    int w; //Вес дуги

//    node () {
//    }

//    node(const T data, const int w = 1) : data(data), w(w)
//    {}

//    friend QDebug operator << (QDebug dbg, const node& nd) {
//        dbg.nospace() << "node(data: " << nd.data << ", w: " << nd.w << " )";
//        return dbg.maybeSpace();
//    }

//    bool operator == (const node& with) {
//        return with.data == this->data && with.w == this->w;
//    }

//};

//template <typename T>
//class Graph {
//private:
//    QMap<T, QVector<node<T>>> adMap;

//public:

//    Graph();

//    void addEdge(const T edge);

//    void updateEdge(const T oldEdge, const T newEdge) {
//        //?

//    }

//    void addNode(const T from, const T to, const int w);

//    void addUNode(const T edge1, const T edge2, const int w);

//    bool checkEdge(const T edge);

//    bool checkNode(const T from, const T to, const int w);

//    bool checkUNode(const T edge1, const T edge2, const int w);

//    bool deleteEdge(const T edge);

//    bool deleteNode(const T from, const T to, const int w);

//    bool deleteUNode(const T edge1, const T edge2, const int w);

//    int size() const;

//    QMap<T, QVector<node<T>>>& toMap() const;

//    void visualize();

//};


//template<typename T>
//Graph<T>::Graph()
//{
//}

//template<typename T>
//void Graph<T>::addEdge(const T edge) {
//    adMap.insert(edge, QVector<node<T>>());
//}

//template<typename T>
//void Graph<T>::addNode(const T from, const T to, const int w) {
//    adMap[from].push_back(node<T>(to, w));
//}

//template<typename T>
//void Graph<T>::addUNode(const T edge1, const T edge2, const int w) {
//    addNode(edge1, edge2, w);
//    if (edge1 != edge2)
//        addNode(edge2, edge1, w);
//}

//template<typename T>
//bool Graph<T>::checkEdge(const T edge) { //Существование вершины
//    if (adMap.contains(edge)) {
//        return true;
//    }

//    return false;
//}

//template<typename T>
//bool Graph<T>::checkNode(const T from, const T to, const int w) { //существование соединения между вершинами
//    if (adMap.contains(from)) {
//        if (adMap[from].indexOf(node<T>(to, w)) != e_codes::not_exists) {
//            return true;
//        }
//    }

//    return false;
//}

//template<typename T>
//bool Graph<T>::checkUNode(const T edge1, const T edge2, const int w) {
//    return (checkNode(edge1, edge2, w) && checkNode(edge2, edge1, w));
//}

//template<typename T>
//bool Graph<T>::deleteEdge(const T edge) { //Удаляет полностью вершину
//    for (QVector<node<T>>& it : adMap) {
//        for (node<T> kt : it) {
//            if (kt.data == edge) {
//                it.removeOne(kt);
//            }
//        }
//    }

//    return adMap.remove(edge) > 0;
//}

//template<typename T>
//bool Graph<T>::deleteNode(const T from, const T to, const int w)
//{
//    if (checkNode(from, to, w))
//        return adMap[from].removeOne(node<T>(to,w));

//    return false;
//}

//template<typename T>
//bool Graph<T>::deleteUNode(const T edge1, const T edge2, const int w)
//{
//    if (checkUNode(edge1, edge2, w)) {
//        return deleteNode(edge1, edge2, w) && deleteNode(edge2,edge1, w);
//    }

//    return false;
//}

//template<typename T>
//int Graph<T>::size() const {
//    return adMap.size();
//}

//template<typename T>
//QMap<T, QVector<node<T> > >& Graph<T>::toMap() const {
//    return adMap;
//}


//template<typename T>
//void Graph<T>::visualize() {
//    qDebug() << adMap;
//}



//#endif // GRAPH_H
