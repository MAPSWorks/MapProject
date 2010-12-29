#include "qgsmapinfo.h"

#include <QStringList>

QGSMapInfo::QGSMapInfo() :
    QObject()
{

}

QString QGSMapInfo::getMapName()
{
    return this->mapName;
}

bool QGSMapInfo::setMapName(QString mapName)
{
    this->mapName = mapName;

    if( (this->mapName == mapName) && !this->mapName.isEmpty())
        return true;
    else
        return false;
}

int QGSMapInfo::getMapSrs()
{
    return this->mapSrs;
}

bool QGSMapInfo::setMapSrs(int mapSrs)
{
    this->mapSrs = mapSrs;

    if( (this->mapSrs == mapSrs) && !this->mapSrs != 0)
        return true;
    else
        return false;
}

void QGSMapInfo::setBoundingBox(QString xMin, QString yMin, QString xMax, QString yMax)
{
    boundingBox = QGSRect(xMin, yMin, xMax, yMax);
}

QGSRect QGSMapInfo::getBoundingBox()
{
    return boundingBox;
}

//void QGSMapInfo::setMapResolution(double mapResolution)
//{
//    this->mapResolution = mapResolution;
//}

//double QGSMapInfo::getMapResolution()
//{
//    return this->mapResolution;
//}

void QGSMapInfo::setTileWidth(int tileWidth)
{
    this->tileWidth = tileWidth;
}

int QGSMapInfo::getTileWidth()
{
    return this->tileWidth;
}

void QGSMapInfo::setTileHeight(int tileHeight)
{
    this->tileHeight = tileHeight;
}

int QGSMapInfo::getTileHeight()
{
    return this->tileHeight;
}

void QGSMapInfo::setTileSize(int tileWidth, int tileHeight)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

//void QGSMapInfo::setZoomLevel(int zoomLevel)
//{
//    this->zoomLevel = zoomLevel;
//}

//int QGSMapInfo::getZoomLevel()
//{
//    return this->zoomLevel;
//}

