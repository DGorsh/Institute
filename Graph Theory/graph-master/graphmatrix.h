#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

//Граф, основанный на матрице смежности
//Предназначен для реализации алгоритмических задач

#include <QVector>

class GraphMatrix
{
public:
    QVector<QVector<int>>* adMatrix;

    GraphMatrix() {
    }

    GraphMatrix(const int size) {
        adMatrix = new QVector<QVector<int>>(size);
    }

    GraphMatrix(QVector<QVector<int>>* data) {
        adMatrix = data;
    }

    void addEdge(const int w) {

    }
};

#endif // GRAPHMATRIX_H
