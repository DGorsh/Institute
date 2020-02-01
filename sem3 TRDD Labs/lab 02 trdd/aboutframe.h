#ifndef ABOUTFRAME_H
#define ABOUTFRAME_H

#include <QDialog>

namespace Ui {
class aboutframe;
}

class aboutframe : public QDialog
{
    Q_OBJECT

public:
    explicit aboutframe(QWidget *parent = 0);
    ~aboutframe();

private:
    Ui::aboutframe *ui;
};

#endif // ABOUTFRAME_H
