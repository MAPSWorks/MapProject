#ifndef QGSIMAGELOADER_H
#define QGSIMAGELOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

#include "../qgsmap.h"

class QGSImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit QGSImageLoader(QString imageURL = "", QString fileName = "", QObject *parent = 0, bool forceReload = false);


    int getLoaderId();
    QFile getImageFile();

signals:
    void imageLoaded(QString fileName, int loaderId);

public slots:
    void saveImage();

private:
    QFile imageFile;
    QNetworkAccessManager *netManager;
    int loaderId;
    bool forceReload;
    QEventLoop eventLoop;

    void getImage(QString imageName = "");
    void setImageFile(QString fileName);
    void setLoaderId(int loaderId);

private slots:
    void netReply(QNetworkReply* reply);


};

#endif // QGSIMAGELOADER_H
