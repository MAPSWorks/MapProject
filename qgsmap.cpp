#include "qgsmap.h"

#include <QGLWidget>

QGSMap::QGSMap(QWidget *parent) :
    QGraphicsView(parent)
{
#ifndef QT_NO_OPENGL
   setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

   //built-in options

   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   setDragMode(QGraphicsView::ScrollHandDrag); //reimplementation inevitable
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
    QGSLayer *lyr = new QGSLayer(layerId, layerName);

    scene()->addItem(lyr);
    lyr->setZValue(0);

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
    scene->setSceneRect(0, 0, 800, 600);

    mapInfo = new QGSMapInfo;
    serverSettings = new QGSSettings;

    if(mapInfo->setMapName(mapName))
    {

        if(this->scene() != NULL)
            this->scene()->clear();

        setScene(scene);

        featureFactory = new QGSFeatueFactory(scene);

        return scene;
    }
    else
    {
        return NULL;
    }
}

