#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTextStream>
#include <QtGui>
#include <QFileDialog>
#include <QLayout>

namespace Ui {
class MainFrame;
}

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

private:
    Ui::MainFrame *ui;
    QFileSystemModel *model;
    QString fileWay;
private slots:
    void on_action_exit_triggered();
    void on_action_help_triggered();
    void on_treeView_activated(const QModelIndex &index);
    void on_listWidget_activated(const QModelIndex &index);
    void on_comboBox_currentIndexChanged(int index);
    void on_boxBold_clicked();
    void on_boxItalic_clicked();
    void on_boxUnder_clicked();
    void on_pushButton_clicked();
    void on_pushButtonSave_clicked();
};

#endif // MAINFRAME_H
