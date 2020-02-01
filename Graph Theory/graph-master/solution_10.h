#ifndef SOLUTION_10_H
#define SOLUTION_10_H

#include <msolution.h>


typedef QVector<int> intVector;
typedef QVector<QVector<int>> intMatrix;

class Solution_10 : MSolution<QPair<MGraphObject, QString>>
{
private:
    intVector vector;
    QString logResult = "";
public:
    Solution_10(const intVector vector) : vector(vector) {
        if (vector.size() == 0)
            throw MUncorrectInput();
    }

    Solution_10() {

    }

    virtual void run() override {
        MGraphObject resultGraph = fromVector(vector);
        logResult.append("Граф построен\n");

        if (isExtrem(resultGraph.toMatrix())) {
            logResult.append("Граф является экстремальным");
            getBase(resultGraph.toMatrix());
        }

        savedResult = MAnswer<QPair<MGraphObject, QString>>(QPair<MGraphObject, QString>(resultGraph, logResult));
    }

    virtual ~Solution_10() override {

    }

    MGraphObject fromVector(QVector<int>& vector) {

        bool isSov = true;
        //Будем считать, что вектор отсортирован
        MGraphObject resultGraph;

        if (vector[0] > vector.size() - 1)
            throw MUncorrectInput();
        if (sum(vector) & 1) {
            throw MUncorrectInput();
        }

        //Добавляем в граф вершины

        for (int i = 0; i < vector.size(); i++) {
            resultGraph.addVertex(QPointF(200 + 150*cos(i*6.28/vector.size()),
                                   200 + 150*sin(i*6.28/vector.size())));
        }

        //Начинаем строить граф
        int k = 0;

        while(k < vector.size()-1) {
            if (vector[k] != 0) {

                for (int i = k+1; i <= vector[k]+k; i++) { //Соединяем вершину с каждой в течение n штук
                    resultGraph.addUNode(resultGraph.getVertexById(k), resultGraph.getVertexById(i));
                }

                for (int i = k+1; i <= vector[k]+k; i++)
                    vector[i]--;

                if (vector.size() - k - vector[k] != 0) {
                    isSov = false;
                }

                vector[k] = 0;

                logResult.append("\nИтерация:");
                for (auto it : vector) {
                    logResult.append(QString::number(it) + " ");
                }
            }

            k++;
        }

        if (isSov) {
            logResult.append("\nГраф является совершенным\n");
        }

        return resultGraph;
    }


    int sum(const QVector<int>& vector) {
        int summ = 0;

        for (auto& it : vector) {
            summ += it;
        }
        return summ;
    }



    bool isExtrem(const QVector<QVector<int>>& matrix) {
        for (int j = 0; j < matrix.size(); j++) {
            for (int i = 0; i < matrix.size()-1; ++i) {
                if (i != j) {
                    if (matrix[j][i] == 0 && matrix[j][i+1] == 1){ //Если ноль правее единицы
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void getBase(const MMatrix& matrix) {
        bool basefound = false;
        //Осуществляет поиск базы графа
        for (int i = 0; i < matrix.size()-1; ++i) {
            for (int j = matrix.size()-1; j > 1; --j) {
                if (matrix[i][j] == 0 && matrix[i][j-1] == 1 && matrix[i+1][j] == 0 && matrix[i+1][j-1] == 0) {
                    logResult.append("\nНайдена база: ").append(QString::number(i)).append(" ").append(QString::number(j-1));
                    basefound = true;
                    break;
                }
            }
        }

        if (!basefound)
            logResult.append("\nНайдена база\n").append(QString::number(0)).append(" ").append(QString::number(matrix.size()-1));
    }

    MAnswer<QPair<MGraphObject, QString>> res() const {
        return savedResult;
    }
};

#endif // SOLUTION_10_H
