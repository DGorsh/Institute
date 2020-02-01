#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QPixmap>
#include <QVariant>
#include <QtAlgorithms>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>

#include <scene.h>
#include <muncorrectinput.h>
#include <msolutionexecutor.h>
#include <solution_0.h>
#include <solution_2.h>
#include <solution_3.h>
#include <solution_7.h>
#include <solution_15.h>
#include <solution_10.h>
#include <solution_14.h>
#include <solution_4.h>
#include <solution_5.h>
#include <solution_6.h>
#include <solution_11.h>
#include <solution_8.h>
#include <solution_12.h>
#include <solution_17.h>
#include <solution_19.h>
#include <solution_21.h>
#include <solution_13.h>

#include <filereader.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVector<Scene*> scenes;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_action_about_triggered();

    void on_action_author_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

    void createTab();

    void on_tabWidget_tabBarClicked(int index);

    void on_matrixWidget_cellChanged(int row, int column);

    void on_tabWidget_tabCloseRequested(int index);

    void on_action_save_as_image_triggered();

    void on_matrixWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_matrixWidget_cellActivated(int row, int column);

    void on_matrixWidget_cellEntered(int row, int column);

    void on_action_file_open_triggered();

    void on_action_save_as_file_triggered();

    void on_pushButton_3_clicked();

    void on_task_0_triggered();


    void on_actionBFS_triggered();

    void on_action_2_triggered();

    void on_action_18_triggered();

    void on_action_3_triggered();

    void on_action_7_triggered();

    void on_action_15_triggered();

    void on_action_10_triggered();

    void on_actionA_triggered();

    void on_action_14_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_pushButton_4_clicked();

    void on_actionIterative_Deeping_triggered();

    void on_action_6_triggered();

    void on_action_11_triggered();

    void on_action_23_triggered();

    void on_action_24_triggered();

    void on_action_16_triggered();

    void on_action_8_triggered();

    void on_action_25_triggered();

    void on_action_26_triggered();

    void on_action_27_triggered();

    void on_action_17_triggered();

    void on_action_9_triggered();

    void on_action_20_triggered();

    void on_action_22_triggered();

    void on_action_21_triggered();

    void on_action_13_triggered();

private:
    Ui::MainWindow *ui;
    bool updateTable = false;
    int lastValue =0;
};

#endif // MAINWINDOW_H
