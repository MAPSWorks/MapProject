#ifndef QGSRECT_H
#define QGSRECT_H

#include <QObject>

class QGSRect
{
public:
    explicit QGSRect();

    void setRect(QString xMin, QString yMin, QString xMax, QString yMax);
    QString getMinX();
    QString getMaxX();
    QString getMinY();
    QString getMaxY();


signals:

public slots:

private:

    QString xMin;
    QString yMin;
    QString xMax;
    QString yMax;

};

#endif // QGSRECT_H
