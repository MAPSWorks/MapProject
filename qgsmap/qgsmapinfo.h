#ifndef QGSMAPINFO_H
#define QGSMAPINFO_H

#include <QObject>
#include <QList>

#include "qgsrect.h"

class QGSRect;

class QGSMapInfo : public QObject
{
    Q_OBJECT
public:
    explicit QGSMapInfo();

    bool setMapName(QString mapName);
    QString getMapName();
    bool setMapSrs(int mapSrs);
    int getMapSrs();

    void setBoundingBox(QString xMin, QString yMin, QString xMax, QString yMax);
    QGSRect getBoundingBox();

    void setMapResolutions(QString mapResolutions);
    QList<double> getMapResolutions();

    void setTileWidth(int tileWidth = 256);
    int getTileWidth();

    void setTileHeight(int tileHeight = 256);
    int getTileHeight();

    void setTileSize(int tileWidth = 256, int tileHeight = 256);


signals:

public slots:

private:
    QString mapName;
    int mapSrs;
    QGSRect boundingBox;
    QList<double> mapResolutions;
    int tileWidth;
    int tileHeight;

};

#endif // QGSMAPINFO_H
