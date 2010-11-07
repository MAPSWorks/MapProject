#ifndef QGSRECT_H
#define QGSRECT_H

#include <QObject>

class QGSRect : public QObject
{
    Q_OBJECT
public:
     QGSRect() {xMin = xMax = yMin = yMax = 0;}
     QGSRect(double xMin, double yMin, double xMax, double yMax);

signals:

public slots:

private:
    double xMin;
    double yMin;
    double xMax;
    double yMax;

};

#endif // QGSRECT_H
