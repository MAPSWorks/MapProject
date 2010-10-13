#include "qgslayer.h"

QGSLayer::QGSLayer(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
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
