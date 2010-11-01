#include "qgssettings.h"
#include <QtDebug>
#include <QStringList>


QGSSettings::QGSSettings(QString serverHost, int serverPort, QObject *parent) :
    QObject(parent)
{
    if(setServerHost(serverHost) && setServerPort(serverPort))
    {
        connectsAndSettings();
        testConection();
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
    else if(reply->url() == QUrl(testUrl + "/geoserver/gwc/service/wms?service=WMS&version=1.1.1&request=getcapabilities&tiled=true"))
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

QList<QString> QGSSettings::getMapList(int EPSG)
{
    mapList.clear();


    QString capableUrl = "http://";
    capableUrl.append(this->serverHost);
    capableUrl.append(":");
    capableUrl.append(QString::number(this->serverPort));
    capableUrl.append("/geoserver/gwc/service/wms?service=WMS&version=1.1.1&request=getcapabilities&tiled=true");

    netManager->get(QNetworkRequest(QUrl(capableUrl)));

    eventLoop.exec();

    xmlFile.open(QIODevice::ReadOnly);

    xmlParser.setContent(&xmlFile);

    QDomElement xmlRoot = xmlParser.documentElement();

    QDomNode node;

    node = xmlRoot.childNodes().at(1).childNodes().at(2).firstChild();

    while(!node.isNull())
    {
        if(node.nodeName() == "TileSet")
        {
            QDomNode tileSet = node.childNodes().at(0);

            if(tileSet.firstChild().nodeValue() == "EPSG:" + QString::number(EPSG))
            {
                QString value = node.childNodes().at(6).firstChild().nodeValue();

                if(value.split(":").count() == 1)
                    mapList.append(value);
            }

        }

         node = node.nextSibling();
    }




    xmlFile.close();

    return mapList;


}
