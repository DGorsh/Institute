#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_author_triggered();


    void on_action_exit_triggered();

    void on_action_open_triggered();


    void on_pushButton_plus_clicked();

    void on_pushButton_minus_clicked();

    void on_action_clear_triggered();

private:
    Ui::MainWindow *ui;
    int size=0;
    QVector<double> x, y;
    int countLines;
    bool openedfile;
};

#endif // MAINWINDOW_H
