#include "PlayListDB.h"
#include <QFile>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

PlayListDB::PlayListDB(QWidget *parent)
{

}

PlayListDB::~PlayListDB()
{

}

bool PlayListDB::isOpen()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_DB = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_DB = QSqlDatabase::addDatabase("QSQLITE");
    }
    if(!m_DB.open())
        return false;
    else
        return OpenDataBase();
}

bool PlayListDB::OpenDataBase()
{
    QFile File(DBPath);
    if(!File.exists())
    {
        CreateDBFile();
        //失败了创建数据库文件
    }
    m_DB.setDatabaseName(DBPath);
    m_DB.close();
    return true;
}

void PlayListDB::CreateDBFile()
{
    QFile DB_Name(DBPath);
    if(DB_Name.open(QIODevice::WriteOnly))
    {
        m_DB.setDatabaseName(DBPath);
        if(!m_DB.open())
        {
            //数据库打不开
            return;
        }
        QSqlQuery sql;
        sql.exec("create table TableID(tableName char,id int primary key,TableShowName Text)");
        sql.exec("create table DefaultList(MusicUrl char primary key,SongName char,Singer char,time varchar,MVUrl char,isLove bool)");
        sql.exec("create table RecentPlay(MusicUrl char primary key,SongName char,Singer char,time varchar,MVUrl char,isLove bool)");
        sql.exec("create table MusicDownList(FilePath char primary key,SongName char,Singer char,time varchar,Size varchar,isMV bool,isLove bool)");
        sql.exec("insert into TableID values('DefaultList',0,'默认列表')");
        sql.exec("insert into TableID values('RecentPlay',1,'最近播放列表')");
        m_DB.close();
    }
    DB_Name.close();
}

QString PlayListDB::GetDBName(int id)
{
    QString DBName = "";
    if(!m_DB.open())
        return DBName;
    QSqlQuery query(m_DB);
    QString msg = QString("select tableName from TableID where id = %1 ").arg(id);
    query.exec(msg);
    if(query.first())
    {
        DBName = query.value(0).toString();
    }
    return DBName;
}

void PlayListDB::Add_DB_Data(int id, SongListState info)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    if(DBName.isEmpty())
        return;
    QString insertMsg = QString("insert into %1 values('%2','%3','%4','%5','%6',%7)").arg(DBName).arg(info.MusicUrl).arg(info.songNmae).arg(info.Singer)
                            .arg(info.songTime).arg(info.MVUrl).arg(info.isLove);
    query.exec(insertMsg);
    m_DB.close();

}

bool PlayListDB::Find_DB_Data(int id, QString hash)
{
    if(!m_DB.open())
        return false;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    if(DBName.isEmpty())
        return false;
    QString FindMsg = QString("select hash from %1 where hash = %2").arg(DBName).arg(hash);
    query.exec(FindMsg);
    if(query.first())
    {
        return true;
    }
    return false;
}

void PlayListDB::RemoveDBTable(int id)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    if(DBName.isEmpty())
        return;
    QString RemoveMsg = QString("DROP TABLE %1").arg(DBName);
    query.exec(RemoveMsg);

    m_DB.close();
}

void PlayListDB::RemoveDBTableData(int id, QString hash)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    if(DBName.isEmpty())
        return;
    QString RemoveMsg = QString("Delete from %1 where MusicUrl = '%2' ").arg(DBName).arg(hash);
    query.exec(RemoveMsg);
    m_DB.close();
}

void PlayListDB::ChangeDBTableData(int id, QString hash, bool isLove)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    if(DBName.isEmpty())
        return;
    QString UpdateMsg = QString("Update %1 set isLove = %2 where MusicUrl = '%3'").arg(DBName).arg(isLove).arg(hash);
    qDebug() << UpdateMsg;
    query.exec(UpdateMsg);
    m_DB.close();
}

QList<SongListState> PlayListDB::Get_DBSongInfo(int id)
{
    QList<SongListState> List;
    if(!m_DB.open())
        return List;
    QSqlQuery query(m_DB);
    QString DBName = GetDBName(id);
    qDebug() << "DBName" << DBName;
    if(DBName.isEmpty())
        return List;
    QString SelectMsg = QString("Select * from %1").arg(DBName);
    query.exec(SelectMsg);
    while(query.next())
    {
        SongListState info;
        info.MusicUrl = query.value(0).toString();
        info.Singer = query.value(1).toString();
        info.songNmae = query.value(2).toString();
        info.songTime = query.value(3).toString();
        info.MVUrl = query.value(4).toString();
        info.isLove = query.value(5).toBool();
        List.push_back(info);
    }
    m_DB.close();

    return List;
}

int PlayListDB::Get_Table_MaxNum()
{
    int max = 0;
    if(m_DB.open())
        return -1;
    QSqlQuery query(m_DB);
    QString MaxNumMsg = QString("select id from TableID");
    query.exec(MaxNumMsg);
    while(query.next())
    {
        max += 1;
    }
    m_DB.close();

    return max;
}

QList<DBTable> PlayListDB::Get_DBTable_IDName()
{
    QList<DBTable> List;
    if(m_DB.open())
        return List;
    QSqlQuery query(m_DB);
    QString IDNameMsg = QString("select id,TableShowName FROM TableID");
    query.exec(IDNameMsg);
    while(query.next())
    {
        DBTable temp;
        temp.id = query.value(0).toInt();
        temp.TableName = query.value(1).toString();
        List.push_back(temp);
    }
    m_DB.close();

    return List;
}

void PlayListDB::Add_DownMusicData(QVariantList List)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);

//    sql.exec("create table MusicDownList(FilePath char primary key,SongName char,Singer char,time varchar,Size varchar,bool isMV,isLove bool)");
    QString insertMsg = QString("insert into MusicDownList values('%1','%2','%3','%4','%5',%6,%7)")
                            .arg(List.at(0).toString()) //FilePath
                            .arg(List.at(1).toString()) //SongName
                            .arg(List.at(2).toString()) //Singer
                            .arg(List.at(3).toString()) //Time
                            .arg(List.at(4).toString()) //Size
                            .arg(List.at(5).toBool())   //isMV
                            .arg(List.at(6).toBool());  //isLove
    query.exec(insertMsg);
    m_DB.close();
}

void PlayListDB::RemoveDownMusicData(QString FilePath)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);

    QString RemoveMsg = QString("Delete from MusicDownList where FilePath = '%2'").arg(FilePath);
    query.exec(RemoveMsg);
    m_DB.close();
}

void PlayListDB::ChangeDownMusicData(QString FilePath, bool isLove)
{
    if(!m_DB.open())
        return;
    QSqlQuery query(m_DB);

    QString UpdateMsg = QString("Update MusicDownList set isLove = %1 where FilePath = '%2'").arg(isLove).arg(FilePath);

    query.exec(UpdateMsg);
    m_DB.close();
}

QList<QVariantList> PlayListDB::Get_DownMusicData()
{
    QList<QVariantList> Var;
    if(!m_DB.open())
        return Var;
    QSqlQuery query(m_DB);
    QString SelectMsg = QString("select * from MusicDownList");
    query.exec(SelectMsg);
    while(query.next())
    {
        QVariantList List;
        List.push_back(query.value(0).toString());
        List.push_back(query.value(1).toString());
        List.push_back(query.value(2).toString());
        List.push_back(query.value(3).toString());
        List.push_back(query.value(4).toString());
        List.push_back(query.value(5).toBool());
        List.push_back(query.value(6).toBool());
        Var.push_back(List);
    }
    m_DB.close();

    return Var;
}

