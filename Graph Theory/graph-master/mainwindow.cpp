#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::information(this, "О программе", "=== Редактор графов ===\n"
                                                  "Программа предназначена для редактирования графов.\n"
                                                  "=== Графическая часть ===\n"
                                                  "Для создания новой вкладки необходимо дважды кликнуть ЛКМ по"
                                                  " названию текущей вкладки.\n"
                                                  "Чтобы работать с вершинами/ребрами, необходимо кликнуть ПКМ по объекту "
                                                  "работы и далее работать с контекстным меню.\n"
                                                  "=== Файловая система ===\n"
                                                  "Матрица смежности (adj). - Содержит матрицу смежности.\n"
                                                  "Первая строчка - заголовок. В нем задана размерность матрицы. Далее - сама матрица\n"
                                                  "Матрица инцидентности (inc) - Содержит матрицу инцидентности\n"
                                                  "Первая строчка - заголовок. В нем задана размерность матрицы. Далее - сама матрица\n"
                                                  "Список вершин (ver) - Содержит список координат вершин\n"
                                                  "Формат Vertex {id(x, y), ...}. Может быть задана также в любом из файлов.\n"
                                                  "Список ребер (edg) - Содержит список ребер\n"
                                                  "Формат Edges {id(weight, begin, end, orient)}");
}

void MainWindow::on_action_author_triggered()
{
    QMessageBox::information(this, "Об авторах", "Группа М8О-312\n"
                                                 "Графика - Дегтярев М. Э.\n"
                                                 "Работа с файлами - Горшков Д. С.");
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug() << index;
}

void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    createTab();
}

void MainWindow::createTab() {
    Scene* scene = new Scene();
    scene->setTableWidget(ui->matrixWidget);
    scenes.push_back(scene);

    ui->tabWidget->addTab(scene, "Граф " + QString::number(scenes.size()));
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    scenes[index]->updateTable();
}

void MainWindow::on_matrixWidget_cellChanged(int row, int column)
{
    if (updateTable) {
        //Приступаем к изменению значений в таблице
        int index = ui->tabWidget->currentIndex();
        QVariant var = ui->matrixWidget->item(row, column)->data(0);
        scenes[index]->matrixChanged(row, column, var.toInt(), ui->checkRemove->isChecked());

        updateTable = false;
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{

}

void MainWindow::on_action_save_as_image_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить как изображение"), "", tr("*.jpeg"));
    Scene* currScene = static_cast<Scene*>(ui->tabWidget->currentWidget());
    QPixmap image = currScene->grab(currScene->sceneRect().toRect());
    image.save(filename);
}

void MainWindow::on_matrixWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    updateTable = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    static_cast<Scene*>(ui->tabWidget->currentWidget())->undo();
}

void MainWindow::on_pushButton_clicked()
{
    static_cast<Scene*>(ui->tabWidget->currentWidget())->redo();
}

void MainWindow::on_matrixWidget_cellActivated(int row, int column)
{
    int index = ui->tabWidget->currentIndex();
    QVariant var = ui->matrixWidget->item(row, column)->data(0);
    lastValue = var.toInt();

}

void MainWindow::on_matrixWidget_cellEntered(int row, int column)
{
}

void MainWindow::on_action_file_open_triggered()
{
    QString CurrentFilePath = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.adj *.inc *.edg *.ver");
    FileReader file(CurrentFilePath, scenes[ui->tabWidget->currentIndex()]->getGraphModel(), this);
    if (!file.mIsReaded()) {
        QMessageBox::warning(this, "Катастрофа!", "Ошибка чтения файла");
        return;
    }
    file.FileReading();
    scenes[ui->tabWidget->currentIndex()]->DRedraw();
    scenes[ui->tabWidget->currentIndex()]->updateTable();
}


void MainWindow::on_action_save_as_file_triggered()
{
    QString CurrentFilePath = QFileDialog::getSaveFileName(this, "Open Dialog", "", "*.adj *.inc *.edg *.ver");
    FileReader file(CurrentFilePath, scenes[ui->tabWidget->currentIndex()]->getGraphModel(), this, true);
    file.FileSaving();
}

void MainWindow::on_pushButton_3_clicked()
{
    static_cast<Scene*>(ui->tabWidget->currentWidget())->free();
}

