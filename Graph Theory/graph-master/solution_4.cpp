#include "solution_4.h"

//алгоритм
//https://codeforces.com/blog/entry/17974?locale=ru

Solution_4::Solution_4  (const MGraphObject& graphObject) : graphObject(graphObject)  {}

void Solution_4::run() {
    //степени вершин.
    QVector <QVector<int>> TempAdjMatrix = graphObject.toMatrix();
    QVector<int> VertexRank(graphObject.countVertexs());
    for (int i = 0; i<graphObject.countVertexs(); i++) {
        VertexRank[i] = 0;
        //по горизонтали (из вершины)
        for (int j = 0; j<graphObject.countVertexs();j++) {
            if (TempAdjMatrix[i][j] != 0) {
                VertexRank[i]++;
            }
        }
        //по вертикали (в вершину)
        for (int j = 0; j<graphObject.countVertexs();j++) {
            if ((TempAdjMatrix[j][i] != 0) && (i != j)) {
                VertexRank[i]++;
            }
        }
    }

    //Нахождение радиуса и диаметра при помощи алгоритма Флойда-Уоршелла
    const int N = graphObject.countVertexs(); // Количество вершин в графе
    QVector<QVector<int>> d; // Дистанции в графе
    d.resize(N);
    for (int i = 0; i < d.size(); i++){
        d[i].resize(N);
    }
    for (int i = 0; i < d.size(); i++) {
        for (int j = 0; j < d.size(); j++) {
            d[i][j] = TempAdjMatrix[i][j];
            if (d[i][j] == 0) {
                d[i][j] = 100000000;
            }
        }
    }
    QVector<int> e(N); // Эксцентриситет вершин
    int rad = INT_MAX; // Радиус графа
    int diam = 0; // Диаметр графа

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    d[i][j] = 0;
                } else {
                    d[i][j] = min_value(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    // Нахождение эксцентриситета
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            e[i] = max_value(e[i], d[i][j]);
        }
    }

    // Нахождение диаметра и радиуса
    for (int i = 0; i < N; i++) {
        rad = min_value(rad, e[i]);
        diam = max_value(diam, e[i]);
    }

    // Вектор степеней вершин
    qSort(VertexRank);
    QString TRad = "inf";
    if (rad < 10000000) TRad = QString::number(rad);
    QString TDiam = "inf";
    if (diam < 10000000) TDiam = QString::number(diam);
    QString TempString = "Radius: " + TRad + ";\n" +
            "Diameter: " + TDiam + ";\n" + "Degree vector {";
    GlobalAnswer = "Радиус: " + TRad + ";\n" +
            "Диаметр: " + TDiam + ";\n" + "Вектор степеней {";
    for (int i = VertexRank.size() - 1; i >= 0; i--) {
        TempString += " " + QString::number(VertexRank[i]);
        GlobalAnswer += " " + QString::number(VertexRank[i]);
    }
    TempString += " };";
    GlobalAnswer += " };";
    //
    this->savedResult = MAnswer<QString>(TempString);
}


Solution_4::~Solution_4() {

}


int Solution_4::min_value (int pFirst, int pSecond) {
    if (pFirst > pSecond) {
        return pSecond;
    } else {
        return pFirst;
    }
}

int Solution_4::max_value (int pFirst, int pSecond) {
    if (pFirst < pSecond) {
        return pSecond;
    } else {
        return pFirst;
    }
}

QString Solution_4::GetAnswer () {
    return GlobalAnswer;
};
