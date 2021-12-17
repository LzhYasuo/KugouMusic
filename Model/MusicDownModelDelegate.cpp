#include "MusicDownModelDelegate.h"
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

MusicDownModelItem::MusicDownModelItem(QObject *parent)
    :QObject (parent)
{

}

MusicDownModelItem::~MusicDownModelItem()
{

}

int MusicDownModelItem::getState() const
{
    return State;
}

void MusicDownModelItem::setState(int value)
{
    State = value;
}

QString MusicDownModelItem::getMusicName() const
{
    return MusicName;
}

void MusicDownModelItem::setMusicName(const QString &value)
{
    MusicName = value;
}

QString MusicDownModelItem::getMusicSinger() const
{
    return MusicSinger;
}

void MusicDownModelItem::setMusicSinger(const QString &value)
{
    MusicSinger = value;
}


int MusicDownModelItem::getNowBar() const
{
    return NowBar;
}

void MusicDownModelItem::setNowBar(int value)
{
    NowBar = value;
}

QString MusicDownModelItem::getMusicSize() const
{
    return MusicSize;
}

void MusicDownModelItem::setMusicSize(const QString &value)
{
    MusicSize = value;
}

int MusicDownModelItem::getTotalBar() const
{
    return TotalBar;
}

void MusicDownModelItem::setTotalBar(int value)
{
    TotalBar = value;
}

QString MusicDownModelItem::getMusicUrl() const
{
    return MusicUrl;
}

void MusicDownModelItem::setMusicUrl(const QString &value)
{
    MusicUrl = value;
}

QString MusicDownModelItem::getMVUrl() const
{
    return MVUrl;
}

void MusicDownModelItem::setMVUrl(const QString &value)
{
    MVUrl = value;
}

QString MusicDownModelItem::getTotalTime() const
{
    return TotalTime;
}

void MusicDownModelItem::setTotalTime(const QString &value)
{
    TotalTime = value;
}

QString MusicDownModelItem::getMusicPath() const
{
    return MusicPath;
}

void MusicDownModelItem::setMusicPath(const QString &value)
{
    MusicPath = value;
}


MusicDownTableModel::MusicDownTableModel()
{
    //    for(int i = 0; i < 15; i++)
    //    {
    //        MusicDownModelItem* item = new MusicDownModelItem();
//        item->setMusicSize("4.44M");
//        item->setNowBar(i);
//        item->setTotalBar(30);
//        item->setMusicName("富士山下");
//        item->setMusicSinger("陈奕迅");
//        item->setState(0);
//        List.push_back(item);
//    }

}

MusicDownTableModel::~MusicDownTableModel()
{

}

int MusicDownTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int MusicDownTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 1;
}

QVariant MusicDownTableModel::data(const QModelIndex &index, int role) const
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
            QVariantList var;
            var.push_back(List.at(index.row())->getState());
            var.push_back(List.at(index.row())->getMusicName());
            var.push_back(List.at(index.row())->getMusicSinger());
            var.push_back(List.at(index.row())->getTotalBar());
            var.push_back(List.at(index.row())->getNowBar());
            var.push_back(List.at(index.row())->getMusicSize());
            return var;
        }
    }
    return QVariant();
}

QVariant MusicDownTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool MusicDownTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
            QVariantList var = value.toList();
            List.at(index.row())->setState(var.at(0).toInt());

        }
        RefrushModelData();
        return true;
    }
    return false;
}

