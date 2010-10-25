#ifndef QGSSETTINGS_H
#define QGSSETTINGS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

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

    bool getServerInfo();

    bool setServerHost(QString serverHost = "localhost");
    bool setServerPort(int serverPort = 18080);

    QString getServerHost();
    int getServerPort();
    ConnectionState getConnectionState();

signals:

public slots:


private:
    QString serverHost;
    int serverPort;

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
