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
    enum tileAxis {X , Y};

    explicit QGSImageLoader(QString imageURL = "", int xTile = 0, int yTile = 0, int xNum = 0, int yNum = 0, QObject *parent = 0, bool forceReload = false);


    int getLoaderId();
    QFile getImageFile();
    void setTileNum(int xTile, int yTile, int xNum, int yNum);
    int getTileNum(int axis, bool actual = true);


signals:
    void imageLoaded(QString fileName, int loaderId);

public slots:
    void saveImage();

private:
    QFile imageFile;
    QNetworkAccessManager *netManager;
    int loaderId;
    bool forceReload;
    int xTile;
    int yTile;
    int xNum;
    int yNum;

    void getImage(QString imageName = "");
    void setImageFile();
    void setLoaderId(int loaderId);


private slots:
    void netReply(QNetworkReply* reply);


};

#endif // QGSIMAGELOADER_H
