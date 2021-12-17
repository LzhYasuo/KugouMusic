#include "SearchHeadDelegate.h"
#include <QTextOption>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QByteArray>
#include <QEvent>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QApplication>
#include <QToolTip>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>

SearchHeadModelItem::SearchHeadModelItem(QObject *parent)
    :QObject (parent)
{

}

SearchHeadModelItem::~SearchHeadModelItem()
{

}

QString SearchHeadModelItem::Get_VoiceName()
{
    return VoiceName;
}

void SearchHeadModelItem::Set_VoiceName(QString msg)
{
    VoiceName = msg;
}

//QString SearchHeadModelItem::Get_VoiceUrl()
//{
//    return VoiceUrl;
//}

//void SearchHeadModelItem::Set_VoiceUrl(QString t)
//{
//    VoiceUrl = t;
//}

QString SearchHeadModelItem::Get_Singer()
{
    return mSinger;
}

void SearchHeadModelItem::Set_Singer(QString s)
{
    mSinger = s;
}

QString SearchHeadModelItem::Get_Album()
{
    return AlbumName;
}

void SearchHeadModelItem::Set_Album(QString s)
{
    AlbumName = s;
}

bool SearchHeadModelItem::Get_Clicked()
{
    return isClicked;
}

void SearchHeadModelItem::Set_Clicked(bool C)
{
    isClicked = C;
}

QString SearchHeadModelItem::Get_SongTime()
{
    return SongTime;
}

void SearchHeadModelItem::Set_SongTime(QString s)
{
    SongTime = s;
}

QString SearchHeadModelItem::Get_LastName()
{
    return lastName;
}

void SearchHeadModelItem::Set_LastName(QString s)
{
    lastName = s;
}



SearchHeadTableModel::SearchHeadTableModel()
{
    SearchHeadModelItem* item = new SearchHeadModelItem();
    item->Set_VoiceName("歌曲名");
    item->Set_Clicked(false);
    item->Set_Singer("歌手");
    item->Set_Album("专辑");
    item->Set_SongTime("时长");
    item->Set_LastName("操作");
    List.push_back(item);
}

SearchHeadTableModel::~SearchHeadTableModel()
{

}

int SearchHeadTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int SearchHeadTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 6;
}

QVariant SearchHeadTableModel::data(const QModelIndex &index, int role) const
{
    if(/*!index.isValid() ||*/ List.size() < 1)
        return QVariant();
    //居中
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == 0)
        {
            return List.at(index.row())->Get_Clicked();
        }
        else if(index.column() == 1)
        {
            return List.at(index.row())->Get_VoiceName();
        }
        else if(index.column() == 2)
        {
            return List.at(index.row())->Get_Singer();
        }
        else if(index.column() == 3)
        {
            return List.at(index.row())->Get_Album();
        }
        else if(index.column() == 4)
        {
            return List.at(index.row())->Get_SongTime();
        }
        else if(index.column() == 5)
        {
            return List.at(index.row())->Get_LastName();
        }
    }
    return QVariant();
}

QVariant SearchHeadTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            return "";
        }
        else if(orientation == Qt::Vertical)
        {
            return "aaaaaaaaaa";
        }
    }
    return QVariant();
}

bool SearchHeadTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || List.size() < 1)
        return false;
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if(index.column() == 0)
        {
            List.at(index.row())->Set_Clicked(value.toBool());
        }
        else if(index.column() == 1)
        {
            List.at(index.row())->Set_VoiceName(value.toString());
        }
        else if(index.column() == 2)
        {
            List.at(index.row())->Set_Singer(value.toString());
        }
        else if(index.column() == 3)
        {

        }
    }
    return false;
}

