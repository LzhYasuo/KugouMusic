#ifndef NETWORK_HTTP_H_
#define NETWORK_HTTP_H_

#include "QNetworkAccessManager"

struct SearchValue
{
    QString SongName;
    QString SingerName;
    QString Album_Name;
    QString Duration;
    QString Hash;
    QString MVHash;
    QString Album_ID;
};

class QNetworkReply;
class NetWorkHttp : public QNetworkAccessManager
{
    Q_OBJECT
public:
    static NetWorkHttp* Get();
    QString Get_KugouKey(int count);
    QByteArray GetReadAll(QString url);
    QList<QVariantList> SearchGetJson(QString url);
    QVariantList SongGetJson(QString hash,QString Album_id);
    QString MVGetJson(QString MVHash);
    void DownSongOrMv(bool isMV,QString url,QString FilePath,QString Time);

signals:
    void updateProgress(QString Url,qint64,qint64);
    void UpdateInfo(QVariantList);
    void WriteOk(QString);
private:
    NetWorkHttp();
    ~NetWorkHttp();

    static QString CovFileSize( const uint64_t &unSize );

    static NetWorkHttp* mHttp;
    const QString dfid = "3KsyWK16LQQx15O2S526TQXX";
//    QNetworkReply* mReply;

};

#endif //NETWORK_HTTP_H_