void MainWindow::on_task_0_triggered()
{
    QVector<MGraphObject> simpleGraphVector;
    Solution_0 mySolution(simpleGraphVector);

    MSolutionExecutor<QString> ex(this, &mySolution);

    ex.asMessage();
    ex.asDebug();

}


/*
 * Запуск BFS алгоритма
 * */
void MainWindow::on_actionBFS_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("BFS: Укажите вершины (из, в)"),
                                         tr("Ожидается ввод двух целых чисел:"), QLineEdit::Normal, "0 1", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() < 2 || list.size() > 2)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов <> 2");
        else {
            int idFrom = list[0].toInt();
            int idTo = list[1].toInt();

            Scene* currentScene = static_cast<Scene*>(ui->tabWidget->currentWidget());
            MGraphObject* usedGraph = currentScene->getGraphModel();

            Solution_2 BFSSolution(*usedGraph, idFrom, idTo,0);

            MSolutionExecutor<QPair<QVector<int>, int>> executor(this, &BFSSolution);

            QString resultText = "Обход графа: ";

            for (auto it : BFSSolution.res().anotherObject.first) {
                currentScene->palliteVertexById(it, MColor::CL_VISITED);
                resultText.append(" ").append(QString::number(it));
            }

            resultText.append("\nДлина пути: ").append(QString::number(BFSSolution.res().anotherObject.second));

            QMessageBox::information(this, "Результат", resultText);
            executor.asDebug();
        }
    }
    else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
    }
}


void MainWindow::on_action_2_triggered()
{

    bool ok;
    QString text = QInputDialog::getText(this, tr("Укажите вершину"),
                                         tr("Ожидается ввод числа:"), QLineEdit::Normal, "0", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() < 1 || list.size() > 1)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов <> 1");
        else {
            int idFrom = list[0].toInt();

            try {
                Solution_3 solution;
                Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
                MGraphObject graph = *currentScene->getGraphModel();
                solution.BellmanFord(graph, idFrom);
                QMessageBox::information(this, "Алгоритм Беллмана-Форда", solution.getres());
            } catch (MUncorrectInput ex) {
                QMessageBox::information(this, "Ошибка", "Осуществён некорректный ввод");
            }
        }
    }
    else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
    }




}

void MainWindow::on_action_18_triggered()
{
    Solution_3 solution;
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();
    solution.FloydWorshell(graph, 0);

    QMessageBox::information(this, "Алгоритм Флойда-Уоршелла", solution.getres());

}

void MainWindow::on_action_3_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Укажите вершину"),
                                         tr("Ожидается ввод числа:"), QLineEdit::Normal, "0", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() < 1 || list.size() > 1)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов <> 1");
        else {
            int idFrom = list[0].toInt();

            try {
                Solution_3 solution;
                Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
                MGraphObject graph = *currentScene->getGraphModel();
                solution.Dijkstra(graph, idFrom);
                QMessageBox::information(this, "Алгоритм Дейкстры", solution.getres());
            } catch (MUncorrectInput ex) {
                QMessageBox::critical(this, "Проблема", "Что-то не так с входными данными");
            }
        }
    }
    else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
    }



}

void MainWindow::on_action_7_triggered()
{
    Solution_7 solution;
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    QPair<MGraphObject, QString> result = solution.inv(graph).anotherObject;

    if (result.second == "Граф является полным") {
        QMessageBox::information(this, "Информация", "Граф является полным");
    } else if (result.second == "Граф дополнен"){
        QMessageBox::information(this, "Информация", "Граф был успешно дополнен");

        this->createTab();
        Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
        usedScene->setGraphModel(result.first);
        usedScene->redr();

    } else {
        QMessageBox::information(this, "Информация", "Процедура не выполнена");
    }



}

void MainWindow::on_action_15_triggered()
{

    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    QVector<int> left;
    QVector<int> rigth;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Укажите левую долю графа"),
                                         tr("Введите последовательность чисел через пробел:"), QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() == 0)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов не может быть нулевым");
        else {
            for (auto it : list) {
                left.push_back(it.toInt());
            }
        }
    }   else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
        return;
    }

    text = QInputDialog::getText(this, tr("Укажите правую долю графа"),
                                 tr("Введите последовательность чисел через пробел:"), QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() == 0)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов не может быть нулевым");
        else {
            for (auto it : list) {
                rigth.push_back(it.toInt());
            }
        }
    }   else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
        return;
    }

    Solution_15 solution(graph, left, rigth);

    solution.run();
    QString result = solution.res().anotherObject;

    QMessageBox::information(this, "Info", result);

}

