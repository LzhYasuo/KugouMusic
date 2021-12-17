#ifndef _PLAY_LIST_DB_H_
#define _PLAY_LIST_DB_H_

#include <QObject>
#include <QSqlDatabase>

struct DBTable
{
    int id;
    QString TableName;
};

struct SongListState
{
    QString songNmae;
    QString Singer;
    QString songTime;
    QString MusicUrl;
    QString MVUrl;
    bool isLove;
};

class PlayListDB : public QObject
{
public:
    PlayListDB(QWidget* parent = nullptr);
    ~PlayListDB();

    bool isOpen();
    //打开数据库
    bool OpenDataBase();
    //创建数据库
    void CreateDBFile();
    //查找是那个数据库表
    QString GetDBName(int);
    //添加数据库表的数据
    void Add_DB_Data(int,SongListState);
    //查找数据库表的数据
    bool Find_DB_Data(int,QString hash);
    //删除表
    void RemoveDBTable(int);
    //删除数据库表的数据
    void RemoveDBTableData(int,QString hash);
    //改变数据库表的数据
    void ChangeDBTableData(int,QString hash,bool isLove);
    //返回数据
    QList<SongListState> Get_DBSongInfo(int);
    //返回表数量
    int Get_Table_MaxNum();
    //返回表与数据
    QList<DBTable> Get_DBTable_IDName();

    //下载的音乐数据库---------
    void Add_DownMusicData(QVariantList List);
    void RemoveDownMusicData(QString FilePath);
    void ChangeDownMusicData(QString FilePath,bool isLove);
    QList<QVariantList> Get_DownMusicData();


private:
    QSqlDatabase m_DB;
    const QString DBPath = "F:\\QTpro\\build-KugouMusic-Desktop_Qt_5_9_8_MinGW_32bit-Release\\release\\SongList.db";
};

#endif //_PLAY_LIST_DB_H_
