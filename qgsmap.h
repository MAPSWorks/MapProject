#ifndef QGSMAP_H
#define QGSMAP_H

#include <QGraphicsView>
#include "qgsmap/qgslayer.h"

class QGSLayer;

class QGSMap : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QGSMap(QWidget *parent = 0);

    QList<QGSLayer*> getLayers();

    QGSLayer* getLayer(int layerId);
    QGSLayer* getLayer(QString layerName);

    QGSLayer* addLayer(int layerId, QString layerName);

    bool deleteLayer(QString layerName);
    bool deleteLayer(int layerId);

    QGraphicsScene* loadMap(QString mapName = "");

signals:

public slots:

private:
    bool mapLoaded;
//    QGSMapInfo mapInfo;

    QList<QGSLayer*> layers;

private slots:

protected:


};

#endif // QGSMAP_H
