#ifndef D_MODEL_DELEGATE_H_
#define D_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QPushButton>
#include <QCheckBox>

class MusicDownEndModelItem : public QObject
{
    Q_OBJECT
public:
    MusicDownEndModelItem(QObject* parent = nullptr);
    ~MusicDownEndModelItem();

    QString Get_VoiceName();
    void Set_VoiceName(QString);

    QString Get_Singer();
    void Set_Singer(QString s);

    bool Get_Clicked();
    void Set_Clicked(bool);

    QString Get_SongTime();
    void Set_SongTime(QString s);

    int Get_ListState();
    void Set_ListState(int);

    QString getMVUrl() const;
    void setMVUrl(const QString &value);

    QString getMusicUrl() const;
    void setMusicUrl(const QString &value);

    QString getSize() const;
    void setSize(const QString &value);

    bool getIsLove() const;
    void setIsLove(bool value);

private:
    int ListState;
    QString VoiceName;
    QString mSinger;
    QString SongTime;
    QString MVUrl;
    QString MusicUrl;
    QString Size;
    bool isLove;
};


class MusicDownEndTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MusicDownEndTableModel();
    ~MusicDownEndTableModel();

//    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(MusicDownEndModelItem*);
    void RefrushModelData();

    void AddListData(QVariantList);
    void AddDBDataList(QList<QVariantList> List);

    QList<MusicDownEndModelItem*> Get_List() {return List;}

    int Get_NowPlayRow() const {return TableNowRow;}
    void Set_NowPlayRow(int Row) {TableNowRow = Row;}

    void RemoveRow(int row);
private:
    QList<MusicDownEndModelItem*> List;
    int TableNowRow = -1;
};

class MusicDownEndTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MusicDownEndTableDelegate(QObject *parent = nullptr);
    virtual ~MusicDownEndTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;

signals:
    void OpenFileSignal(const QModelIndex& index);
    void DeleteSignal(const QModelIndex& index);
    void LoveSignal(const QModelIndex& index);
private:
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

private:
    /*QScopedPointer<*/QPushButton* btn_Love;
    QPushButton* btn_Delete;
    QPushButton* btn_Menu;
    QPushButton* btn_Down;
    QPushButton* btn_File;
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

#endif //D_MODEL_DELEGATE_H_
