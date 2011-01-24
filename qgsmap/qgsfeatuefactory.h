#ifndef QGSFEATUEFACTORY_H
#define QGSFEATUEFACTORY_H

#include <QGraphicsScene>
#include "qgslayer.h"

class QGSLayer;

class QGSFeatueFactory
{
public:
    QGSFeatueFactory(QGraphicsScene *scene);

    QGraphicsItem* addPoint(double X, double Y, QGSLayer *lyr);


private:

    QGraphicsScene *scene;
    QGraphicsScene* getScene();

};

#endif // QGSFEATUEFACTORY_H
