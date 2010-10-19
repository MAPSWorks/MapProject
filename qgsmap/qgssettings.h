#ifndef QGSSETTINGS_H
#define QGSSETTINGS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QGSSettings : public QObject
{
    Q_OBJECT
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

signals:

public slots:

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


};

#endif // QGSSETTINGS_H
