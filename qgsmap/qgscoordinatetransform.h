#ifndef QGSCOORDINATETRANSFORM_H
#define QGSCOORDINATETRANSFORM_H

#include <QObject>
#include <qmath.h>
#include <QPoint>

#include "qgsmap/qgsrect.h"

class QGSCoordinateTransform : public QObject
{
    Q_OBJECT
public:
    explicit QGSCoordinateTransform(int tileSize = 256)
    {
          this->tileSize = tileSize;
          this->initialResolution = 2 * M_PI * 6378137 / this->tileSize;
          this->originShift = 2 * M_PI * 6378137 / 2;
    }

    QPointF latLonToMeters(QPointF pt);
    QPointF latLonToMeters(double x, double y);

    QPointF metersToLatLon(QPointF pt);
    QPointF metersToLatLon(double x, double y);

    QPoint metersToPixels(QPointF pt, int zoom = 0);
    QPoint metersToPixels(double x, double y, int zoom = 0);

    QPoint pixelsToTile(QPoint pt);
    QPoint pixelsToTile(int x, int y);

    QPointF pixelsToMeters(QPoint pt, int zoom = 0);
    QPointF pixelsToMeters(int x, int y, int zoom = 0);

    double getResolution(int zoom = 0);
    int getZoom(double resolution);

    QGSRect getTileBounds(int x, int y, int zoom = 0);
    QGSRect getTileBounds(QPoint pt, int zoom = 0);


signals:

public slots:

private:
    int tileSize;
    double originShift;
    double initialResolution;

};

#endif // QGSCOORDINATETRANSFORM_H
