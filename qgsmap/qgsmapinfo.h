#ifndef QGSMAPINFO_H
#define QGSMAPINFO_H

#include <QObject>

#include "qgsrect.h"

class QGSMapInfo : public QObject
{
    Q_OBJECT
public:
    explicit QGSMapInfo();

    bool setMapName(QString mapName);
    QString getMapName();

    QGSRect boundingBox;


signals:

public slots:

private:
    QString mapName;
    int mapSrs;






};

#endif // QGSMAPINFO_H
