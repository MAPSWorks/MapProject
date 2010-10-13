#include "qgslayer.h"

QGSLayer::QGSLayer(QString layerName, int layerId, QGraphicsItem *parent) :

    QGraphicsItem(parent)
{
}

QRectF QGSLayer::boundingRect() const
{
    return QRectF(10,10,10,10);
}

void QGSLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    //painter->drawRect(widget->rect());
}

QString QGSLayer::getName()
{
    return this->layerName;
}

bool QGSLayer::setName(QString layerName)
{
    this->layerName = QString(layerName);

    if(this->layerName == layerName)
        return true;
    else
        return false;
}

int QGSLayer::getId()
{
    return this->layerId;
}

bool QGSLayer::setId(int layerId)
{
    this->layerId = layerId;

    if(this->layerId == layerId)
        return true;
    else
        return false;
}
