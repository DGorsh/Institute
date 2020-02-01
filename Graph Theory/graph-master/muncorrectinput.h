#ifndef MUNCORRECTINPUT_H
#define MUNCORRECTINPUT_H

#include <QException>


class MUncorrectInput : public QException
{
public:

    void raise() const override;

    MUncorrectInput *clone() const override;

    const char* what();
};

#endif // MUNCORRECTINPUT_H
