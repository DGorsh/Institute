#ifndef MOUSEDRAWINGVIEW_H
#define MOUSEDRAWINGVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QMouseEvent>

class MousedView : public QGraphicsView {
private:
    int SelectedFigure;

public:
    //публичные переменные, чтоб не возиться с функциями
    int radius;
    int h;
    int w;
    QPen Pen{Qt::black};
    QBrush Back{Qt::white, Qt::NoBrush};


    MousedView(QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent*);
    void ChangeFigure(int);
};

#endif // MOUSEDRAWINGVIEW_H
