#include "NetWorkHttp.h"
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QByteArray>

NetWorkHttp* NetWorkHttp::mHttp = new NetWorkHttp();

NetWorkHttp *NetWorkHttp::Get()
{
    return mHttp;
}

QString NetWorkHttp::Get_KugouKey(int count)
{
    char s[] = {"abcdefghijklmnopqrstuvwxyz0123456789"};
    QString key = "";
    qsrand(static_cast<uint>(clock()));
    for(int i=0; i<count; i++){
        int n = qrand() % static_cast<int>(strlen(s));
        key += QString(s[n]);
    }
    return key;
}

QByteArray NetWorkHttp::GetReadAll(QString url)
{
    QNetworkRequest mRequest;
    mRequest.setUrl(url);
    QNetworkReply* mReply = this->get(mRequest);
    QEventLoop loop;
    this->connect(mReply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QByteArray btes = mReply->readAll();
    mReply->deleteLater();
    return btes;
}

QList<QVariantList> NetWorkHttp::SearchGetJson(QString name)
{
    QList<QVariantList> var;
    const QString url = QString("http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword=%1&page=1&pagesize=40&showtype=1").arg(name);
    QJsonDocument json = QJsonDocument::fromJson(GetReadAll(url));
    QJsonArray SongJson = json.object().value("data").toObject().value("info").toArray();
    for(int i=0; i<SongJson.size(); i++){
        QVariantList Value;
        Value.push_back(SongJson[i].toObject().value("songname").toString());
        Value.push_back(SongJson[i].toObject().value("singername").toString());
        Value.push_back(SongJson[i].toObject().value("album_name").toString());
        int Duration = SongJson[i].toObject().value("duration").toInt();
        Value.push_back(QString("%1:%2").arg(Duration/60,2,10,QLatin1Char(' ')).arg(Duration%60,2,10,QLatin1Char('0')));
        Value.push_back(SongJson[i].toObject().value("hash").toString());
        Value.push_back(SongJson[i].toObject().value("mvhash").toString());
        Value.push_back(SongJson[i].toObject().value("album_id").toString());
        var.push_back(Value);
    }
    return var;
}

QVariantList NetWorkHttp::SongGetJson(QString hash,QString Album_id)
{
    QString key = Get_KugouKey(4);
    qWarning() << key;
    QString kg_mid = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Md5).toHex();
    QString url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + hash + "&mid=" + kg_mid + "&dfid=" + dfid + "&album_id=" + Album_id;
    QJsonDocument json = QJsonDocument::fromJson(GetReadAll(url));
    QString SongJson = json.object().value("data").toObject().value("play_url").toString();
    QString s =  json.object().value("data").toObject().value("lyrics").toString();
    QString imgurl = json.object().value("data").toObject().value("img").toString();
    QStringList line = s.split("\n");
    QStringList Lyrics;
    QStringList LyricsTime;
    QVariantList var;
    qDebug() << url;
    for(int i=0; i<line.size(); i++)
    {
        if(line.at(i).contains("]"))
        {
            QStringList strlist = line.at(i).split("]");
            QString stime = strlist.at(0).mid(1);
            QString Songer = strlist.at(1).split("\r").first();
            if(!Songer.isEmpty())
            {
                Lyrics.push_back(Songer);
                LyricsTime.push_back(stime);
            }
        }
    }
    qDebug() << Lyrics;
    qDebug() << LyricsTime;
    qDebug() << SongJson;
    var.push_back(Lyrics);
    var.push_back(LyricsTime);
    var.push_back(SongJson);
    var.push_back(imgurl);

    return var;
}

QString NetWorkHttp::MVGetJson(QString mvHash)
{
    qDebug()<<mvHash;
    const QString url = QString("http://m.kugou.com/app/i/mv.php?cmd=100&ismp3=1&ext=mp4&hash=%1").arg(mvHash);
    QJsonDocument json = QJsonDocument::fromJson(GetReadAll(url));
    QString mvurl = json.object().value("mvdata").toObject().value("rq").toObject().value("downurl").toString();
    if (mvurl == "") {
        mvurl = json.object().value("mvdata").toObject().value("sq").toObject().value("downurl").toString();
    }
    if (mvurl == "") {
        mvurl = json.object().value("mvdata").toObject().value("le").toObject().value("downurl").toString();
    }

    return mvurl;
}

void NetWorkHttp::DownSongOrMv(bool isMV,QString url,QString FilePath,QString Time)
{
    qDebug() << url;
    QUrl Downurl = QString(url);

    QNetworkRequest Listrequest(url);
    QNetworkReply *Listreply = this->get(Listrequest);
    connect(Listreply, &QNetworkReply::finished, [=]() {
        QByteArray btes = Listreply->readAll();
        QVariantList var;
        QString MusicNameSinger = FilePath.split("/").last().split(".mp4").first();
        QString MusicName = MusicNameSinger.split("-").first();
        QString MusicSinger = MusicNameSinger.split("-").last();
        int TotolSize = btes.size();
        QString MusicUrl = url;
        QString MusicPath = FilePath;
        var << MusicName << MusicSinger << CovFileSize(btes.size()) << TotolSize << url << isMV << Time << MusicPath;
        emit UpdateInfo(var);
        qDebug() << "add";

        QNetworkRequest request(url);
        QNetworkReply *reply = this->get(request);
        connect(reply, &QNetworkReply::downloadProgress, this,[=](qint64 pro,qint64 total){
            qDebug() << pro;
            emit updateProgress(url,pro,total);
        });
        connect(reply, &QNetworkReply::finished, [=]() {
            switch (reply->error())
            {
            case QNetworkReply::NoError :
            {
                QFile file(FilePath);
                if(file.open(QIODevice::WriteOnly))
                {
                    file.write(reply->readAll());
                    file.flush();
                    file.close();
                }
                emit WriteOk(url);
                break;
            }
            default:
                break;
            }
            reply->deleteLater();
        });
    });
}

QString NetWorkHttp::CovFileSize( const uint64_t &unSize )
{
    QString sSize;
    double fSize = unSize * 1.0;
    if(fSize < 1024)//byte
    {
        sSize = QString("%1").sprintf("%.2f B", fSize);
    }
    else if( fSize >= 1024 && fSize < 1024*1024 )//kb
    {
        fSize = fSize/1024;
        sSize = QString("%1").sprintf("%.2f KB", fSize);
    }
    else if( fSize >= 1024*1024 && fSize < 1024*1024*1024)//mb
    {
        fSize = fSize/1024/1024;
        sSize = QString("%1").sprintf("%.2f MB", fSize);
    }
    else if( fSize >= 1024*1024*1024 && fSize < 1024 * 1024 * 1024 * 1024 )//gb
    {
        fSize = fSize/1024/1024/1024;
        sSize = QString("%1").sprintf("%.2f GB", fSize);
    }
    else{
        fSize = fSize/1024/1024/1024/1024;
        sSize = QString("%1").sprintf("%.2f TB", fSize);
    }
    return sSize;
}

NetWorkHttp::NetWorkHttp()
{
}

NetWorkHttp::~NetWorkHttp()
{
//    mReply->deleteLater();
}
