#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = ui->gsMap->loadMap();

    scene->clear();

    QPixmap pix("lol.png");
    QGSLayer *lyr = ui->gsMap->addLayer(1, "Test");
    QGraphicsLineItem *line = scene->addLine(0,0,30,35);

    QGraphicsPixmapItem *itm = scene->addPixmap(pix);

    line->setParentItem(lyr);
    itm->setParentItem(lyr);

    line->setZValue(1);
    itm->setZValue(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QGSLayer *lyr = ui->gsMap->getLayer(1);

    if(lyr->isVisible())
        lyr->setVisible(false);
    else
        lyr->setVisible(true);


}
