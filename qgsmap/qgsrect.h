#ifndef QGSRECT_H
#define QGSRECT_H

#include <QObject>
#include <QPointF>

class QGSRect
{
public:
    explicit QGSRect();

    void setRect(QString xMin, QString yMin, QString xMax, QString yMax);
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
