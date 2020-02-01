#include "solution_5.h"
//http://alice.pnzgu.ru:8080/~dvn/fb61499/search/musatov/index.htm

Solution_5::Solution_5  (const MGraphObject& graphObjectA, const MGraphObject& graphObjectB) :
    graphObjectA(graphObjectA), graphObjectB(graphObjectB)  {
    GlobalAnswer = "";
}

void Solution_5::run() {
    //Строим вектора степеней вершин
    //граф 1
    QVector <QVector<int>> TempAdjMatrix = graphObjectA.toMatrix();
    QVector<int> VertexRankA(graphObjectA.countVertexs());
    for (int i = 0; i<graphObjectA.countVertexs(); i++) {
        VertexRankA[i] = 0;
        //по горизонтали (из вершины)
        for (int j = 0; j<graphObjectA.countVertexs();j++) {
            if (TempAdjMatrix[i][j] != 0) {
                VertexRankA[i]++;
            }
        }
        //по вертикали (в вершину)
        for (int j = 0; j<graphObjectA.countVertexs();j++) {
            if ((TempAdjMatrix[j][i] != 0) && (i != j)) {
                VertexRankA[i]++;
            }
        }
    }
    qSort(VertexRankA);

    //граф 2
    QVector <QVector<int>> TempAdjMatrixB = graphObjectB.toMatrix();
    QVector<int> VertexRankB(graphObjectB.countVertexs());
    for (int i = 0; i<graphObjectB.countVertexs(); i++) {
        VertexRankB[i] = 0;
        //по горизонтали (из вершины)
        for (int j = 0; j<graphObjectB.countVertexs();j++) {
            if (TempAdjMatrixB[i][j] != 0) {
                VertexRankB[i]++;
            }
        }
        //по вертикали (в вершину)
        for (int j = 0; j<graphObjectB.countVertexs();j++) {
            if ((TempAdjMatrixB[j][i] != 0) && (i != j)) {
                VertexRankB[i]++;
            }
        }
    }

    qSort(VertexRankB);
    //изоморфность
    if ((VertexRankA != VertexRankB)) {
        this->savedResult = MAnswer<QString>("Векторы степеней вершин графов А и В не равны => сильная неизоморфность.");
        GlobalAnswer = "Векторы степеней вершин графов А и В не равны => сильная неизоморфность.";
    } else {
        //Алгоритм Ульмана
        QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
        for (int i=0; i < PermutationMatrix.size(); i++) {
            PermutationMatrix[i].resize(graphObjectA.countVertexs());
        }
            UllmanAlgorithm (TempAdjMatrix, TempAdjMatrixB, PermutationMatrix, 1);
        this->savedResult = MAnswer<QString>(this->GlobalAnswer);
    }
}

void Solution_5::UllmanAlgorithm (QVector<QVector<int>> AdjMatrixA, QVector<QVector<int>> AdjMatrixB, QVector<QVector<int>> PermMatrix, int Counter) {
    if (Counter > AdjMatrixB.size()) {

        //bool ZeroMatrix = true;
        QString TempStringAnswer = "P = (";
        for (int i = 0; i < PermMatrix.size(); i++){
            for (int j = 0; j < PermMatrix.size(); j++){
                TempStringAnswer += " " + QString::number(PermMatrix[i][j]);
         /*       if (PermMatrix[i][j] != 0) {
                    ZeroMatrix = false;
                }*/
            }
            TempStringAnswer += "; ";
        }
        TempStringAnswer += ");";
        qDebug() << TempStringAnswer;
        //if (!ZeroMatrix) {
            GlobalAnswer = "Перестановки по алгоритму Ульмана существуют, следовательно графы изоморфны";
        //
    } else {
        QVector<QVector<int>> TempPermMatrix = PermMatrix;
        for (int i = 0; i < AdjMatrixA.size(); i++) {
            for (int j = 0; j < AdjMatrixA.size(); j++) {
                if (j != i) {
                    TempPermMatrix[Counter-1][j] = 0;
                } else {
                    TempPermMatrix[Counter-1][j] = 1;
                }
            }
            if ((TempPermMatrix[0][2] == 1) && (TempPermMatrix[1][3] == 1)) {
                int q = 0;
            }
            //подграф S(M1):
            QVector<QVector<int>> SubgraphMain (Counter);
            for (int k = 0; k < Counter; k++){
                SubgraphMain[k].resize(Counter);
                for(int j = 0; j < Counter; j++) {
                    if (AdjMatrixB[k][j]) {
                        SubgraphMain[k][j] = 1;
                    } else {
                        SubgraphMain[k][j] = 0;
                    }
                }
            }
            //подграф S(P):
            QVector<QVector<int>> SubgraphPerm (Counter);
            for (int k = 0; k < Counter; k++){
                SubgraphPerm[k].resize(AdjMatrixA.size());
                for(int j = 0; j < AdjMatrixA.size(); j++) {
                    SubgraphPerm[k][j] = TempPermMatrix[k][j];
                }
            }
            if (SubgraphMain == (Multiple(Multiple(SubgraphPerm, AdjMatrixA), Transpose(SubgraphPerm)))){
                UllmanAlgorithm(AdjMatrixA, AdjMatrixB, TempPermMatrix, Counter + 1);
            }
        }
    }
}

QVector<QVector<int>> Solution_5::Transpose(const QVector<QVector<int>> &Matrix) {
    QVector<QVector<int>> ReturnMatrix(Matrix[0].size());
    for (int i = 0; i < ReturnMatrix.size(); i++) {
        ReturnMatrix[i].resize(Matrix.size());
        for (int j = 0; j < Matrix.size(); j++) {
            ReturnMatrix[i][j] = Matrix[j][i];
        }
    }
    return ReturnMatrix;
}

QVector<QVector<int>> Solution_5::Multiple(const QVector<QVector<int>> &MatrixA, const QVector<QVector<int>> &MatrixB) {
    QVector<QVector<int>> ReturnMatrix(MatrixA.size());
    for (int i = 0; i < ReturnMatrix.size(); i++) {
        ReturnMatrix[i].resize(MatrixB[0].size());
        for (int j = 0; j < MatrixB[0].size(); j++) {
            ReturnMatrix[i][j] = 0;
            for (int k = 0; k < MatrixB.size(); k++) {
                ReturnMatrix[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
    return ReturnMatrix;
}


Solution_5::~Solution_5() {

}

QString Solution_5::GetAnswer(){
    return GlobalAnswer;
}
