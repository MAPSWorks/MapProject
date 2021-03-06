#include "qgsxmlparser.h"

#include <QtDebug>
#include <QStringList>
#include <qmath.h>

QGSXmlParser::QGSXmlParser()
{
}

QList<QGSMapInfo*> QGSXmlParser::parseMapList(QString SRS, int tileWidth, int tileHeight)
{
    QList<QGSMapInfo*> mapList;

    QDomNodeList layersList = documentElement().elementsByTagName("Layer");

    for(int i=0;i<layersList.count();i++)
    {
        QDomElement layer = layersList.at(i).toElement();

        QString mapName = layer.elementsByTagName("Name").at(0).firstChild().nodeValue();
        QDomNodeList srsList = layer.elementsByTagName("SRS");

        bool srsExists = false;

        for(int i=0;i<srsList.count();i++)
        {
            if(srsList.at(i).firstChild().nodeValue() == QString("EPSG:").append(SRS))
            {
                srsExists = true;
                break;
            }
        }
//        QString x = layer.attribute();

        if(srsExists && mapName.split(":").count() == 1)
        {
            QGSMapInfo *mi = new QGSMapInfo;

            QDomNodeList bboxList = layer.elementsByTagName("BoundingBox");

            QString xMin;
            QString yMin;
            QString xMax;
            QString yMax;

            for(int i=0;i<bboxList.count();i++)
            {
                QDomElement bbox = bboxList.at(i).toElement();

                if(bbox.attribute("SRS") == QString("EPSG:").append(SRS))
                {
                    xMin = bbox.attribute("minx");
                    yMin = bbox.attribute("miny");
                    xMax = bbox.attribute("maxx");
                    yMax = bbox.attribute("maxy");

                    break;
                }
            }

            mi->setMapName(mapName);
            mi->setMapSrs(SRS.toInt());
            mi->setBoundingBox(xMin, yMin,xMax, yMax);
            mi->setTileSize(tileWidth, tileHeight);

            mapList.append(mi);
        }
    }



    return mapList;
}
