#include "MusicDownEndModelDelegate.h"
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

MusicDownEndModelItem::MusicDownEndModelItem(QObject *parent)
    :QObject (parent)
{

}

MusicDownEndModelItem::~MusicDownEndModelItem()
{

}

QString MusicDownEndModelItem::Get_VoiceName()
{
    return VoiceName;
}

void MusicDownEndModelItem::Set_VoiceName(QString msg)
{
    VoiceName = msg;
}

QString MusicDownEndModelItem::Get_Singer()
{
    return mSinger;
}

void MusicDownEndModelItem::Set_Singer(QString s)
{
    mSinger = s;
}

//bool MusicDownEndModelItem::Get_Clicked()
//{
//    return isClicked;
//}

//void MusicDownEndModelItem::Set_Clicked(bool C)
//{
//    isClicked = C;
//}

QString MusicDownEndModelItem::Get_SongTime()
{
    return SongTime;
}

void MusicDownEndModelItem::Set_SongTime(QString s)
{
    SongTime = s;
}

int MusicDownEndModelItem::Get_ListState()
{
    return ListState;
}

void MusicDownEndModelItem::Set_ListState(int state)
{
    ListState = state;
}

QString MusicDownEndModelItem::getMVUrl() const
{
    return MVUrl;
}

void MusicDownEndModelItem::setMVUrl(const QString &value)
{
    MVUrl = value;
}

QString MusicDownEndModelItem::getMusicUrl() const
{
    return MusicUrl;
}

void MusicDownEndModelItem::setMusicUrl(const QString &value)
{
    MusicUrl = value;
}

QString MusicDownEndModelItem::getSize() const
{
    return Size;
}

void MusicDownEndModelItem::setSize(const QString &value)
{
    Size = value;
}

bool MusicDownEndModelItem::getIsLove() const
{
    return isLove;
}

void MusicDownEndModelItem::setIsLove(bool value)
{
    isLove = value;
}

MusicDownEndTableModel::MusicDownEndTableModel()
{
    //    for(int i = 0; i < 5; i++)
    //    {
    //        MusicDownEndModelItem* Item = new MusicDownEndModelItem();
//        Item->Set_ListState(0);
//        List.append(Item);
//    }
//    this->RefrushModelData();
}

MusicDownEndTableModel::~MusicDownEndTableModel()
{

}

int MusicDownEndTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int MusicDownEndTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 1;
}

QVariant MusicDownEndTableModel::data(const QModelIndex &index, int role) const
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
            var.push_back(List.at(index.row())->Get_ListState());
            var.push_back(List.at(index.row())->Get_VoiceName());
            var.push_back(List.at(index.row())->Get_Singer());
            var.push_back(List.at(index.row())->getSize());
            var.push_back(List.at(index.row())->Get_SongTime());
            var.push_back(List.at(index.row())->getMVUrl());
            var.push_back(List.at(index.row())->getIsLove());
//            qDebug() << "index.row" << index.row() << "data :" << var.size();
            return var;
        }
    }
    return QVariant();
}

QVariant MusicDownEndTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool MusicDownEndTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
            List.at(index.row())->Set_ListState(var.at(0).toInt());
        }
        RefrushModelData();
        return true;
    }
    return false;
}

