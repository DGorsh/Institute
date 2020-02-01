#include "solution_11.h"


Solution_11::Solution_11(const QVector<int> &base) : bases(base) {
    if (base.size() != 8) {
        throw MUncorrectInput();
    }

}

Solution_11::Solution_11() {

}

void Solution_11::run() {
    baseToGraph(bases, 0);
}

MGraphObject Solution_11::baseToGraph(QVector<int> &base, int number) { 
    QVector<int> base_1 = {base[number], base[number+1]};
    QVector<int> base_2 = {base[number+2], base[number+3]};

    if (number == 0)
        for (int i = 0; i < 4; ++i) {
            if (n < base[i])
                n = base[i];
        }

    //Теперь проверяем размерность баз
    qStableSort(base_1.begin(), base_1.end(), qLess<int>());
    qStableSort(base_2.begin(), base_2.end(), qLess<int>());


    if (base_1[0] > base_2[0] || base_1[1] < base_2[1]) {
        throw MUncorrectInput();
    }


    MGraphObject resultGraph;
    MMatrix matrix(n, QVector<int>(n, 0)); //Создаём матрицу смежности графа

    //Теперь ставим единицы там где заданы требуемые базы


    matrix[base_1[0]][base_1[1]] = 1;
    matrix[base_2[0]][base_2[1]] = 1;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {

        }
    }


    for (auto& it : matrix) {
        qDebug() << it;
    }

    return resultGraph;


}
