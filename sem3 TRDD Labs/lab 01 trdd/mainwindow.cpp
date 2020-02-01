//Горшков Дмитрий М8О-212Б
//Помимо расширения функционала было добавлено масштабирование фигур (ибо тоже не совсем ясно, что имелось ввиду
//в задании, а заодно и цвет (просто так, чтобы был)


#include "mainwindow.h"
#include "dialogabout.h"
#include "ui_mainwindow.h"
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel();
    root = new QStandardItem("Фигура");
    root->setFlags(root->flags() & ~Qt::ItemIsEditable);

    //Элементы "Фигуры". Новые элементы - за счет добавления в вектор.
    figureNames.push_back("Круг");
    figureNames.push_back("Эллипс");

    ui->treeView->setModel(model);

    //Заполняем модель
    //основной узел
    model->appendRow(root);
    //объекты для основного узла. Расширение функционала за счет добавления элементов в вектор figureNames
    for(auto &i : figureNames) {
        QStandardItem *item = new QStandardItem(i);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        root->appendRow(item);
    }

    //graphic view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,800);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//хэлп
void MainWindow::on_action_about_triggered()
{
    DialogAbout aboutfr;
    aboutfr.setModal(true);
    aboutfr.exec();
}

//выход
void MainWindow::on_action_exit_triggered()
{
    QCoreApplication::quit();
}

//ширина
void MainWindow::on_spin_width_editingFinished()
{
    ui->graphicsView->w = ui->spin_width->value();
}
 //высота
void MainWindow::on_spin_heigth_editingFinished()
{
    ui->graphicsView->h = ui->spin_heigth->value();
}

//радиус
void MainWindow::on_spinBox_radius_editingFinished()
{
    ui->graphicsView->radius = ui->spinBox_radius->value();
}

//перо
void MainWindow::on_combo_pen_currentIndexChanged(int index)
{
    switch (index) {
       case 0: ui->graphicsView->Pen.setColor(Qt::black); break;
       case 1: ui->graphicsView->Pen.setColor(Qt::white); break;
       case 2: ui->graphicsView->Pen.setColor(Qt::red); break;
       case 3: ui->graphicsView->Pen.setColor(Qt::green); break;
       case 4: ui->graphicsView->Pen.setColor(Qt::blue); break;
    }
}

//заливка
void MainWindow::on_combo_back_currentIndexChanged(int index)
{
    switch (index) {
       case 0: ui->graphicsView->Back.setColor(Qt::black);
               ui->graphicsView->Back.setStyle(Qt::SolidPattern);break;
       case 1: ui->graphicsView->Back.setColor(Qt::white);
               ui->graphicsView->Back.setStyle(Qt::NoBrush);break;
       case 2: ui->graphicsView->Back.setColor(Qt::red);
               ui->graphicsView->Back.setStyle(Qt::SolidPattern);break;
       case 3: ui->graphicsView->Back.setColor(Qt::green);
               ui->graphicsView->Back.setStyle(Qt::SolidPattern);break;
       case 4: ui->graphicsView->Back.setColor(Qt::blue);
               ui->graphicsView->Back.setStyle(Qt::SolidPattern);break;
    }
}

//меняем фигуру при выборе в treeView. описание ChangeFigure в mousedrawingview.cpp
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    ui->graphicsView->ChangeFigure(index.row()); //смотрим по индексу.
}
