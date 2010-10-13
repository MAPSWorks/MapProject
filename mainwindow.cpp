#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene;

    QPixmap pix("lol.png");

    QGSLayer *lyr = ui->gsMap->addLayer(0, "Layer 1", scene);

    QGraphicsLineItem *line = scene->addLine(0,0,30,35);

    QGraphicsPixmapItem *itm = scene->addPixmap(pix);

    line->setParentItem(lyr);
    itm->setParentItem(lyr);

    line->setZValue(1);
    itm->setZValue(0);

    ui->gsMap->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QList<QGSLayer*> layers = ui->gsMap->getLayers();

    QGSLayer *lyr = layers.at(0);

    if(lyr->isVisible())
        lyr->setVisible(false);
    else
        lyr->setVisible(true);


}
