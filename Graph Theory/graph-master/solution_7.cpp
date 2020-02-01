#include "solution_7.h"

MAnswer<QPair<MGraphObject, QString> > Solution_7::inv(MGraphObject &object) {

    //float m = object.countNodes() / 2.0;
    //int n = static_cast<int>(ceilf(m));

    MGraphObject result;
    for (auto& it : object.getVertexs_link()) {
        result.addVertex(it);
    }

    if (true) { //Первое условие пройдено
        bool flag = true;
        QVector<QVector<int>> minMatrix = object.toMinMatrix(); //Кастуем к матрице смежности

        for (int i = 0; i < minMatrix.size() && flag; i++) {
            for (int j = 0; j < minMatrix.size() && flag; j++) {
                if (i != j && minMatrix[i][j] == 0) {
                    flag = false;
                }

                if (i == j && minMatrix[i][j] != 0) {
                    flag = false;
                }
            }
        }


        if (flag) {
            return MAnswer<QPair<MGraphObject, QString>>
                                                         (QPair<MGraphObject, QString>
                                                          (MGraphObject(), "Граф является полным"));
        } else {
            for (auto& vertex : object.getVertexs_link()) {
                for (auto& withvertex: object.getVertexs_link()) {
                    if (vertex.id != withvertex.id) {
                        if (!object.checkNode( //Проверяем существование ноды
                                               object.getVertexById(vertex.id),
                                               object.getVertexById(withvertex.id),
                                               1
                                               )) {
                            result.addNode(object.getVertexById(vertex.id),
                                           object.getVertexById(withvertex.id), 1);
                        }
                    }
                }
            }


            return MAnswer<QPair<MGraphObject, QString>>
                                                         (QPair<MGraphObject, QString>
                                                          (result, "Граф дополнен"));
        }

    }

}

Solution_7::Solution_7(MGraphObject &object) : graphObject(object) {

}

Solution_7::Solution_7() {

}

void Solution_7::run() {

}

Solution_7::~Solution_7() {

}
