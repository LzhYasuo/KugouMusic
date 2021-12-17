 #include "PlayListData.h"
#include <QDebug>

PlayListData* PlayListData::Data = new PlayListData();

PlayListData::PlayListData(QWidget *parent)
{
    DBData = new PlayListDB();
    DBData->isOpen();
    TableList = DBData->Get_DBTable_IDName();

    for(int i = 0; i < TableList.size(); i++)
    {
        QList<SongListState> temp =  DBData->Get_DBSongInfo(TableList.at(i).id);
        MapList[TableList.at(i).id] = temp;
    }
}

PlayListData::~PlayListData()
{

}

PlayListData *PlayListData::Get()
{
    return Data;
}

QList<int> PlayListData::Get_All_ID()
{
    QList<int> All_ID_List;
    for(int i = 0; i < TableList.size(); i++)
    {
        All_ID_List.push_back(TableList.at(i).id);
    }
    return All_ID_List;
}

QString PlayListData::Get_TableName(int id)
{
    QString TableName = "";
    for(int i = 0; i < TableList.size(); i++)
    {
        if(TableList.at(i).id == id)
        {
            TableName = TableList.at(i).TableName;
        }
    }
    return TableName;
}

void PlayListData::AddDBTableData(int id,QVariantList List)
{
    SongListState var;
    var.songNmae = List.at(0).toString();
    var.Singer = List.at(1).toString();
    var.songTime = List.at(2).toString();
    var.MusicUrl = List.at(3).toString();
    var.MVUrl = List.at(4).toString();
    var.isLove = List.at(5).toBool();
    qDebug() << List.at(3).toString();
    DBData->Add_DB_Data(id,var);
}

void PlayListData::MoiftyTableDataLove(int id, QString Hash, bool isLove)
{
    DBData->ChangeDBTableData(id,Hash,isLove);
}

void PlayListData::DeleteTableData(int id, QString Hash)
{
    DBData->RemoveDBTableData(id,Hash);
}

QList<QVariantList> PlayListData::GetDBTableData(int id)
{
    QList<QVariantList> var;
    QList<SongListState> List = DBData->Get_DBSongInfo(id);
    qDebug() << List.size();
    for(int i = 0; i < List.size(); i++)
    {
        QVariantList v;
        v.push_back(List.at(i).songNmae);
        v.push_back(List.at(i).Singer);
        v.push_back(List.at(i).songTime);
        v.push_back(List.at(i).MusicUrl);
        v.push_back(List.at(i).MVUrl);
        v.push_back(List.at(i).isLove);
        var.push_back(v);
    }

    return var;
}

void PlayListData::AddMusicDownData(QVariantList List)
{
    DBData->Add_DownMusicData(List);
}

void PlayListData::RemoveMusicDownData(QString FilePath)
{
    DBData->RemoveDownMusicData(FilePath);
}

void PlayListData::MoiftyMusicDownData(bool isLove, QString FilePath)
{
    DBData->ChangeDownMusicData(FilePath,isLove);
}

QList<QVariantList> PlayListData::GetMusicDownData()
{
    QList<QVariantList> var;
    var = DBData->Get_DownMusicData();

    return var;
}



