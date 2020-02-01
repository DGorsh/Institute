#ifndef FILEREADER_H
#define FILEREADER_H
#include <QString>
#include <QMessageBox>
#include <QDialog>
#include <scene.h>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <map>

namespace FSConstants {
const std::vector<std::pair<QString, QString>> ErrorMessages = {
    //чтение файла
    std::pair<QString, QString> ("Катастрофа! Ошибка чтения файла", "Вы не выбрали файл"),
    std::pair<QString, QString> ("Катастрофа! Ошибка чтения файла", "Формат файла не отвечает требованиям программы!"),
    std::pair<QString, QString> ("Катастрофа! Ошибка чтения файла", "Вы ввели неверное имя файла!"),
    //матрица смежности (заголовок)
    std::pair<QString, QString> ("Чтение матрицы смежности (заголовок)", "Вы не задали число вершин!"),
    std::pair<QString, QString> ("Чтение матрицы смежности (заголовок)", "Число вершин не может быть нулевым или отрицательным!"),
    std::pair<QString, QString> ("Чтение матрицы смежности (заголовок)", "Матрица смежности в данном файле уже задавалась!"),
    std::pair<QString, QString> ("Чтение матрицы смежности (заголовок)", "Количество вершин из иатрицы не соответствует заданному!"),
    std::pair<QString, QString> ("Чтение матрицы смежности (заголовок)", "Неверный тип файла!"),
    //матрица смежности (матрица)
    std::pair<QString, QString> ("Ошибка чтения матрицы смежности", "Несоответствие размеров матрицы смежности и числа вершин!"),
    //Матрица инцидентности (заголовок)
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Матрица инциндентности в данном файле уже задавалась!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Вы неверно задали число ребер и вершин!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Число вершин или ребер не может быть нулевым или отрицательным!!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Число ребер слишком велико!!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Количество вершин или ребер из матрицы не соответствует заданному!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Неверный тип файла!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (заголовок)", "Ошибка ввода!!"),
    //матрица инцидентности (матрица)
    std::pair<QString, QString> ("Чтение матрицы инцидентности (матрица)", "Плохой размер!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (матрица)", "не равно!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (матрица)", "ошибка!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (матрица)", "матрица!"),
    std::pair<QString, QString> ("Чтение матрицы инцидентности (матрица)", "дубликат!"),
    //Задание вершин
    std::pair<QString, QString> ("Обработка ввода", "Отсутствует закрывающая фигурная скобка!!"),
    std::pair<QString, QString> ("Обработка ввода", "Нельзя начинать скобки с закрывающейся!"),
    std::pair<QString, QString> ("Обработка ввода", "Неверная целостность скобок!"),
    std::pair<QString, QString> ("Обработка ввода", "Неверный ввод элементов !"),
    std::pair<QString, QString> ("Обработка ввода", "Неверная расстановка скобок!"),

    std::pair<QString, QString> ("Чтение вершин", "Разница между максимально введенным индексом и заданным числом вершин слишком велика!"),
    std::pair<QString, QString> ("Чтение вершин", "Некорректный тип файла!"),
    std::pair<QString, QString> ("Чтение вершин", "Ошибка ввода номеров вершин!"),
    //задание ребер
    std::pair<QString, QString> ("Чтение ребер", "Количество ребер больше, чем того позволяет количество вершин"),
    std::pair<QString, QString> ("Чтение ребер", "Ссылка на несуществующее ребро!!"),
    std::pair<QString, QString> ("Чтение ребер", "Некорректный тип файла"),

    std::pair<QString, QString> ("Чтение файла", "Ошибка ввода!!"),
};
}

enum FSErrors {
    FSE_FILE_INCORRECTOPENING,
    FSE_FILE_INCORRECTFORMAT,
    FSE_FILE_INCORRECTREADING,

    FSE_ADJHEAD_NOTVERTEX,
    FSE_ADJHEAD_VERTEXINCORRECT,
    FSE_ADJHEAD_DUBLICATE,
    FSE_ADJHEAD_VERTEXAMMOERROR,
    FSE_ADJHEAD_FILEFORMAT,

    FSE_ADJBODY_BADVERTEXSIZE,

    FSE_INCHEAD_DUBLICATE,
    FSE_INCHEAD_COUNTERROR,
    FSE_INCHEAD_NOTEQUALZERO,
    FSE_INCHEAD_MUCHVertexS,
    FSE_INCHEAD_VERTEXCOUNT,
    FSE_INCHEAD_FILEFORMAT,
    FSE_INCHEAD_INPUTERROR,

