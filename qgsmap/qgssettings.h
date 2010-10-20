#ifndef QGSSETTINGS_H
#define QGSSETTINGS_H

#include <QObject>
<<<<<<< HEAD
=======
#include <QNetworkAccessManager>
#include <QNetworkReply>
>>>>>>> acbcfe76a74a984cdf3bca8d3d5c589c0d4a6ffa

class QGSSettings : public QObject
{
    Q_OBJECT
<<<<<<< HEAD
public:
    explicit QGSSettings(QObject *parent = 0);
=======
    Q_ENUMS(TestReply)
public:
    enum TestReply{
        NotAvailable = 0,
        Available = 1,
        Unknown = 2
    };


    explicit QGSSettings(QString serverHost = "localhost", int serverPort = 8080, QObject *parent = 0);

    bool getServerInfo();

    bool setServerHost(QString serverHost = "localhost");
    bool setServerPort(int serverPort = 8080);

    QString getServerHost();
    int getServerPort();
>>>>>>> acbcfe76a74a984cdf3bca8d3d5c589c0d4a6ffa

signals:

public slots:

<<<<<<< HEAD
=======
private:
    QString serverHost;
    int serverPort;
    TestReply testReply;

    QNetworkAccessManager *netManager;

    bool testConection();
    void connectsAndSettings();
    void setTestReply(TestReply tr);

private slots:

    void netReply(QNetworkReply* reply);
    TestReply getTestReply();


>>>>>>> acbcfe76a74a984cdf3bca8d3d5c589c0d4a6ffa
};

#endif // QGSSETTINGS_H
