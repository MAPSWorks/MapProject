#include "qgsimageloader.h"
#include <QDir>

#include "../qgsmap.h"

QGSImageLoader::QGSImageLoader(QString urlString, QObject *parent):
        QObject(parent)
{
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netReply(QNetworkReply*)));

    netManager->get(QNetworkRequest(QUrl(urlString)));
}

void QGSImageLoader::netReply(QNetworkReply *reply)
{
    QByteArray data;
    QFile pngFile;
    QDir cacheDir = QDir(".");
    QGSMapInfo *mi = ((QGSMap*)parent())->getMapInfo();

    int r = rand();

    data = reply->readAll();

    //


    if(!cacheDir.exists("cache"))
        cacheDir.mkdir("cache");

    cacheDir = QDir("cache");
    cacheDir.rmpath(".");

    if(!cacheDir.exists(QString::number(mi->getMapSrs())))
        cacheDir.mkdir(QString::number(mi->getMapSrs()));

    cacheDir = QDir("cache/"+QString::number(mi->getMapSrs()));

    if(!cacheDir.exists(mi->getMapName()))
        cacheDir.mkdir(mi->getMapName());



//    QString pth = cacheDir.path();
    pngFile.setFileName(cacheDir.path()+"/"+mi->getMapName()+"/"+QString::number(r)+"temp.png");
    pngFile.open(QIODevice::WriteOnly);

    pngFile.write(data);

    pngFile.close();
}
