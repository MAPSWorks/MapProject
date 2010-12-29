#ifndef QGSMAP_H
#define QGSMAP_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QDir>

#include "qgsmap/qgslayer.h"
#include "qgsmap/qgsfeatuefactory.h"
#include "qgsmap/qgsmapinfo.h"
#include "qgsmap/qgssettings.h"
#include "qgsmap/qgsrect.h"
#include "qgsmap/qgsimageloader.h"
#include "qgsmap/qgscoordinatetransform.h"

class QGSLayer;
class QGSFeatueFactory;
class QGSSettings;
class QGSMapInfo;
class QGSRect;
class QGSImageLoader;
class QGSCoordinateTransform;


class QGSMap : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QGSMap(QWidget *parent = 0);

    //pubclasses
    QGSFeatueFactory *featureFactory;


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

    void setCurrentZoom(int zoom);
    int getCurrentZoom();

    //server settings
    bool setServerSettings(QString serverHost = "localhost", int EPSG = 900913, int serverPort = 18080);
    QGSSettings* getServerSettings();

    //cache dir
    QDir setCacheDir(QString cachePath);
    QDir getCacheDir();


signals:
    void resolutionChanged(double resolution);
    void mouseMoveEvent(QMouseEvent *event);

public slots:

private:
    bool mapLoaded;
    QGSMapInfo *mapInfo;
    QGSSettings *serverSettings;
    QNetworkAccessManager *netManager;
    int currentZoom;
    QDir cacheDir;
    QList<QGSImageLoader*> imageLoaders;
    QGSLayer *mapCanvas;

    QList<QGSLayer*> layers;
    QStringList mapFormatsList;

    void initMap();
    void setMapInfo(QGSMapInfo *mapInfo);

    void requestImageFile(int xMin, int yMax);
    QTransform getWorldToScreen();

    void setMapCanvas();
    void clearMapCanvas();
    QGSLayer* getMapCanvas();



private slots:
    void recieveImageFile(QString fileName, int loaderId);
    void paintMap(bool reloadMap = false);

protected:

};

#endif // QGSMAP_H