void MainWindow::on_action_10_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    QVector<int> input;
    bool ok;
    QString text =  QInputDialog::getText(this, tr("Введите вектор"),
                                                    tr("Введите последовательность чисел через пробел:"), QLineEdit::Normal, "6 4 4 3 3 2 2", &ok);
    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() == 0)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов не может быть нулевым");
        else {
            for (auto it : list) {
                input.push_back(it.toInt());
            }
        }
    }   else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
        return;
    }

    Solution_10 solution(input);


    try {
        solution.run();
        currentScene->setGraphModel(solution.res().anotherObject.first);
        QMessageBox::information(this, "Информация", solution.res().anotherObject.second);

        currentScene->redr();

    } catch (MUncorrectInput ex) {
        QMessageBox::critical(this, "Ошибка", "Был осуществлён некорректный ввод");
    }
}
void MainWindow::on_actionA_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("A_STAR: Укажите вершины (из, в)"),
                                         tr("Ожидается ввод двух целых чисел:"), QLineEdit::Normal, "0 1", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() < 2 || list.size() > 2)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов <> 2");
        else {
            int idFrom = list[0].toInt();
            int idTo = list[1].toInt();

            Scene* currentScene = static_cast<Scene*>(ui->tabWidget->currentWidget());
            MGraphObject* usedGraph = currentScene->getGraphModel();

            Solution_2 BFSSolution(*usedGraph, idFrom, idTo, 1);

            MSolutionExecutor<QPair<QVector<int>, int>> executor(this, &BFSSolution);

            QString resultText = "Обход графа: ";

            for (auto it : BFSSolution.res().anotherObject.first) {
                currentScene->palliteVertexById(it, MColor::CL_VISITED);
                resultText.append(" ").append(QString::number(it));
            }

            resultText.append("\nДлина пути: ").append(QString::number(BFSSolution.res().anotherObject.second));

            QMessageBox::information(this, "Результат", resultText);
            executor.asDebug();
        }
    }
    else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
    }
}

void MainWindow::on_action_14_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    Solution_14 s;

    QPair<MGraphObject, int> result = s.pallite_new(graph, 0);

    currentScene->setGraphModel(result.first);
    currentScene->redr();
    QMessageBox::information(this, "Результат", "Хроматическое число графа:"+QString::number(result.second));


}



void MainWindow::on_action_4_triggered()
{
    MGraphObject* usedGraph = static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel();
    Solution_4 mySolution(*usedGraph);

    MSolutionExecutor<QString> ex(this, &mySolution);

    ex.asMessage();
    ex.asDebug();

    QMessageBox::information(this, "Решение", mySolution.GetAnswer());
}

void MainWindow::on_action_5_triggered()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Выбор сцен с графами"));
    QSpinBox *ledit1 = new QSpinBox(&dlg);
    QSpinBox *ledit2 = new QSpinBox(&dlg);

    ledit1->setMaximum(ui->tabWidget->count());
    ledit2->setMaximum(ui->tabWidget->count());
    ledit1->setMinimum(1);
    ledit2->setMinimum(1);


    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("Граф А:"), ledit1);
    layout->addRow(tr("Граф В:"), ledit2);
    layout->addWidget(btn_box);


    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted) {
        const int str1 = ledit1->value();
        const int str2 = ledit2->value();
        MGraphObject* usedGraphA = static_cast<Scene*>(ui->tabWidget->widget(str1-1))->getGraphModel();
        MGraphObject* usedGraphB = static_cast<Scene*>(ui->tabWidget->widget(str2-1))->getGraphModel();
        Solution_5 mySolution(*usedGraphA, *usedGraphB);

        MSolutionExecutor<QString> ex(this, &mySolution);

        ex.asMessage();
        ex.asDebug();

        QMessageBox::information(this, "Решение", mySolution.GetAnswer());
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    currentScene->changeMode(CREATE);
}

