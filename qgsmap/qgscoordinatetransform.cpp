#include "qgscoordinatetransform.h"

//QGSCoordinateTransform::QGSCoordinateTransform(QObject *parent) :
//    QObject(parent)
//{
//}

double QGSCoordinateTransform::getResolution(int zoom)
{
    double res = this->initialResolution / pow(2, zoom);
    return res;
}


int QGSCoordinateTransform::getZoom(double resolution)
{
    int zoom;
    zoom = log2(initialResolution / resolution);
    return zoom;
}

QPointF QGSCoordinateTransform::latLonToMeters(double x, double y)
{
    return latLonToMeters(QPointF(x, y));
}

QPointF QGSCoordinateTransform::latLonToMeters(QPointF pt)
{
    double mx = 0;
    double my = 0;

    mx = pt.y() * originShift / 180.0;
    my = log( tan((90 + pt.x()) * M_PI / 360.0 )) / (M_PI / 180.0);

    my = my * originShift / 180.0;

    return QPointF(mx, my);
}

QPointF QGSCoordinateTransform::metersToLatLon(double x, double y)
{
    return metersToLatLon(QPointF(x, y));
}

QPointF QGSCoordinateTransform::metersToLatLon(QPointF pt)
{
    double lat = 0;
    double lon = 0;

    lon = (pt.x() / originShift) * 180.0;
    lat = (pt.y() / originShift) * 180.0;

    lat = 180 / M_PI * (2 * atan( exp( lat * M_PI / 180.0)) - M_PI / 2.0);

    return QPointF(lat, lon);
}

QPoint QGSCoordinateTransform::metersToPixels(double x, double y, int zoom)
{
    return metersToPixels(QPointF(x, y), zoom);
}

QPoint QGSCoordinateTransform::metersToPixels(QPointF pt, int zoom)
{
    int px = 0;
    int py = 0;

    double res = getResolution( zoom );
    px = (pt.x() + originShift) / res;
    py = (pt.y() + originShift) / res;

    return QPoint(px, py);
}

QPointF QGSCoordinateTransform::pixelsToMeters(int x, int y, int zoom)
{
    return pixelsToMeters(QPoint(x, y), zoom);
}

QPointF QGSCoordinateTransform::pixelsToMeters(QPoint pt, int zoom)
{
    double mx = 0;
    double my = 0;
    double res = getResolution( zoom );

    mx = pt.x() * res - originShift;
    my = pt.y() * res - originShift;

    return QPointF(mx, my);
}

QPoint QGSCoordinateTransform::pixelsToTile(int x, int y)
{
    return pixelsToTile(QPoint(x, y));
}

QPoint QGSCoordinateTransform::pixelsToTile(QPoint pt)
{
    int tx = 0;
    int ty = 0;

    tx = int( ceil( (float)pt.x() / tileWidth ) - 1 );
    ty = int( ceil( (float)pt.y() / tileHeight ) - 1 );

    return QPoint(tx, ty);
}

QGSRect QGSCoordinateTransform::getTileBounds(int x, int y, int zoom)
{
    return getTileBounds(QPoint(x, y), zoom);
}

QGSRect QGSCoordinateTransform::getTileBounds(QPoint pt, int zoom)
{
    QPointF minP;
    QPointF maxP;

    int mix = pt.x()*tileWidth;
    int miy = pt.y()*tileHeight;

    int maxx = (pt.x()+1)*tileWidth;
    int may = (pt.y()+1)*tileHeight;

    minP = pixelsToMeters( mix, miy, zoom );
    maxP = pixelsToMeters( maxx, may, zoom );

    return QGSRect(minP.x(), minP.y(), maxP.x(), maxP.y());
}

QPoint QGSCoordinateTransform::metersToTile(double x, double y, int zoom)
{
    return metersToTile(QPoint(x, y), zoom);
}

QPoint QGSCoordinateTransform::metersToTile(QPointF pt, int zoom)
{
    QPoint result = metersToPixels(pt, zoom);

    return pixelsToTile(result);
}

QPoint QGSCoordinateTransform::toGoogle(int x, int y, int zoom)
{
    return toGoogle(QPoint(x, y), zoom);
}

QPoint QGSCoordinateTransform::toGoogle(QPoint pt, int zoom)
{
    int x = pt.x();
    int y = (pow(2,zoom) - 1) - pt.y();

    return QPoint(x, y);
}

void QGSCoordinateTransform::setGoogleTiling()
{
    this->googleTile = true;
}

void QGSCoordinateTransform::setTMSTiling()
{
    this->googleTile = false;
}
