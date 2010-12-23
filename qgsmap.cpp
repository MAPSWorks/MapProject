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

            setCurrentResolution(getMapInfo()->getMapResolution());
            setCacheDir(".");
            setCacheDir("cache/" + QString::number(getMapInfo()->getMapSrs()) + "/" + getMapInfo()->getMapName() + "/" + QString::number(getCurrentResolution()));

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

    for(int t=-256;t <= 256;t=t+256)
    {
        requestImageFile(-256, t);
        requestImageFile(0, t);
        requestImageFile(256, t);
    }

}

void QGSMap::requestImageFile(int xMin, int yMax)
{
    QGSRect bbox = getImageBoundingBox(xMin, yMax);
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

void QGSMap::setCurrentResolution(double resolution)
{
    this->currentResolution = resolution;
}

double QGSMap::getCurrentResolution()
{
    return this->currentResolution;
}

void QGSMap::wheelEvent(QWheelEvent *event)
{
//    double d = event->delta();
//    double rf = 1 + d/1024;
//    double cr = getCurrentResolution();

//    cr = cr + d/8;

//    scale( rf, rf );

    //qDebug() << getCurrentResolution() << cr << rf;

    //emit resolutionChanged(event->delta());
}

QGSRect QGSMap::getImageBoundingBox(QPoint pt)
{
    return getImageBoundingBox(pt.x(), pt.y());
}

QGSRect QGSMap::getImageBoundingBox(int xMin, int yMax)
{
    int x = xMin;
    int y = yMax;

    int w = getMapInfo()->getTileWidth();
    int h = getMapInfo()->getTileHeight();

    QTransform t = getWorldToScreen().inverted();

    double minx = 0;
    double miny = 0;
    double maxx = 0;
    double maxy = 0;

    t.map( (x+w), (y+h), &maxx, &miny );
    t.map( x, y, &minx, &maxy);

    QGSRect r;
    r.setRect(QString().setNum(minx), QString::number(miny), QString::number(maxx), QString::number(maxy));


    return r;
}

QTransform QGSMap::getWorldToScreen()
{
    QTransform tr;
    double scale = 1/getCurrentResolution();

    tr.translate(0, 0);
    tr.scale(scale, -(scale));

    if(getMapInfo() != NULL)
    {
        tr.translate(-getMapInfo()->getBoundingBox().getMinX().toDouble(), -getMapInfo()->getBoundingBox().getMaxY().toDouble());
    }

    return tr;
}

QPoint QGSMap::mapToScreen(double x, double y)
{
    return mapToScreen(QPointF(x, y));
}

QPoint QGSMap::mapToScreen(QPointF pt)
{
    QTransform t = getWorldToScreen();
    QPointF dest = t.map(pt);

    return QPoint((int)dest.x(), (int)dest.y());
}

QPointF QGSMap::screenToMap(int x, int y)
{
    return screenToMap(QPoint(x, y));
}

QPointF QGSMap::screenToMap(QPoint pt)
{
    QPointF src = pt;
    QPointF dest;
    QTransform t = getWorldToScreen().inverted();
    dest = t.map(src);

    return dest;
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

    scene()->addItem(imgItem);

    for(int i=0;i<imageLoaders.count();i++)
    {
        QGSImageLoader *iLoader;
        if(iLoader->getLoaderId() == loaderId)
        {
            imageLoaders.removeAt(i);
            disconnect(iLoader, SIGNAL(imageLoaded(QString,int)), this, SLOT(recieveImageFile(QString,int)));
            delete iLoader;
            break;
        }
    }
}
