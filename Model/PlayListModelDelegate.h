#ifndef _PLAYLIST_MODEL_DELEGATE_H_
#define _PLAYLIST_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QPushButton>
#include <QCheckBox>
#include <QMutex>
#include <qDebug>

class PlayListModelItem : public QObject
{
    Q_OBJECT
public:
    PlayListModelItem(QObject* parent = nullptr);
    ~PlayListModelItem();

    QString Get_VoiceName();
    void Set_VoiceName(QString);

    QString Get_Singer();
    void Set_Singer(QString s);

    bool Get_Clicked();
    void Set_Clicked(bool);

    QString Get_SongTime();
    void Set_SongTime(QString s);

/*    QString Get_LastName();
    void Set_LastName(QString s)*/;

    int Get_ListState();
    void Set_ListState(int);

    QString Get_PlayMusicUrl();
    void Set_PlayMusicUrl(QString);

    QString Get_PlayMVMusicUrl();
    void Set_PlayMVMusicUrl(QString);

    QString Get_NowTime();
    void Set_NowTime(QString);

    bool Get_isLove();
    void Set_isLove(bool);

    QMap<QStringList, QStringList> getSongLyciesTime() const;
    void setSongLyciesTime(const QMap<QStringList, QStringList> &value);

    QStringList getSongLycies() const;
    void setSongLycies(const QStringList &value);

    QStringList getLyciesTime() const;
    void setLyciesTime(const QStringList &value);

private:
    int ListState;
    QString VoiceName;
    QString mSinger;
    QString SongTime;
    //    QString lastName;
    QString MVUrl;
    QString MusicUrl;
    QString NowTime;
    bool isLove;
    bool isClicked;
    QStringList SongLycies;
    QStringList LyciesTime;
    QMap<QStringList,QStringList> SongLyciesTime;
};


class PlayModelTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    PlayModelTableModel();
    ~PlayModelTableModel();

//    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(PlayListModelItem*);
    void RefrushModelData();
    void PushBackData(QVariantList);
    void InitData(QVariantList);
    void RemoveRow(int row);

    int Get_NowPlayRow() const {return mNowPlayRow;}
    void Set_NowPlayRow(int row) {mNowPlayRow = row;}
    void AddPlayNextMusic(int row) {PlayNextList.push_back(row);}
    QList<PlayListModelItem*> Get_List() {return List;}
    int Get_Size() const {return List.size();}
    int Get_PlayNextList() const {return PlayNextList.size();}
    int Take_PlayNextList() {return PlayNextList.takeFirst();}
    int Get_MVListSize() const{return MVList.size();}
    int Get_NextMVRow(int row) const;
    int Get_PreMVRow(int row) const;
    int Get_FirstMVRow() const {return MVList.at(0);}
    QList<int> Get_MVList() const {return MVList;}
    QMutex mutex;

private:
    QList<int> MVList;
    QList<int> PlayNextList;
    QList<PlayListModelItem*> List;
    int mNowPlayRow = -1;
};

class PlayListTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit PlayListTableDelegate(QObject *parent = nullptr);
    virtual ~PlayListTableDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;
private:
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

signals:
    void AddButtonClicked(const QModelIndex& index);
    void MVButtonClicked(const QModelIndex& index);
    void DownButtonClicked(const QModelIndex& index);
    void LoveButtonClicked(const QModelIndex& index);
    void DeleteButtonClicked(const QModelIndex& index);
    void MenuCButtonClicked(int row);
private:
    /*QScopedPointer<*/QPushButton* btn_Add;
    /*QScopedPointer<*/QPushButton* btn_MV;
    /*QScopedPointer<*/QPushButton* btn_Love;
    QPushButton* btn_Delete;
    QPushButton* btn_Menu;
    QPushButton* btn_Down;
    QPushButton* btn_RedLove;
    const int mWidth = 15;
    const int mHeight = 17;
    const int mSpacing = 12;
    const int ButtonSize = 3;
    QPoint MousePoint;
    int ButtonState;
    int ListState;
    QStringList WarnningText;
};

#endif //_PLAYLIST_MODEL_DELEGATE_H_
