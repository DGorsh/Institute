#include "solution_12.h"

Solution_12::Solution_12(const MGraphObject& graphObject) :  graphObject( graphObject) {

}

QString Solution_12::Prim() {
    QString Answer = "";
    QVector<QVector<int>> g = graphObject.toMatrix();
    int n = g.size();
    QVector<bool> used (n);
    QVector<int> min_e (n, INF), sel_e (n, -1);
    min_e[0] = 0;
    for (int i=0; i<n; i++) {
        int v = -1;
        for (int j=0; j<n; j++)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        if (min_e[v] == INF) {
            Answer = "No MST!";
            return Answer;
        }

        used[v] = true;
        if (sel_e[v] != -1)
            Answer += "Начало: " + QString::number(v) + " | Конец: " + QString::number(sel_e[v]);

        for (int to=0; to<n; ++to)
            if ((g[v][to] < min_e[to]) && (g[v][to] != 0)) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
        Answer += "\n";
    }
    return "" + Answer;
}


QString Solution_12::Kruskal() {
    int n = graphObject.toMatrix().size();
    QString Result = "";
    QVector < QPair < int, QPair<int,int> > > g; // вес - вершина 1 - вершина 2
    QVector<QVector<int>> TempAdj = graphObject.toMatrix();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (TempAdj[i][j] != 0) {
                QPair<int, int> Temp1 = QPair<int, int>(i,j);
                QPair<int, QPair<int, int>> Temp2 = QPair<int, QPair<int, int>>(TempAdj[i][j], Temp1);
                g.push_back(Temp2);
            }
        }
    }
    int m = g.size();
    int cost = 0;
    QVector < QPair<int,int> > res;

    qSort (g.begin(), g.end());
    QVector<int> tree_id (n);
    for (int i=0; i<n; ++i)
        tree_id[i] = i;
    for (int i=0; i<m; ++i)
    {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        if (tree_id[a] != tree_id[b])
        {
            cost += l;
            res.push_back (QPair<int, int>(a, b));
            int old_id = tree_id[b],  new_id = tree_id[a];
            for (int j=0; j<n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }
    for (int i = 0;i<res.size(); i++) {
        Result += "Начало: " + QString::number(res[i].first) + " | Конец: " + QString::number(res[i].second)+"\n";
    }
    return Result;
}

QString Solution_12::Boruvki() {
    /*QVector < QPair < int, QPair<int,int> > > a;
    QVector < QPair < int, QPair<int,int> > > mst;
    QVector < QPair < int, QPair<int,int> > > b;// вес - вершина 1 - вершина 2
    QVector<int> e;
    QVector<QVector<int>> Components;
    QVector<QVector<int>> TempAdj = graphObject.toMatrix();
    for (int i = 0; i < TempAdj.size(); i++) {
        for (int j = i; j < TempAdj.size(); j++) {
            if (TempAdj[i][j] != 0) {
                QPair<int, int> Temp1 = QPair<int, int>(i,j);
                QPair<int, QPair<int, int>> Temp2 = QPair<int, QPair<int, int>>(TempAdj[i][j], Temp1);
                a.push_back(Temp2);
            }
        }
    }
    e.resize(TempAdj.size());
    for (int E = 0; E < TempAdj.size(); E++) {
        int min_weight = INF;
        int edgeid = -1;
        for (int T = 0; T < a.size(); T++) {
            if (a[T].second.first == E) {
                if (a[T].first < min_weight) {
                    min_weight = a[T].first;
                    edgeid = T;
                }
            }
        }
        if (edgeid!= -1) {
            e[E] = edgeid;
        }
    }
    //связность
    for (int i = 0; i< e.size(); i++) {
        int begin = a[i].second.first, end = a[i].second.first;
        bool Finded;
        for(int j = 0; j<Components.size(); j++) {
            for(int k =0; k<Components[j].size(); k++) {
                int temp = Components[j][k];
                if ((a[temp].second.first == begin) || (a[temp].second.second == begin) || (a[temp].second.first == end) ||
                        (a[temp].second.second == end)) {
                    Components[j].push_back(i);
                } else {
                    Components.push_back(QVector<int>(1, i));
                }
            }
        }
    }*/
    int n = graphObject.toMatrix().size();
    QString Result = "";
    QVector < QPair < int, QPair<int,int> > > g; // вес - вершина 1 - вершина 2
    QVector<QVector<int>> TempAdj = graphObject.toMatrix();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (TempAdj[i][j] != 0) {
                QPair<int, int> Temp1 = QPair<int, int>(i,j);
                QPair<int, QPair<int, int>> Temp2 = QPair<int, QPair<int, int>>(TempAdj[i][j], Temp1);
                g.push_back(Temp2);
            }
        }
    }
    int m = g.size();
    int cost = 0;
    QVector < QPair<int,int> > res;

    qSort (g.begin(), g.end());
    QVector<int> tree_id (n);
    for (int i=0; i<n; ++i)
        tree_id[i] = i;
    for (int i=0; i<m; ++i)
    {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        if (tree_id[a] != tree_id[b])
        {
            cost += l;
            res.push_back (QPair<int, int>(a, b));
            int old_id = tree_id[b],  new_id = tree_id[a];
            for (int j=0; j<n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }

    for (int i = 0;i<res.size(); i++) {
        Result += "Начало: " + QString::number(res[i].first) + ", Конец: " + QString::number(res[i].second)+"\n";
    }
    return Result;
}

void Solution_12::run() {
    this->savedResult = MAnswer<QString>("This is a simple result");
}

Solution_12::~Solution_12() {

}

int Solution_12::min_value (QVector<int> Vector) {
    int index = 0;
    for (int i = 0; i < Vector.size(); i++) {
        if (Vector[i] < Vector[index]) {
            index = i;
        };
    }
    return index;
};