void MusicDownEndTableModel::RefrushModel(MusicDownEndModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void MusicDownEndTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void MusicDownEndTableModel::AddListData(QVariantList var)
{
//        var << Name << Singer << Size << Time << Path << isMV;
    MusicDownEndModelItem* Item = new MusicDownEndModelItem();
    Item->Set_ListState(0);
    Item->Set_VoiceName(var.at(0).toString());
    Item->Set_Singer(var.at(1).toString());
    Item->setSize(var.at(2).toString());
    Item->Set_SongTime(var.at(3).toString());
    Item->setIsLove(false);
    if(var.at(5).toBool())
    {
        Item->setMVUrl(var.at(4).toString());
        Item->setMusicUrl("");
    }
    else
    {
        Item->setMusicUrl(var.at(4).toString());
        Item->setMVUrl("");
    }
    List.append(Item);
    this->RefrushModelData();
}

void MusicDownEndTableModel::AddDBDataList(QList<QVariantList> var)
{
    for(int i = 0; i < var.size(); i++)
    {
         MusicDownEndModelItem* Item = new MusicDownEndModelItem();
         Item->Set_ListState(0);
         if(var.at(i).at(5).toBool())
         {
             Item->setMVUrl(var.at(i).at(0).toString());
         }
         else
             Item->setMusicUrl(var.at(i).at(0).toString());
         Item->Set_VoiceName(var.at(i).at(1).toString());
         Item->Set_Singer(var.at(i).at(2).toString());
         Item->Set_SongTime(var.at(i).at(3).toString());
         Item->setSize(var.at(i).at(4).toString());
         Item->setIsLove(var.at(i).at(6).toBool());
         List.append(Item);
    }
    qDebug() << "List.size " << List.size();
    this->RefrushModelData();
}

void MusicDownEndTableModel::RemoveRow(int row)
{
    List.removeAt(row);
}



MusicDownEndTableDelegate::MusicDownEndTableDelegate(QObject *parent)
    :QStyledItemDelegate(parent),
      btn_Love(new QPushButton()),
      btn_Delete(new QPushButton()),
      btn_Menu(new QPushButton()),
      btn_Down(new QPushButton()),
      btn_File(new QPushButton()),
      btn_RedLove(new QPushButton())
{

    btn_Love->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/love_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/love_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/love_1_1.png);}");

    btn_Delete->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/delete_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/delete_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/delete_1_3.png);}");

    btn_Menu->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/muen_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/muen_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/muen_1_3.png);}");

    btn_Down->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/down_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/down_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/down_3.png);}");

    btn_File->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/Left/Paint/Left/btn_File_1.png);} \
                                 QPushButton:hover {image:url(:/Left/Paint/Left/btn_File_2.png);} \
                                 QPushButton:pressed {image:url(:/Left/Paint/Left/btn_File_3.png);}");

    btn_RedLove->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/btn_RedLove.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/btn_RedLove_hover.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/btn_RedLove_press.png);}");



    WarnningText<< "打开" << "载入" << "下载";
}

MusicDownEndTableDelegate::~MusicDownEndTableDelegate()
{
    btn_Love->deleteLater();
    btn_Delete->deleteLater();
    btn_Menu->deleteLater();
}

void MusicDownEndTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nTop =  (option.rect.height() - mHeight) / 2;
    int SongNameWidth = 170;
    int SongNameHeight = 20;
    int SongTimeWidth = 80;
    int SongTimeHeight = 20;
    if(index.column() == 0)
    {
        QVariantList List = index.data(Qt::DisplayRole).toList();
//        qDebug() << "index : " << index.row() << "List :" << index.data(index.row()).toList().size();
        if(List.size() < 7)
            return;
        int State = List.at(0).toInt();
        QString MusicNameSinger = List.at(2).toString() + "-" + List.at(1).toString();
        QString Size = List.at(3).toString();
        QString TotalTime = List.at(4).toString();
        QString MV = List.at(5).toString();
        bool isLove = List.at(6).toBool();
        bool isMV = false;
        if(MV.isEmpty())
            isMV = false;
        else
            isMV = true;
        if(State == 0)
        {
            QRect SongTextRect(option.rect.left() + mWidth,option.rect.top() + nTop,SongNameWidth,SongNameHeight);
            QString mos = index.model()->data(index,Qt::DisplayRole).toString();
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,MusicNameSinger,o);

            QRect TimeTextRect(SongNameWidth + ((mWidth + mSpacing) * 2) + mSpacing,option.rect.top() + nTop,SongTimeWidth,SongTimeHeight);
            QString mos1 = index.model()->data(index,Qt::DisplayRole).toString();
            o.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            painter->drawText(TimeTextRect,Size,o);

        }
        else if(State == 1)
        {
            QRect SongTextRect(option.rect.left() + mWidth,option.rect.top() + nTop,SongNameWidth,SongNameHeight);
            QString mos = index.model()->data(index,Qt::DisplayRole).toString();
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,MusicNameSinger,o);

            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    int nTop =  (option.rect.height() - mHeight) / 2;
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth + mWidth + mSpacing + mWidth + mSpacing+ (mWidth + mSpacing) * i),
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

                    QWidget* pWidget = nullptr;
                    if(i == 0)
                    {
                        pWidget = btn_File;
                    }
                    if(i == 1)
                    {
                        pWidget = btn_Delete;
                    }
                    if(i == 2)
                    {
                        pWidget = btn_Menu;
                    }
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    int nTop =  (option.rect.height() - mHeight) / 2;
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
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

                    QWidget* pWidget = nullptr;
                    if(i == 0)
                    {
                        pWidget = btn_File;
                    }
                    if(i == 1)
                    {
                        if(isLove)
                            pWidget = btn_RedLove;
                        else
                            pWidget = btn_Love;
                    }
                    if(i == 2)
                    {
                        pWidget = btn_Delete;
                    }
                    if(i == 3)
                    {
                        pWidget = btn_Menu;
                    }
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
            }
        }
        else if(State == 2)
        {
            int PaintButtonWidth = 50;
            int PaintButtonHeight = 50;
            int PaintButtonPos = option.rect.left()  + mWidth;
            int SongTextPos = PaintButtonPos + PaintButtonWidth + mSpacing;
            int SongTextTop = option.rect.top() + 5;
            int SongTextHeight = 20;
            int SongTextWidth = SongNameWidth - PaintButtonWidth - mSpacing;
            int SongTimeTop = SongTextTop + SongTextHeight + 5;
            int SongTimeWidth = 100;
            int SongTimeHeight = 15;

            //图片按钮
            QStyleOptionButton buttonPaint;
            buttonPaint.rect = QRect(PaintButtonPos,
                                option.rect.top(),  PaintButtonWidth, PaintButtonHeight);
            buttonPaint.state |= QStyle::State_Enabled;
            QApplication::style()->drawControl(QStyle::CE_PushButton,&buttonPaint,painter);

            //歌名
            QRect SongTextRect(SongTextPos,option.rect.top() + 5,SongTextWidth,SongTextHeight);
            QString mos = MusicNameSinger;
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,mos,o);

            //歌时长
            QRect SongTimeRect(SongTextPos,SongTimeTop,SongTimeWidth,SongTimeHeight);
            mos = "00:00/" + TotalTime;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTimeRect,mos,o);

            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
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
                    QWidget* pWidget = nullptr;
                    if(i == 0)
                    {
                        pWidget = btn_File;
                    }
                    if(i == 1)
                    {
                        pWidget = btn_Delete;
                    }
                    if(i == 2)
                    {
                        pWidget = btn_Menu;
                    }
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth + mWidth + mSpacing  + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
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
                    QWidget* pWidget = nullptr;
                    if(i == 0)
                    {
                        pWidget = btn_File;
                    }
                    if(i == 1)
                    {
                        if(isLove)
                            pWidget = btn_RedLove;
                        else
                            pWidget = btn_Love;
                    }
                    if(i == 2)
                    {
                        pWidget = btn_Delete;
                    }
                    if(i == 3)
                    {
                        pWidget = btn_Menu;
                    }
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
            }

        }
    }
}

QRect MusicDownEndTableDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&checkBoxStyleOption);
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x()+viewItemStyleOptions.rect.width()/2-checkBoxRect.width()/2,
                         viewItemStyleOptions.rect.y()+viewItemStyleOptions.rect.height()/2-checkBoxRect.height()/2);
    return QRect(checkBoxPoint,checkBoxRect.size());
}

