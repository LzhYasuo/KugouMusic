#ifndef _KUGOUMUSICLYRICS_H_
#define _KUGOUMUSICLYRICS_H_
#include "KugouBaseControl.h"
#include <QMap>

#include <QMutex>
class KugouMusicLyrics : public KugouBaseControl
{
    Q_OBJECT
public:
    KugouMusicLyrics(QWidget* parent = nullptr);
    ~KugouMusicLyrics();

signals:
    void ColorChoose();
    void ColorNoChoose();

public slots:
    void MusicSongLyricsTimeSlot(QStringList,QStringList);
    void StartMove(QString value);
    void SeekLyrics(QString value);
    void ClearLyrics();
private:
    void Init();
    void ClearWidget();
    QStringList mLyrics;
    QStringList mLyricsTime;

    QMap<QStringList,QStringList> LyricsMap;
    int mSeek = 0;
    int mMax = 0;
    QMutex mux;
};


#endif //_KUGOUMUSICLYRICS_H_