void MainWindow::on_actionIterative_Deeping_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Iterative Deeping: Укажите вершины (из, в)"),
                                         tr("Ожидается ввод двух целых чисел:"), QLineEdit::Normal, "0 1", &ok);

    if (ok && !text.isEmpty()) {
        QStringList list = text.split(" ");

        if (list.size() < 2 || list.size() > 2)
            QMessageBox::critical(this, "Некорректный ввод", "Число аргументов <> 2");
        else {
            int idFrom = list[0].toInt();
            int idTo = list[1].toInt();

            Scene* currentScene = static_cast<Scene*>(ui->tabWidget->currentWidget());
            MGraphObject* usedGraph = currentScene->getGraphModel();

            Solution_2 BFSSolution(*usedGraph, idFrom, idTo, 1);

            MSolutionExecutor<QPair<QVector<int>, int>> executor(this, &BFSSolution);

            QString resultText = "Обход графа: ";

            for (auto it : BFSSolution.res().anotherObject.first) {
                currentScene->palliteVertexById(it, MColor::CL_VISITED);
                resultText.append(" ").append(QString::number(it));
            }

            resultText.append("\nДлина пути: ").append(QString::number(BFSSolution.res().anotherObject.second));

            QMessageBox::information(this, "Результат", resultText);
            executor.asDebug();
        }
    }
    else {
        QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте ещё раз.");
    }
}

void MainWindow::on_action_6_triggered()
{
    Solution_3 solution;
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();
    solution.Jhonson(graph, 0);
    QMessageBox::information(this, "Алгоритм Джонсона", solution.getres());
}

void MainWindow::on_action_11_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    QVector<int> input = {2,1,1,2,1,2,1,2};
    Solution_11 sol(input);
    sol.run();
}

void MainWindow::on_action_23_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    Solution_6 solution(graph, false);
    QMessageBox::information(this, "Информация", solution.getComponents(graph));
}

void MainWindow::on_action_24_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    Solution_6 solution(graph, true);
    QMessageBox::information(this, "Информация", solution.getComponents(graph));
}

void MainWindow::on_action_16_triggered()
{
    Solution_7 solution;
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    QVector <QVector<int>> TempAdjMatrix = graph.toMatrix();
    QVector<int> VertexRankA(graph.countVertexs());
    for (int i = 0; i<graph.countVertexs(); i++) {
        VertexRankA[i] = 0;
        //по горизонтали (из вершины)
        for (int j = 0; j<graph.countVertexs();j++) {
            if (TempAdjMatrix[i][j] != 0) {
                VertexRankA[i]++;
            }
        }
        //по вертикали (в вершину)
        for (int j = 0; j<graph.countVertexs();j++) {
            if ((TempAdjMatrix[j][i] != 0) && (i != j)) {
                VertexRankA[i]++;
            }
        }
    }
    qSort(VertexRankA);
    Solution_17 mySolution(VertexRankA);
    bool Worked = mySolution.ResultReturn().contains("Далее решения нет");

    if (Worked) {
        QMessageBox::information(this, "Информация", "Не 2-комплекс!");
        return;
    }

    QPair<MGraphObject, QString> result = solution.inv(graph).anotherObject;

    if (result.second == "Граф является полным") {
        QMessageBox::information(this, "Информация", "Граф является полным");
    } else if (result.second == "Граф дополнен"){
        QMessageBox::information(this, "Информация", "Граф был успешно дополнен");

        this->createTab();
        Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
        usedScene->setGraphModel(result.first);
        usedScene->redr();

    } else {
        QMessageBox::information(this, "Информация", "Процедура не выполнена");
    }
}

