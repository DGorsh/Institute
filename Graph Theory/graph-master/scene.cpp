#include "scene.h"


void Scene::initActions() {
    QVector<QString> actNames = {"Добавить петлю",
                                 "Передвинуть вершину",
                                 "Присоединить к...",
                                 "Двунаправленно присоединить к...",
                                 "Удалить вершину"};

    QVector<QString> nodeActNames = {"Изменить форму",
                                     "Удалить ребро",
                                     "Изменить направление",
                                     "Добавить обратное ребро"};

    for (auto currString : actNames) {
        addAction(new QAction(currString, this));
    }

    for (auto currString : nodeActNames) {
        addNodeAction(new QAction(currString, this));
    }

    connect(actions[0], &QAction::triggered, this, &Scene::addLoop);
    connect(actions[1], &QAction::triggered, this, &Scene::moveVertex);
    connect(actions[2], &QAction::triggered, this, &Scene::addConnection);
    connect(actions[3], &QAction::triggered, this, &Scene::addUConnection);
    connect(actions[4], &QAction::triggered, this, &Scene::destroyVertex);

    connect(actionsNode[0], &QAction::triggered, this, &Scene::moveNode);
    connect(actionsNode[1], &QAction::triggered, this, &Scene::destroyNode);
    connect(actionsNode[2], &QAction::triggered, this, &Scene::swapNode);
    connect(actionsNode[3], &QAction::triggered, this, &Scene::appendNode);
}

QPointF Scene::bezueFunction(const QPointF &P0, const QPointF &P1, const QPointF &P2, const double t) {
    double first_exp = (1-t)*(1-t);
    double second_exp = 2*t*(1-t);
    double third_exp = t*t;

    QPointF result = first_exp*P0 + second_exp*P1 + third_exp*P2;

    return result;
}

QVector<QPointF> Scene::bezueArr(const QPointF &P0, const QPointF &P1, const QPointF &P2) {
    QVector<QPointF> result;

    for (double t = 0; t <= 1; t+=0.1) {
        result.push_back(bezueFunction(P0,P1,P2,t));
    }

    return result;
}

Scene::Scene(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    setSceneRect(0,0, width(), height());
    setMouseTracking(true);

    currentMode = MModes::CREATE;
    activeVertex = supportVertex = nullptr;
    activeNode = nullptr;

    initActions();
}

void Scene::updateTable() {
    if (currentTable != nullptr) {
        QVector<QVector<int>> matrix = graphModel.toMatrix();
        currentTable->clear();
        currentTable->setRowCount(matrix.size());
        currentTable->setColumnCount(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {

                QTableWidgetItem *widget = new QTableWidgetItem();
                widget->setText(QString::number(matrix[i][j]));
                currentTable->setItem(i,j,widget);
            }
        }
    }
}

void Scene::writeHistory() {
    // +------
    if (currentGraph < historyVector.size() - 1) {
        //Удаляем всё, что находится впереди:
        historyVector.remove(currentGraph+1, historyVector.size()-1-currentGraph);
    }

    historyVector.push_back(graphModel);
    currentGraph = historyVector.size()-1;

    //qDebug() << "Written history " << currentGraph ;
}

void Scene::undo() {
    if (currentGraph >= historyVector.size())
        currentGraph = historyVector.size();

    if (currentGraph > 0) {
        graphModel = historyVector[--currentGraph];
        redraw();
    }

    //qDebug() << "Undo. Current graph: " << currentGraph;
    updateTable();
}

void Scene::redo() {
    if (currentGraph < 0)
        currentGraph = 0;

    if (currentGraph < historyVector.size()) {
        graphModel = historyVector[currentGraph++];
        redraw();
    }
    //qDebug() << "Redo. Current graph: " << currentGraph;
    updateTable();
}

int Scene::histSize() const {
    return historyVector.size();
}

int Scene::histIndex() const {
    return currentGraph;
}

void Scene::setTableWidget(QTableWidget *widget) {
    currentTable = widget;
}

void Scene::setActions(const QList<QAction *> list) {
    actions = list;
}

void Scene::addAction(QAction *action) {
    actions.push_back(action);
}

void Scene::addNodeAction(QAction *action) {
    actionsNode.push_back(action);
}

void Scene::addVertex(const QPointF &coordinates) {
    writeHistory();
    graphModel.addVertex(coordinates);
    updateTable();
}

void Scene::addLoop() {
    if (activeVertex != nullptr) {
        writeHistory();
        graphModel.addNode(activeVertex, activeVertex, 50);
        activeVertex = nullptr;
        changeMode(NONE);
        updateTable();
    }
}

