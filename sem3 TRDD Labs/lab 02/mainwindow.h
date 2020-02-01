#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
//#include <tablemodel.h>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QtXlsx>
#include <QDebug>

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
    void on_action_open_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Button_Font_clicked();

    void changeButtons();

    void on_tableView_entered(const QModelIndex &index);

    void on_Button_TextColor_clicked();

    void on_Button_BackColor_clicked();

    void on_combo_BackStyle_currentIndexChanged(int index);

    void on_spinBox_Size_valueChanged(int arg1);

    void on_combo_Align_activated(int index);

    void on_checkBox_Bold_clicked();

    void on_checkBox_Italic_clicked();

    void on_checkBox_Underline_clicked();

    void on_action_save_triggered();

    void on_action_prepod_triggered();


    void on_pushButton_Table_clicked();

    void on_action_packet_triggered();

private:
    QXlsx::Document *xlsxFile;
    QXlsx::Document *xlsxFileSave;

    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStandardItem *item;

};

#endif // MAINWINDOW_H
