#include "qgsfeatuefactory.h"

QGSFeatueFactory::QGSFeatueFactory(QGraphicsScene *scene)
{
    this->scene = scene;
}

QGraphicsItem* QGSFeatueFactory::addPoint(QGSLayer *lyr, double X, double Y)
{
    QGraphicsItem *point = scene->addEllipse(X, Y, 5, 5);
    point->setParentItem(lyr);

    return point;
}
