#include "qgsimageloader.h"

#include <QtDebug>

QGSImageLoader::QGSImageLoader(QString imageURL, QString fileName, QObject *parent, bool forceReload) :
    QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    this->forceReload = forceReload;
    setLoaderId(rand());
    setImageFile(fileName);

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
    else
        qDebug() << "loaded";


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

bool QGSImageLoader::setImageFile(QString fileName)
{
    QDir cacheDir;
    QGSMap *map = (QGSMap*)parent();
    QString filePath;

    cacheDir = map->getCacheDir();
    filePath = cacheDir.path()+"/"+fileName + ".png";
    imageFile.setFileName(filePath);

}
