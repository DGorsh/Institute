#include "mainwindow.h"
#include "aboutframe.h"
#include "ui_mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openedfile  = false;
    countLines = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_author_triggered()
{
    aboutframe aboutfr;
    aboutfr.setModal(true);
    aboutfr.exec();
}


void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_action_open_triggered()
{
    // Вызываем диалог и сохраняем путь до файла в строку
    QString filePath = QFileDialog::getOpenFileName(0, "Открыть график", QString(), "Graphic (*.txt)");
    QFile readFile(filePath);
    QTextStream stream(&readFile);
    countLines = 0;
    ui->widget->clearGraphs();
    bool correct;
    if (readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while (!stream.atEnd())
        {
            QString currentLine = stream.readLine();

            if( currentLine.isEmpty() )
            {
                continue;
            }

            // Считываем 1 строку
            size = currentLine.toInt(&correct, 10);
            if (!correct) {
                QMessageBox::warning(this, "Что-то пошло не так","Увы, но юзер не так ввел данные в файл.");
                return;
            }

            // Меняем размер вектора
            x.resize(size), y.resize(size);
            for (int i = 0; i < size; i++)
            {
                // Считываем в стринг лист строчки
                QStringList list = stream.readLine().simplified().split(' ');
                if (list.size() != 2) {
                    QMessageBox::warning(this, "Что-то пошло не так","Увы, но юзер не так ввел данные в файл.");
                    return;
                }
                x[i] = list.at(0).toDouble(&correct);
                if (!correct) {
                    QMessageBox::warning(this, "Что-то пошло не так","Увы, но юзер не так ввел данные в файл.");
                    return;
                };
                y[i] = list.at(1).toDouble(&correct);
                if (!correct) {
                    QMessageBox::warning(this, "Что-то пошло не так","Увы, но юзер не так ввел данные в файл.");
                    return;
                }
            }
            //Установим область для оси Ox, которая будет показываться на графике
            double xmin = x[0], xmax = x[0], ymin = y[0], ymax = y[0];
            for (auto &i: x) {
                if (i < xmin) xmin = i;
                if (i > xmax) xmax = i;
            }
            for (auto &i: y) {
                if (i < ymin) ymin = i;
                if (i > ymax) ymax = i;
            }
            ui->widget->xAxis->setRange(xmin-0.5, xmax+0.5);
            ui->widget->yAxis->setRange(ymin-0.5, ymax+0.5);
            ui->widget->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->widget->graph(countLines)->setData(x, y);
            ui->widget->graph(countLines)->setPen(QColor(50, 50, 50, 255)); //Задаем цвет точки
            //формируем вид точек
            ui->widget->graph(countLines++)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
        }
        readFile.close();
        openedfile = true;
    }
    else
        qDebug() << "File opening error.";

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("X");
    ui->widget->yAxis->setLabel("Y");

    // Перерисовываем график на нашем widget
    ui->widget->replot();
}

void MainWindow::on_pushButton_plus_clicked()
{
    if (openedfile) {
        for(int i = 0; i < countLines; i++){
            int tempsize = ui->widget->graph(i)->dataCount();
            QVector<double> xtemp(tempsize), ytemp(tempsize);
            for (int j = 0; j < tempsize; j++)
            {
                xtemp[j] = ui->widget->graph(i)->data().data()->at(j)->mainKey() * 1.2;
                ytemp[j] = ui->widget->graph(i)->data().data()->at(j)->mainValue() * 1.2;
            }
            ui->widget->graph(i)->setData(xtemp, ytemp);
        }
        ui->widget->replot();
    }
}

void MainWindow::on_pushButton_minus_clicked()
{
    if (openedfile) {
        for(int i = 0; i < countLines; i++){
            int tempsize = ui->widget->graph(i)->dataCount();
            QVector<double> xtemp(tempsize), ytemp(tempsize);
            for (int j = 0; j < tempsize; j++)
            {
                xtemp[j] = ui->widget->graph(i)->data().data()->at(j)->mainKey() * 0.8;
                ytemp[j] = ui->widget->graph(i)->data().data()->at(j)->mainValue() * 0.8;
            }
            ui->widget->graph(i)->setData(xtemp, ytemp);
        }
        ui->widget->replot();
    }
}

void MainWindow::on_action_clear_triggered()
{
    if (openedfile) {
        for(int i = 0; i < countLines; i++){
            int tempsize = ui->widget->graph(i)->dataCount();
            QVector<double> xtemp(tempsize), ytemp(tempsize);
            ui->widget->graph(i)->setData(xtemp, ytemp);
        }
        ui->widget->replot();
    }
}