void SearchHeadTableModel::RefrushModel(SearchHeadModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void SearchHeadTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void SearchHeadTableModel::SetNameList(QStringList List)
{
    msg = List;
}

void SearchHeadTableModel::PushBackList()
{
    SearchHeadModelItem* item = new SearchHeadModelItem();
    item->Set_VoiceName("歌曲名");
    item->Set_Clicked(false);
    item->Set_Singer("歌手");
    item->Set_Album("专辑");
    item->Set_SongTime("时长");
    item->Set_LastName("操作");
    List.push_back(item);
}


SearchHeadTableDelegate::SearchHeadTableDelegate(QObject *parent)
    :QStyledItemDelegate(parent),
      btn_Play(new QPushButton()),
      btn_Add(new QPushButton()),
      btn_Down(new QPushButton()),
      ChooseMusic(new QCheckBox())
{
    btn_Play->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/SearchModelImg/Paint/play.png);} \
                                 QPushButton:hover {image:url(:/SearchModelImg/Paint/play_hover.png);} \
                                 QPushButton:pressed {image:url(:/SearchModelImg/Paint/play_Press.png);}");

    btn_Add->setStyleSheet("QPushButton {border: none; background-color: transparent; image: url(:/SearchModelImg/Paint/add.png);} \
                                 QPushButton:hover {image: url(:/SearchModelImg/Paint/add_hover.png);} \
                                 QPushButton:pressed {image: url(:/SearchModelImg/Paint/add_press.png);}");

    btn_Down->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/SearchModelImg/Paint/down.png);} \
                                 QPushButton:hover {image:url(:/SearchModelImg/Paint/down_hover.png);} \
                                 QPushButton:pressed {image:url(:/SearchModelImg/Paint/down_press.png);}");


    WarnningText<< "打开" << "载入" << "下载";
}

SearchHeadTableDelegate::~SearchHeadTableDelegate()
{
    btn_Add->deleteLater();
    btn_Play->deleteLater();
    btn_Down->deleteLater();
    ChooseMusic->deleteLater();
}

void SearchHeadTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor FullColor = QColor();
    painter->setPen(QColor(150,150,150));
    FullColor = QColor(230,230,230);
    if(index.column() == 0)
    {
        QStyleOptionButton CheckBoxOption;
        CheckBoxOption.palette = QPalette(QColor(150,150,150));
        CheckBoxOption.state |= QStyle::State_Enabled;
        bool checked = index.model()->data(index,Qt::DisplayRole).toBool();
        if(checked)
            CheckBoxOption.state |= QStyle::State_On;
        else
            CheckBoxOption.state |= QStyle::State_Off;
        CheckBoxOption.rect = CheckBoxRect(option);
        QWidget* pWidget = ChooseMusic;
        if(index.row() == 0)
        {
            ChooseMusic->setStyleSheet("QCheckBox{color:rgb(150,150,150);}");
        }
        else
        {
            ChooseMusic->setStyleSheet("");
        }
        painter->fillRect(option.rect,QBrush(FullColor));
        pWidget->style()->drawControl(QStyle::CE_CheckBox,&CheckBoxOption,painter,pWidget);
    }
    if(index.column() == 1)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        painter->fillRect(option.rect,QBrush(FullColor));
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 2)
    {
        QString msg = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption x;
        x.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        painter->fillRect(option.rect,QBrush(FullColor));
        painter->drawText(option.rect,msg,x);
    }
    else if(index.column() == 3)
    {
        QString msg = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption x;
        x.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        painter->fillRect(option.rect,QBrush(FullColor));
        painter->drawText(option.rect,msg,x);
    }
    else if(index.column() == 4)
    {
        QString msg = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption x;
        x.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        painter->fillRect(option.rect,QBrush(FullColor));
        painter->drawText(option.rect,msg,x);
    }
    else if(index.column() == 5)
    {
        painter->fillRect(option.rect,QBrush(FullColor));
        QString msg = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption x;
        x.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        painter->fillRect(option.rect,QBrush(FullColor));
        painter->drawText(option.rect,msg,x);
    }
}

QRect SearchHeadTableDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&checkBoxStyleOption);
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x()+viewItemStyleOptions.rect.width()/2-checkBoxRect.width()/2,
                         viewItemStyleOptions.rect.y()+viewItemStyleOptions.rect.height()/2-checkBoxRect.height()/2);
    return QRect(checkBoxPoint,checkBoxRect.size());
}

bool SearchHeadTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    bool RState = false;
    QModelIndex mIndex = index.model()->index(0,99);
    bool isHead = index.model()->data(mIndex,Qt::DisplayRole).toBool();
    if(index.column() == 0)
    {
        if((event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::MouseButtonDblClick))
        {
            if(mouse_event->button() != Qt::LeftButton )
            {
                return false;
            }

            if(event->type() == QEvent::MouseButtonDblClick)
            {
                return false;
            }
            if(isHead)
            {
                model->setData(index,!(model->data(index).toBool()));
            }
            else
            {
                model->setData(index,!(model->data(index).toBool()));
            }
            RState = true;
        }
    }
    return RState;
}
