#ifndef QGSRECT_H
#define QGSRECT_H

#include <QObject>
#include <QPointF>

class QGSRect
{
public:
    explicit QGSRect()
    {
        QGSRect(0,0,0,0);
    }

    explicit QGSRect(QString xMin, QString yMin, QString xMax, QString yMax)
    {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
    }

    explicit QGSRect(double xMin, double yMin, double xMax, double yMax)
    {
        this->xMin = QString::number(xMin);
        this->xMax = QString::number(xMax);
        this->yMin = QString::number(yMin);
        this->yMax = QString::number(yMax);
    }

    QString getMinX();
    QString getMaxX();
    QString getMinY();
    QString getMaxY();

    QPointF center();
    void clearPlus();


signals:

public slots:

private:

    QString xMin;
    QString yMin;
    QString xMax;
    QString yMax;

};

#endif // QGSRECT_H
