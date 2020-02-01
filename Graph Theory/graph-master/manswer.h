#ifndef MANSWER_H
#define MANSWER_H

#include <QString>
#include <QVector>
#include <mgraphobject.h>

template <typename T>
struct MAnswer
{
    T anotherObject;

    MAnswer(const T& anotherObject = T()) : anotherObject(anotherObject) {
    }

    friend QDebug operator << (QDebug deb, const MAnswer& self) {
        deb.nospace() << "MAnswer: [ " << self.anotherObject << " ]";
        return deb.maybeSpace();
    }

};

#endif // MANSWER_H
