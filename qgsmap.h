#ifndef QGSMAP_H
#define QGSMAP_H

#include <QGraphicsView>
#include "qgsmap/qgslayer.h"
#include "qgsmap/qgsfeatuefactory.h"
#include "qgsmap/qgsmapinfo.h"
#include "qgsmap/qgssettings.h"

class QGSLayer;
class QGSFeatueFactory;
class QGSSettings;
class QGSMapInfo;


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

    //server settings
    bool setServerSettings(QString serverHost = "localhost", int serverPort = 18080);
    QGSSettings* getServerSettings();


signals:

public slots:

private:
    bool mapLoaded;
    QGSSettings *serverSettings;
    QNetworkAccessManager *netManager;

    QList<QGSLayer*> layers;

    void initMap();
    void setMapInfo(QGSMapInfo *mapInfo);


private slots:
    void netReply(QNetworkReply* reply);

protected:

};

#endif // QGSMAP_H
