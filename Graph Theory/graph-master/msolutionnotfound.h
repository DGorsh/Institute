#ifndef MSOLUTIONNOTFOUND_H
#define MSOLUTIONNOTFOUND_H

#include <QException>

class MSolutionNotFound : public QException
{
public:
    const char *what();
};

#endif // MSOLUTIONNOTFOUND_H
