#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QStandardItemModel>

class TableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    void SetFormula(int, int, QString);
    void GetFormula(int, int);
    void ChangeData();

signals:

public slots:

private:
    QString formula;

};

#endif // TABLEMODEL_H