    FSE_INCBODY_BADSIZE,
    FSE_INCBODY_NOTEQUAL,
    FSE_INCBODY_ELEMCOUNT,
    FSE_INCBODY_MATRIXERROR,
    FSE_INCBODY_DUBLICATE,

    FSE_VERTEX_FIGURECLOSED,
    FSE_VERTEX_FIGURESTART,
    FSE_VERTEX_FIGUREAMMO,
    FSE_VERTEX_INCORRECTINPUT,
    FSE_VERTEX_INCORRECTFIGURE,

    FSE_VERTEX_DIFFERENT,
    FSE_VERTEX_FILEFORMAT,
    FSE_VERTEX_VERTEXFORMAT,

    FSE_VertexS_BADVertexSSIZE,
    FSE_VertexS_NOVERTEXEXISTS,
    FSE_VertexS_FILEFORMAT,

    FSE_INPUT_ERROR,
};

class FileReader
{
private:
    //параметры файла
    QString         CurrentFilePath;
    QWidget*        MainFrame;
    QFileInfo       CurrentFileInfo;
    QFile           CurrentFile;
    QTextStream*    FileStream;
    bool            FileOpen;

    //параметры чтения
    QString         TempBufferA, TempBufferB;
    unsigned int    CurrentData;
    unsigned char   CurrentElement;
    unsigned char   CurrentChecked; //87654321; 1-vertexes  2-Vertexs  3-adj 4-inc;
    bool            CorrectInput;
    bool            Readed;
    std::vector<std::vector<int>> CurrentMatrix;
    std::vector<int> CurrentDataSize; //0- vertex, 1- Vertexs

    MGraphObject*   CurrentScene;

    char            CurrentReading;

public:
    FileReader() = default;

    //конструктор с чтением файла
    FileReader(QString AFilePath, MGraphObject *CurrentScene, QWidget *Frame) {
        this->MainFrame = Frame;
        this->FileOpen = false;
        this->CurrentFilePath = AFilePath;
        //проверка на закрытие окна диалога
        if (!AFilePath.isEmpty()){
            this->CurrentFileInfo.setFile(this->CurrentFilePath);
        } else {
            this->mErrorMessage(FSErrors::FSE_FILE_INCORRECTOPENING);
            return;
        }

        //проверка на расширение файла
        if (this->CurrentFileInfo.suffix() != "adj" && this->CurrentFileInfo.suffix() != "inc" &&
            this->CurrentFileInfo.suffix() != "edg" && this->CurrentFileInfo.suffix() != "ver" &&
            this->CurrentFileInfo.suffix() != "gph") {
            this->mErrorMessage(FSErrors::FSE_FILE_INCORRECTFORMAT);
            return;
        }

        //попытка открыть файл
        this->CurrentFile.setFileName(this->CurrentFilePath);
        if (!this->CurrentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            this->mErrorMessage(FSErrors::FSE_FILE_INCORRECTREADING);
            return;
        }

        //Если все хорошо, задаем начальные параметры
        this->CurrentData = 0;
        this->CurrentElement = 0;
        this->CurrentChecked = 0; //87654321; 1-vertexes  2-Vertexs  3-adj 4-inc;
        this->CorrectInput = false;
        this->Readed = false;
        this->CurrentMatrix.resize(0);
        this->CurrentDataSize.resize(2); //0- vertex, 1- Vertexs
        this->FileOpen = true;
        this->CurrentScene = CurrentScene;
    }

    FileReader(QString AFilePath, MGraphObject *CurrentScene, QWidget *Frame, bool saving) {

        this->CurrentFile.setFileName(AFilePath);
        this->CurrentFile.open(QIODevice::WriteOnly | QIODevice::Text);
        this->FileStream = new QTextStream(&this->CurrentFile);
        this->CurrentFileInfo.setFile(this->CurrentFile);

        //Если все хорошо, задаем начальные параметры
        this->CurrentData = 0;
        this->CurrentElement = 0;
        this->CurrentChecked = 0; //87654321; 1-vertexes  2-Vertexs  3-adj 4-inc;
        this->CorrectInput = false;
        this->Readed = false;
        this->CurrentMatrix.resize(0);
        this->CurrentDataSize.resize(2); //0- vertex, 1- Vertexs
        this->FileOpen = true;
        this->CurrentScene = CurrentScene;
    }

    ~FileReader() = default;

    //валидно ли чтение
    bool mIsReaded () {
        return this->FileOpen;
    }

