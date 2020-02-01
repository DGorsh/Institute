#include "solution_8.h"

//формат данных
// 0 - х вершин
// 1 - у вершин
// 2 - ребро из
// 3 - ребро в

Solution_8::Solution_8  (const MGraphObject& graphObjectA, const MGraphObject& graphObjectB) :
    graphObjectA(graphObjectA), graphObjectB(graphObjectB)  {
}

//пересечение
QVector<QVector<int>> Solution_8::Conjuction() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    //коньюнкция
    //если есть перестановки
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (AVal && BVal) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}

QVector<QVector<int>> Solution_8::Disjuction() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    //коньюнкция
    //если есть перестановки
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (AVal || BVal) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}


QVector<QVector<int>> Solution_8::Substraction(bool bAsubB) {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        bool Finded = false;
        for (int j = 0; j < ResultMatrix.size(); j++) {
            if (bAsubB) {
                if (AdjMatrixA[i] == AdjMatrixB[j]) {
                    Finded = true;
                }
            } else {
                if (AdjMatrixB[i] == AdjMatrixA[j]) {
                    Finded = true;
                }
            }
        }
        if (!Finded) {
            if (bAsubB) {
                ResultMatrix[i] = AdjMatrixA[i];
            } else {
                ResultMatrix[i] = AdjMatrixB[i];
            }
        }

    }
    return ResultMatrix;
}

//=======================================
//========      ИМПЛИКАЦИЯ      =========
//=======================================
QVector<QVector<int>> Solution_8::Implication(bool bAsubB) {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    //коньюнкция
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (bAsubB) {
                if (!AVal || BVal) {
                    ResultMatrix[i][j] = 1;
                } else {
                    ResultMatrix[i][j] = 0;
                }
            } else {
                if (!BVal || AVal) {
                    ResultMatrix[i][j] = 1;
                } else {
                    ResultMatrix[i][j] = 0;
                }
            }
        }

    }
    return ResultMatrix;
}


//=======================================
//========     КОИМПЛИКАЦИЯ     =========
//=======================================
QVector<QVector<int>> Solution_8::Coimplication(bool bAsubB) {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (bAsubB) {
                if (AVal && !BVal) {
                    ResultMatrix[i][j] = 1;
                } else {
                    ResultMatrix[i][j] = 0;
                }
            } else {
                if (BVal && !AVal) {
                    ResultMatrix[i][j] = 1;
                } else {
                    ResultMatrix[i][j] = 0;
                }
            }
        }

    }
    return ResultMatrix;
}

//=======================================
//========   ИСКЛЮЧАЮЩЕЕ ИЛИ    =========
//=======================================
QVector<QVector<int>> Solution_8::XOR() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if ((!AVal && BVal) || (AVal && !BVal)) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}

//=======================================
//========   ЭКВИВАЛЕНТНОСТЬ    =========
//=======================================
QVector<QVector<int>> Solution_8::Equivalence() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if ((AVal && BVal) || (!AVal && !BVal)) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}

//=======================================
//========    ШТРИХ ШЕФФЕРА     =========
//=======================================
QVector<QVector<int>> Solution_8::Sheffer() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (!(AVal && BVal)) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}

//=======================================
//========    CТРЕЛКА ПИРСА     =========
//=======================================
QVector<QVector<int>> Solution_8::Pirs() {
    QVector<QVector<int>> ResultMatrix; //результат
    //матрицы смежности
    QVector<QVector<int>> AdjMatrixA = this->graphObjectA.toMatrix();
    QVector<QVector<int>> AdjMatrixB = this->graphObjectB.toMatrix();
    //размерность результирующей матрицы
    //в коньюнкции - наименьшая матрица

    if (AdjMatrixA.size() > AdjMatrixB.size()){
        ResultMatrix.resize(AdjMatrixA.size());
    } else {
        ResultMatrix.resize(AdjMatrixB.size());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        ResultMatrix[i].resize(ResultMatrix.size());
    }
    //составление результирующей матрицы
    //перестановки (по Ульману)
    TransportAnswer.clear();
    QVector<QVector<int>> PermutationMatrix(graphObjectA.countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(graphObjectA.countVertexs());
    }
    for (int i = 0; i < ResultMatrix.size(); i++) {
        for (int j = 0; j < ResultMatrix.size(); j++) {
            bool AVal = false, BVal = false;
            AVal = AdjMatrixA[i][j] != 0 ? true : false;
            BVal = AdjMatrixB[i][j] != 0 ? true : false;
            if (!AVal && !BVal) {
                ResultMatrix[i][j] = 1;
            } else {
                ResultMatrix[i][j] = 0;
            }
        }
    }
    return ResultMatrix;
}

//если есть перетановки
QVector<QVector<int>> Solution_8::Retranslate(const QVector<QVector<int>> &Matrix) {

}

//Ульман
void Solution_8::UllmanAlgorithm (QVector<QVector<int>> AdjMatrixA, QVector<QVector<int>> AdjMatrixB, QVector<QVector<int>> PermMatrix, int Counter) {
    if (Counter > AdjMatrixB.size()) {

        //bool ZeroMatrix = true;
        if (TransportAnswer.size() == 0) {
            TransportAnswer = PermMatrix;
        }
        return;
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

QVector<QVector<int>> Solution_8::Transpose(const QVector<QVector<int>> &Matrix) {
    QVector<QVector<int>> ReturnMatrix(Matrix[0].size());
    for (int i = 0; i < ReturnMatrix.size(); i++) {
        ReturnMatrix[i].resize(Matrix.size());
        for (int j = 0; j < Matrix.size(); j++) {
            ReturnMatrix[i][j] = Matrix[j][i];
        }
    }
    return ReturnMatrix;
}

QVector<QVector<int>> Solution_8::Multiple(const QVector<QVector<int>> &MatrixA, const QVector<QVector<int>> &MatrixB) {
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

Solution_8::~Solution_8() {

}

void Solution_8::run() {}
