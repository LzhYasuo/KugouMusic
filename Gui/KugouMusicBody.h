#ifndef _KUGOU_MUSIC_BODY_H_
#define _KUGOU_MUSIC_BODY_H_

#include "KugouBaseControl.h"
#include <QVariantList>

enum PlayModel
{
    SignalMusicModel,
    SignalLoopMusicModel,
    OrderOfMusicModel,
    ListMusicModel,
    RandomMusicModel,
};

enum PlayType
{
    MusisPlayer,
    MVPlayer,
};

enum LeftMusicList
{
    LoaclListWidget,
    NetworkListWidget,
    MusicRadioListWidget,
    PhoneMusicWidget,
    LoaclMusicWidget,
};

enum RightMusicList
{
    MusicLibWidget,
    RadioWidget,
    PlayListWidget,
    MVWidget,
    LiveWidget,
    LyriceWidget,
    SearchMusicWidget,
    VoiceWidget,
};

class KugouMusicBody : public KugouBaseControl
{
    Q_OBJECT
public:
    KugouMusicBody(QWidget* parent = nullptr);
    ~KugouMusicBody();

    PlayModel Get_Model() const {return Model;}

public slots:
    void SlotSearchSlot(QString name);

protected:
    bool eventFilter(QObject *o, QEvent *e);

public slots:
    void MusicModelSlot();
signals:
    void SearchWidgetChange(QString name);
    void ChangeName();
    void PlaySongSignal(QString,QString,QString);
    void StartPlayerSignal(int);
    void UpdateSliderPosSignal(qint64);
    void UpdatePlayerName(QString);
    void SeekPlaySignal(int value);
    void PlayerChangeStateSignal();
    void MVClickSignal(QString,QString);
    void MVPageShow();
    void SeekPlay(int value);
    void PlayerStateChange(bool);
    void PlayListDataSignal(bool,QVariantList);
    void SetPlayListNowTime(QString t);
    void PlayListPlay(QString,QString,bool);
    void PlayListPlayMV(QString,QString,bool);
    void PlayNothing();
    void ModelChange(PlayType);
    void SignalMusicModelSignal(int);
    void OrderOfMusicModelSignal(int);
    void ListMusicModelSignal(int);
    void RandomMusicModelSignal(int);
    void LoveState(bool);
    void ClearBottomInfo();
    void ChangeVolumeSignal(double value);
    void SwitchLeftPage(int);
    void ClearNowPlayRow();
    void ClearDownNowPlayRow();

    void ClearLyricsWidget();
    void ChangeImage(QString);
    void SeekLyrics(QString value);
    void UpdateLyrics(QString value);
    void MusicSongLyricsTime(QStringList,QStringList);
    void PreMusicSignal();
    void NextMusicSignal();
    void LoveClickeSignal();
    void DownCliKcedSignal();

private:
    void Init();
    QWidget* InitLeftWidget();
    QWidget* InitRightWidget();
    QWidget* CreateLeftListWidget(LeftMusicList);
    QWidget* CreateRightListWidget(RightMusicList);
    QWidget* CreateLeftWidgetButtonList(QString Name,int id);

private:
    PlayType Type = MusisPlayer;
    PlayModel Model = SignalMusicModel ;
    QString SearchName;
    QString StartTime;
    QString LastTime;
    QString LyricsTime;
    int mDruation;
    bool MVStare = true;
    int Page = 5;
};

#endif //_KUGOU_MUSIC_BODY_H_
