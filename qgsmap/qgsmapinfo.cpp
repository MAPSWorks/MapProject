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
    boundingBox.setRect(xMin, yMin,xMax, yMax);
}

QGSRect QGSMapInfo::getBoundingBox()
{
    return boundingBox;
}

void QGSMapInfo::setMapResolutions(QString mapResolutions)
{
    QStringList list = mapResolutions.split(" ");

    for(int i=0;i<list.count();i++)
    {
        this->mapResolutions.append(list.at(i).toDouble());
    }
}

QList<double> QGSMapInfo::getMapResolutions()
{
    return this->mapResolutions;
}

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


