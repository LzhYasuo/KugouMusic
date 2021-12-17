#include "SearchHeaderView.h"
#include "SearchHeadDelegate.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <qpainter.h>

SearchHeadTableView::SearchHeadTableView(QWidget* parent)
    :QTableView (parent)
{
    this->setMouseTracking(true);
    // Model
//    this->setFixedWidth(785);
//    this->setMinimumSize(785,0);
    tableModel = new SearchHeadTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new SearchHeadTableDelegate;
    this->setItemDelegate(tableDelegate);
//    tableDelegate->Set_Table(tableModel);

    this->View_Init();
}

SearchHeadTableView::~SearchHeadTableView()
{

}

void SearchHeadTableView::AllTableSetFalse()
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->Set_Clicked(false);
    }
}

void SearchHeadTableView::View_Init()
{
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setShowGrid(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    this->setColumnWidth(0,20);
    this->setColumnWidth(1,200);
    this->setColumnWidth(2,170);
    this->setColumnWidth(3,190);
    this->setColumnWidth(4,70);
    this->setColumnWidth(5,130);
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

    this->setStyleSheet("border:none;");
}
