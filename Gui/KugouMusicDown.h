#ifndef _KUGOUMUSIC_DOWN_H_
#define _KUGOUMUSIC_DOWN_H_

#include <QDialog>

class KugouMusicDown: public QDialog
{
    Q_OBJECT
public:
    KugouMusicDown(QString,QString,QString,QString,QWidget* parent = nullptr);
    ~KugouMusicDown();

    void Init();

signals:
    void MusicDown(QString,QString,QString Time);
    void MVDown(QString,QString,QString Time);
private:
    QString mNameSinger;
    QString mMusicUrl;
    QString mMVUrl;
    QString mTime;
};

#endif //_KUGOUMUSIC_DOWN_H_
