#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gsMap->setServerSettings("localhost", 8080);
//    ui->gsMap->setServerSettings("10.254.53.244");

    if(ui->gsMap->getServerSettings() != NULL)
    {

        QList<QGSMapInfo*> list = ui->gsMap->getServerSettings()->getMapList(900913);//4326 900913 41001

        for(int i=0;i<list.count();i++)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(list.at(i)->getMapName());
            ui->listWidget->addItem(item);
        }



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
    QGSMapInfo *mi = ui->gsMap->getServerSettings()->getMapInfo(ui->listWidget->currentItem()->text());

    ui->mapBox->setTitle(mi->getMapName());

    ui->srsLabel->setText(QString::number(mi->getMapSrs()));

    ui->xMinLbl->setText(mi->getBoundingBox().getMinX());
    ui->xMaxLbl->setText(mi->getBoundingBox().getMaxX());
    ui->yMinLbl->setText(mi->getBoundingBox().getMinY());
    ui->yMaxLbl->setText(mi->getBoundingBox().getMaxY());
    ui->resoLbl->setText(QString::number(mi->getMapResolution()));


    QGraphicsScene *scene = ui->gsMap->loadMap(mi->getMapName());

    if(scene != NULL)
    {

    }
}

