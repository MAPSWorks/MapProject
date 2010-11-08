#include "qgsmap.h"

#include <QGLWidget>
#include <QtDebug>

QGSMap::QGSMap(QWidget *parent) :
    QGraphicsView(parent)
{
#ifndef QT_NO_OPENGL
   setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

   //nulls and spells
   serverSettings = NULL;
   netManager = new QNetworkAccessManager(this);

   //built-in options

   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   setDragMode(QGraphicsView::ScrollHandDrag); //reimplementation inevitable

   //netManager->blockSignals(true);
   connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netReply(QNetworkReply*)));

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
        mapInfo = getMapInfoByName(mapName);

        if(mapInfo != NULL)
        {
            QGraphicsScene *scene = new QGraphicsScene;

            setScene(scene);

            featureFactory = new QGSFeatueFactory(scene);

            //to complex! maybe variables for bbox and stuff?
            QString urlBuffer;
            urlBuffer.append( "http://" );
            urlBuffer.append( getServerSettings()->getServerHost() );
            urlBuffer.append( ":" );
            urlBuffer.append( QString::number(getServerSettings()->getServerPort()) );

            urlBuffer.append( "/geoserver/gwc/service/wms/" );
            urlBuffer.append( "?LAYERS=" ).append( getMapInfo()->getMapName() );
            urlBuffer.append( "&FORMAT=image/png&SERVICE=WMS&VERSION=1.1.1&" );
            urlBuffer.append( "REQUEST=GetMap&STYLES=&EXCEPTIONS=application/vnd.ogc.se_inimage&" );
            urlBuffer.append( "SRS=EPSG:").append(QString::number(getMapInfo()->getMapSrs())).append("&BBOX=" );
            urlBuffer.append( getMapInfo()->getBoundingBox().getMinX() ).append( "," );
            urlBuffer.append( getMapInfo()->getBoundingBox().getMinY() ).append( "," );
            urlBuffer.append( getMapInfo()->getBoundingBox().getMaxX() ).append( "," );
            urlBuffer.append( getMapInfo()->getBoundingBox().getMaxY() );
            urlBuffer.append( "&WIDTH=" ).append( QString::number(getMapInfo()->getTileWidth()) ).append( "&HEIGHT=" ).append( QString::number(getMapInfo()->getTileHeight()) );

            //netManager->blockSignals(false);
            netManager->get(QNetworkRequest(QUrl(urlBuffer)));
            //

            return scene;
        }
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

bool QGSMap::setServerSettings(QString serverHost, int serverPort)
{
    serverSettings = new QGSSettings(serverHost, serverPort);

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


QGSMapInfo* QGSMap::getMapInfoByName(QString mapName)
{
    QList<QGSMapInfo*> list = getServerSettings()->getMapList(41001);

    for(int i=0;i<list.count();i++)
    {
        QGSMapInfo* mi = list.at(i);

        if(mi->getMapName() == mapName)
        {
            return mi;
            break;
        }

    }

    return NULL;
}

QGSMapInfo* QGSMap::getMapInfo()
{
    return this->mapInfo;
}

void QGSMap::netReply(QNetworkReply *reply)
{
    QByteArray data;
    QFile pngFile;

    data = reply->readAll();

    pngFile.setFileName("temp.png");
    pngFile.open(QIODevice::WriteOnly);

    pngFile.write(data);

    pngFile.close();

    QPixmap pix("temp.png");

    scene()->addPixmap(pix);

   // netManager->blockSignals(true);

}
