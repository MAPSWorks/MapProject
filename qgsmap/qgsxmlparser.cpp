#include "qgsxmlparser.h"

#include <QtDebug>
#include <QStringList>

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

        if(layer.attribute("queryable") == "1" && srsExists && mapName.split(":").count() == 1)
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

            double mapResolution = (xMax.toDouble() - xMin.toDouble()) / (double)tileWidth;

            mi->setMapName(mapName);
            mi->setMapSrs(SRS.toInt());
            mi->setBoundingBox(xMin, yMin,xMax, yMax);
            mi->setMapResolution(mapResolution);
            mi->setTileSize(tileWidth, tileHeight);

            mapList.append(mi);
        }
    }



    return mapList;
}

QList<QDomNode> QGSXmlParser::getNodesByName(QString nodeName)
{
    QList<QDomNode> nodesList;

    QDomElement xmlRoot = documentElement();

    xmlRoot.elementsByTagName("Layers");

    QDomNode node = xmlRoot;

    for(int i=0;i<node.childNodes().count();i++)
    {

    }

    return nodesList;
}
