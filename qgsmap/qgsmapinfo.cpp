#include "qgsmapinfo.h"

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