void Scene::addConnection() {
    if (activeVertex != nullptr) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Укажите вес"),
                                             tr("Осуществите ввод целого числа:"), QLineEdit::Normal, "1", &ok);

        if (ok && !text.isEmpty()) {
            bufw = text.toInt();

            writeHistory();
            changeMode(CONNECT);
            activeVertex->color = CL_SELECTED;
        }
        else {
            QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте добавить ребро ещё раз");
        }
    }
}

void Scene::addUConnection() {
    if (activeVertex != nullptr) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Укажите вес"),
                                             tr("Осуществите ввод целого числа:"), QLineEdit::Normal, "1", &ok);

        if (ok && !text.isEmpty()) {
            bufw = text.toInt();

            writeHistory();
            changeMode(UCONNECT);
            activeVertex->color = CL_SELECTED;
        }
        else {
            QMessageBox::critical(this, "Вы ввели неверное значение.", "Попробуйте добавить ребро ещё раз");
        }
    }
}

void Scene::destroyNode() {

    if (activeNode != nullptr) {
        writeHistory();
        for (auto &node_t : graphModel.nodes) {
            for (auto &node_v : node_t) {
                if (node_v == *activeNode) {
                    node_t.removeOne(node_v);
                    updateTable();
                    activeNode = nullptr;
                    return;
                }
            }
        }
        updateTable();
        activeNode = nullptr;
    }
}

void Scene::destroyVertex() {
    if (activeVertex != nullptr) {
        writeHistory();
        changeMode(DESTROY);
        graphModel.deleteVertex(activeVertex);
        activeVertex = nullptr;
        changeMode(NONE);
        updateTable();
    }
}

void Scene::moveNode() {
    if (activeNode != nullptr) {
        //writeHistory();
        changeMode(MOVE_CENTER);
    }
}

void Scene::moveVertex() {
    if (activeVertex != nullptr) {
        //writeHistory();
        changeMode(MOVE);
        activeVertex->color = CL_SELECTED;
    }
}

void Scene::swapNode() {
    if (activeNode != nullptr){
        writeHistory();
        graphModel.reverseNode(activeNode);
        activeNode = nullptr;
        updateTable();
    }
}

void Scene::appendNode() {
    if (activeNode != nullptr) {
        writeHistory();

        MVertex* from = graphModel.getVertexById(activeNode->parent);
        MVertex* to = graphModel.getVertexById(activeNode->data);

        graphModel.addNode(to, from, activeNode->w);
        activeNode = nullptr;
        updateTable();
    }
}

void Scene::addText(const QString &text) {
    placedText = text;
    redraw();
}

void Scene::clearText() {
    placedText.clear();
}

void Scene::matrixChanged(int row, int column, int w, bool remove) {
    try {
        MVertex *from = graphModel.getVertexByIndex(row);
        MVertex *to = graphModel.getVertexByIndex(column);
        MVertexNode* node = graphModel.getNodeById(from->id, to->id);

        writeHistory();
        if (node != nullptr) {

            if (remove && w == 0) {
                graphModel.deleteNode(from, to, node->w);
            } else
                node->w = w;
        } else {
            //Создаём новое ребро с запрошенным весом
            if (!(row == 0 && column == 0 && w == 0))
                graphModel.addNode(from, to, w);
        }

    } catch (int exception) {
        if (exception == MConstants::not_exists)
            qDebug() << "Error. Not exists Vertex";
    }




    redraw();

}

void Scene::changeMode(const MModes mode) {
    currentMode = mode;
}

void Scene::clear() {
    activeVertex = supportVertex = nullptr;
    activeNode = nullptr;
    scene->clear();

    clearText();
    updateTable();
    unpalliteAll();
    redraw();
}

void Scene::free() {
    graphModel.clear();
    clear();
}

void Scene::palliteVertex(MVertex *vertex, MColor color) {
    if (vertex != nullptr)
        vertex->color = color;

    redraw();
}

void Scene::palliteVertexById(unsigned id, MColor color) {
    MVertex* currentVertex = graphModel.getVertexById(id);
    if (currentVertex != nullptr) {
        palliteVertex(currentVertex, color);
    }

    redraw();
}

void Scene::unpalliteAll() {
    for (auto& it : graphModel.Vertexs)
        it.color = CL_DEFAULT;

}

Scene::~Scene() {
    clear();
}

