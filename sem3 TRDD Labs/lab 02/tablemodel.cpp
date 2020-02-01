#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QStandardItemModel(parent)
{
}

void TableModel::SetFormula(int row, int column, QString text) {
    this->formula = this->item(row, column)->text();
    if (this->formula[0] == '=') {
    }
};
