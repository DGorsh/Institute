#include "solution_17.h"

Solution_17::Solution_17(const QVector<int> Data) :  VectorData( Data ) {

}

void Solution_17::run() {
    QVector<int> ResultVector (VectorData.size(), 0);
    int Mark = 1;
    int StartPosition = 0;
    int SizeValue = 2;
    Result = "";
    while ((VectorData != ResultVector) && (StartPosition != VectorData.size())) {
        int VectorSize = 0;
        if (VectorData[StartPosition] == 0) {
            StartPosition++;
            Mark=StartPosition+1;
            SizeValue = Mark + 1;
        }
        if ((Mark >= VectorData.size()) || (SizeValue >= VectorData.size())) {
            break;
        }
        for (int i = 0; i < VectorData.size(); i++) {
            Result += QString::number(VectorData[i]) + "  ";
        }
        int MinValue = VectorData[StartPosition];
        if (VectorData[Mark] < MinValue) {
            MinValue = VectorData[Mark];
        }
        for (int i = SizeValue; i < VectorData.size(); i++) {
            if ((VectorData[i] != 0)) {
                VectorSize++;
            }
        }
        if (VectorSize < MinValue) {
            MinValue = VectorSize;
        }
        VectorData[StartPosition] -= MinValue;
        VectorData[Mark] -= MinValue;
        for (int i = SizeValue; i < ResultVector.size(); i++) {
            if (MinValue) {
                if ((VectorData[i] != 0) && (i != StartPosition) && (i != Mark)){
                    VectorData[i]--;
                    MinValue--;}
                else {
                    bool Temp = false;
                    for (int j = 0; j < ResultVector.size(); j++) {
                        if ((VectorData[j] != 0) && (!Temp) && (j != StartPosition) && (j != Mark)) {
                            VectorData[j]--;
                            Temp = true;
                            MinValue--;
                        }
                    }
                }
            }
        }
        if (VectorData[StartPosition] != 0) {
            Mark++;
            SizeValue++;
        }
        Result +="\n";
    }
    if (VectorData == ResultVector) {
        for (int i = 0; i < VectorData.size(); i++) {
            Result += "0  ";
        }
    } else {
        Result += "Далее решения нет";
    }
    this->savedResult = MAnswer<QString>(Result);
}

QString Solution_17::ResultReturn() {
    return Result;
}