void MusicDownTableModel::RefrushModel(MusicDownModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void MusicDownTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void MusicDownTableModel::AddListData(QVariantList var)
{
    MusicDownModelItem* Item = new MusicDownModelItem();
    Item->setState(0);
    Item->setMusicName(var.at(0).toString());
    Item->setMusicSinger(var.at(1).toString());
    Item->setMusicSize(var.at(2).toString());
    Item->setTotalBar(var.at(3).toInt());
    Item->setNowBar(0);
    if(var.at(5).toBool())
    {
        Item->setMVUrl(var.at(4).toString());
    }
    else
        Item->setMusicUrl(var.at(4).toString());
    Item->setTotalTime(var.at(6).toString());
    Item->setMusicPath(var.at(7).toString());
    List.append(Item);
    this->RefrushModelData();
}



MusicDownTableDelegate::MusicDownTableDelegate(QObject *parent)
    :QStyledItemDelegate(parent),
      StopBar(new QProgressBar),
        mBar(new QProgressBar()),
      btn_Delete(new QPushButton())
{

    StopBar->setStyleSheet(
        "QProgressBar{ \
    border: none; \
    text-align: center; \
    background: rgb(100, 100, 100); \
        border-radius:10px; \
    }\
    QProgressBar::chunk { \
    background: rgb(100, 100, 100);\
        border-radius:10px;\
    }"
    );

    mBar->setStyleSheet(
    "QProgressBar{ \
    border: none; \
    text-align: center; \
    background: rgb(170, 170, 170); \
        border-radius:10px; \
    }\
    QProgressBar::chunk { \
    background: rgb(0, 170, 255);\
        border-radius:10px;\
    }");



    btn_Delete->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/delete_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/delete_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/delete_1_3.png);}");



    WarnningText<< "打开" << "载入" << "下载";
}

MusicDownTableDelegate::~MusicDownTableDelegate()
{
    mBar->deleteLater();
    btn_Delete->deleteLater();
}

void MusicDownTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nTop =  (option.rect.height() - mHeight) / 2;
    int SongNameWidth = 90;
    int ProWidth = 110;
    int SizeWidth = 80;
    int StateHeight = 20;

    int SongNameLeft = mWidth;
    int ProLeft = SongNameLeft + mSpacing + SongNameWidth;
    int SizeLeft = ProLeft + mSpacing + ProWidth;

    if(index.column() == 0)
    {
        QVariantList List = index.data(Qt::DisplayRole).toList();
        if(List.size() < 1)
            return;
        int State = List.at(0).toInt();
        QString MusicNameSinger = List.at(2).toString() + "-" + List.at(1).toString();
        int TotalSize = List.at(3).toInt();
        int NowSize = List.at(4).toInt();
        QString MusicSize = List.at(5).toString();
        if(State == 0)
        {
            QRect SongTextRect(option.rect.left() + SongNameLeft,option.rect.top() + nTop,SongNameWidth,StateHeight);
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,MusicNameSinger,o);

            // 设置进度条的风格
            QStyleOptionProgressBar progressBarOption;
            progressBarOption.initFrom(option.widget);
            // 设置进度条显示的区域
            progressBarOption.rect = QRect(option.rect.left() + ProLeft, option.rect.top() + nTop,  ProWidth, StateHeight);
            // 设置最小值
            progressBarOption.minimum = 0;
            // 设置最大值
            progressBarOption.maximum = TotalSize;
            // 设置对齐方式
            progressBarOption.textAlignment = Qt::AlignCenter;
            // 设置进度
            progressBarOption.progress = NowSize;
            // 设置文本（百分比）
            progressBarOption.text = QString("%1%").arg((double(NowSize) / double(TotalSize)) * 100);
            // 设置文本可见
            progressBarOption.textVisible = true;


            //绘制进度条
            mBar->style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, mBar);

            QRect TimeTextRect(option.rect.left() + SizeLeft,option.rect.top() + nTop,SizeWidth,StateHeight);
            QString mos1 = index.model()->data(index,Qt::DisplayRole).toString();
            o.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            painter->drawText(TimeTextRect,MusicSize,o);
        }
        else if(State == 1)
        {
            QRect SongTextRect(option.rect.left() + SongNameLeft,option.rect.top() + nTop,SongNameWidth,StateHeight);
            QString mos = index.model()->data(index,Qt::DisplayRole).toString();
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,MusicNameSinger,o);

            // 设置进度条的风格
            QStyleOptionProgressBar progressBarOption;
            progressBarOption.initFrom(option.widget);
            // 设置进度条显示的区域
            progressBarOption.rect = QRect(option.rect.left() + ProLeft, option.rect.top() + nTop,  ProWidth, StateHeight);
            // 设置最小值
            progressBarOption.minimum = 0;
            // 设置最大值
            progressBarOption.maximum = TotalSize;
            // 设置对齐方式
            progressBarOption.textAlignment = Qt::AlignCenter;
            // 设置进度
            progressBarOption.progress = NowSize;
            // 设置文本（百分比）
            progressBarOption.text = QString("%1%").arg((double(NowSize) / double(TotalSize)) * 100);
            // 设置文本可见
            progressBarOption.textVisible = true;

            //绘制进度条
            StopBar->style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, StopBar);

            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing + 10),
                                option.rect.top() + nTop,  mWidth, mHeight);
            button.state |= QStyle::State_Enabled;
            if(button.rect.contains(MousePoint))
            {
                if(ButtonState == 1)
                {
                    button.state |= QStyle::State_MouseOver;
                }
                else if(ButtonState == 2)
                {
                    button.state |= QStyle::State_Sunken;
                }
            }

            btn_Delete->style()->drawControl(QStyle::CE_PushButton, &button, painter, btn_Delete);
        }
    }
}

