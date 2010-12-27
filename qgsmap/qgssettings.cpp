#include "qgssettings.h"
#include <QtDebug>
#include <QStringList>


QGSSettings::QGSSettings(QString serverHost, int EPSG, int serverPort, QObject *parent) :
    QObject(parent)
{
    if(setServerHost(serverHost) && setServerPort(serverPort))
    {
        connectsAndSettings();
        testConection();
        this->EPSG = EPSG;
    }
    else
    {
        qDebug() << "Unable to set server host|port";
    }

}

bool QGSSettings::setServerHost(QString serverHost)
{
    this->serverHost = serverHost;

    if(this->serverHost == serverHost)
        return true;
    else
        return false;
}

bool QGSSettings::setServerPort(int serverPort)
{
    this->serverPort = serverPort;

    if((this->serverPort == serverPort))
        return true;
    else
        return false;
}

QString QGSSettings::getServerHost()
{
    return this->serverHost;
}

int QGSSettings::getServerPort()
{
    return this->serverPort;
}

void QGSSettings::testConection()
{
    QString url = "http://";
    url.append(this->serverHost);
    url.append(":");
    url.append(QString::number(this->serverPort));
    url.append("/test");

    netManager->get(QNetworkRequest(QUrl(url)));

    if(getConnectionState() == Unknown)
        eventLoop.exec();

}

void QGSSettings::netReply(QNetworkReply *reply)
{
    QString testUrl = "http://";
    testUrl.append(this->serverHost);
    testUrl.append(":");
    testUrl.append(QString::number(this->serverPort));


    if(reply->url() == QUrl(testUrl + "/test"))
    {
        if(reply->error() == 203)
            setConnectionState(Available);
        else
            setConnectionState(NotAvailable);

        eventLoop.exit();
    }
    else if(reply->url() == QUrl(testUrl + "/geoserver/gwc/service/wms?SERVICE=WMS&VERSION=1.1.1&REQUEST=getcapabilities&TILED=true"))
    {
        if(reply->error() != 404)
        {
            QByteArray data;

            data = reply->readAll();

            xmlFile.setFileName("temp.xml");
            xmlFile.open(QIODevice::WriteOnly);

            xmlFile.write(data);

            xmlFile.close();

            eventLoop.exit();

        }


    }
}

QGSSettings::ConnectionState QGSSettings::getConnectionState()
{
    return connectionState;
}

void QGSSettings::setConnectionState(ConnectionState connectionState)
{
    this->connectionState = connectionState;
}

void QGSSettings::connectsAndSettings()
{
    netManager = new QNetworkAccessManager(this);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netReply(QNetworkReply*)));

    setConnectionState(Unknown);

}

QList<QGSMapInfo*> QGSSettings::getMapList(bool reload, int tileWidth, int tileHeight)
{
    if(reload || mapList.count() == 0)
    {
        mapList.clear();


        QString capableUrl = "http://";
        capableUrl.append(this->serverHost);
        capableUrl.append(":");
        capableUrl.append(QString::number(this->serverPort));
        capableUrl.append("/geoserver/gwc/service/wms?SERVICE=WMS&VERSION=1.1.1&REQUEST=getcapabilities&TILED=true");

        netManager->get(QNetworkRequest(QUrl(capableUrl)));

        eventLoop.exec();

        xmlFile.open(QIODevice::ReadOnly);

        xmlParser.setContent(&xmlFile);

        mapList = xmlParser.parseMapList(QString::number(EPSG), tileWidth, tileHeight);


        xmlFile.close();
    }

    return mapList;


}

QGSMapInfo* QGSSettings::getMapInfo(QString mapName)
{
    if(!mapList.isEmpty())
    {

        for(int i=0;i<mapList.count();i++)
        {
            QGSMapInfo* mi = mapList.at(i);

            if(mi->getMapName() == mapName)
            {
                return mi;
                break;
            }

        }
    }

    return NULL;
}
