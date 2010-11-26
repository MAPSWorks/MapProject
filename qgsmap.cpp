#include "qgsmap.h"

#include <QGLWidget>
#include <QtDebug>
#include <QApplication>

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
        setMapInfo(getServerSettings()->getMapInfo(mapName));
        setCurrentResolution(getMapInfo()->getMapResolution());

        if(mapInfo != NULL)
        {
            QGraphicsScene *scene = new QGraphicsScene;

            setScene(scene);

            featureFactory = new QGSFeatueFactory(scene);

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

void QGSMap::paintMap()
{

    int xCount = width() / getMapInfo()->getTileWidth() + 1;
    int yCount = height() / getMapInfo()->getTileHeight() + 1;

    QGSRect bbox = getMapInfo()->getBoundingBox();

    QPoint p0 = mapToScreen(bbox.getMinX().toDouble(), bbox.getMinY().toDouble());

    int startX =  -p0.x() / getMapInfo()->getTileWidth();
    int startY = ( p0.y() - height() ) / getMapInfo()->getTileHeight();

    int imgXstart = p0.x() + startX * getMapInfo()->getTileWidth();
    int imgYstart = p0.y() - startY * getMapInfo()->getTileHeight();
    //
//    for ( int y = startY; y <= startY + yCount; y++ )
//    {

//    }

    QGSRect ibbox = getImageBoundingBox(getMapInfo()->getBoundingBox().getMinX().toDouble(), getMapInfo()->getBoundingBox().getMaxY().toDouble());

    getImageFile(ibbox);
}

QString QGSMap::getImageFile(QGSRect bbox)
{
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
    urlBuffer.append( "&WIDTH=" ).append( QString::number(width())).append( "&HEIGHT=" ).append( QString::number(height()) );

    //netManager->blockSignals(false);
    netManager->get(QNetworkRequest(QUrl(urlBuffer)));

    return "s";

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

QGSRect QGSMap::getImageBoundingBox(double xMin, double yMax)
{
    QPoint scrPt = mapToScreen(xMin, yMax);

    int x = scrPt.x();
    int y = scrPt.y();

    int w = getMapInfo()->getTileWidth();
    int h = getMapInfo()->getTileHeight();

    QTransform t = getWorldToScreen().inverted();

    double minx = 0;
    double miny = 0;
    double maxx = 0;
    double maxy = 0;

    t.map( (x+2*w), (y+2*h), &maxx, &miny );
    t.map( (x+w), (y+h), &minx, &maxy );

    QGSRect r;
    r.setRect(QString().setNum(minx), QString::number(miny), QString::number(maxx), QString::number(maxy));
    r.clearPlus();

    return r;
}

QTransform QGSMap::getWorldToScreen()
{
    QTransform tr;
    double scale = 1/getCurrentResolution();

    tr.translate( (double)width()/2, (double)height()/2 );
    tr.scale(scale, -(scale) );

    QPointF pt = getMapInfo()->getBoundingBox().center();

    tr.translate(-pt.x(), -pt.y());
    tr.toAffine();

    return tr;
}

QPoint QGSMap::mapToScreen(double x, double y)
{
    mapToScreen(QPointF(x, y));
}

QPoint QGSMap::mapToScreen(QPointF pt)
{
    QTransform t = getWorldToScreen();
    QPointF dest = t.map(pt);

    return QPoint((int)dest.x(), (int)dest.y());
}

QPointF QGSMap::screenToMap(int x, int y)
{
    screenToMap(QPoint(x, y));
}

QPointF QGSMap::screenToMap(QPoint pt)
{
    QPointF src = pt;
    QPointF dest;
    QTransform t = getWorldToScreen().inverted();
    dest = t.map(src);

    return dest;
}
