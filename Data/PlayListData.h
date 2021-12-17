#ifndef _PLAY_LIST_DATA_H_
#define _PLAY_LIST_DATA_H_

#include <QObject>
#include <QMap>
#include <QList>
#include "PlayListDB.h"

class PlayListData : public QObject
{
public:
    static PlayListData* Get();

    QList<int> Get_All_ID();
    QList<SongListState> Get_IDList(int id);
    QString Get_TableName(int id);

    void AddDBTableData(int id,QVariantList List);
    void MoiftyTableDataLove(int id,QString Hash,bool isLove);
    void DeleteTableData(int id,QString Hash);
    QList<QVariantList> GetDBTableData(int id);

    void AddMusicDownData(QVariantList);
    void RemoveMusicDownData(QString FilePath);
    void MoiftyMusicDownData(bool isLove,QString FilePath);
    QList<QVariantList> GetMusicDownData();
private:
    PlayListData(QWidget* parent = nullptr);
    ~PlayListData();

private:
    static PlayListData* Data;
    QMap<int,QList<SongListState>> MapList;
    QList<DBTable> TableList;
    PlayListDB* DBData;
};

#endif //_PLAY_LIST_DATA_H_
