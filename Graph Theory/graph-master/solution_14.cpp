#include <solution_14.h>

//Подразумевается, что граф неориентированный
QPair<MGraphObject, int> Solution_14::pallite_BFS(MGraphObject &in_graph, int fromId) {


    for (auto& it : in_graph.getVertexs_link()) {
        it.color = CL_DEFAULT;
    }
    //Перед заливкой граф будет пересобираться
    QVector<MColor> numOfColors = {CL_RED, CL_BLUE, CL_GREEN, CL_GRAY, CL_BLACK, CL_YELLOW}; //Список всех доступных цветов для раскраски

    MMatrix matrix = in_graph.toMatrix();
    MGraphObject graph;

    int k = 0;
    for (auto& it : in_graph.getVertexs_link()) {
        graph.addVertex(it.point);
    }
    //Теперь сборка графа

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j] != 0) {
               graph.addNode(graph.getVertexById(i), graph.getVertexById(j), matrix[i][j]);
            }
        }
    }


    QVector<QVector<MColor>> groups(graph.countVertexs(), QVector<MColor>()); //Группы цветов

    QQueue<int> Q;

    graph.getVertexById(fromId)->flag = MConstants::flag_visited;
    graph.getVertexById(fromId)->color = CL_RED;

    Q.push_back(fromId);

    groups[graph.getIndexByVertexId(graph.getVertexById(fromId)->id)].push_back(CL_RED);

    while(!Q.isEmpty()) {
        unsigned v = Q.front();
        Q.pop_front();

        int index = graph.getIndexByVertexId(v);

        if (index == MConstants::not_exists)
            throw MUncorrectInput();

        MColor unusedColor = graph.getVertexById(v)->color;

        for (auto& node : graph.getNodes_link()[index]) {
            /*
                 * Здесь будет браться меньший элемент
                 *
                 * */
            MVertexNode* minNode = graph.getMinWNodeById(node.parent, node.data);

            MVertex* vertex = graph.getVertexById(minNode->data);

            if (vertex->color == CL_DEFAULT) {
                vertex->flag = MConstants::flag_visited;
                //Теперь переходим вот здесь к раскраске
                //Находимся в вершине - нужно обойти все вершины, связанные c текущим

                //Берем индекс
                int tmp_index = graph.getIndexByVertexId(vertex->id);

                int activeColor = 0;


                for (auto& it : graph.getNodes_link()[tmp_index]){
                    while (groups[graph.getIndexByVertexId(it.data)].indexOf(numOfColors[activeColor]) != MConstants::not_exists) {
                        activeColor++;
                    }
                }


                groups[tmp_index].push_back(numOfColors[activeColor]);

                vertex->color = numOfColors[activeColor];





                Q.push_back(vertex->id);
            }
        }
    }

    int max = 0;
    for (auto& it : graph.getVertexs_link()) {
        if (it.color - CL_RED+1 > max)
            max = it.color - CL_RED+1;
    }

    return QPair<MGraphObject, int> (graph, max);

}
