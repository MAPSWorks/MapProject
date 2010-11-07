#include "qgsrect.h"

QGSRect::QGSRect(double xMin, double yMin, double xMax, double yMax)
{
    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;
}
