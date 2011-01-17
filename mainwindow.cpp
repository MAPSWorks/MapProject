#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    ui->gsMap->setServerSettings("localhost"); //4326 900913 41001
    ui->gsMap->setServerSettings("10.254.53.144", 900913, 18080);

    if(ui->gsMap->getServerSettings() != NULL)
    {

        QList<QGSMapInfo*> list = ui->gsMap->getServerSettings()->getMapList();

        for(int i=0;i<list.count();i++)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(list.at(i)->getMapName());
            ui->listWidget->addItem(item);
        }

        connect(ui->gsMap, SIGNAL(mouseMoveEvent(QMouseEvent*)), this, SLOT(showCoords(QMouseEvent*)));
        connect(ui->gsMap, SIGNAL(tilesToLoad(int)), this, SLOT(setPBar(int)));
        connect(ui->gsMap, SIGNAL(tileLoaded()), this, SLOT(stepPBar()));

    }
    else
        qDebug() << "Server unreachable";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    disconnect(this, SLOT(showCoords(QMouseEvent*)));

    QGSMapInfo *mi = ui->gsMap->getServerSettings()->getMapInfo(ui->listWidget->currentItem()->text());

    ui->mapBox->setTitle(mi->getMapName());

    ui->srsLabel->setText(QString::number(mi->getMapSrs()));

    ui->xMinLbl->setText(mi->getBoundingBox().getMinX());
    ui->xMaxLbl->setText(mi->getBoundingBox().getMaxX());
    ui->yMinLbl->setText(mi->getBoundingBox().getMinY());
    ui->yMaxLbl->setText(mi->getBoundingBox().getMaxY());

    QGraphicsScene *scene = ui->gsMap->loadMap(mi->getMapName());

    if(scene != NULL)
    {

    }

    connect(ui->gsMap, SIGNAL(mouseMoveEvent(QMouseEvent*)), this, SLOT(showCoords(QMouseEvent*)));
}

void MainWindow::showCoords(QMouseEvent *event)
{
    QPoint pt = event->pos();


}

void MainWindow::setPBar(int numTiles)
{
    ui->pBar1->setValue(0);
    ui->pBar1->setMaximum(numTiles);
}

void MainWindow::stepPBar()
{
    int v = ui->pBar1->value()+1;
    ui->pBar1->setValue(v);
}
