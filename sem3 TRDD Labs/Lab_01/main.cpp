//Автор программы - Горшков Д.С. (М8О-212Б)

#include "mainframe.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrame w;
    w.show();

    return a.exec();
}