    //===============================================================
    //чтение файла
    void FileReading() {
         while (!this->CurrentFile.atEnd()){
             if(!this->FileOpen) {
                 return;
             }
             this->TempBufferA = this->CurrentFile.readLine();
             this->Readed = false;
             //удаление комментариев
             if (this->TempBufferA.contains("%")) {
                 this->TempBufferA.remove(this->TempBufferA.contains("%"), this->TempBufferA.size()-this->TempBufferA.contains("%"));
             }

             //обработка
             //если обрабатываем матрицу смежности
             if(this->CurrentElement == 1 && !this->Readed) {
                 this->mAdjMatrixReading();
                 this->Readed = true;
             }
             //обработка
             //если обрабатываем матрицу инциндентности
             if(this->CurrentElement == 2 && !this->Readed) {
                 this->mIncMatrixReading();
                 this->Readed = true;
             }
             //обработка
             //если обрабатываем заголовок матрицы смежности
             if (this->TempBufferA.contains("Adjacency") && !this->Readed){
                 if (this->CurrentFileInfo.suffix() != "adj" && this->CurrentFileInfo.suffix() != "gph") {
                     this->mErrorMessage(FSErrors::FSE_ADJHEAD_FILEFORMAT);
                     return;
                 }
                 this->mAdjHeaderReading();
                 this->Readed = true;
             }
             //обработка
             //если обрабатываем заголовок матрицы инциндентности
             if (this->TempBufferA.contains("Incidence") && !this->Readed){
                 if (this->CurrentFileInfo.suffix() != "inc" && this->CurrentFileInfo.suffix() != "gph") {
                     this->mErrorMessage(FSErrors::FSE_INCHEAD_FILEFORMAT);
                     return;
                 }
                 this->mIncHeaderReading();
                 this->Readed = true;
             }
             //обработка
             //если обрабатываем считывание вершин
             if (this->TempBufferA.contains("Vertex") && !this->Readed) {
                 this->mVertexReading();
                 this->Readed = true;
             }
             //обработка
             //если обрабатываем считывание ребер
             if (this->TempBufferA.contains("Vertexs") && !this->Readed){
                 if (this->CurrentFileInfo.suffix() != "edg" && this->CurrentFileInfo.suffix() != "gph") {
                     this->mErrorMessage(FSErrors::FSE_VertexS_FILEFORMAT);
                     return;
                 }
                 this->mVertexsReading();
                 this->Readed = true;
             }

             //обработка
             //если обрабатываем команду очистки графа
             if (this->TempBufferA.contains("Clear") && !this->Readed){
                 this->CurrentScene->clear();
                 this->Readed = true;
             }

             if (!this->Readed && !this->TempBufferA.isEmpty() && this->TempBufferA!="\n") {
                 this->mErrorMessage(FSErrors::FSE_VertexS_FILEFORMAT);
                 return;
             }
         }
    }

