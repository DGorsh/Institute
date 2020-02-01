#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <vector>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsItem>

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

    void on_action_about_triggered();

    void on_action_exit_triggered();

    void on_spin_width_editingFinished();

    void on_spin_heigth_editingFinished();

    void on_spinBox_radius_editingFinished();

    void on_combo_pen_currentIndexChanged(int index);

    void on_combo_back_currentIndexChanged(int index);

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStandardItem *root;
    QGraphicsScene *scene;
    QVector<QString> figureNames;
};

#endif // MAINWINDOW_H