void Scene::mouseReleaseEvent(QMouseEvent *event) {
    QPointF coordinates = mapToScene(event->pos());
    lastRPoint = coordinates;

    if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::LeftButton) {

        unpalliteAll();

        if (currentMode == MOVE && activeVertex != nullptr) {
            activeVertex->color = CL_DEFAULT;
            activeVertex = nullptr;
            changeMode(NONE);
        }

        if (currentMode == CONNECT && activeVertex != nullptr) {
            supportVertex = graphModel.getVertexByPos(coordinates);
            if (supportVertex != nullptr) {
                graphModel.addNode(activeVertex, supportVertex, bufw);
                activeVertex->color = CL_DEFAULT;
                activeVertex = supportVertex = nullptr;
                changeMode(NONE);
            }
        }

        if (currentMode == UCONNECT && activeVertex != nullptr) {
            supportVertex = graphModel.getVertexByPos(coordinates);
            if (supportVertex != nullptr) {
                graphModel.addUNode(activeVertex, supportVertex, bufw);
                activeVertex->color = CL_DEFAULT;
                activeVertex = supportVertex = nullptr;
                changeMode(NONE);
            }
        }

        if (currentMode == DESTROY && activeVertex != nullptr) {
            graphModel.deleteVertex(activeVertex);
            activeVertex = nullptr;
            changeMode(NONE);
        }

        if (currentMode == MOVE_CENTER && activeNode != nullptr) {
            activeNode->center = coordinates;
            activeNode = nullptr;
            changeMode(NONE);
        }

        if (currentMode == CREATE) {
            addVertex(coordinates);
        }

        updateTable();

    } else if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::MiddleButton) {
        addVertex(coordinates);
    } else {
        if ((activeVertex = graphModel.getVertexByPos(coordinates)) != nullptr) {
            QMenu mainMenu(this);
            mainMenu.addActions(actions);
            mainMenu.exec(this->mapToGlobal(event->pos()));
        }

        if ((activeNode = graphModel.getNodeByPos(coordinates)) != nullptr) {
            QMenu mainMenu(this);
            mainMenu.addActions(actionsNode);
            mainMenu.exec(this->mapToGlobal(event->pos()));
        }
    }

    redraw();
}

void Scene::mouseMoveEvent(QMouseEvent *event) {
    QPointF coordinates = mapToScene(event->pos());

    if (currentMode == MOVE && activeVertex != nullptr) {
        activeVertex->point = coordinates;
        redraw();
    } else if (currentMode == MOVE_CENTER && activeNode != nullptr) {
        activeNode->center.setX(coordinates.x());
        activeNode->center.setY(coordinates.y());
        redraw();
    }
}

void Scene::redraw()
{
    scene->clear();

    if (!placedText.isEmpty()) {
        QGraphicsTextItem* text = scene->addText(placedText);
        text->setPos(scene->width()-40, scene->height()-20);
        placedText.clear();
    }

    for (auto &it : graphModel.Vertexs) {

        QGraphicsEllipseItem *item = scene->addEllipse(it.point.x()-(MConstants::Vertex_diam / 2), it.point.y()-(MConstants::Vertex_diam / 2), MConstants::Vertex_diam, MConstants::Vertex_diam);

        if (it.color == CL_SELECTED)
            item->setBrush(Qt::gray);
        else if (it.color == CL_VISITED)
            item->setBrush(Qt::red);
        else if (it.color == CL_RED)
            item->setBrush(Qt::red);
        else if (it.color == CL_BLUE)
            item->setBrush(Qt::blue);
        else if (it.color == CL_GRAY)
            item->setBrush(Qt::gray);
        else if (it.color == CL_YELLOW)
            item->setBrush(Qt::yellow);
        else if (it.color == CL_GREEN)
            item->setBrush(Qt::green);

        QGraphicsTextItem *text = scene->addText(/*QString::number(graphModel.Vertexs.indexOf(it)+1) + "id: " + */QString::number(it.id));
        text->setPos(it.point.x()-MConstants::Vertex_diam/2, it.point.y()-MConstants::Vertex_diam/3);


        int index = graphModel.Vertexs.indexOf(it);


        for (auto &kt : graphModel.nodes[index]) {
            QPen linePen;
            linePen.setWidth(lineWidth);

            //Классифицируем на явление петли
            QGraphicsTextItem *text = scene->addText(QString::number(kt.w));

            text->setPos(kt.center.x(), kt.center.y());

            int delta = 0;

            if (it.id == kt.data) { //Петля
                delta = MConstants::Vertex_diam / 3;
            }

            QGraphicsLineItem* begin = scene->addLine(it.point.x()-delta, it.point.y()+delta, kt.center.x(), kt.center.y());

            begin->setPen(linePen);

            MVertex* tempVertex = graphModel.getVertexById(kt.data);

            QGraphicsLineItem* endl = scene->addLine(kt.center.x(), kt.center.y(), tempVertex->point.x()+delta, tempVertex->point.y() - delta);

            QBrush brush;

            linePen.setColor(Qt::red);
            endl->setPen(linePen);

            scene->addEllipse(kt.center.x()-(MConstants::point_center / 2), kt.center.y()-(MConstants::point_center / 2), MConstants::point_center, MConstants::point_center);

        }
    }
}


