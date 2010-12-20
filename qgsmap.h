#ifndef QGSMAP_H
#define QGSMAP_H

#include <QGraphicsView>
#include <QWheelEvent>

#include "qgsmap/qgslayer.h"
#include "qgsmap/qgsfeatuefactory.h"
#include "qgsmap/qgsmapinfo.h"
#include "qgsmap/qgssettings.h"
#include "qgsmap/qgsimageloader.h"
#include "qgsmap/qgsrect.h"

class QGSLayer;
class QGSFeatueFactory;
class QGSSettings;
class QGSMapInfo;
class QGSRect;
class QGSImageLoader;


class QGSMap : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QGSMap(QWidget *parent = 0);

    //pubclasses
    QGSFeatueFactory *featureFactory;
    QGSMapInfo *mapInfo;

    //layer operations
    QList<QGSLayer*> getLayers();

    QGSLayer* getLayer(int layerId);
    QGSLayer* getLayer(QString layerName);

    QGSLayer* addLayer(int layerId, QString layerName);

    bool deleteLayer(QString layerName);
    bool deleteLayer(int layerId);

    //map operations
    QGSMapInfo* getMapInfo();
    QGraphicsScene* loadMap(QString mapName = "");

    void setCurrentResolution(double resolution);

    double getCurrentResolution();

    QPoint mapToScreen(QPointF pt);
    QPoint mapToScreen(double x, double y);
    QPointF screenToMap(QPoint pt);
    QPointF screenToMap(int x, int y);

    //server settings
    bool setServerSettings(QString serverHost = "localhost", int serverPort = 18080);
    QGSSettings* getServerSettings();


signals:
    void resolutionChanged(double resolution);
    void mouseMoveEvent(QMouseEvent *event);

public slots:

private:
    bool mapLoaded;
    QGSSettings *serverSettings;
    QNetworkAccessManager *netManager;
    double currentResolution;

    QList<QGSLayer*> layers;
    QStringList mapFormatsList;

    void initMap();
    void setMapInfo(QGSMapInfo *mapInfo);
    void wheelEvent(QWheelEvent *event);
    QString getImageFile(int xMin, int yMax);
    QTransform getWorldToScreen();
    QGSRect getImageBoundingBox(int xMin, int yMax);
    QGSRect getImageBoundingBox(QPoint pt);



private slots:
    void netReply(QNetworkReply* reply);
    void paintMap();

protected:

};

#endif // QGSMAP_H
