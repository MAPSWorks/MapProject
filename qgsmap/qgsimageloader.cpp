#include "qgsimageloader.h"

#include <QtDebug>

QGSImageLoader::QGSImageLoader(QString imageURL, int xTile, int yTile, int xNum, int yNum, QObject *parent, bool forceReload) :
    QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    this->forceReload = forceReload;
    setLoaderId(rand());
    setTileNum(xTile, yTile, xNum, yNum);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netReply(QNetworkReply*)));

    netManager->get(QNetworkRequest(QUrl(imageURL)));


}

void QGSImageLoader::netReply(QNetworkReply *reply)
{
    QByteArray data;

    data = reply->readAll();

    if(!imageFile.exists())
    {
        imageFile.open(QIODevice::WriteOnly);
        imageFile.write(data);
        imageFile.close();
    }

    emit imageLoaded(imageFile.fileName(), getLoaderId());

}

void QGSImageLoader::saveImage()
{

}

void QGSImageLoader::setLoaderId(int loaderId)
{
    this->loaderId = loaderId;
}

int QGSImageLoader::getLoaderId()
{
    return this->loaderId;
}

void QGSImageLoader::setImageFile()
{
    QDir cacheDir;
    QGSMap *map = (QGSMap*)parent();
    QString filePath;

    QString fileName = QString::number(xTile)+ "_" + QString::number(yTile) + ".png";

    cacheDir = map->getCacheDir();
    filePath = cacheDir.path()+"/"+fileName;
    imageFile.setFileName(filePath);

}

void QGSImageLoader::setTileNum(int xTile, int yTile, int xNum, int yNum)
{
    this->xTile = xTile;
    this->yTile = yTile;
    this->xNum = xNum;
    this->yNum = yNum;

    setImageFile();
}

 int QGSImageLoader::getTileNum(int axis, bool actual)
 {
     switch(axis)
     {
     case X:
         if(actual)
             return this->xTile;
         else
             return this->xNum;
         break;
     case Y:
         if(actual)
             return this->yTile;
         else
             return this->yNum;
         break;
     }
     return NULL;
 }
