#include "SearchListView.h"
#include "SearchModelDelegate.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <qpainter.h>
#include <QMouseEvent>

SearchTableView::SearchTableView(QWidget* parent)
    :QTableView (parent)
{
    this->setMouseTracking(true);
    // Model
//    this->setFixedWidth(785);
//        this->setMinimumSize(785,0);
    tableModel = new SearchTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new SearchTableDelegate;
    this->setItemDelegate(tableDelegate);
//    tableDelegate->Set_Table(tableModel);

    this->View_Init();
}

SearchTableView::~SearchTableView()
{

}

void SearchTableView::AddTableList(QList<QVariantList> var)
{
    tableModel->ReMoveAll();
    tableModel->PushBackList(var);
}

void SearchTableView::AddPlayListVar(bool isMV,int row)
{
    QVariantList var;
    var.push_back(this->tableModel->Get_List().at(row)->Get_VoiceName());
    var.push_back(this->tableModel->Get_List().at(row)->Get_Singer());
    var.push_back(this->tableModel->Get_List().at(row)->Get_SongTime());
    var.push_back(this->tableModel->Get_List().at(row)->Get_Hash());
    var.push_back(this->tableModel->Get_List().at(row)->Get_AlbumID());
    var.push_back(this->tableModel->Get_List().at(row)->Get_MVHash());

    emit AddPlayList(isMV,var);
}

void SearchTableView::AllTableSetFalse()
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->Set_Clicked(false);
    }
}

void SearchTableView::View_Init()
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
    this->setColumnWidth(2,155);
    this->setColumnWidth(3,185);
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

    this->connect(this,&QTableView::doubleClicked,this,[=](const QModelIndex &index){

//        QVariantList var;
        int row = index.row();
//        QString SongTime = tableModel->Get_List().at(row)->Get_SongTime();
//        QString MVHash = tableModel->Get_List().at(row)->Get_MVHash();
//        QString mos = tableModel->Get_List().at(row)->Get_Hash();
//        QString alubm_id = tableModel->Get_List().at(row)->Get_AlbumID();
//        QString SingName = tableModel->Get_List().at(row)->Get_VoiceName();
//        QString Singer = tableModel->Get_List().at(row)->Get_Singer();
//        QString album_id = tableModel->Get_List().at(row)->Get_AlbumID();
//        emit DoubleClickedSong(mos,alubm_id,Singer + "-" + SingName);

        AddPlayListVar(false,row);
    });

    this->connect(tableDelegate,&SearchTableDelegate::PlayButtonClicked,this,[=](int row){
//        QString mos = tableModel->Get_List().at(row)->Get_Hash();
//        QString alubm_id = tableModel->Get_List().at(row)->Get_AlbumID();
//        QString SingName = tableModel->Get_List().at(row)->Get_VoiceName();
//        QString Singer = tableModel->Get_List().at(row)->Get_Singer();
//        emit DoubleClickedSong(mos,alubm_id,Singer + "-" + SingName);

        AddPlayListVar(false,row);
    });
    this->connect(tableDelegate,&SearchTableDelegate::MVButtonClicked,this,[=](int row){
//        QString mvHash = tableModel->Get_List().at(row)->Get_MVHash();
//        QString SingName = tableModel->Get_List().at(row)->Get_VoiceName();
//        QString Singer = tableModel->Get_List().at(row)->Get_Singer();
//        emit MVClicked(mvHash,SingName+ "-" + Singer);

        AddPlayListVar(true,row);
    });
    this->connect(tableDelegate,&SearchTableDelegate::AddButtonClicked,this,[=](int row){

    });
    this->connect(tableDelegate,&SearchTableDelegate::DownButtonClicked,this,[=](int row){

    });

    this->setStyleSheet("border:none;");
}
