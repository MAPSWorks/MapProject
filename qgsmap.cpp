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

            setCurrentZoom(0);
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

    //int zoom = getCurrentZoom();
    requestImageFile(0,0);




}

void QGSMap::requestImageFile(int xMin, int yMax)
{
    QGSCoordinateTransform ct;

    QGSRect bbox = ct.getTileBounds(ct.pixelsToTile(0, 0));
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
   // urlBuffer.append( "&WIDTH=" ).append( QString::number(getMapInfo()->getTileWidth())).append( "&HEIGHT=" ).append( QString::number(getMapInfo()->getTileHeight()) );

    QString fileName = QString::number(xMin)+ "_" + QString::number(yMax) + ".png";

    QGSImageLoader *iLoader = new QGSImageLoader(urlBuffer, fileName, this);
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

    QStringList list = fileName.split("/");
    QString imagePos = list.at(list.count()-1);

    int tx;
    int ty;

    list = imagePos.split(".");
    imagePos = list.at(0);

    list = imagePos.split("_");

    tx = QString(list.at(0)).toInt();
    ty = QString(list.at(1)).toInt();

    imgItem->setPos(tx, ty);
//    imgItem->setParentItem(getMapCanvas());

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

    mapCanvas = new QGSLayer(0x01, "bckgrnd_original");

}

void QGSMap::clearMapCanvas()
{
    mapCanvas = NULL;
    delete mapCanvas;
}
