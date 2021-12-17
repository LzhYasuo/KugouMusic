#ifndef Music_Down_End_TableView_H_
#define Music_Down_End_TableView_H_

#include <QWidget>
#include <QTableView>

enum MusicDownOrderRamdom
{
    MusicDownOrder,
    MusicDownRamdom
};

enum MusicDownPreNex
{
    MusicDownPre,
    MusicDownNext,
};

class MusicDownEndTableModel;
class MusicDownEndTableDelegate;
class MusicDownEndTableView : public QTableView
{
    Q_OBJECT
public:
    MusicDownEndTableView(QWidget* parent = nullptr);
    ~MusicDownEndTableView();

    void mouseMoveEvent(QMouseEvent *event);

    void AddDBDataList(QList<QVariantList>);

    void PlayMVMusicUrl(int row);

    void SwitchMusicMV(MusicDownOrderRamdom,MusicDownPreNex);
public slots:
    void AllTableSetFalse();
    void AddListData(QVariantList List);
    void ClearDownNowPlayRow();

    void SignalMusicModelSlot();
    void OrderOfMusicModelSlot();
    void ListMusicModelSlot();
    void RandomMusicModelSlot();
    void SetLoveState();
signals:
    void OpenUrl(QString);
    void PlayUrl(QString,QString,bool,bool);
    void AddMusicDownDB(QVariantList);

    void ChangeDBLove(QString,bool,bool);
    void PlayNothing();
    void DeleteDB(QString);
private:
    void View_Init();
    //model
    MusicDownEndTableModel* tableModel;
    //delegate
    MusicDownEndTableDelegate* tableDelegate;
};


#endif //Music_Down_End_TableView_H_
