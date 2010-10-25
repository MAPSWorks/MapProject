#include "qgssettings.h"
#include <QtDebug>

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
    testUrl.append("/test");

    if(reply->url() == QUrl(testUrl))
    {
        if(reply->error() == 203)
            setConnectionState(Available);
        else
            setConnectionState(NotAvailable);

        eventLoop.exit();
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
