#ifndef QGSXMLPARSER_H
#define QGSXMLPARSER_H

#include <qdom.h>
#include "qgsmapinfo.h"
#include "qgscoordinatetransform.h"

class QGSMapInfo;
class QGSCoordinateTransform;

class QGSXmlParser : public QDomDocument
{
public:
    QGSXmlParser();

    QList<QGSMapInfo*> parseMapList(QString SRS, int tileWidth=256, int tileHeight=256);

};

#endif // QGSXMLPARSER_H
