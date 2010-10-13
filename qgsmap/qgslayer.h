#ifndef QGSLAYER_H
#define QGSLAYER_H

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>
#include <QPolygonF>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>

class QGSLayer : public QGraphicsItem
{
public:
    QGSLayer(QGraphicsItem *parent = 0);

    int getId();
    bool setId(int layerId);

    QString getName();
    bool setName(QString layerName);

signals:

public slots:

private:
    int layerId;
    QString layerName;

};

#endif // QGSLAYER_H
