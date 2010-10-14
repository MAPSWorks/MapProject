#ifndef QGSFEATUEFACTORY_H
#define QGSFEATUEFACTORY_H

#include <QGraphicsScene>
#include "qgslayer.h"

class QGSLayer;

class QGSFeatueFactory
{
public:
    QGSFeatueFactory(QGraphicsScene *scene);

    QGraphicsItem* addPoint(QGSLayer *lyr, double X, double Y);


private:
    QGraphicsScene *scene;


};

#endif // QGSFEATUEFACTORY_H
