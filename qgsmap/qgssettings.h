#ifndef QGSSETTINGS_H
#define QGSSETTINGS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <qdom.h>
#include <QFile>

#include "qgsmapinfo.h"
#include "qgsxmlparser.h"

class QGSMapInfo;
class QGSXmlParser;


class QGSSettings : public QObject
{
    Q_OBJECT
    Q_ENUMS(ConnectionState)
public:
    enum ConnectionState{
        NotAvailable = 0,
        Available = 1,
        Unknown = 2
    };

    explicit QGSSettings(QString serverHost = "localhost", int serverPort = 18080, QObject *parent = 0);

    //

    ///

    void getServerInfo();

    bool setServerHost(QString serverHost = "localhost");
    bool setServerPort(int serverPort = 18080);

    QString getServerHost();
    int getServerPort();
    ConnectionState getConnectionState();

    QList<QGSMapInfo*> getMapList(int EPSG = 41001, bool reload=false, int tileWidth=256, int tileHeight=256);
    QGSMapInfo* getMapInfo(QString mapName);

signals:

public slots:


private:
    QString serverHost;
    int serverPort;
    QList<QGSMapInfo*> mapList;

    QGSXmlParser xmlParser;
    QFile xmlFile;


    QEventLoop eventLoop;
    QNetworkAccessManager *netManager;
    ConnectionState connectionState;

    void testConection();

    void connectsAndSettings();


private slots:

    void netReply(QNetworkReply* reply);

    void setConnectionState(ConnectionState connectionState);


};

#endif // QGSSETTINGS_H
