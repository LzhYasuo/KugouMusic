#include "PlayListView.h"
#include "PlayListModelDelegate.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <qpainter.h>
#include <QMouseEvent>

PlayListView::PlayListView(int id,QWidget* parent)
    :QTableView (parent),
      mid(id)
{
    this->setMouseTracking(true);
    // Model
    this->setFixedWidth(600);
    tableModel = new PlayModelTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new PlayListTableDelegate;
    this->setItemDelegate(tableDelegate);
//    tableDelegate->Set_Table(tableModel);

    this->View_Init();
}

PlayListView::~PlayListView()
{

}

void PlayListView::mouseMoveEvent(QMouseEvent *event)
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
            if(tableModel->Get_List().at(row)->Get_ListState() == 2)
                continue;
            tableModel->Get_List().at(row)->Set_ListState(1);
        }
    }
    tableModel->RefrushModelData();

    return QTableView::mouseMoveEvent(event);
}

void PlayListView::SetLoveState()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    const int row = tableModel->Get_NowPlayRow();
    bool isLove = tableModel->Get_List().at(row)->Get_isLove();
    isLove = !isLove;
    tableModel->Get_List().at(row)->Set_isLove(isLove);
    QString MusicUrl = tableModel->Get_List().at(row)->Get_PlayMusicUrl();
    tableModel->RefrushModelData();
    emit ChangeDBLove(mid,MusicUrl,isLove,true);
}

void PlayListView::ClearNowPlayRow()
{
    tableModel->Set_NowPlayRow(-1);
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        this->setRowHeight(i,30);
        tableModel->Get_List().at(i)->Set_ListState(0);
    }
}

void PlayListView::AddInitData(QVariantList List)
{
    tableModel->InitData(List);

//    this->resize(600,tableModel->Get_Size() * 30 + 20);
}

void PlayListView::PlayMusicUrl(int row)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        this->setRowHeight(i, 30);
        tableModel->Get_List().at(i)->Set_ListState(0);
    }
    this->setRowHeight(row, 50);
    tableModel->Get_List().at(row)->Set_ListState(2);
    tableModel->Set_NowPlayRow(row);
    tableModel->RefrushModelData();
    QString Name = tableModel->Get_List().at(row)->Get_Singer() + "-" + tableModel->Get_List().at(row)->Get_VoiceName();
    QString MusicUrl = tableModel->Get_List().at(row)->Get_PlayMusicUrl();
    QStringList MusicLyrics = tableModel->Get_List().at(row)->getSongLycies();
    QStringList MusicLyricsTime = tableModel->Get_List().at(row)->getLyciesTime();
    bool isLove = tableModel->Get_List().at(row)->Get_isLove();
    emit MusicSongLyricsTime(MusicLyrics,MusicLyricsTime);
    emit PlayListPlayMusic(Name,MusicUrl,isLove);
}

void PlayListView::PlayMVurl(int row)
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        this->setRowHeight(i, 30);
        tableModel->Get_List().at(i)->Set_ListState(0);
    }

    this->setRowHeight(row, 50);
    QVariantList var;
    var.push_back(2);
    tableModel->Set_NowPlayRow(row);
    tableModel->Get_List().at(row)->Set_ListState(2);
    tableModel->RefrushModelData();
    QString Name = tableModel->Get_List().at(row)->Get_Singer() + "-" + tableModel->Get_List().at(row)->Get_VoiceName();
    QString MVUrl = tableModel->Get_List().at(row)->Get_PlayMVMusicUrl();
    bool isLove = tableModel->Get_List().at(row)->Get_isLove();
    emit PlayListPlayMV(Name,MVUrl,isLove);
}

void PlayListView::AddMusicData(bool isMV,QVariantList var)
{
    int row = JudgeMusic(var.at(3).toString());
    qDebug() << row;
    if(row == -1)
    {
        tableModel->PushBackData(var);
        emit AddForSql(mid,var);
        int ChooseLine = tableModel->Get_Size() - 1;
        this->setRowHeight(ChooseLine,50);
        tableModel->Set_NowPlayRow(ChooseLine);
//        this->resize(600,tableModel->Get_Size() * 30 + 20);

        for(int i = 0; i < tableModel->Get_Size(); i++)
        {
            if(i != ChooseLine)
            {
                this->setRowHeight(i,30);
            }
        }
        if(isMV)
            PlayMVurl(ChooseLine);
        else
        PlayMusicUrl(ChooseLine);
    }
    else
    {
        qDebug() << "重复的" << row;
        for(int i = 0; i < tableModel->Get_Size(); i++)
        {
            this->setRowHeight(i, 30);
            tableModel->Get_List().at(i)->Set_ListState(0);
        }
        QModelIndex index = this->model()->index(row,0);
        QVariantList var;
        this->setRowHeight(row,50);
        var.push_back(2);
        tableModel->setData(index,var);
        if(isMV)
            PlayMVurl(row);
        else
            PlayMusicUrl(row);
    }
}

