#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gsMap->setServerSettings(); //"10.254.53.244"

    QGraphicsScene *scene = ui->gsMap->loadMap("test");

    if(scene != NULL)
    {

        QPixmap pix("lol.png");
        QGSLayer *lyr = ui->gsMap->addLayer(1, "Test");

        ui->gsMap->featureFactory->addPoint(lyr, 10, 10);
        ui->gsMap->featureFactory->addPoint(lyr, 20, 10);
        ui->gsMap->featureFactory->addPoint(lyr, 0, 23);

        QList<QGSMapInfo*> list = ui->gsMap->getServerSettings()->getMapList(41001);

        for(int i=0;i<list.count();i++)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(list.at(i)->getMapName());
            ui->listWidget->addItem(item);
        }



    }
    else
        qDebug() << "Map cannot be loaded";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    QGSMapInfo *mi = (QGSMapInfo *)ui->listWidget->currentItem();

    ui->mapBox->setTitle(mi->getMapName());
}
