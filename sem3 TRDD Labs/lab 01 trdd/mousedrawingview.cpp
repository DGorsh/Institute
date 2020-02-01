#include <mousedrawingview.h>

MousedView:: MousedView(QWidget *parent) : QGraphicsView(parent) {
    SelectedFigure = 0;

    radius = 15;
    h = 40;
    w = 80;
}

//нажатие на кнопку мыши
void MousedView::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        QPointF ps = mapToScene(event->pos());
        switch (SelectedFigure) {
        //круг
        case 0:
            this->scene()->addEllipse(ps.x()-radius,ps.y()-radius,radius*2,radius*2, Pen, Back);
            break;
        //эллипс
        case 1:
            this->scene()->addEllipse(ps.x()-w/2,ps.y()-h/2,w,h, Pen, Back);
            break;
        }
    }
}

void MousedView::ChangeFigure(int figureid){
    SelectedFigure = figureid;
}


