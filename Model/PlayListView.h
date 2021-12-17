#ifndef PLAYLISTVIEW_H_
#define PLAYLISTVIEW_H_

#include <QWidget>
#include <QTableView>


enum Ramdom_Order
{
    Ramdom,
    Order,
};

enum Next_Pre
{
    Next,
    Pre
};

class PlayModelTableModel;
class PlayListTableDelegate;
class PlayListView : public QTableView
{
    Q_OBJECT
public:
    PlayListView(int id,QWidget* parent = nullptr);
    ~PlayListView();

    void AddMusicData(bool isMV,QVariantList var);
    int JudgeMusic(QString hash);
    void AddInitData(QVariantList List);

    void PlayMusicUrl(int row);
    void PlayMVurl(int row);

    void SwitchMusicMV(int,Ramdom_Order,Next_Pre);

protected:
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void AllTableSetFalse();
    void SetDownState();
    void SetLoveState();
    void ClearNowPlayRow();
public slots:
    void SignalMusicModelSlot(int);
    void OrderOfMusicModelSlot(int);
    void ListMusicModelSlot(int);
    void RandomMusicModelSlot(int);
signals:
    void OpenUrl(QString);
    void PlayListPlayMusic(QString,QString,bool);
    void PlayListPlayMV(QString,QString,bool);
    void AddForSql(int,QVariantList);
    void ChangeDBLove(int,QString,bool,bool);
    void DeleteDB(int,QString);
    void PlayNothing();
    void DownButtonClicked(QString,QString,QString,QString);
    void MusicSongLyricsTime(QStringList,QStringList);

    void NoNextPlayMusic();
    void PlayListEnd();
private:
    void View_Init();
    //model
    PlayModelTableModel* tableModel;
    //delegate
    PlayListTableDelegate* tableDelegate;

    int mid;
};


#endif //PLAYLISTVIEW_H_
