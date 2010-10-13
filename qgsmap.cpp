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

QGSLayer* QGSMap::addLayer(int layerId, QString layerName)
{
    QGSLayer *lyr = new QGSLayer;

    lyr->setId(layerId);
    lyr->setName(layerName);

    scene()->addItem(lyr);

    return lyr;
}

bool QGSMap::deleteLayer(int layerId)
{
    QGSLayer *lyr = getLayer(layerId);

    delete lyr;

        if(getLayer(layerId) == NULL)
            return true;
        else
            return false;
}

bool QGSMap::deleteLayer(QString layerName)
{
    QGSLayer *lyr = getLayer(layerName);

    delete lyr;

        if(getLayer(layerName) == NULL)
            return true;
        else
            return false;
}

QGraphicsScene * QGSMap::loadMap(QString mapName)
{
    QGraphicsScene *scene = new QGraphicsScene;

    if(!mapName.isEmpty())
        ;

    if(this->scene() != NULL)
        this->scene()->clear();

    setScene(scene);

    return scene;
}

