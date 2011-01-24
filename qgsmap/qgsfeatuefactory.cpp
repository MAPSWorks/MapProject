#include "qgsfeatuefactory.h"

QGSFeatueFactory::QGSFeatueFactory(QGraphicsScene *scene)
{
    this->scene = scene;
}

QGraphicsScene* QGSFeatueFactory::getScene()
{
    return this->scene;
}

QGraphicsItem* QGSFeatueFactory::addPoint(double X, double Y, QGSLayer *parent)
{
    QGraphicsItem *point = getScene()->addEllipse(X, Y, 5, 5);
    point->setParentItem(parent);

    return point;
}