QRect MusicDownTableDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&checkBoxStyleOption);
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x()+viewItemStyleOptions.rect.width()/2-checkBoxRect.width()/2,
                         viewItemStyleOptions.rect.y()+viewItemStyleOptions.rect.height()/2-checkBoxRect.height()/2);
    return QRect(checkBoxPoint,checkBoxRect.size());
}

bool MusicDownTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    int nTop =  (option.rect.height() - mHeight) / 2;
    int SongNameWidth = 90;
    int ProWidth = 110;
    int SongNameLeft = mWidth;
    int ProLeft = SongNameLeft + mSpacing + SongNameWidth;
    int SizeLeft = ProLeft + mSpacing + ProWidth;

    bool RState = false;
    QVariantList List = index.data(Qt::DisplayRole).toList();
    if(List.size() < 1)
        return RState;
    int State = List.at(0).toInt();
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    MousePoint = mouse_event->pos();
    if(event->type() == QEvent::MouseMove)
    {
        if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing + 10),
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                ButtonState = 1;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing  + 10),
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                ButtonState = 2;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing  + 10),
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                qDebug() << index.row() << " : =DeleteR";
            }
        }
    }
    return RState;
}


#if 0
bool MusicDownTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    int nTop =  (option.rect.height() - mHeight) / 2;
    int SongNameWidth = 100;
    int ProWidth = 120;
    int SongNameLeft = mWidth;
    int ProLeft = SongNameLeft + mSpacing + SongNameWidth;
    int SizeLeft = ProLeft + mSpacing + ProWidth;

    for(int i = 0; i < model->rowCount(); i++)
    {
        QVariantList var;
        var.push_back(0);
        model->setData(model->index(i,0),var,Qt::DisplayRole);
    }

    bool RState = false;
    QVariantList List = index.data(Qt::DisplayRole).toList();
    if(List.size() < 1)
        return RState;
    int State = List.at(0).toInt();
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    MousePoint = mouse_event->pos();
    if(event->type() == QEvent::MouseMove)
    {
        if(index.column() == 0)
        {
            if(option.rect.contains(MousePoint))
            {
                QVariantList var;
                var.push_back(1);
                model->setData(index,var);
//                for(int i = 0; i < model->rowCount(); i++)
//                {
//                    QVariantList List = model->index(i,0).data(Qt::DisplayRole).toList();
//                    if(i == index.row())
//                        continue;
//                    QVariantList var;
//                    var.push_back(0);
//                    model->setData(model->index(i,0),var,Qt::DisplayRole);
//                }

                if(State == 1)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((option.rect.left() + SizeLeft + mSpacing),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if(button.rect.contains(MousePoint))
                    {
                        ButtonState = 1;
                    }
                }
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing),
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                ButtonState = 2;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect((option.rect.left() + SizeLeft + mSpacing),
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                qDebug() << index.row() << " : =DeleteR";
            }
        }
    }
    return RState;
}
#endif
