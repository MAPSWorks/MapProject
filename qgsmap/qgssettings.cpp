#include "qgssettings.h"
#include <QtDebug>

QGSSettings::QGSSettings(QString serverHost, int serverPort, QObject *parent) :
    QObject(parent)
{
    if(setServerHost(serverHost) && setServerPort(serverPort))
    {

    }
    else
        qDebug() << "Unable to set server host|port";


    connectsAndSettings();
    testConection();


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

bool QGSSettings::testConection()
{
    QString url = "http://";
    url.append(this->serverHost);
    url.append(":");
    url.append(QString::number(this->serverPort));
    url.append("/test");

    netManager->get(QNetworkRequest(QUrl(url)));

    if(getTestReply() == Unknown)
        eventLoop.exec();

    if(getTestReply() == Available)
    {
        setTestReply(Unknown);
        return true;
    }
    else
    {
        setTestReply(Unknown);
        return false;
    }


}

void QGSSettings::netReply(QNetworkReply *reply)
{
    QString url = "http://";
    url.append(this->serverHost);
    url.append(":");
    url.append(QString::number(this->serverPort));
    url.append("/test");

    if(reply->url() == QUrl(url))
    {
        if(reply->error() == 203)
            setTestReply(Available);
        else
            setTestReply(NotAvailable);

        eventLoop.exit();
    }
}

QGSSettings::TestReply QGSSettings::getTestReply()
{
    return testReply;
}

void QGSSettings::setTestReply(TestReply tr)
{
    testReply = tr;
}

void QGSSettings::connectsAndSettings()
{
    netManager = new QNetworkAccessManager(this);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netReply(QNetworkReply*)));

    setTestReply(Unknown);

}