int PlayListView::JudgeMusic(QString hash)
{
    for(int i = 0; i < tableModel->Get_Size(); i++)
    {
        if(tableModel->Get_List().at(i)->Get_PlayMusicUrl() == hash)
        {
            qDebug() << hash << "  " << tableModel->Get_List().at(i)->Get_PlayMusicUrl();
            //若是存在
            return i;
        }
    }
    return -1;
}

void PlayListView::AllTableSetFalse()
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->Set_Clicked(false);
    }
}

void PlayListView::SetDownState()
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    int row = tableModel->Get_NowPlayRow();
    QString Name = tableModel->Get_List().at(row)->Get_VoiceName();
    QString Singer = tableModel->Get_List().at(row)->Get_Singer();
    QString NameSinger = Singer + "-" + Name;
    QString MusicUrl = tableModel->Get_List().at(row)->Get_PlayMusicUrl();
    QString MVUrl = tableModel->Get_List().at(row)->Get_PlayMVMusicUrl();
    QString Time = tableModel->Get_List().at(row)->Get_SongTime();
    emit DownButtonClicked(NameSinger,MusicUrl,MVUrl,Time);
}

//单曲循环
void PlayListView::SignalMusicModelSlot(int type)
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

//顺序播放
void PlayListView::OrderOfMusicModelSlot(int type)
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_PlayNextList() > 0)
    {
        const int row = tableModel->Take_PlayNextList();
        PlayMusicUrl(row);
    }
    else
    {
        //音乐模式
        if(type == 0)
        {
            if(tableModel->Get_NowPlayRow() == -1)
            {
                emit NoNextPlayMusic();
            }
            else if(tableModel->Get_NowPlayRow() == tableModel->Get_List().size() - 1)
            {
                emit PlayListEnd();
            }
            else
            {
                const int row = tableModel->Get_NowPlayRow() + 1;
                tableModel->Set_NowPlayRow(row);
                PlayMusicUrl(row);
            }
        }
        //MV模式
        else
        {
            if(tableModel->Get_NowPlayRow() == -1)
            {
                emit NoNextPlayMusic();
            }
            int row = tableModel->Get_NextMVRow(tableModel->Get_NowPlayRow());
            if(row == -1)
            {
                emit PlayListEnd();
            }
            else
            {
                tableModel->Set_NowPlayRow(row);
                PlayMVurl(row);
            }
        }
    }
}

void PlayListView::ListMusicModelSlot(int type)
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_PlayNextList() > 0)
    {
        const int row = tableModel->Take_PlayNextList();
        PlayMusicUrl(row);
    }
    else
    {
        if(type == 0)
        {
            if(tableModel->Get_NowPlayRow() == -1)
            {
                emit NoNextPlayMusic();
            }
            else if(tableModel->Get_NowPlayRow() == tableModel->Get_List().size() - 1)
            {
                tableModel->Set_NowPlayRow(0);
                const int row = tableModel->Get_NowPlayRow();
                tableModel->Set_NowPlayRow(row);
                PlayMusicUrl(row);
            }
            else
            {
                const int row = tableModel->Get_NowPlayRow() + 1;
                tableModel->Set_NowPlayRow(row);
                PlayMusicUrl(row);
            }
        }
        else
        {
            if(tableModel->Get_NowPlayRow() == -1)
            {
                emit NoNextPlayMusic();
            }
            int row = tableModel->Get_NextMVRow(tableModel->Get_NowPlayRow());
            if(row == -1)
            {
                int FirstRow = tableModel->Get_FirstMVRow();
                tableModel->Set_NowPlayRow(FirstRow);
                PlayMVurl(FirstRow);
            }
            else
            {
                tableModel->Set_NowPlayRow(row);
                PlayMVurl(row);
            }
        }
    }
}