void MainWindow::on_action_8_triggered()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Выбор сцен с графами"));
    QSpinBox *ledit1 = new QSpinBox(&dlg);
    QSpinBox *ledit2 = new QSpinBox(&dlg);
    QComboBox *ledit4 = new QComboBox(&dlg);

    ledit4->addItems({"Коньюнкция А и В", "Дизъюнкция  А и В", "Вычитание В из А", "Вычитание А из В",
                     "Импликация А из В", "Импликация В из А", "Коимпликация А из В", "Коимпликация В из А",
                     "Исключающее или А и В", "Эквивалентность А и В", "Штрих Шефера", "Стрелка Пирса", "Все операции"});

    ledit1->setMaximum(ui->tabWidget->count());
    ledit2->setMaximum(ui->tabWidget->count());
    ledit1->setMinimum(1);
    ledit2->setMinimum(1);


    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("Граф А:"), ledit1);
    layout->addRow(tr("Граф В:"), ledit2);
    layout->addRow(tr("Операция:"), ledit4);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted) {
        const int str1 = ledit1->value();
        const int str2 = ledit2->value();
        MGraphObject* usedGraphA = static_cast<Scene*>(ui->tabWidget->widget(str1-1))->getGraphModel();
        MGraphObject* usedGraphB = static_cast<Scene*>(ui->tabWidget->widget(str2-1))->getGraphModel();
        if (usedGraphA->countVertexs() != usedGraphB->countVertexs()) {
            QMessageBox::information(this, "Решение", "Количество вершин в графах не равны!");
            return;
        }
        Solution_8 mySolution(*usedGraphA, *usedGraphB);
                    QMessageBox::information(this, "Решение", QString::number(ledit4->currentIndex()));
        QVector<QVector<int>> Adj;
        switch (ledit4->currentIndex()) {
            case 0: Adj = mySolution.Conjuction(); break;
            case 1: Adj = mySolution.Disjuction(); break;
            case 2: Adj = mySolution.Substraction(true); break;
            case 3: Adj = mySolution.Substraction(false); break;
            case 4: Adj = mySolution.Implication(true); break;
            case 5: Adj = mySolution.Implication(false); break;
            case 6: Adj = mySolution.Coimplication(true); break;
            case 7: Adj = mySolution.Coimplication(false); break;
            case 8: Adj = mySolution.XOR(); break;
            case 9: Adj = mySolution.Equivalence(); break;
            case 10: Adj = mySolution.Sheffer(); break;
            case 11: Adj = mySolution.Pirs(); break;
            case 12: {
                for (int i = 0; i < 12; i++) {
                    this->createTab();
                    Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
                    QVector<QVector<int>> GResult;
                    MGraphObject *temp = usedScene->getGraphModel();
                    switch (i) {
                        case 0: GResult = mySolution.Conjuction(); break;
                        case 1: GResult = mySolution.Disjuction(); break;
                        case 2: GResult = mySolution.Substraction(true); break;
                        case 3: GResult = mySolution.Substraction(false); break;
                        case 4: GResult = mySolution.Implication(true); break;
                        case 5: GResult = mySolution.Implication(false); break;
                        case 6: GResult = mySolution.Coimplication(true); break;
                        case 7: GResult = mySolution.Coimplication(false); break;
                        case 8: GResult = mySolution.XOR(); break;
                        case 9: GResult = mySolution.Equivalence(); break;
                        case 10: GResult = mySolution.Sheffer(); break;
                        case 11: GResult = mySolution.Pirs(); break;
                    }
                    for (int j = 0; j < GResult.size(); j++) {
                        temp->addVertex(QPointF(200 + 150*cos(j*6.28/GResult.size()),
                                                200 + 150*sin(j*6.28/GResult.size())));
                    }
                    for (int j = 0; j < GResult.size(); j++) {
                        for (int k = 0; k < GResult.size(); k++) {
                            if (GResult[j][k] != 0) {
                                temp->addNode(temp->getVertexById(j), temp->getVertexById(k), 1);
                            }
                        }
                    }
                    usedScene->redr();
                }
            }
        }
        QString Temp = "";
        for (int i = 0; i<Adj.size() ; i++) {
            for (int j = 0; j<Adj.size() ; j++) {
                Temp += QString::number(Adj[i][j]);
            }
            Temp += ";\n";
        }
        QMessageBox::information(this, "Result", Temp);

        MSolutionExecutor<QString> ex(this, &mySolution);

        ex.asMessage();
        ex.asDebug();
    }
}

