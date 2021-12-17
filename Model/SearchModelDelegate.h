#ifndef D_MODEL_DELEGATE_H_
#define D_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QPushButton>
#include <QCheckBox>

class SearchModelItem : public QObject
{
    Q_OBJECT
public:
    SearchModelItem(QObject* parent = nullptr);
    ~SearchModelItem();

    QString Get_VoiceName();
    void Set_VoiceName(QString);

    QString Get_Singer();
    void Set_Singer(QString s);

    QString Get_Album();
    void Set_Album(QString s);

    bool Get_Clicked();
    void Set_Clicked(bool);

    QString Get_SongTime();
    void Set_SongTime(QString s);

    QString Get_Hash();
    void Set_Hash(QString s);

    QString Get_MVHash();
    void Set_MVHash(QString s);

    QString Get_AlbumID();
    void Set_AlbumID(QString s);
private:
    QString VoiceName;
    QString mSinger;
    QString VoiceUrl;
    QString AlbumName;
    QString SongTime;
    QString hash;
    QString mvhash;
    QString AlbumID;
    bool isClicked;
};


class SearchTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    SearchTableModel();
    ~SearchTableModel();

//    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(SearchModelItem*);
    void RefrushModelData();
    void SetNameList(QStringList);

    void PushBackList(QList<QVariantList>);
    void ReMoveAll();

    QList<SearchModelItem*> Get_List() {return List;}

private:
    bool mHead;
    QList<SearchModelItem*> List;
    QStringList msg;
};

class SearchTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SearchTableDelegate(QObject *parent = nullptr);
    virtual ~SearchTableDelegate();
    void Set_Table(SearchTableModel* t) {table = t;};

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;
private:
    SearchTableModel* table;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

private:
    /*QScopedPointer<*/QPushButton* btn_Play;
    /*QScopedPointer<*/QPushButton* btn_Add;
    /*QScopedPointer<*/QPushButton* btn_Down;
    QPushButton* btn_MV;
    QCheckBox* ChooseMusic;
    const int mWidth = 25;
    const int mHeight = 20;
    const int mSpacing = 5;
    const int ButtonSize = 4;
    QPoint MousePoint;
    int ButtonState;
    QStringList WarnningText;

signals:
    void MVButtonClicked(int row);
    void PlayButtonClicked(int row);
    void AddButtonClicked(int row);
    void DownButtonClicked(int row);
};

#endif //D_MODEL_DELEGATE_H_
