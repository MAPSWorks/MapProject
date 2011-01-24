#include "qgsmap.h"

#include <QGLWidget>
#include <QtDebug>
#include <QApplication>
#include <QDir>


QGSMap::QGSMap(QWidget *parent) :
    QGraphicsView(parent)
{
#ifndef QT_NO_OPENGL
   setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

   //nulls and spells
   serverSettings = NULL;


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

QGraphicsScene* QGSMap::loadMap(QString mapName)
{
    if(serverSettings != NULL)
    {
        setMapInfo(getServerSettings()->getMapInfo(mapName));
        if(scene() != NULL)
        {
            scene()->clear();
        }

        if(getMapInfo() != NULL)
        {
            QGraphicsScene *scene = new QGraphicsScene;
            featureFactory = new QGSFeatueFactory(scene);

            setScene(scene);
            setMapCanvas();
            setCurrentZoom(3);
            setCacheDir(".");
            setCacheDir("cache/" + QString::number(getMapInfo()->getMapSrs()) + "/" + getMapInfo()->getMapName() + "/" + QString::number(getCurrentZoom()));

            paintMap();

            return scene;
        }
        return NULL;
    }
    else
    {
        qDebug() << "Server settings are not defined!";
        return NULL;
    }

}

QGSSettings* QGSMap::getServerSettings()
{
    return this->serverSettings;
}

bool QGSMap::setServerSettings(QString serverHost, int EPSG, int serverPort)
{
    serverSettings = new QGSSettings(serverHost, EPSG, serverPort);

    if(serverSettings->getConnectionState() == QGSSettings::Available)
    {
        return true;
    }
    else
    {
        serverSettings = NULL;
        qDebug() << "Unable to connect";
        return false;
    }
}


void QGSMap::setMapInfo(QGSMapInfo *mapInfo)
{
    this->mapInfo = mapInfo;
}

QGSMapInfo* QGSMap::getMapInfo()
{
    return this->mapInfo;
}

void QGSMap::paintMap(bool reloadMap)
{
    QGSCoordinateTransform ct;
    QPointF centerPoint = getMapInfo()->getBoundingBox().center();

    QPoint ptZero = ct.metersToTile(centerPoint, getCurrentZoom());
    QPoint ptPxZero = ct.metersToPixels(centerPoint, getCurrentZoom());

    QGSRect bbox = ct.getTileBounds(ptZero.x(), ptZero.y(), getCurrentZoom());

    //init the coordinate transform

    float L = bbox.getMaxX().toFloat() - bbox.getMinX().toFloat();
    float x = centerPoint.x() - bbox.getMinX().toFloat();

    float l = getMapInfo()->getTileWidth();

    float x1 = (x/L)*l;


    int hTiles = ((float)width() / 256) + 1;
    int vTiles = ((float)height() / 256) + 1;

    int si = 0;
    int sj = 0;

    for(int i=(ptZero.x()-1);i<(ptZero.x()+hTiles);i++)
    {
        for(int j=(ptZero.y()-1);j<(ptZero.y()+vTiles);j++)
        {
            requestImageFile(i, j, si, sj);
            si++;
        }
        sj++;
    }

    QGSLayer *can = getMapCanvas();

    can->setPos((-ptPxZero.x()+width()/2), (-ptPxZero.y()+height()/2));
}

void QGSMap::requestImageFile(int xTile, int yTile, int xNum, int yNum)
{
    QGSCoordinateTransform ct;

    QGSRect bbox = ct.getTileBounds(xTile, yTile, getCurrentZoom());
    bbox.clearPlus();

    //to complex! maybe variables for bbox and stuff?
    QString urlBuffer;
    urlBuffer.append( "http://" );
    urlBuffer.append( getServerSettings()->getServerHost() );
    urlBuffer.append( ":" );
    urlBuffer.append( QString::number(getServerSettings()->getServerPort()) );

    urlBuffer.append( "/geoserver/gwc/service/wms/" );
    urlBuffer.append( "?LAYERS=" ).append( getMapInfo()->getMapName() );
    urlBuffer.append( "&FORMAT=").append("image/png").append("&SERVICE=WMS&VERSION=1.1.1&" );
    urlBuffer.append( "REQUEST=GetMap&STYLES=&EXCEPTIONS=application/vnd.ogc.se_inimage&" );
    urlBuffer.append( "SRS=EPSG:").append(QString::number(getMapInfo()->getMapSrs())).append("&BBOX=" );
    urlBuffer.append( bbox.getMinX() ).append( "," );
    urlBuffer.append( bbox.getMinY() ).append( "," );
    urlBuffer.append( bbox.getMaxX() ).append( "," );
    urlBuffer.append( bbox.getMaxY() );
    urlBuffer.append( "&WIDTH=").append(QString::number(getMapInfo()->getTileWidth())).append("&HEIGHT=").append(QString::number(getMapInfo()->getTileHeight()));



    QGSImageLoader *iLoader = new QGSImageLoader(urlBuffer, xTile, yTile, xNum, yNum, this);
    imageLoaders.append(iLoader);
    connect(iLoader, SIGNAL(imageLoaded(QString,int)), this, SLOT(recieveImageFile(QString,int)));



}

void QGSMap::setCurrentZoom(int zoom)
{
    this->currentZoom = zoom;
}

int QGSMap::getCurrentZoom()
{
    return this->currentZoom;
}



QDir QGSMap::setCacheDir(QString cachePath)
{
    if(!cacheDir.exists(cachePath))
        cacheDir.mkpath(cachePath);

    cacheDir = QDir(cachePath);

    return cacheDir;
}

QDir QGSMap::getCacheDir()
{
    return cacheDir;
}

void QGSMap::recieveImageFile(QString fileName, int loaderId)
{
    QPixmap imagePixmap = QPixmap(fileName);
    QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem(imagePixmap);

    QGSImageLoader *imgLoad = getLoaderById(loaderId);
    int tx = imgLoad->getTileNum(X, false)*256;
    int ty = imgLoad->getTileNum(Y, false)*256;

    imgItem->setPos(tx, ty);
    imgItem->setParentItem(getMapCanvas());

    scene()->addItem(imgItem);

    for(int i=0;i<imageLoaders.count();i++)
    {
        QGSImageLoader *iLoader = imageLoaders.at(i);
        if(iLoader->getLoaderId() == loaderId)
        {
            imageLoaders.removeAt(i);
            disconnect(iLoader, SIGNAL(imageLoaded(QString,int)), this, SLOT(recieveImageFile(QString,int)));
            //delete iLoader;
            break;
        }
    }
}

QGSLayer* QGSMap::getMapCanvas()
{
    return mapCanvas;

}

void QGSMap::setMapCanvas()
{
    if(mapCanvas != NULL)
        clearMapCanvas();

    mapCanvas = new QGSLayer(13116, "bckgrnd_original");

}

void QGSMap::clearMapCanvas()
{
    mapCanvas = NULL;
    delete mapCanvas;
}

QGSImageLoader* QGSMap::getLoaderById(int loaderId)
{
    for(int i=0;i<imageLoaders.count();i++)
    {
        QGSImageLoader *iLoader = imageLoaders.at(i);
        if(iLoader->getLoaderId() == loaderId)
            return iLoader;
    }

    return NULL;
}

QTransform QGSMap::getWorldToScreen()
{
    QTransform tr;
    double scale = 1;

    tr.translate(0, 0);
    tr.scale(scale, -(scale));

    if(getMapInfo() != NULL)
    {
        tr.translate(-getMapInfo()->getBoundingBox().getMinX().toDouble(), -getMapInfo()->getBoundingBox().getMaxY().toDouble());
    }

    return tr;
}
