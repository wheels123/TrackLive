#include "dialogserver.h"
#include "ui_dialogserver.h"
#include "QStringListModel.h"
DialogServer::DialogServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogServer)
{
    ui->setupUi(this);

    QStringList num;
    num<<QString("1")<<QString("2")<<QString("3")<<QString("4");
    QStringListModel *model = new QStringListModel(num);
    ui->listViewClient->setModel(model);

}

DialogServer::~DialogServer()
{
    delete ui;
}

 void DialogServer::updateListViewClient(QStringList list)
 {
     QStringListModel *model = new QStringListModel(list);
     ui->listViewClient->setModel(model);
 }

 void DialogServer::updateTreeViewPath(QString pathId,QString pathPoint)
 {

 }

 void DialogServer::updateTreeViewPath(Robot* robot)
 {
    QStandardItemModel *qstmodel=new QStandardItemModel();
    int pathNum=robot->getPathNum();
    for(int i=0;i<pathNum;i++)
    {
        QString pathname;
        pathname.append("P ");
        pathname.append(QString::number(i,10));
        pathname.append(" RID ");
        pathname.append(QString::number(robot->getPathRobotIdByIndex(i),10));
        pathname.append(" ID ");
        pathname.append(QString::number(robot->getPathIdByIndex(i),10));
        pathname.append(" MaxNum ");
        pathname.append(QString::number(robot->getPathPointNumMax(i),10));
        pathname.append(" Num ");
        pathname.append(QString::number(robot->getPathPointNum(i),10));

        pathname.append(robot->robotStateToString(i));

        QStandardItem* item    = new QStandardItem(pathname);
        QStringList list = robot->pathToString(i);

        int pointNum=robot->getPathPointNum(i);
        for(int j=0;j<pointNum;j++)
        {
           QStandardItem* itemSub    = new QStandardItem(list.at(j));
           item->appendRow(itemSub);
        }
        qstmodel->appendRow(item);
    }
    ui->treeViewPath->setModel(qstmodel);
    ui->treeViewPath->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeViewPath->setAutoFillBackground(true);
    ui->treeViewPath->expandAll();
 }

 void DialogServer::updateTreeViewMainPath(Robot* robot)
 {
    QStandardItemModel *qstmodel=new QStandardItemModel();
    int pathNum=robot->getMainPathNum();

    QString pathname;
    pathname.append("MP ");
    pathname.append(" MaxNum ");
    pathname.append(QString::number(pathNum,10));
    QStandardItem* item    = new QStandardItem(pathname);
    QStringList list = robot->mainPathToString();

    for(int j=0;j<list.size();j++)
    {
       QStandardItem* itemSub    = new QStandardItem(list.at(j));
       item->appendRow(itemSub);
    }
    qstmodel->appendRow(item);

    ui->treeViewMainPath->setModel(qstmodel);
    ui->treeViewMainPath->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeViewMainPath->setAutoFillBackground(true);
    ui->treeViewMainPath->expandAll();
 }

