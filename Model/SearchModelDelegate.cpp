#include "SearchModelDelegate.h"
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

SearchModelItem::SearchModelItem(QObject *parent)
    :QObject (parent)
{

}

SearchModelItem::~SearchModelItem()
{

}

QString SearchModelItem::Get_VoiceName()
{
    return VoiceName;
}

void SearchModelItem::Set_VoiceName(QString msg)
{
    VoiceName = msg;
}

//QString SearchModelItem::Get_VoiceUrl()
//{
//    return VoiceUrl;
//}

//void SearchModelItem::Set_VoiceUrl(QString t)
//{
//    VoiceUrl = t;
//}

QString SearchModelItem::Get_Singer()
{
    return mSinger;
}

void SearchModelItem::Set_Singer(QString s)
{
    mSinger = s;
}

QString SearchModelItem::Get_Album()
{
    return AlbumName;
}

void SearchModelItem::Set_Album(QString s)
{
    AlbumName = s;
}

bool SearchModelItem::Get_Clicked()
{
    return isClicked;
}

void SearchModelItem::Set_Clicked(bool C)
{
    isClicked = C;
}

QString SearchModelItem::Get_SongTime()
{
    return SongTime;
}

void SearchModelItem::Set_SongTime(QString s)
{
    SongTime = s;
}

QString SearchModelItem::Get_Hash()
{
    return hash;
}

void SearchModelItem::Set_Hash(QString s)
{
    hash = s;
}

QString SearchModelItem::Get_MVHash()
{
    return mvhash;
}

void SearchModelItem::Set_MVHash(QString s)
{
    mvhash = s;
}

QString SearchModelItem::Get_AlbumID()
{
    return AlbumID;
}

void SearchModelItem::Set_AlbumID(QString s)
{
    AlbumID = s;
}



SearchTableModel::SearchTableModel()
{

}

SearchTableModel::~SearchTableModel()
{

}

int SearchTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int SearchTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 6;
}

QVariant SearchTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || List.size() < 1)
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
            return List.at(index.row())->Get_MVHash();
        }
    }
    return QVariant();
}

QVariant SearchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            return "";
        }
        else if(orientation == Qt::Vertical)
        {
            return "";
        }
    }
    return QVariant();
}

bool SearchTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
        else if(index.column() == 5)
        {

        }
    }
    return false;
}

void SearchTableModel::RefrushModel(SearchModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void SearchTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void SearchTableModel::SetNameList(QStringList List)
{
    msg = List;
}

void SearchTableModel::PushBackList(QList<QVariantList> var)
{
    for(int i = 0; i < var.size(); i++)
    {
        SearchModelItem* item = new SearchModelItem();
        item->Set_VoiceName(var.at(i).at(0).toString());
        item->Set_Clicked(false);
        item->Set_Singer(var.at(i).at(1).toString());
        item->Set_Album(var.at(i).at(2).toString());
        item->Set_SongTime(var.at(i).at(3).toString());
        item->Set_Hash(var.at(i).at(4).toString());
        item->Set_MVHash(var.at(i).at(5).toString());
        item->Set_AlbumID(var.at(i).at(6).toString());
        List.push_back(item);
    }
    RefrushModelData();

}

void SearchTableModel::ReMoveAll()
{
    List.clear();
}


SearchTableDelegate::SearchTableDelegate(QObject *parent)
    :QStyledItemDelegate(parent),
      btn_Play(new QPushButton()),
      btn_Add(new QPushButton()),
      btn_Down(new QPushButton()),
      btn_MV(new QPushButton()),
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

    btn_MV->setStyleSheet("QPushButton {border: none; background-color: transparent; image: url(:/PlayList/Paint/PlayList/mv_1_1.png);} \
                                 QPushButton:hover {image: url(:/PlayList/Paint/PlayList/mv_1_2.png);} \
                                 QPushButton:pressed {image: url(:/PlayList/Paint/PlayList/mv_1_3.png);}");




    WarnningText<< "打开" << "载入" << "下载";
}

SearchTableDelegate::~SearchTableDelegate()
{
    btn_Add->deleteLater();
    btn_Play->deleteLater();
    btn_Down->deleteLater();
    ChooseMusic->deleteLater();
}

void SearchTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor FullColor = QColor();
#if 0
    if(index.row() == 0)
    {
        painter->setPen(QColor(150,150,150));
    }
    else
    {
        painter->setPen(QColor(50,50,50));
    }
    if(index.row() % 2 == 0)
    {
        FullColor = QColor(230,230,230);
    }
    else if(index.row() % 2 == 1)
    {
        FullColor = QColor(255,255,255);
    }
#endif
    FullColor = QColor(255,255,255);
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
        int nHalf = (option.rect.width() - mWidth * ButtonSize - mSpacing * (ButtonSize - 1)) / 2;
        int nTop =  (option.rect.height() - mHeight) / 2;
        for(int i = 0; i < ButtonSize; i++)
        {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() + nHalf + mWidth * i + mSpacing * i,
                                option.rect.top() + nTop,  mWidth, mHeight);
            button.state |= QStyle::State_Enabled;
            if (button.rect.contains(MousePoint))
            {
                if(ButtonState == 1)
                {
                    //小部件是否在鼠标下面
                    button.state |= QStyle::State_MouseOver;
                }
                //按钮按下
                else if(ButtonState == 2)
                {
                    //小部件是否按下
                    button.state |= QStyle::State_Sunken;
                }
            }
            QWidget* pWidget = nullptr;
            if(i == 0)
            {
                if(!index.model()->data(index,Qt::DisplayRole).toString().isEmpty())
                {
                    pWidget = btn_MV;
                    pWidget->style()->drawControl(QStyle::CE_PushButton, &button, painter,pWidget);
                }
            }
            else if(i == 1)
            {
                pWidget = btn_Play;
                pWidget->style()->drawControl(QStyle::CE_PushButton, &button, painter,pWidget);
            }
            else if(i == 2)
            {
                pWidget = btn_Add;
                pWidget->style()->drawControl(QStyle::CE_PushButton, &button, painter,pWidget);
            }
            else if(i == 3)
            {
                pWidget = btn_Down;
                pWidget->style()->drawControl(QStyle::CE_PushButton, &button, painter,pWidget);
            }
        }
    }
}

QRect SearchTableDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&checkBoxStyleOption);
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x()+viewItemStyleOptions.rect.width()/2-checkBoxRect.width()/2,
                         viewItemStyleOptions.rect.y()+viewItemStyleOptions.rect.height()/2-checkBoxRect.height()/2);
    return QRect(checkBoxPoint,checkBoxRect.size());
}

bool SearchTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    bool RState = false;
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
            model->setData(index,!(model->data(index).toBool()));
            RState = true;
        }
    }
    else if(index.column() == 5)
    {
        MousePoint = mouse_event->pos();

        for (int i = 0; i < ButtonSize; ++i)
        {
            QStyleOptionButton button;
            int nHalf = (option.rect.width() - mWidth * ButtonSize - mSpacing * (ButtonSize - 1)) / 2;
            int nTop =  (option.rect.height() - mHeight) / 2;
            button.rect = QRect(option.rect.left() + nHalf + mWidth * i + mSpacing * i,
                                option.rect.top() + nTop,  mWidth, mHeight);

            if (!button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::ArrowCursor);
                ButtonState = 0;
                continue;
            }
            RState = true;
            if(i == 0)
            {
                if(index.model()->data(index,Qt::DisplayRole).toString().isEmpty())
                {
                    break;
                }
            }
            if(event->type() == QEvent::MouseMove)
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 1;
                break;
            }
            if(event->type() == QEvent::MouseButtonPress && mouse_event->button() == Qt::LeftButton)
            {
                ButtonState = 2;
                break;
            }
            else if(event->type() == QEvent::MouseButtonRelease && mouse_event->button() == Qt::LeftButton)
            {
                if(i == 0)
                {
                    emit MVButtonClicked(index.row());
                }
                else if(i == 1)
                {
                    emit PlayButtonClicked(index.row());
                }
                else if(i == 2)
                {
                    emit AddButtonClicked(index.row());
                }
                else if(i == 3)
                {
                    emit DownButtonClicked(index.row());
                }
                break;
            }
        }
    }
    return RState;
}
