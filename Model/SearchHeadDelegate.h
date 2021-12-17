#ifndef SEARCH_HEAD_MODEL_DELEGATE_H_
#define SEARCH_HEAD_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QPushButton>
#include <QCheckBox>

class SearchHeadModelItem : public QObject
{
    Q_OBJECT
public:
    SearchHeadModelItem(QObject* parent = nullptr);
    ~SearchHeadModelItem();

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

    QString Get_LastName();
    void Set_LastName(QString s);
private:
    QString VoiceName;
    QString mSinger;
    QString VoiceUrl;
    QString AlbumName;
    QString SongTime;
    QString lastName;
    bool isClicked;
};


class SearchHeadTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    SearchHeadTableModel();
    ~SearchHeadTableModel();

//    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(SearchHeadModelItem*);
    void RefrushModelData();
    void SetNameList(QStringList);

    void PushBackList();

    QList<SearchHeadModelItem*> Get_List() {return List;}

private:
    bool mHead;
    QList<SearchHeadModelItem*> List;
    QStringList msg;
};

class SearchHeadTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SearchHeadTableDelegate(QObject *parent = nullptr);
    virtual ~SearchHeadTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;
private:
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

private:
    /*QScopedPointer<*/QPushButton* btn_Play;
    /*QScopedPointer<*/QPushButton* btn_Add;
    /*QScopedPointer<*/QPushButton* btn_Down;
    QCheckBox* ChooseMusic;
    const int mWidth = 25;
    const int mHeight = 20;
    const int mSpacing = 5;
    const int ButtonSize = 3;
    QPoint MousePoint;
    int ButtonState;
    QStringList WarnningText;
};

#endif //SEARCH_HEAD_MODEL_DELEGATE_H_
