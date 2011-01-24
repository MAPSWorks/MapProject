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
    explicit QGSCoordinateTransform(int tileWidth = 256, int tileHeight = 256, bool googleTiling = true)
    {
          this->tileWidth = tileWidth;
          this->tileHeight = tileHeight;
          this->initialResolution = 2 * M_PI * 6378137 / this->tileWidth;
          this->originShift = 2 * M_PI * 6378137 / 2;
          this->googleTile = googleTiling;
    }

    QPointF latLonToMeters(QPointF pt);
    QPointF latLonToMeters(double x, double y);

    QPointF metersToLatLon(QPointF pt);
    QPointF metersToLatLon(double x, double y);

    QPoint metersToPixels(QPointF pt, int zoom = 0);
    QPoint metersToPixels(double x, double y, int zoom = 0);

    QPoint pixelsToTile(QPoint pt);
    QPoint pixelsToTile(int x, int y);

    QPoint metersToTile(QPointF pt, int zoom = 0);
    QPoint metersToTile(double x, double y, int zoom = 0);

    QPointF pixelsToMeters(QPoint pt, int zoom = 0);
    QPointF pixelsToMeters(int x, int y, int zoom = 0);

    double getResolution(int zoom = 0);
    int getZoom(double resolution);

    QGSRect getTileBounds(int x, int y, int zoom = 0);
    QGSRect getTileBounds(QPoint pt, int zoom = 0);

    void setGoogleTiling();
    void setTMSTiling();

    QPoint toGoogle(QPoint pt, int zoom = 0);
    QPoint toGoogle(int x, int y, int zoom = 0);



signals:

public slots:

private:
    int tileWidth;
    int tileHeight;
    double originShift;
    double initialResolution;
    bool googleTile;

};

#endif // QGSCOORDINATETRANSFORM_H
