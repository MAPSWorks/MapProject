#ifndef QGSXMLPARSER_H
#define QGSXMLPARSER_H

#include <qdom.h>
#include "qgsmapinfo.h"

class QGSMapInfo;

class QGSXmlParser : public QDomDocument
{
public:
    QGSXmlParser();

    QList<QGSMapInfo*> parseMapList(QString SRS, int tileWidth=256, int tileHeight=256);

};

#endif // QGSXMLPARSER_H