void MainWindow::on_action_25_triggered()
{
    MGraphObject* usedGraph = static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel();
    Solution_12 mySolution(*usedGraph);

    MSolutionExecutor<QString> ex(this, &mySolution);

    ex.asMessage();
    ex.asDebug();

    QMessageBox::information(this, "Решение (Алгоритм Прима)", mySolution.Prim());
    if (!mySolution.Prim().contains("No")) {
        QStringList TempData = mySolution.Prim().split("\n");
        this->createTab();
        Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
        QVector<QVector<int>> GResult;
        MGraphObject *temp = usedScene->getGraphModel();
        for (int i = 0; i < usedGraph->countVertexs(); i++) {
            temp->addVertex(QPointF(usedGraph->getVertexById(i)->point.x(), usedGraph->getVertexById(i)->point.y()));
        }
        for (int i = 0; i < TempData.size(); i++) {
            if (TempData[i].contains("Начало") && TempData[i].contains("Конец")) {
                QStringList Temp = TempData[i].split(" | ");
                Temp[0].remove(0, 8);
                Temp[1].remove(0, 7);
                temp->addNode(temp->getVertexById(Temp[0].toInt()), temp->getVertexById(Temp[1].toInt()), 1);
            }
        }
     }

}

void MainWindow::on_action_26_triggered()
{
    MGraphObject* usedGraph = static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel();
    Solution_12 mySolution(*usedGraph);

    MSolutionExecutor<QString> ex(this, &mySolution);

    ex.asMessage();
    ex.asDebug();

    QMessageBox::information(this, "Решение (Алгоритм Крускала)", mySolution.Kruskal());
    if (!mySolution.Kruskal().contains("No")) {
        QStringList TempData = mySolution.Kruskal().split("\n");
        this->createTab();
        Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
        QVector<QVector<int>> GResult;
        MGraphObject *temp = usedScene->getGraphModel();
        for (int i = 0; i < usedGraph->countVertexs(); i++) {
            temp->addVertex(QPointF(usedGraph->getVertexById(i)->point.x(), usedGraph->getVertexById(i)->point.y()));
        }
        for (int i = 0; i < TempData.size(); i++) {
            if (TempData[i].contains("Начало") && TempData[i].contains("Конец")) {
                QStringList Temp = TempData[i].split(" | ");
                Temp[0].remove(0, 8);
                Temp[1].remove(0, 7);
                temp->addNode(temp->getVertexById(Temp[0].toInt()), temp->getVertexById(Temp[1].toInt()), 1);
            }
        }
     }
}

void MainWindow::on_action_27_triggered()
{
    MGraphObject* usedGraph = static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel();
    Solution_12 mySolution(*usedGraph);

    MSolutionExecutor<QString> ex(this, &mySolution);

    ex.asMessage();
    ex.asDebug();

    QMessageBox::information(this, "Решение (Алгоритм Борувки)", mySolution.Prim());
    if (!mySolution.Prim().contains("No")) {
        QStringList TempData = mySolution.Prim().split("\n");
        this->createTab();
        Scene* usedScene = dynamic_cast<Scene*>(ui->tabWidget->widget(scenes.size()-1));
        QVector<QVector<int>> GResult;
        MGraphObject *temp = usedScene->getGraphModel();
        for (int i = 0; i < usedGraph->countVertexs(); i++) {
            temp->addVertex(QPointF(usedGraph->getVertexById(i)->point.x(), usedGraph->getVertexById(i)->point.y()));
        }
        for (int i = 0; i < TempData.size(); i++) {
            if (TempData[i].contains("Начало") && TempData[i].contains("Конец")) {
                QStringList Temp = TempData[i].split(" | ");
                Temp[0].remove(0, 8);
                Temp[1].remove(0, 7);
                temp->addNode(temp->getVertexById(Temp[0].toInt()), temp->getVertexById(Temp[1].toInt()), 1);
            }
        }
     }
}

void MainWindow::on_action_17_triggered()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Выбор сцен с графами"));
    QLineEdit *ledit = new QLineEdit(&dlg);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("Вектор:"), ledit);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted) {
        QVector<int> VectorData = {11, 10, 9, 8, 6, 5, 2};
        VectorData.clear();
        QStringList TextData = ledit->text().split(" ");
        for (int i = 0; i < TextData.size(); i++) {
            VectorData.push_back(TextData[i].toInt());
        }
        bool Extreme = true;
        for (int i = 1; i < TextData.size(); i++) {
            if (VectorData[i] > VectorData[i-1]) {
                Extreme = false;
            }
        }
        Solution_17 mySolution(VectorData);

        MSolutionExecutor<QString> ex(this, &mySolution);

        ex.asMessage();
        ex.asDebug();

        QMessageBox::information(this, "Решение (2-комплекс)", mySolution.ResultReturn());
        bool Worked = mySolution.ResultReturn().contains("Далее решения нет");
        QString Answer = "Симплексы: \n";
        if (!Worked) {
            for (int i = 0; i < VectorData.size(); i++) {
                for (int j = i + 1; j < VectorData.size(); j++) {
                    for (int k = j + 1; k < VectorData.size(); k++) {
                        if ((VectorData[i] > 0) && (VectorData[j] > 0) && (VectorData[k] > 0))
                            Answer += "(" + QString::number(i+1) +", " + QString::number(j+1) + ", "+ QString::number(k+1) + ")\n";
                        VectorData[i]--;
                        VectorData[j]--;
                        VectorData[k]--;
                    }
                }
            }
            QMessageBox::information(this, "Решение (2-комплекс)", Answer);
        }


    }
}

