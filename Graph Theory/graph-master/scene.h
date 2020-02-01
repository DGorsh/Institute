/*
 * Большой класс отрисовки сцены. Предназначен для хранения и визуализации хранящегося графа
*/
#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPointF>
#include <QColor>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QPolygon>
#include <QGraphicsTextItem>
#include <QMenu>
#include <QAction>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>

#include <mgraphobject.h>

/*
 * Наследованный класс Scene. Хранит в памяти граф, имеет методы оперирования над графом, ожидает рефактор
 * */

class Scene : public QGraphicsView
{

private:

    /*
     * Private values
     * */
    QGraphicsScene* scene;
    QTableWidget* currentTable;

    MGraphObject graphModel; //This is base graph model

    MVertex* activeVertex,
         * supportVertex;
    MVertexNode* activeNode;

    QPointF lastRPoint;
    QList<QAction*> actions;
    QList<QAction*> actionsNode;

    QVector<MGraphObject> historyVector;

    MModes currentMode;

    QString placedText;

    int bufw;
    int currentGraph;
    const int lineWidth = 3;

    /*
     * Private methods
     * */
    void initActions();


public:

    explicit Scene(QWidget *parent = 0);

    ~Scene() override;

    /*
     * Setters
     * */

    void setTableWidget(QTableWidget* widget);

    void setActions(const QList<QAction*> list);

    /*
     * Widget Methods
     * */
public:

    void redr() {
        redraw();
        graphModel.clearColor();

    }
    void addAction(QAction* action);

    void addNodeAction(QAction* action);

    void addVertex(const QPointF& coordinates);

    void addLoop();

    void addConnection();

    void addUConnection();

    void appendNode();

    void addText(const QString& text);

    void clearText();

    void matrixChanged(int row, int column, int w, bool remove = false);

    void changeMode(const MModes mode);

    /*
     * Очищает сцену без освобождения памяти от самого графа
     * */
    void clear();

    /*
     * Очищает сцену, также очищает память графа.
     * */
    void free();

    void destroyNode();

    void destroyVertex();

    void moveNode();

    void moveVertex();

    void swapNode();

    void updateTable();

    //С ней какая-то проблема -_-
    void writeHistory();

    void undo();

    void redo();

    int histSize() const;

    int histIndex() const;

    /*
     *
     * */
    void palliteVertex(MVertex* vertex, MColor color = MColor::CL_DEFAULT);

    /*
     *
     * */
    void palliteVertexById(unsigned id, MColor color = MColor::CL_DEFAULT);

    /*
     *
     * */
    void unpalliteAll();
    /*
     * Other usefull methods
     * */
    QPointF bezueFunction(const QPointF& P0, const QPointF& P1, const QPointF& P2, const double t);

    QVector<QPointF> bezueArr(const QPointF& P0, const QPointF& P1, const QPointF& P2);

    MGraphObject* getGraphModel() {
        return &graphModel;
    }

    void setGraphModel(const MGraphObject graphModel) {
        this->graphModel = graphModel;
    }

    void DRedraw() {
        redraw();
    }

/*
 * Protected values
 * */
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void redraw();
};

#endif // SCENE_H
