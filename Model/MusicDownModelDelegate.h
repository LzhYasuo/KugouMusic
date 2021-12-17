#ifndef D_MODEL_DELEGATE_H_
#define D_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QPushButton>
#include <QCheckBox>
#include <QProgressBar>

class MusicDownModelItem : public QObject
{
    Q_OBJECT
public:
    MusicDownModelItem(QObject* parent = nullptr);
    ~MusicDownModelItem();


    int getState() const;
    void setState(int value);

    QString getMusicName() const;
    void setMusicName(const QString &value);

    QString getMusicSinger() const;
    void setMusicSinger(const QString &value);

    int getNowBar() const;
    void setNowBar(int value);

    QString getMusicSize() const;
    void setMusicSize(const QString &value);

    int getTotalBar() const;
    void setTotalBar(int value);

    QString getMusicUrl() const;
    void setMusicUrl(const QString &value);

    QString getMVUrl() const;
    void setMVUrl(const QString &value);

    QString getTotalTime() const;
    void setTotalTime(const QString &value);

    QString getMusicPath() const;
    void setMusicPath(const QString &value);

private:
    int State;
    QString MusicName;
    QString MusicSinger;
    QString MusicSize;
    int TotalBar;
    int NowBar;
    QString MusicUrl;
    QString MVUrl;
    QString TotalTime;
    QString MusicPath;
};


class MusicDownTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MusicDownTableModel();
    ~MusicDownTableModel();

//    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(MusicDownModelItem*);
    void RefrushModelData();
    void AddListData(QVariantList List);

    QList<MusicDownModelItem*> Get_List() {return List;}

private:
    QList<MusicDownModelItem*> List;
};

class MusicDownTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MusicDownTableDelegate(QObject *parent = nullptr);
    virtual ~MusicDownTableDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;
private:
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

private:
    QProgressBar* StopBar;
    QProgressBar* mBar;
    QPushButton* btn_Delete;
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
