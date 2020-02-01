#include <solution_0.h>

Solution_0::Solution_0(QVector<MGraphObject> &graphVector) : MSolution(graphVector) {

}

Solution_0::Solution_0() {}

void Solution_0::run() {
    this->savedResult = MAnswer<QString>("This is a simple result");
}

Solution_0::~Solution_0() {

}