bool MusicDownEndTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    bool RState = false;
    ButtonState = 0;
    QVariantList List = index.data(Qt::DisplayRole).toList();
    if(List.size() < 1)
        return RState;
    int State = List.at(0).toInt();
    QString MV = List.at(5).toString();
    bool isMV = false;
    if(!MV.isEmpty())
        isMV = true;
    else
        isMV = false;
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    MousePoint = mouse_event->pos();
    if(event->type() == QEvent::MouseMove)
    {
        int SongNameWidth = 170;
        if(State == 1)
        {
            int nTop =  (option.rect.height() - mHeight) / 2;
            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 1;
                    break;
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 1;
                    break;
                }
            }
        }
        else if(State == 2)
        {
            int SongTextTop = option.rect.top() + 5;
            int SongTextHeight = 20;
            int SongTimeTop = SongTextTop + SongTextHeight + 5;

            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);

                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 1;
                    break;
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth + mWidth + mSpacing  + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);

                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 1;
                    break;
                }
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        int SongNameWidth = 170;
        int nTop =  (option.rect.height() - mHeight) / 2;
        int SongTextTop = option.rect.top() + 5;
        int SongTextHeight = 20;
        int SongTimeTop = SongTextTop + SongTextHeight + 5;

        if(State == 1)
        {
            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 2;
                    break;
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 2;
                    break;
                }
            }
        }
        else if(State == 2)
        {
            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 2;
                    break;
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    ButtonState = 2;
                    break;
                }
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        int SongNameWidth = 170;
        int nTop =  (option.rect.height() - mHeight) / 2;
        int SongTextTop = option.rect.top() + 5;
        int SongTextHeight = 20;
        int SongTimeTop = SongTextTop + SongTextHeight + 5;

        if(State == 1)
        {
            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    if(i == 0)
                    {
                        emit OpenFileSignal(index);
                    }
                    else if(i == 1)
                    {
                        emit DeleteSignal(index);
                    }
                    else if(i == 2)
                    {
                        qDebug() << "Button2";
                    }
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    if(i == 0)
                    {
                        emit OpenFileSignal(index);
                    }
                    else if(i == 1)
                    {
                        emit LoveSignal(index);
                    }
                    else if(i == 2)
                    {
                        emit DeleteSignal(index);
                    }
                    else if(i == 3)
                    {
                        qDebug() << "Button3";
                    }

                }
            }
        }
        else if(State == 2)
        {
            int PaintButtonWidth = 50;
            int PaintButtonHeight = 50;
            int PaintButtonPos = option.rect.left()  + mWidth;
            QStyleOptionButton buttonPaint;
            buttonPaint.rect = QRect(PaintButtonPos,
                                     option.rect.top(),  PaintButtonWidth, PaintButtonHeight);
            if(buttonPaint.rect.contains(MousePoint))
            {
                qDebug() << index.row() << " : buttonPaint";
            }
            if(isMV)
            {
                for(int i = 0; i < 3; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    if(i == 0)
                    {
                        emit OpenFileSignal(index);
                    }
                    else if(i == 1)
                    {
                        emit DeleteSignal(index);
                    }
                    else if(i == 2)
                    {
                        qDebug() << "Button2";
                    }
                }
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    QStyleOptionButton button;
                    button.rect = QRect((SongNameWidth +mWidth + mSpacing + (mWidth + mSpacing) * i),
                                        SongTimeTop,  mWidth, mHeight);
                    if (!button.rect.contains(MousePoint))
                        continue;

                    if(i == 0)
                    {
                        emit OpenFileSignal(index);
                    }
                    else if(i == 1)
                    {
                        emit LoveSignal(index);
                    }
                    else if(i == 2)
                    {
                        emit DeleteSignal(index);
                    }
                    else if(i == 3)
                    {
                        qDebug() << "Button3";
                    }
                }
            }
        }
    }
    return 1;
}
