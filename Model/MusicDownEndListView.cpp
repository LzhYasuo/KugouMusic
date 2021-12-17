#include "MusicDownEndListView.h"
#include "MusicDownEndModelDelegate.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <qpainter.h>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QTextCodec>
#include <QProcess>
#include <QDir>

MusicDownEndTableView::MusicDownEndTableView(QWidget* parent)
    :QTableView (parent)
{
    this->setMouseTracking(true);
    // Model
    this->setFixedWidth(600);
    tableModel = new MusicDownEndTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new MusicDownEndTableDelegate;
    this->setItemDelegate(tableDelegate);
//    tableDelegate->Set_Table(tableModel);

    this->View_Init();
}

MusicDownEndTableView::~MusicDownEndTableView()
{

}

void MusicDownEndTableView::mouseMoveEvent(QMouseEvent *event)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        if(tableModel->Get_List().at(i)->Get_ListState() == 2)
            continue;
        tableModel->Get_List().at(i)->Set_ListState(0);
    }
    int row = indexAt(event->pos()).row();
    if(row >= 0)
    {
        for(int i = 0; i < tableModel->Get_List().size(); i++)
        {
            if(tableModel->Get_List().at(row)->Get_ListState() != 2)
                tableModel->Get_List().at(row)->Set_ListState(1);
        }
    }
    tableModel->RefrushModelData();

    return QTableView::mouseMoveEvent(event);
}

void MusicDownEndTableView::AddDBDataList(QList<QVariantList> List)
{
    tableModel->AddDBDataList(List);
}

void MusicDownEndTableView::PlayMVMusicUrl(int row)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        this->setRowHeight(i, 30);
        tableModel->Get_List().at(i)->Set_ListState(0);
    }
    this->setRowHeight(row, 50);
    tableModel->Get_List().at(row)->Set_ListState(2);
    tableModel->RefrushModelData();

    bool isMV = false;
    QString OpenUrl = "";
    QString Name = tableModel->Get_List().at(row)->Get_VoiceName();
    QString Singer = tableModel->Get_List().at(row)->Get_Singer();
    QString MusicUrl = tableModel->Get_List().at(row)->getMusicUrl();
    QString MVUrl = tableModel->Get_List().at(row)->getMVUrl();
    QString NameSinger = Singer + "-" + Name;
    bool isLove = tableModel->Get_List().at(row)->getIsLove();

    if(MusicUrl.isEmpty())
    {
        isMV = true;
        OpenUrl = MVUrl;
    }
    else
    {
        isMV = false;
        OpenUrl = MusicUrl;
    }
    tableModel->Set_NowPlayRow(row);
    emit PlayUrl(NameSinger,OpenUrl,isLove,isMV);
}

void MusicDownEndTableView::SwitchMusicMV(MusicDownOrderRamdom Type, MusicDownPreNex Model)
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_List().size() == 0)
        return;
    int row = 0;
    if(Type == MusicDownRamdom)
    {
        row = qrand() % tableModel->Get_List().size();
    }
    else
    {
        if(Model == MusicDownNext)
        {
            if(tableModel->Get_NowPlayRow() == tableModel->Get_List().size() - 1)
            {
                row = 0;
            }
            else
            {
                row = tableModel->Get_NowPlayRow() + 1;
            }
        }
        else
        {
            if(tableModel->Get_NowPlayRow() == 0)
            {
                row = tableModel->Get_List().size() - 1;
            }
            else
            {
                row = tableModel->Get_NowPlayRow() - 1;
            }
        }
    }
    tableModel->Set_NowPlayRow(row);
    PlayMVMusicUrl(row);
}


void MusicDownEndTableView::AllTableSetFalse()
{
//    for(int i = 0; i < tableModel->Get_List().size(); i++)
//    {
//        tableModel->Get_List().at(i)->Set_Clicked(false);
    //    }
}

void MusicDownEndTableView::AddListData(QVariantList List)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        if(List.at(5).toBool())
        {
            if(List.at(4).toString() == tableModel->Get_List().at(i)->getMVUrl())
                return;
        }
        else
            if(List.at(4).toString() == tableModel->Get_List().at(i)->getMusicUrl())
            return;
    }
    tableModel->AddListData(List);

//    .arg(List.at(0).toString()) //FilePath
//        .arg(List.at(1).toString()) //SongName
//        .arg(List.at(2).toString()) //Singer
//        .arg(List.at(3).toString()) //Time
//        .arg(List.at(4).toString()) //Size
//        .arg(List.at(5).toBool())   //isMV
//        .arg(List.at(6).toBool());  //isLove

    QVariantList var;
    bool isMV = false;
    QString FilePath = "";
    int row = tableModel->Get_List().size() - 1;
    QString MusicPath = tableModel->Get_List().at(row)->getMusicUrl();
    QString MVPath = tableModel->Get_List().at(row)->getMVUrl();
    if(MusicPath.isEmpty())
    {
        isMV = true;
        FilePath = MVPath;
    }
    else
    {
        isMV = false;
        FilePath = MusicPath;
    }

    var.push_back(FilePath);
    var.push_back(tableModel->Get_List().at(row)->Get_VoiceName());
    var.push_back(tableModel->Get_List().at(row)->Get_Singer());
    var.push_back(tableModel->Get_List().at(row)->Get_SongTime());
    var.push_back(tableModel->Get_List().at(row)->getSize());
    var.push_back(isMV);
    var.push_back(tableModel->Get_List().at(row)->getIsLove());

    emit AddMusicDownDB(var);
}

