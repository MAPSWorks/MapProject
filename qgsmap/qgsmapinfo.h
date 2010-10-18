#ifndef QGSMAPINFO_H
#define QGSMAPINFO_H

#include <QObject>

class QGSMapInfo : public QObject
{
    Q_OBJECT
public:
    explicit QGSMapInfo();

    bool setMapName(QString mapName);
    QString getMapName();

signals:

public slots:

private:
    QString mapName;

};

#endif // QGSMAPINFO_H