    void FileSaving() {
        if (this->CurrentFileInfo.suffix() == "ver") {
            this->mVertexSaving();
        }
        if (this->CurrentFileInfo.suffix() == "adj") {
            this->mAdjSaving();
        }
        if (this->CurrentFileInfo.suffix() == "inc") {
            this->mIncSaving();
        }
        if (this->CurrentFileInfo.suffix() == "edg") {
            this->mEdgSaving();
        }
        this->CurrentFile.close();
        delete this->FileStream;
    }


private:
    //===============================================================
    //чтение матрицы смежности
    void mAdjMatrixReading () {
        this->FileOpen = false;
        QStringList TempRow = this->TempBufferA.split(" ");
        //проверка количества элементов ряда с числом вершин
        if (TempRow.size() != this->CurrentDataSize[0]){
            this->mErrorMessage(FSErrors::FSE_ADJBODY_BADVERTEXSIZE);
            return;
        }
        //заполнение матрицы
        for (int i = 0; i < this->CurrentDataSize[0]; i++){
            this->CurrentMatrix[this->CurrentDataSize[0]-this->CurrentData][i] = TempRow[i].toInt();
        }
        //Если число рядов, которые необходимо считать, достигло 0
        CurrentData--;
        if(CurrentData == 0) {
            CurrentElement=0;
            //если число вершин, заданных в графе, равно 0
            if(this->CurrentScene->countVertexs() == 0){
                this->CurrentScene->clear();
                //добавление вершин
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                   this->CurrentScene->addVertex(QPointF(200 + 150*cos(i*6.28/this->CurrentDataSize[0]),
                                                     200 + 150*sin(i*6.28/this->CurrentDataSize[0])));
                }
                //добавление ребер
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                    for (int j = 0; j < this->CurrentDataSize[0]; j++){
                        if (this->CurrentMatrix[i][j] != 0) {
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(i),
                                                        this->CurrentScene->getVertexById(j),
                                                        this->CurrentMatrix[i][j]);
                        }
                    }
                }
            //если в программе уже задавались вершины
            } else {
                if (this->CurrentDataSize[0] != this->CurrentScene->countVertexs()) {
                    this->mErrorMessage(FSErrors::FSE_ADJBODY_BADVERTEXSIZE);
                    return;
                }
                //обработка вершин
                std::vector<std::vector<int>> TempMatrix(3);
                for (int it = 0; TempMatrix[0].size() != this->CurrentDataSize[0]; it++) {
                    if (this->CurrentScene->getVertexById(it) != nullptr){
                        TempMatrix[0].push_back(it);
                        TempMatrix[1].push_back(this->CurrentScene->getVertexById(it)->point.x());
                        TempMatrix[2].push_back(this->CurrentScene->getVertexById(it)->point.y());
                    }
                }
                this->CurrentScene->clear();
                //добавление вершин
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                   this->CurrentScene->addVertex(QPointF(TempMatrix[1][i],TempMatrix[2][i]));
                }
                //добавление ребер
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                    for (int j = 0; j < this->CurrentDataSize[0]; j++){
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempMatrix[0][i]),
                                                        this->CurrentScene->getVertexById(TempMatrix[0][j]),
                                                        this->CurrentMatrix[i][j]);
                    }
                }
            }
        }
        this->FileOpen = true;
    }



    //===============================================================
    //чтение матрицы инцидентности
    void mIncMatrixReading () {
        this->FileOpen = false;
        QStringList TempRow = this->TempBufferA.split(" ");
        //проверка количества элементов ряда с числом вершин
        if (TempRow.size() != this->CurrentDataSize[1]){
            this->mErrorMessage(FSErrors::FSE_INCBODY_BADSIZE);
            return;
        }
        //заполнение матрицы
        for (int i = 0; i < this->CurrentDataSize[1]; i++){
            if (TempRow[i].toInt() < -1 || TempRow[i].toInt() > 1) {
                this->mErrorMessage(FSErrors::FSE_INCBODY_NOTEQUAL);
                return;
            }
            this->CurrentMatrix[this->CurrentDataSize[0]-this->CurrentData][i] = TempRow[i].toInt();
        }

        //Если число рядов, которые необходимо считать, достигло 0
        CurrentData--;
        if(CurrentData == 0) {
            //проверка на то, что всего два элемента в столбце и на корректность направления
            int TempCorrectFirst, TempCorrectSecond;
            char TempSumm, TempElements; //-1+1=0  1+1 = 2  0+1=1
            for (int i = 0; i<this->CurrentDataSize[1]; i++){
                TempCorrectFirst = 0;
                TempCorrectSecond = 0;
                TempElements = 0;
                for (int j = 0; j < this->CurrentDataSize[0]; j++){
                    if (this->CurrentMatrix[j][i] != 0) {
                        TempElements++;
                        if (TempCorrectFirst == 0) {
                            TempCorrectFirst = this->CurrentMatrix[j][i];
                        } else {
                            TempCorrectSecond = this->CurrentMatrix[j][i];
                        }
                    }
                }
                if (TempElements < 1 || TempElements > 2) {
                    this->mErrorMessage(FSErrors::FSE_INCBODY_ELEMCOUNT);
                    return;
                }
                if (((TempCorrectFirst == -1) && (TempCorrectSecond == -1)) ||
                    ((TempCorrectFirst == -1) && (TempElements == 1))){
                    this->mErrorMessage(FSErrors::FSE_INCBODY_MATRIXERROR);
                    return;
                }
            }
            // проверка на дубликаты
            for (int i = 0; i<this->CurrentDataSize[1]; i++){
                TempCorrectFirst = 0;
                TempCorrectSecond = 0;
                for (int j = 0; j < this->CurrentDataSize[0]; j++){
                    if (this->CurrentMatrix[j][i] != 0) {
                        if (TempCorrectFirst == 0) {
                            TempCorrectFirst = j+1;
                        } else {
                            TempCorrectSecond = j+1;
                        }
                    }
                }
                for (int j = 0; j < this->CurrentDataSize[1]; j++){
                    if ((CurrentMatrix[TempCorrectFirst-1][j] == CurrentMatrix[TempCorrectFirst-1][i]) &&
                        (j != i) && TempCorrectSecond != 0) {
                        if ((CurrentMatrix[TempCorrectSecond-1][j] == CurrentMatrix[TempCorrectSecond-1][i])){
                            this->mErrorMessage(FSErrors::FSE_INCBODY_DUBLICATE);
                            return;
                        }
                    }
                }
            }
            std::vector<std::vector<int>> TempMatrix(3);
            //если число вершин, заданных в графе, равно 0
            if(this->CurrentScene->countVertexs() == 0){
                this->CurrentScene->clear();
                //добавление вершин
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                   TempMatrix[0].push_back(i);
                   this->CurrentScene->addVertex(QPointF(200 + 150*cos(i*6.28/this->CurrentDataSize[0]),
                                                     200 + 150*sin(i*6.28/this->CurrentDataSize[0])));
                }
            } else {
                if (this->CurrentDataSize[0] != this->CurrentScene->countVertexs()) {
                    this->mErrorMessage(FSErrors::FSE_ADJBODY_BADVERTEXSIZE);
                    return;
                }
                //обработка вершин
                for (int it = 0; TempMatrix[0].size() != this->CurrentDataSize[0]; it++) {
                    if (this->CurrentScene->getVertexById(it) != nullptr){
                        TempMatrix[0].push_back(it);
                        TempMatrix[1].push_back(this->CurrentScene->getVertexById(it)->point.x());
                        TempMatrix[2].push_back(this->CurrentScene->getVertexById(it)->point.y());
                    }
                }
                this->CurrentScene->clear();
                //добавление вершин
                for (int i = 0; i < this->CurrentDataSize[0]; i++) {
                   this->CurrentScene->addVertex(MVertex(TempMatrix[0][i],
                                               QPointF(TempMatrix[1][i],TempMatrix[2][i])));
                }
            }
                //добавление ребер
                bool orgraf = false;
                bool destination = false; //true - из первого во второй
                for (int i = 0; i < this->CurrentDataSize[1]; i++) {
                    TempCorrectFirst = 0;
                    TempCorrectSecond = 0;
                    orgraf = false;
                    destination = false;
                    for (int j = 0; j < this->CurrentDataSize[0]; j++){
                        if(CurrentMatrix[j][i]!=0){
                            if (TempCorrectFirst == 0) {
                                if (CurrentMatrix[j][i]<0){
                                    orgraf = true;
                                    destination = true;
                                }
                                TempCorrectFirst = TempMatrix[0][j]+1;
                            } else {
                                if (CurrentMatrix[j][i]<0){
                                    orgraf = true;
                                    destination = false;
                                }
                                TempCorrectSecond = TempMatrix[0][j]+1;
                            }
                        }
                    }
                    if (orgraf){
                        if (destination){
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        this->CurrentScene->getVertexById(TempCorrectSecond-1),
                                                        1);
                        } else {
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempCorrectSecond-1),
                                                        this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        1);
                        }
                    } else {
                        if (TempCorrectSecond == 0){
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        1);
                        } else {
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        this->CurrentScene->getVertexById(TempCorrectSecond-1),
                                                        1);
                            this->CurrentScene->addNode(this->CurrentScene->getVertexById(TempCorrectSecond-1),
                                                        this->CurrentScene->getVertexById(TempCorrectFirst-1),
                                                        1);
                        }
                    }
                }
            //если в программе уже задавались вершины
                //добавление ребер
        }
        this->FileOpen = true;
    }


    //============================================================
    //матрица смежности (заголовок)
    void mAdjHeaderReading() {
        this->FileOpen = false;
        //1 строчка - число вершин
        QRegExp rx("(\\d+)");
        int pos = this->TempBufferA.contains("Adjacency") + 8;
        while ((pos = rx.indexIn(this->TempBufferA, pos)) != -1) {
             this->TempBufferB = rx.cap(1);
             pos += rx.matchedLength();
        }
        this->CurrentElement = 1;
        //если буффер пуст (нет числа в строке)
        if (this->TempBufferB.isEmpty()){
            this->mErrorMessage(FSErrors::FSE_ADJHEAD_NOTVERTEX);
            return;
        }
        this->CurrentData = this->TempBufferB.toInt();
        //если число вершин меньше или равно 0
        if (this->CurrentData < 1){
            this->mErrorMessage(FSErrors::FSE_ADJHEAD_VERTEXINCORRECT);
            return;
        }
        //если вершины уже заданы
        if (this->CurrentScene->countVertexs()!=0) {
            if (this->CurrentData!=this->CurrentScene->countVertexs()) {
                this->mErrorMessage(FSE_ADJHEAD_VERTEXAMMOERROR);
                return;
            }
        }
        this->CurrentMatrix.resize(this->CurrentData);
        for (int i = 0; i<this->CurrentData; i++) {
            this->CurrentMatrix[i].resize(this->CurrentData);
        }
        this->CurrentDataSize[0] = this->CurrentData;
        this->FileOpen = true;
    }


    //============================================================
    //матрица инцидентности (заголовок)
    void mIncHeaderReading() {
        this->FileOpen = false;
        //1 строчка - число вершин
        QRegExp rx("(\\d+)");\
        this->CurrentDataSize.clear();
        int pos = this->TempBufferA.contains("Incidence") + 9;
        while ((pos = rx.indexIn(this->TempBufferA, pos)) != -1) {
             this->TempBufferB = rx.cap(1);
             pos += rx.matchedLength();
             this->CurrentDataSize.push_back(this->TempBufferB.toInt());
        }
        this->CurrentElement = 2;
        //если ошибка чтения (не 2 элемента в CurrentDataSize)
        if (this->CurrentDataSize.size()!=2) {
            this->mErrorMessage(FSErrors::FSE_INCHEAD_COUNTERROR);
            return;
        }
        this->CurrentData = this->CurrentDataSize[0];
        //если число вершин или ребер меньше или равно 0
        if (this->CurrentData < 1 || this->CurrentDataSize[1] < 1) {
            this->mErrorMessage(FSErrors::FSE_INCHEAD_NOTEQUALZERO);
            return;
        }
        //если вершины уже заданы
        if (this->CurrentScene->countVertexs()!=0) {
            if (this->CurrentData!=this->CurrentScene->countVertexs()) {
                this->mErrorMessage(FSE_INCHEAD_VERTEXCOUNT);
                return;
            }
        }
        /*if (this->CurrentDataSize[1] > this->CurrentDataSize[0]*(this->CurrentDataSize[0]-1)/2) {
            this->mErrorMessage(FSE_INCHEAD_MUCHVertexS);
            return;
        }*/
        this->CurrentMatrix.resize(this->CurrentData);
        for (int i = 0; i<this->CurrentData; i++) {
            this->CurrentMatrix[i].resize(this->CurrentDataSize[1]);
        }
        this->FileOpen = true;
    }


    //===================================================
    //считывание списка вершин
    void mVertexReading(){
        mFiguresCorrect(0, 3);
        this->CurrentData = 0;
        if (this->CurrentScene->countVertexs() != 0){
            for (int i = 0; i<this->CurrentMatrix[0].size(); i = i+3) {
                this->CurrentData += this->CurrentMatrix[0][i];
            }
            /*if (this->CurrentData - this->CurrentScene->countVertexs() > 50) {
                this->mErrorMessage(FSErrors::FSE_VERTEX_DIFFERENT);
                return;
            }*/
            for (int i = 0; i<this->CurrentMatrix[0].size(); i = i+3) {
                if (this->CurrentScene->getVertexById(this->CurrentMatrix[0][i]) != nullptr) {
                    this->CurrentScene->DMoveVertex(this->CurrentMatrix[0][i], QPointF(this->CurrentMatrix[0][i+1], this->CurrentMatrix[0][i+2]));
                } else {
                    this->CurrentScene->addVertex(MVertex(this->CurrentMatrix[0][i], QPointF(this->CurrentMatrix[0][i+1], this->CurrentMatrix[0][i+2])));
                }
            }
        } else {
            int TempCorrect = 0;
            for (int i = 0; i<this->CurrentMatrix[0].size(); i = i+3) {
                if (this->CurrentMatrix[0][i]!=TempCorrect) {
                    this->mErrorMessage(FSErrors::FSE_VERTEX_VERTEXFORMAT);
                    return;
                }
                this->CurrentScene->addVertex(QPointF(this->CurrentMatrix[0][i+1], this->CurrentMatrix[0][i+2]));
                TempCorrect++;
            }
        }
    }


    //=======================================================
    //считывание ребер
    void mVertexsReading(){
        mFiguresCorrect(1, 5);
        CurrentData = 0;
        if (this->CurrentScene->countVertexs() != 0){
           for (int i = 0; i<CurrentMatrix[0].size(); i = i+5) {
                CurrentData ++;
            }

            if (CurrentData > this->CurrentScene->countVertexs()*(this->CurrentScene->countVertexs()+1)) {
                this->mErrorMessage(FSErrors::FSE_VertexS_BADVertexSSIZE);
                return;
            }


            for (int i = 0; i<CurrentMatrix[0].size(); i = i+5) {
                if ((this->CurrentScene->getVertexById(CurrentMatrix[0][i+2]) == nullptr) ||
                    (this->CurrentScene->getVertexById(CurrentMatrix[0][i+3]) == nullptr)){
                    this->mErrorMessage(FSErrors::FSE_VertexS_NOVERTEXEXISTS);
                    return;
                }
            if (CurrentMatrix[0][i+4] == 1) {
                this->CurrentScene->addNode(this->CurrentScene->getVertexById(CurrentMatrix[0][i+2]),
                this->CurrentScene->getVertexById(CurrentMatrix[0][i+3]),CurrentMatrix[0][i+1]);
            } else {
                this->CurrentScene->addNode(this->CurrentScene->getVertexById(CurrentMatrix[0][i+2]),
                                            this->CurrentScene->getVertexById(CurrentMatrix[0][i+3]),
                                            CurrentMatrix[0][i+1]);
                this->CurrentScene->addNode(this->CurrentScene->getVertexById(CurrentMatrix[0][i+3]),
                                            this->CurrentScene->getVertexById(CurrentMatrix[0][i+2]),
                                            CurrentMatrix[0][i+1]);
                }
            }
        }
    }

    //проверка корректности в файле с вершинами, ребрами
    void mFiguresCorrect(char Type, char Elements) {
        if (TempBufferA.contains("{")){
            if (!TempBufferA.contains("}")) {
                this->mErrorMessage(FSErrors::FSE_VERTEX_FIGURECLOSED);
                return;
            }
        }
        //проверка скобок
        int CorrectCounter = 0;
        for (int i = 0; i < TempBufferA.size(); i++) {
                if (TempBufferA[i] == "(") {
                CorrectInput = true;
                CorrectCounter++;
            }
            if (TempBufferA[i] == ")") {
                if (!CorrectInput) {
                    this->mErrorMessage(FSErrors::FSE_VERTEX_FIGURESTART);
                    return;
                }
                CorrectCounter--;
                }
        }
        if (CorrectCounter != 0) {
            this->mErrorMessage(FSErrors::FSE_VERTEX_FIGUREAMMO);
            return;
        }

        //чтение чисел
        QRegExp rx("(\\d+)");
        int pos = 0;
        if (Type == 0) {
            pos = TempBufferA.contains("Vertex") + 6;
        } else {
            pos = TempBufferA.contains("Vertexs") + 5;
        }
        CurrentMatrix.clear();
        CurrentMatrix.resize(Elements);
        while ((pos = rx.indexIn(TempBufferA, pos)) != -1) {
            TempBufferB = rx.cap(1);
            pos += rx.matchedLength();
            CurrentMatrix[0].push_back(TempBufferB.toInt());
            CurrentMatrix[2].push_back(pos-TempBufferB.size());
        }
        if ((CurrentMatrix[0].size()) % Elements != 0) {
            this->mErrorMessage(FSErrors::FSE_VERTEX_INCORRECTINPUT);
            return;
        }

        CurrentMatrix[1].clear();
        //проверка чисел в скобках
        for ( int i = 0; i < TempBufferA.size(); i++){
            if (TempBufferA[i] == "(" || TempBufferA[i] == ")") {
                CurrentMatrix[1].push_back(i);
                }
            }
        CorrectCounter = 0;
        CurrentData = 0;
        for (int i = 0; i < CurrentMatrix[2].size(); i++){
            switch (i%(Elements)) {
                case 0:
                    if (CurrentMatrix[2][i] > CurrentMatrix[1][CurrentData*2]) {
                        this->mErrorMessage(FSErrors::FSE_VERTEX_INCORRECTFIGURE);
                        return;
                    }
                    break;
                default:
                    if (CurrentMatrix[2][i] < CurrentMatrix[1][CurrentData*2] && CurrentMatrix[2][i] > CurrentMatrix[1][CurrentData*2 + 1]) {
                        this->mErrorMessage(FSErrors::FSE_VERTEX_INCORRECTFIGURE);
                        return;
                    }
                    break;
            }
            if (i%Elements == (Elements-1)) {
                CurrentData++;
            }
        }
    }

    void mVertexSaving () {
        this->TempBufferA = "Vertex {";
        this->CurrentData = 0;
        bool FirstValue = false;
        while (this->CurrentData != this->CurrentScene->countVertexs()+1) {
            if (this->CurrentScene->getVertexById(this->CurrentData) != nullptr) {
                if (!FirstValue){
                    this->TempBufferA += QString::number(this->CurrentData) +
                        "(" + QString::number((int)this->CurrentScene->getVertexById(this->CurrentData)->point.x()) +
                        ", " + QString::number((int)this->CurrentScene->getVertexById(this->CurrentData)->point.y()) +
                        ")";
                    FirstValue = true;
                } else {
                    this->TempBufferA += ", " + QString::number(this->CurrentData) +
                        "(" + QString::number((int)this->CurrentScene->getVertexById(this->CurrentData)->point.x()) +
                        ", " + QString::number((int)this->CurrentScene->getVertexById(this->CurrentData)->point.y()) +
                        ")";
                }
            }
            this->CurrentData++;
        }
        *this->FileStream << this->TempBufferA + "} \n";
    }

    void mAdjSaving() {
        this->TempBufferA = "Adjacency {" + QString::number(this->CurrentScene->countVertexs()) + "}\n";
        this->CurrentData = 0;
        bool FirstValue = false;
        QVector<QVector<int>> CurrentMat = this->CurrentScene->toMatrix();
        for (int i=0; i < CurrentMat.size(); i++) {
            for (int j=0; j < CurrentMat[i].size(); j++) {
                if (j==0) {
                    this->TempBufferA += QString::number(CurrentMat[i][j]);
                } else {
                    this->TempBufferA += " " + QString::number(CurrentMat[i][j]);
                }
            }
            this->TempBufferA += "\n";
        }
        *this->FileStream << this->TempBufferA;
    }

    void mIncSaving() {
        this->TempBufferA = "Incidence {" + QString::number(this->CurrentScene->countVertexs()) + ", " +
                QString::number(this->CurrentScene->countNodes()) + "}\n";
        QVector<QVector<int>> CurrentMat = this->CurrentScene->toMatrix();
        this->CurrentMatrix.clear();
        for (int i=0; i < this->CurrentScene->countVertexs(); i++) {
            for (int j=0; j < this->CurrentScene->countVertexs(); j++) {
                std::vector<int> Temp(this->CurrentScene->countVertexs());
                for (int k = 0; k < Temp.size(); k++){
                    Temp[k] = 0;
                }
                if(CurrentMat[i][j] != 0) {
                    if (i == j) {
                        Temp[i] = 1;
                    } else {
                        Temp[i] = -1;
                        Temp[j] = 1;
                    }
                }
                this->CurrentMatrix.push_back(Temp);
            }
        }
        for (int i=0; i < this->CurrentScene->countVertexs(); i++) {
            for (int j=0; j < this->CurrentMatrix.size(); j++) {
                if (j==0) {
                    this->TempBufferA += QString::number(this->CurrentMatrix[j][i]);
                } else {
                    this->TempBufferA += " " + QString::number(this->CurrentMatrix[j][i]);
                }
            }
            this->TempBufferA += "\n";
        }
        *this->FileStream << this->TempBufferA;
    }

    void mEdgSaving() {
        this->TempBufferA = "Vertexs {";
        QVector<QVector<int>> CurrentMat = this->CurrentScene->toMatrix();
        bool FirstValue = false;
        this->CurrentData = 0;
        for (int i = 0; i < CurrentMat.size(); i++){
            for (int j = 0; j < CurrentMat[i].size(); j++){
                if (CurrentMat[i][j] != 0) {
                    if (!FirstValue){
                        FirstValue = true;
                    } else {
                        this->TempBufferA += ", ";
                    }
                    this->TempBufferA += QString::number(this->CurrentData) +
                        "(" + QString::number(CurrentMat[i][j]) + ", " +
                            QString::number(i) + ", " +
                            QString::number(j) + ", ";
                    if (CurrentMat[i][j] == CurrentMat[j][i]) {
                        this->TempBufferA += "1)";
                    } else {
                        this->TempBufferA += "0)";
                    }
                }
                this->CurrentData++;
            }
        }
        *this->FileStream << this->TempBufferA+"}";
    }


    //сообщение об ошибке
    void mErrorMessage (int ErrorIndex){
        QMessageBox::warning(MainFrame, FSConstants::ErrorMessages[ErrorIndex].first,
                             FSConstants::ErrorMessages[ErrorIndex].second);
    }
};

#endif // FILEREADER_H
