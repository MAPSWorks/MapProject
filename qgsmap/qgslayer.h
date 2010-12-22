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
    QGSLayer(int layerId = -1, QString layerName = "", QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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
