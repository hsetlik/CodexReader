#ifndef QTUTIL_H
#define QTUTIL_H
#include <QColor>

struct MyQtUtil
{
    static QColor colorLerp(const QColor& colorA, const QColor& colorB, float p);
};

#endif // QTUTIL_H