void MainWindow::on_action_9_triggered()
{
    Solution_5 TempUllman;
    Solution_5 TempUllman2;
    QVector<QVector<int>> K5Matrix(5);
    for (int i = 0; i < K5Matrix.size(); i++){
        for(int j = 0; j < K5Matrix.size(); j++){
            K5Matrix[i].push_back((i!=j)?1:0);
        }
    }
    QVector<QVector<int>> K33Matrix(6);
    for (int i = 0; i < K33Matrix.size(); i++){
        for(int j = 0; j < K33Matrix.size(); j++){
            if (i <= 2) {
                if (j <= 2) {
                    K33Matrix[i].push_back(0);
                } else {
                    K33Matrix[i].push_back(1);
                }
            } else {
                if (j <= 2) {
                    K33Matrix[i].push_back(1);
                } else {
                    K33Matrix[i].push_back(0);
                }
            }
        }
    }
    MGraphObject* usedGraph = static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel();
    QVector<QVector<int>> PermutationMatrix(usedGraph->countVertexs());
    for (int i=0; i < PermutationMatrix.size(); i++) {
        PermutationMatrix[i].resize(usedGraph->countVertexs());
    }
    if (usedGraph->countVertexs() >= 5) {
        TempUllman.UllmanAlgorithm(static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel()->toMatrix(),
                               K5Matrix, PermutationMatrix, 1);
    }
    if (TempUllman.GetAnswer().contains("Перестановки по алгоритму Ульмана существуют")) {
        QMessageBox::information(this, "Ошибка", "Один из подграфов графа G изоморфен графу К(5) - граф не планарен!");
        return;
    }
    if (usedGraph->countVertexs() >= 6) {
        TempUllman2.UllmanAlgorithm(static_cast<Scene*>(ui->tabWidget->currentWidget())->getGraphModel()->toMatrix(),
                               K33Matrix, PermutationMatrix, 1);
    }
    if (TempUllman2.GetAnswer().contains("Перестановки по алгоритму Ульмана существуют")) {
        QMessageBox::information(this, "Ошибка", "Один из подграфов графа G изоморфен графу К(3,3) - граф не планарен!");
        return;
    }
    QMessageBox::information(this, "Информация", "Граф планарен!");
}

void MainWindow::on_action_20_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();

    Solution_19 sol;
    sol.solve(graph);

    QMessageBox::information(this, "Задача о коммивояжере", sol.getResult());
}

void MainWindow::on_action_22_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
        MGraphObject graph = *currentScene->getGraphModel();

        Solution_21 sol;
        MMatrix graphi = sol.generateGraph(10000);
        sol.algorithmComparator(graphi);

        QFile file("out.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << sol.getLog();

        //QMessageBox::information(this, "21 задача", sol.getLog());
}

void MainWindow::on_action_21_triggered()
{

}

void MainWindow::on_action_13_triggered()
{
    Scene* currentScene = dynamic_cast<Scene*>(ui->tabWidget->currentWidget());
    MGraphObject graph = *currentScene->getGraphModel();
    Solution_13 mySolution;
    QVector<int> Cycles = mySolution.Cycle_wideWalk(graph.toMatrix(), 0);
    if (Cycles.size()!=0) {
        QMessageBox::information(this, "Задача о циклах", "Циклы не найдены!");
        QMessageBox::information(this, "Центр и глубина", mySolution.centerVer(graph));
        QMessageBox::information(this, "Код Прюфера", mySolution.Prufer(graph));
    } else {
        QMessageBox::information(this, "Задача о коммивояжере", "Циклы найдены!");
    }


}
