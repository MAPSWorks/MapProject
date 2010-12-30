#include "qgsrect.h"
#include <QRegExp>

QString QGSRect::getMinX()
{
    return this->xMin;
}

QString QGSRect::getMaxX()
{
    return this->xMax;
}

QString QGSRect::getMinY()
{
    return this->yMin;
}

QString QGSRect::getMaxY()
{
    return this->yMax;
}

QPointF QGSRect::center()
{
    double x = xMin.toDouble() + (xMax.toDouble() - xMin.toDouble())/2;
    double y = yMin.toDouble() + (yMax.toDouble() - yMin.toDouble())/2;

    return QPointF(x, y);
}

void QGSRect::clearPlus()
{
    xMin.remove(QRegExp("[+]."));
    yMin.remove(QRegExp("[+]."));
    xMax.remove(QRegExp("[+]."));
    yMax.remove(QRegExp("[+]."));
}


