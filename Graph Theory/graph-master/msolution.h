/*
 * 2019, Maxim Degtyarev
 * Simple solution class
 * */

#include <mgraphobject.h>
#include <muncorrectinput.h>
#include <msolutionnotfound.h>
#include <manswer.h>

#include <QVector>
#include <QMessageBox>
#include <QtAlgorithms>


#ifndef MSOLUTION_H
#define MSOLUTION_H
#define INF 100000

typedef int distance;
typedef int parent;
typedef QVector<QVector<int>> MMatrix;

template <typename ANS_TYPE>
class MSolution
{
protected:
    QVector<MGraphObject> graphVector;
    MAnswer<ANS_TYPE> savedResult;

public:

    MSolution() {
        graphVector = QVector<MGraphObject>();
    }

    /*
     * Constructor of your solution
     * */
    MSolution(QVector<MGraphObject>& graphVector) {}

    /*
     * Start your solution
     * */
    virtual void run() {}

    /*
     * Returns result of your solution
     * */
    MAnswer<ANS_TYPE> result() const {
        return savedResult;
    }

    /*
     * Destructor
     * */
    virtual ~MSolution() {}


};


#endif // MSOLUTION_H