void PlayListView::RandomMusicModelSlot(int type)
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(type == 0)
    {
        int row = qrand() % tableModel->Get_List().size();
        tableModel->Set_NowPlayRow(row);
        PlayMusicUrl(row);
    }
    else
    {
        int row = qrand() & tableModel->Get_MVListSize();
        int ChooseRow = tableModel->Get_MVList().at(row);
        tableModel->Set_NowPlayRow(ChooseRow);
        PlayMVurl(ChooseRow);
    }
}

void PlayListView::SwitchMusicMV(int PlayType,Ramdom_Order Type,Next_Pre Model)
{
    if(tableModel->Get_NowPlayRow() < 0)
        return;
    if(tableModel->Get_Size() == 0)
        return;
    int row = 0;
    //Music
    if(tableModel->Get_PlayNextList() > 0)
    {
        row = tableModel->Take_PlayNextList();
        tableModel->Set_NowPlayRow(row);
        PlayMusicUrl(row);
    }
    else
    {
        if(PlayType == 0)
        {
            if(Type == Ramdom)
            {
                row = qrand() % tableModel->Get_List().size();
            }
            else
            {
                if(Model == Next)
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
            PlayMusicUrl(row);
        }
        //MV
        else
        {
            if(Type == Ramdom)
            {
                int qrandrow = qrand() % tableModel->Get_MVListSize();
                row = tableModel->Get_MVList().at(qrandrow);
            }
            else
            {
                if(Model == Next)
                {
                    row = tableModel->Get_NextMVRow(tableModel->Get_NowPlayRow());
                    if(row == -1)
                    {
                        row = tableModel->Get_FirstMVRow();
                    }
                }
                else
                {
                    row = tableModel->Get_PreMVRow(tableModel->Get_NowPlayRow());
                    if(row == -1)
                    {
                        int LastRow = tableModel->Get_MVListSize() - 1;
                        row = tableModel->Get_MVList().at(LastRow);
                    }
                }
            }
            tableModel->Set_NowPlayRow(row);
            PlayMVurl(row);
        }
    }
}

void PlayListView::View_Init()
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

    this->connect(this,&QTableView::doubleClicked,this,[=](const QModelIndex &index){
        int row = index.row();
        PlayMusicUrl(row);
    });
    this->connect(tableDelegate,&PlayListTableDelegate::LoveButtonClicked,this,[=](const QModelIndex& index){
        bool isLove = tableModel->Get_List().at(index.row())->Get_isLove();
        isLove = !isLove;
        tableModel->Get_List().at(index.row())->Set_isLove(isLove);
        QString MusicUrl = tableModel->Get_List().at(index.row())->Get_PlayMusicUrl();
        tableModel->RefrushModelData();
        bool isLine = false;
        if(index.row() != tableModel->Get_NowPlayRow())
            isLine = false;
        else
            isLine = true;
        emit ChangeDBLove(mid,MusicUrl,isLove,isLine);
    });
    this->connect(tableDelegate,&PlayListTableDelegate::MVButtonClicked,this,[=](const QModelIndex& index){
        int row = index.row();
        PlayMVurl(row);
    });
    this->connect(tableDelegate,&PlayListTableDelegate::AddButtonClicked,this,[=](const QModelIndex& index){
        int row = index.row();
        tableModel->AddPlayNextMusic(row);
    });
    this->connect(tableDelegate,&PlayListTableDelegate::DownButtonClicked,this,[=](const QModelIndex& index){
        QString Name = tableModel->Get_List().at(index.row())->Get_VoiceName();
        QString Singer = tableModel->Get_List().at(index.row())->Get_Singer();
        QString NameSinger = Singer + "-" + Name;
        QString MusicUrl = tableModel->Get_List().at(index.row())->Get_PlayMusicUrl();
        QString MVUrl = tableModel->Get_List().at(index.row())->Get_PlayMVMusicUrl();
        QString Time = tableModel->Get_List().at(index.row())->Get_SongTime();
        emit DownButtonClicked(NameSinger,MusicUrl,MVUrl,Time);
    });
    this->connect(tableDelegate,&PlayListTableDelegate::DeleteButtonClicked,this,[=](const QModelIndex& index){
        if(index.row() == tableModel->Get_NowPlayRow())
        {
            //还原高度
            tableModel->Set_NowPlayRow(-1);
            this->setRowHeight(index.row(),30);
            emit PlayNothing();
        }
        QString RemoveUrl = tableModel->Get_List().at(index.row())->Get_PlayMusicUrl();
        tableModel->RemoveRow(index.row());
        tableModel->RefrushModelData();

        emit DeleteDB(mid,RemoveUrl);
    });
}
