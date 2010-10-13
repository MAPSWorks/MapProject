#include "qgsmap.h"

#include <QGLWidget>

QGSMap::QGSMap(QWidget *parent) :
    QGraphicsView(parent)
{

#ifndef QT_NO_OPENGL
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

}

QList<QGSLayer*> QGSMap::getLayers()
{
    layers.clear();

    for(int i=0;i<items().count();i++)
    {
        QGSLayer *itm = (QGSLayer*)items().at(i);

        if(itm->topLevelItem() == itm)
            layers.append(itm);
    }

    return layers;
}

QGSLayer* QGSMap::getLayer(int layerId)
{
    foreach(QGSLayer *lyr, getLayers())
    {
        if(lyr->getId() == layerId)
        {
            return lyr;
            break;
        }
    }
    return 0;
}

QGSLayer* QGSMap::getLayer(QString layerName)
{
    foreach(QGSLayer *lyr, getLayers())
    {
        if(lyr->getName() == layerName)
        {
            return lyr;
            break;
        }
    }
    return 0;
}

QGSLayer* QGSMap::addLayer(int layerId, QString layerName, QGraphicsScene *scene)
{
    QGraphicsRectItem *item = scene->addRect(QRectF());
    QGSLayer *lyr = (QGSLayer *)item;
    lyr->setId(layerId);
    lyr->setName(layerName);

    return lyr;
}