void MusicDownEndTableView::ClearDownNowPlayRow()
{
    tableModel->Set_NowPlayRow(0);
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        this->setRowHeight(i, 30);
        tableModel->Get_List().at(i)->Set_ListState(0);
    }
}

void MusicDownEndTableView::SignalMusicModelSlot()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->Set_ListState(0);
        this->setRowHeight(i,30);
    }
    tableModel->Set_NowPlayRow(-1);
}

void MusicDownEndTableView::OrderOfMusicModelSlot()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_NowPlayRow() == tableModel->Get_List().size() - 1)
    {
        for(int i = 0; i < tableModel->Get_List().size(); i++)
        {
            tableModel->Get_List().at(i)->Set_ListState(0);
            this->setRowHeight(i,30);
        }
        tableModel->Set_NowPlayRow(-1);
    }
    else
    {
        const int row = tableModel->Get_NowPlayRow() + 1;
        tableModel->Set_NowPlayRow(row);
        PlayMVMusicUrl(row);
    }
}

void MusicDownEndTableView::ListMusicModelSlot()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_NowPlayRow() == tableModel->Get_List().size() - 1)
    {
        const int row = 0;
        tableModel->Set_NowPlayRow(row);
        PlayMVMusicUrl(row);
    }
    else
    {
        const int row = tableModel->Get_NowPlayRow() + 1;
        tableModel->Set_NowPlayRow(row);
        PlayMVMusicUrl(row);
    }
}

void MusicDownEndTableView::RandomMusicModelSlot()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    int row = qrand() % tableModel->Get_List().size();
    tableModel->Set_NowPlayRow(row);
    PlayMVMusicUrl(row);
}

void MusicDownEndTableView::SetLoveState()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    int row = tableModel->Get_NowPlayRow();
    bool isLove = tableModel->Get_List().at(row)->getIsLove();
    isLove = !isLove;
    tableModel->Get_List().at(row)->setIsLove(isLove);

    QString FilePath = tableModel->Get_List().at(row)->getMusicUrl();
    tableModel->RefrushModelData();
    emit ChangeDBLove(FilePath,isLove,true);
}

void MusicDownEndTableView::View_Init()
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
    tableModel->Set_NowPlayRow(-1);

    this->setStyleSheet("border:1px solid rgb(170,170,170);");

    this->connect(this,&QTableView::doubleClicked,this,[=](const QModelIndex &index){
        PlayMVMusicUrl(index.row());
    });

    this->connect(tableDelegate,&MusicDownEndTableDelegate::DeleteSignal,this,[=](const QModelIndex& index){
        if(index.row() == tableModel->Get_NowPlayRow())
        {
            //还原高度
            tableModel->Set_NowPlayRow(-1);
            this->setRowHeight(index.row(),30);
            emit PlayNothing();
        }
        QString RemoveUrl = "";
        QString MusicUrl = tableModel->Get_List().at(index.row())->getMusicUrl();
        QString MVUrl = tableModel->Get_List().at(index.row())->getMVUrl();
        if(MusicUrl.isEmpty())
            RemoveUrl = MVUrl;
        else
            RemoveUrl = MusicUrl;

        QFileInfo FileInfo(RemoveUrl);

        if (FileInfo.isFile())//如果是文件
            QFile::remove(RemoveUrl);

        tableModel->RemoveRow(index.row());


        tableModel->RefrushModelData();

        emit DeleteDB(RemoveUrl);
    });
    this->connect(tableDelegate,&MusicDownEndTableDelegate::LoveSignal,this,[=]( const QModelIndex& index){
        bool isLine = false;
        int row = index.row();
        bool isLove = tableModel->Get_List().at(row)->getIsLove();
        isLove = !isLove;
        tableModel->Get_List().at(row)->setIsLove(isLove);
        if(tableModel->Get_NowPlayRow() == row)
            isLine = true;
        QString FilePath = tableModel->Get_List().at(row)->getMusicUrl();

        tableModel->RefrushModelData();

        emit ChangeDBLove(FilePath,isLove,isLine);
    });

    this->connect(tableDelegate,&MusicDownEndTableDelegate::OpenFileSignal,this,[=](const QModelIndex& index){

        QString url = tableModel->Get_List().at(index.row())->getMusicUrl();
        QString MVUrl = tableModel->Get_List().at(index.row())->getMVUrl();
        QString openUrl = "";
        if(url.isEmpty())
            openUrl = MVUrl;
        else
            openUrl = url;
//        QTextCodec* codec = QTextCodec::codecForName("GBK");
//        QString OpenUrl = codec->fromUnicode(openUrl);

//        QDesktopServices::openUrl(OpenUrl);
//        QString SpStr = openUrl.split("/").last();
//        openUrl = openUrl.split(SpStr).first();
//        qDebug() << openUrl;

        QProcess process;
        openUrl.replace("/","\\");
        QString cmd = QString("explorer.exe /select,\"%1\"").arg(openUrl);
        qDebug()<<cmd;
        process.startDetached(cmd);
//        QProcess process(this);
//        process.setProgram("cmd");
//        QStringList argument;
//        argument << "/c" <<"start"<<""""<<openUrl;//双引号必须加，例 cmd start C:\Users\Student>start "" "C:\Program Files"
//        process.setArguments(argument);
//        process.start();
//        process.waitForStarted(); //等待程序启动
//        process.waitForFinished();//等待程序关闭
    });
}
