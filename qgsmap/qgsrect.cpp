#include "qgsrect.h"
#include <QRegExp>

QGSRect::QGSRect()
{
}

void QGSRect::setRect(QString xMin, QString yMin, QString xMax, QString yMax)
{
    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;
}

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
    double x = (xMax.toDouble() - xMin.toDouble())/2;
    double y = (yMax.toDouble() - yMin.toDouble())/2;

    return QPointF(x, y);
}

void QGSRect::clearPlus()
{
    xMin.remove(QRegExp("[+]."));
    yMin.remove(QRegExp("[+]."));
    xMax.remove(QRegExp("[+]."));
    yMax.remove(QRegExp("[+]."));
}


