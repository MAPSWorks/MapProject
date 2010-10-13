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

    QGSLayer* addLayer(int layerId, QString layerName, QGraphicsScene *scene);

signals:

public slots:

private:

private slots:

protected:
    QList<QGSLayer*> layers;

};

#endif // QGSMAP_H
