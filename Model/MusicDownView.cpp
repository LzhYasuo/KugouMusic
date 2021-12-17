#include "MusicDownView.h"
#include "MusicDownModelDelegate.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>
#include <qpainter.h>

MusicDownTableView::MusicDownTableView(QWidget* parent)
    :QTableView (parent)
{
    this->setMouseTracking(true);
    // Model
    this->setFixedWidth(600);
    tableModel = new MusicDownTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new MusicDownTableDelegate;
    this->setItemDelegate(tableDelegate);

    this->View_Init();
}

MusicDownTableView::~MusicDownTableView()
{

}

void MusicDownTableView::AddListData(QVariantList var)
{
    QString url = var.at(4).toString();
    if(var.at(5).toBool())
    {
        for(int i = 0; i < tableModel->Get_List().size(); i++)
        {
            if(tableModel->Get_List().at(i)->getMVUrl() == var.at(4).toString() == url)
            {
                return;
            }
        }
    }
    else
    {
        for(int i = 0; i < tableModel->Get_List().size(); i++)
        {
            if(tableModel->Get_List().at(i)->getMusicUrl() == var.at(4).toString() == url)
            {
                return;
            }
        }
    }
    tableModel->AddListData(var);
}

void MusicDownTableView::mouseMoveEvent(QMouseEvent *event)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->setState(0);
    }
    int row = indexAt(event->pos()).row();
    if(row >= 0)
    {
        for(int i = 0; i < tableModel->Get_List().size(); i++)
        {
            tableModel->Get_List().at(row)->setState(1);
        }
    }
    tableModel->RefrushModelData();

    return QTableView::mouseMoveEvent(event);
}

void MusicDownTableView::SlotUpdateProgress(QString url, qint64 pro, qint64 total)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        if(tableModel->Get_List().at(i)->getMusicUrl() == url)
        {
            tableModel->Get_List().at(i)->setNowBar(pro);
        }
        if(tableModel->Get_List().at(i)->getMVUrl() == url)
        {
            tableModel->Get_List().at(i)->setNowBar(pro);
        }
    }
    tableModel->RefrushModelData();
}

void MusicDownTableView::SendData(QString url)
{
    int row = -1;
    bool isMV = false;
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        if(tableModel->Get_List().at(i)->getMusicUrl().isEmpty())
        {
            if(tableModel->Get_List().at(i)->getMVUrl() == url)
            {
                row = i;
                isMV = true;
                break;
            }
        }
        else
        {
            if(tableModel->Get_List().at(i)->getMusicUrl() == url)
            {
                row = i;
                isMV = false;
                break;
            }
        }
    }
    QVariantList var;
    QString Name = tableModel->Get_List().at(row)->getMusicName();
    QString Singer = tableModel->Get_List().at(row)->getMusicSinger();
    QString Time = tableModel->Get_List().at(row)->getTotalTime();
    QString Path = tableModel->Get_List().at(row)->getMusicPath();
    QString Size = tableModel->Get_List().at(row)->getMusicSize();
    var << Name << Singer << Size << Time << Path << isMV;

    emit SendDownEndData(var);
}

void MusicDownTableView::AllTableSetFalse()
{
}

void MusicDownTableView::View_Init()
{
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setShowGrid(false);
    this->setColumnWidth(0,310);
    //禁止拖拽
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    //设置默认高度
    this->verticalHeader()->setDefaultSectionSize(30);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(30);
    //设置行列表头无法点击
    this->setCornerButtonEnabled(false);
    this->horizontalHeader()->setSectionsClickable(false);
    this->verticalHeader()->setSectionsClickable(false);
    QTableView::horizontalHeader()->hide();
    QTableView::verticalHeader()->hide();
}

