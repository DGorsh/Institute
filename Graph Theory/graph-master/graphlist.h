//#ifndef GRAPHLIST_H
//#define GRAPHLIST_H

////Граф, базирующийся на списке смежности. Представляется как вектор векторов
////Предназначен для реализации алгоритмов

//#include <QVector>
//#include <QDebug>

//struct node {
//    int data; //Сами данные вершины
//    int w; //Вес дуги

//    node () {
//    }

//    node(const int data, const int w = 1) : data(data), w(w)
//    {}

//    friend QDebug operator << (QDebug dbg, const node& nd) {
//        dbg.nospace() << "node(data: " << nd.data << ", w: " << nd.w << " )";
//        return dbg.maybeSpace();
//    }

//    bool operator == (const node& with) {
//        return with.data == this->data && with.w == this->w;
//    }

//};

//class GraphList
//{
//private:
//    QVector<QVector<node>> graph;

//public:
//    GraphList();


//};

//#endif // GRAPHLIST_H
