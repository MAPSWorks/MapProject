#include "qgsrect.h"

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


