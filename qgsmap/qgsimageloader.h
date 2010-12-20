#ifndef QGSIMAGELOADER_H
#define QGSIMAGELOADER_H

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include <QObject>

#include "qgsmapinfo.h"


class QGSImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit QGSImageLoader(QString urlString, QObject *parent = 0);

private:
    QNetworkAccessManager *netManager;


private slots:
    void netReply(QNetworkReply* reply);
};

#endif // QGSIMAGELOADER_H
