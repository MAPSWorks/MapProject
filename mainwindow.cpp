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

    QPixmap pix("lol.png");
    QGSLayer *lyr = ui->gsMap->addLayer(1, "Test");

    QGraphicsPixmapItem *itm = scene->addPixmap(pix);

    itm->setParentItem(lyr);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    if(item != NULL)
    {

    QGSLayer *lyr = ui->gsMap->getLayer(item->text(0));

    if(lyr->isVisible())
        lyr->setVisible(false);
    else
        lyr->setVisible(true);

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->treeWidget->clear();

    QList<QGSLayer*> layers = ui->gsMap->getLayers();

    for(int i=0;i<layers.count();i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, layers.at(i)->getName());
        ui->treeWidget->addTopLevelItem(item);
    }
}
