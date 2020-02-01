#ifndef MSOLUTIONEXECUTOR_H
#define MSOLUTIONEXECUTOR_H

#include <msolution.h>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>

template<typename ANS_TYPE>
class MSolutionExecutor
{
private:
    MAnswer<ANS_TYPE> answer;
    QMainWindow* parent;

public:
    MSolutionExecutor() {

    }

    MSolutionExecutor(QMainWindow *parent, MSolution<ANS_TYPE> *solution) : parent(parent) {
        try {
            solution->run();
            answer = solution->result();
        } catch (MSolutionNotFound& ex) {
            QMessageBox::information(parent, "Ошибка", "Решение задачи не найдено. Попробуйте изменить входные данные");
        } catch (MUncorrectInput& ex) {
            QMessageBox::information(parent, "Ошибка", "Был осуществён некорректный ввод. Проверьте ввод ещё раз.");
        }
    }

    void asMessage() {
        //QMessageBox::information(parent, "Решение задачи", answer);
    }

    void asDebug() {
        qDebug() << "MSolutionExecutor: " << answer;
    }

    ~MSolutionExecutor() {

    }

};

#endif // MSOLUTIONEXECUTOR_H
