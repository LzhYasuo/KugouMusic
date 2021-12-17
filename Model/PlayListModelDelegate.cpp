#include "PlayListModelDelegate.h"
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

PlayListModelItem::PlayListModelItem(QObject *parent)
    :QObject (parent)
{

}

PlayListModelItem::~PlayListModelItem()
{

}

QString PlayListModelItem::Get_VoiceName()
{
    return VoiceName;
}

void PlayListModelItem::Set_VoiceName(QString msg)
{
    VoiceName = msg;
}

QString PlayListModelItem::Get_Singer()
{
    return mSinger;
}

void PlayListModelItem::Set_Singer(QString s)
{
    mSinger = s;
}

bool PlayListModelItem::Get_Clicked()
{
    return isClicked;
}

void PlayListModelItem::Set_Clicked(bool C)
{
    isClicked = C;
}

QString PlayListModelItem::Get_SongTime()
{
    return SongTime;
}

void PlayListModelItem::Set_SongTime(QString s)
{
    SongTime = s;
}

//QString PlayListModelItem::Get_LastName()
//{
//    return lastName;
//}

//void PlayListModelItem::Set_LastName(QString s)
//{
//    lastName = s;
//}

int PlayListModelItem::Get_ListState()
{
    return ListState;
}

void PlayListModelItem::Set_ListState(int state)
{
    ListState = state;
}

QString PlayListModelItem::Get_PlayMusicUrl()
{
    return MusicUrl;
}

void PlayListModelItem::Set_PlayMusicUrl(QString url)
{
    MusicUrl = url;
}

QString PlayListModelItem::Get_PlayMVMusicUrl()
{
    return MVUrl;
}

void PlayListModelItem::Set_PlayMVMusicUrl(QString url)
{
    MVUrl = url;
}

QString PlayListModelItem::Get_NowTime()
{
    return NowTime;
}

void PlayListModelItem::Set_NowTime(QString t)
{
    NowTime = t;
}

bool PlayListModelItem::Get_isLove()
{
    return isLove;
}

void PlayListModelItem::Set_isLove(bool b)
{
    isLove = b;
}

QMap<QStringList, QStringList> PlayListModelItem::getSongLyciesTime() const
{
    return SongLyciesTime;
}

void PlayListModelItem::setSongLyciesTime(const QMap<QStringList, QStringList> &value)
{
    SongLyciesTime = value;
}

QStringList PlayListModelItem::getSongLycies() const
{
    return SongLycies;
}

void PlayListModelItem::setSongLycies(const QStringList &value)
{
    SongLycies = value;
}

QStringList PlayListModelItem::getLyciesTime() const
{
    return LyciesTime;
}

void PlayListModelItem::setLyciesTime(const QStringList &value)
{
    LyciesTime = value;
}

//QMap<QStringList, QString> PlayListModelItem::getLyTime() const
//{
//    return lyTime;
//}

//void PlayListModelItem::setLyTime(const QMap<QStringList, QString> &value)
//{
//    lyTime = value;
//}

PlayModelTableModel::PlayModelTableModel()
{

}

PlayModelTableModel::~PlayModelTableModel()
{

}

int PlayModelTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int PlayModelTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 1;
}

QVariant PlayModelTableModel::data(const QModelIndex &index, int role) const
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
            var.push_back(List.at(index.row())->Get_Clicked());
            var.push_back(List.at(index.row())->Get_VoiceName());
            var.push_back(List.at(index.row())->Get_Singer());
            var.push_back(List.at(index.row())->Get_SongTime());
            var.push_back(List.at(index.row())->Get_PlayMusicUrl());
            var.push_back(List.at(index.row())->Get_PlayMVMusicUrl());
            var.push_back(List.at(index.row())->Get_NowTime());
            var.push_back(List.at(index.row())->Get_isLove());
            return var;
        }
    }
    return QVariant();
}

QVariant PlayModelTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool PlayModelTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
////            if(var.size() > 2)
//                List.at(index.row())->Set_isLove(var.at(1).toBool());
        }
        RefrushModelData();
        return true;
    }
    return false;
}

void PlayModelTableModel::RefrushModel(PlayListModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void PlayModelTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

void PlayModelTableModel::InitData(QVariantList var)
{
    PlayListModelItem* item = new PlayListModelItem();
    item->Set_ListState(0);
    item->Set_Clicked(0);
    item->Set_VoiceName(var.at(0).toString());
    item->Set_Singer(var.at(1).toString());
    item->Set_SongTime(var.at(2).toString());
    item->Set_PlayMusicUrl(var.at(3).toString());
    item->Set_PlayMVMusicUrl(var.at(4).toString());
    item->Set_isLove(var.at(5).toBool());

    List.append(item);
    if(!item->Get_PlayMVMusicUrl().isEmpty())
        MVList.push_back(List.size() - 1);
    RefrushModelData();

}

void PlayModelTableModel::RemoveRow(int row)
{
    mutex.lock();
    List.removeAt(row);
    mutex.unlock();
}

int PlayModelTableModel::Get_NextMVRow(int row) const
{
    int NextRow = -1;
    for(int i = 0; i < MVList.size(); i++)
    {
        if(row == MVList.at(i))
        {
            if(row == MVList.at(MVList.size() - 1))
                NextRow = -1;
            else
                NextRow = MVList.at(i + 1);
            break;
        }
    }
    return NextRow;
}

int PlayModelTableModel::Get_PreMVRow(int row) const
{
    int PreRow = -1;
    for(int i = 0; i < MVList.size(); i++)
    {
        if(row == MVList.at(i))
        {
            if(i == 0)
                PreRow = -1;
            else
                PreRow = MVList.at(i - 1);
            break;
        }
    }
    return PreRow;
}

void PlayModelTableModel::PushBackData(QVariantList var)
{
    for(int i = 0; i < List.size(); i++)
    {
        List.at(i)->Set_ListState(0);
    }
    PlayListModelItem* item = new PlayListModelItem();
    item->Set_ListState(2);
    item->Set_Clicked(0);
    item->Set_VoiceName(var.at(0).toString());
    item->Set_Singer(var.at(1).toString());
    item->Set_SongTime(var.at(2).toString());
    item->Set_PlayMusicUrl(var.at(3).toString());
    item->Set_PlayMVMusicUrl(var.at(4).toString());
    item->Set_isLove(false);
    item->setSongLycies(var.at(6).toStringList());
    item->setLyciesTime(var.at(7).toStringList());

    qDebug() << "var 5 " << var.at(6).toStringList().size() << "var 6" << var.at(7).toStringList().size();

    List.append(item);
    if(!item->Get_PlayMVMusicUrl().isEmpty())
        MVList.push_back(List.size() - 1);
    RefrushModelData();

}

//void PlayModelTableModel::SetNowTime(QString t)
//{

//}



PlayListTableDelegate::PlayListTableDelegate(QObject *parent)
    :QStyledItemDelegate(parent),
      btn_Add(new QPushButton()),
      btn_MV(new QPushButton()),
      btn_Love(new QPushButton()),
      btn_Delete(new QPushButton()),
      btn_Menu(new QPushButton()),
      btn_Down(new QPushButton()),
      btn_RedLove(new QPushButton())
{

    btn_Add->setStyleSheet("QPushButton "
                           "{"
                           "border: none;"
                           "background-color: transparent;"
                           "image:url(:/PlayList/Paint/PlayList/add_1_1.png);"
                           "}"
                           "QPushButton:hover "
                           "{"
                           "image:url(:/PlayList/Paint/PlayList/add_1_2.png);"
                           "}"
                           "QPushButton:pressed"
                           "{"
                           "image:url(:/PlayList/Paint/PlayList/add_1_3.png);"
                           "}");

    btn_MV->setStyleSheet("QPushButton {border: none; background-color: transparent; image: url(:/PlayList/Paint/PlayList/mv_1_1.png);} \
                                 QPushButton:hover {image: url(:/PlayList/Paint/PlayList/mv_1_2.png);} \
                                 QPushButton:pressed {image: url(:/PlayList/Paint/PlayList/mv_1_3.png);}");

    btn_Love->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/love_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/love_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/love_1_1.png);}");

    btn_RedLove->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/btn_RedLove.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/btn_RedLove_hover.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/btn_RedLove_press.png);}");

    btn_Delete->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/delete_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/delete_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/delete_1_3.png);}");

    btn_Menu->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/muen_1_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/muen_1_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/muen_1_3.png);}");

    btn_Down->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/PlayList/Paint/PlayList/down_1.png);} \
                                 QPushButton:hover {image:url(:/PlayList/Paint/PlayList/down_2.png);} \
                                 QPushButton:pressed {image:url(:/PlayList/Paint/PlayList/down_3.png);}");



    WarnningText<< "打开" << "载入" << "下载";
}

PlayListTableDelegate::~PlayListTableDelegate()
{
    btn_Add->deleteLater();
    btn_MV->deleteLater();
    btn_Love->deleteLater();
    btn_Delete->deleteLater();
    btn_Menu->deleteLater();
    btn_RedLove->deleteLater();
}

void PlayListTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nTop =  (option.rect.height() - mHeight) / 2;
    int SongNameWidth = 170;
    int SongNameHeight = 20;
    int SongTimeWidth = 50;
    int SongTimeHeight = 20;
    if(index.column() == 0)
    {
        QVariantList List = index.model()->data(index,Qt::DisplayRole).toList();
        if(List.size() < 1)
            return;
        int State = List.at(0).toInt();
        QString SingNameEr = List.at(3).toString() + " - " + List.at(2).toString();
        QString MVUrl = List.at(6).toString();
        QString SongTime =  List.at(4).toString();
        QString PlayingTime = "00:00/" + List.at(4).toString();
        bool isLove = List.at(8).toBool();
        if(State == 0)
        {
            QRect SongTextRect(option.rect.left() + mWidth,option.rect.top() + nTop,SongNameWidth,SongNameHeight);
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,SingNameEr,o);

            QStyleOptionButton button;
            button.rect = QRect(SongNameWidth + mWidth + mSpacing,
                                option.rect.top() + nTop,  mWidth, mHeight);
            button.state |= QStyle::State_Enabled;

            if(!MVUrl.isEmpty())
            {
                QWidget* pWidget = btn_MV;
                pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
            }


            QRect TimeTextRect(SongNameWidth + mWidth + mSpacing + ((mWidth + mSpacing) * 2) + mSpacing,option.rect.top() + nTop,SongTimeWidth,SongTimeHeight);
            o.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            painter->drawText(TimeTextRect,SongTime,o);

        }
        else if(State == 1)
        {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            button.state |= QStyle::State_Enabled;
            QWidget* pWidget = btn_Add;
            pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);

            QRect SongTextRect(option.rect.left() + mWidth,option.rect.top() + nTop,SongNameWidth,SongNameHeight);
            QString mos = index.model()->data(index,Qt::DisplayRole).toString();
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,SingNameEr,o);

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
                if(!MVUrl.isEmpty())
                {
                    if(i == 0)
                    {
                        pWidget = btn_MV;
                        pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                    }
                }
                if(i == 1)
                {
                    if(isLove)
                        pWidget = btn_RedLove;
                    else
                        pWidget = btn_Love;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
                if(i == 2)
                {
                    pWidget = btn_Delete;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
                if(i == 3)
                {
                    pWidget = btn_Menu;
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
            //按钮
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
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
            QWidget* AddWidget = btn_Add;
            AddWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,AddWidget);


            //图片按钮
            QStyleOptionButton buttonPaint;
            buttonPaint.rect = QRect(PaintButtonPos,
                                option.rect.top(),  PaintButtonWidth, PaintButtonHeight);
            buttonPaint.state |= QStyle::State_Enabled;
            QApplication::style()->drawControl(QStyle::CE_PushButton,&buttonPaint,painter);

            //歌名
            QRect SongTextRect(SongTextPos,option.rect.top() + 5,SongTextWidth,SongTextHeight);
            QString mos = SingNameEr;
            QTextOption o;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTextRect,mos,o);

            //歌时长
            QRect SongTimeRect(SongTextPos,SongTimeTop,SongTimeWidth,SongTimeHeight);
            mos = PlayingTime;
            o.setAlignment(Qt::AlignLeft);
            painter->drawText(SongTimeRect,mos,o);

            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
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
                    if(!MVUrl.isEmpty())
                    {
                        pWidget = btn_MV;
                        pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                    }
                }
                if(i == 1)
                {
                    pWidget = btn_Down;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
                if(i == 2)
                {
                    if(isLove)
                        pWidget = btn_RedLove;
                    else
                        pWidget = btn_Love;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
                if(i == 3)
                {
                    pWidget = btn_Delete;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
                if(i == 4)
                {
                    pWidget = btn_Menu;
                    pWidget->style()->drawControl(QStyle::CE_PushButton,&button,painter,pWidget);
                }
            }
        }
    }
}

QRect PlayListTableDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&checkBoxStyleOption);
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x()+viewItemStyleOptions.rect.width()/2-checkBoxRect.width()/2,
                         viewItemStyleOptions.rect.y()+viewItemStyleOptions.rect.height()/2-checkBoxRect.height()/2);
    return QRect(checkBoxPoint,checkBoxRect.size());
}

bool PlayListTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    bool RState = false;
    ButtonState = 0;
    QVariantList List = index.data(Qt::DisplayRole).toList();
    if(List.size() < 1)
        return RState;
    int State = List.at(0).toInt();
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    MousePoint = mouse_event->pos();
    if(event->type() == QEvent::MouseMove)
    {
        int SongNameWidth = 170;
        if(State == 1)
        {
            int nTop =  (option.rect.height() - mHeight) / 2;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 1;
            }
            for(int i = 0; i < 4; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                    option.rect.top() + nTop,  mWidth, mHeight);
                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 1;
                break;
            }
        }
        else if(State == 2)
        {
            int SongTextTop = option.rect.top() + 5;
            int SongTextHeight = 20;
            int SongTimeTop = SongTextTop + SongTextHeight + 5;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 1;
            }

            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
                                    SongTimeTop,  mWidth, mHeight);

                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 1;
                break;

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
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
            }
            for(int i = 0; i < 4; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                    option.rect.top() + nTop,  mWidth, mHeight);
                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
                break;
            }
        }
        else if(State == 2)
        {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
            }
            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
                                    SongTimeTop,  mWidth, mHeight);

                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
                break;

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
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                emit AddButtonClicked(index);
            }
            for(int i = 0; i < 4; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                    option.rect.top() + nTop,  mWidth, mHeight);
                if (!button.rect.contains(MousePoint))
                    continue;
                if(i == 0)
                {
                    qDebug() << "MV";
                    emit MVButtonClicked(index);
                }
                else if(i == 1)
                {
                    emit LoveButtonClicked(index);
                }
                else if(i == 2)
                {
                    emit DeleteButtonClicked(index);
                }
                else if(i == 3)
                {
                    //菜单
                }

            }
        }
        else if(State == 2)
        {
            int PaintButtonWidth = 50;
            int PaintButtonHeight = 50;
            int PaintButtonPos = option.rect.left()  + mWidth;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                emit AddButtonClicked(index);
            }

            QStyleOptionButton buttonPaint;
            buttonPaint.rect = QRect(PaintButtonPos,
                                     option.rect.top(),  PaintButtonWidth, PaintButtonHeight);
            if(buttonPaint.rect.contains(MousePoint))
            {
            }
            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
                                    SongTimeTop,  mWidth, mHeight);

                if (!button.rect.contains(MousePoint))
                    continue;

                if(i == 0)
                {
                    emit MVButtonClicked(index);
                }
                else if(i == 1)
                {
                    emit DownButtonClicked(index);
                }
                else if(i == 2)
                {
                    //我喜欢
                    emit LoveButtonClicked(index);
                }
                else if(i == 3)
                {
                    emit DeleteButtonClicked(index);
                }
                else if(i == 4)
                {
                    //菜单
                }

            }
        }
    }
    return 1;
}


#if 0

bool PlayListTableDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    bool RState = false;
    ButtonState = 0;
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
                if(State != 2)
                {
                    QVariantList var;
                    var.push_back(1);
                    model->setData(index,var);
                }
                for(int i = 0; i < model->rowCount(); i++)
                {
                    QVariantList List = model->index(i,0).data(Qt::DisplayRole).toList();
                    if(List.at(0).toInt() == 2)
                        continue;
                    if(i == index.row())
                        continue;
                    QVariantList var;
                    var.push_back(0);
                    model->setData(model->index(i,0),var,Qt::DisplayRole);
                }

                int SongNameWidth = 170;
                if(State == 1)
                {
                    int nTop =  (option.rect.height() - mHeight) / 2;
                    QStyleOptionButton button;
                    button.rect = QRect(option.rect.left() ,
                                        option.rect.top() + nTop,  mWidth, mHeight);
                    if(button.rect.contains(MousePoint))
                    {
                        QApplication::setOverrideCursor(Qt::PointingHandCursor);
                        ButtonState = 1;
                    }
                    for(int i = 0; i < 4; i++)
                    {
                        QStyleOptionButton button;
                        button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                            option.rect.top() + nTop,  mWidth, mHeight);
                        if (!button.rect.contains(MousePoint))
                            continue;

                        QApplication::setOverrideCursor(Qt::PointingHandCursor);
                        ButtonState = 1;
                        break;
                    }
                }
                else if(State == 2)
                {
                    int SongTextTop = option.rect.top() + 5;
                    int SongTextHeight = 20;
                    int SongTimeTop = SongTextTop + SongTextHeight + 5;
                    QStyleOptionButton button;
                    button.rect = QRect(option.rect.left() ,
                                        option.rect.top() + 15,  mWidth, mHeight);
                    if(button.rect.contains(MousePoint))
                    {
                        QApplication::setOverrideCursor(Qt::PointingHandCursor);
                        ButtonState = 1;
                    }

                    for(int i = 0; i < 5; i++)
                    {
                        QStyleOptionButton button;
                        button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
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
            int nTop =  (option.rect.height() - mHeight) / 2;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
            }
            for(int i = 0; i < 4; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                    option.rect.top() + nTop,  mWidth, mHeight);
                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
                break;
            }
        }
        else if(State == 2)
        {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
            }
            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
                                    SongTimeTop,  mWidth, mHeight);

                if (!button.rect.contains(MousePoint))
                    continue;

                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                ButtonState = 2;
                break;

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
            int nTop =  (option.rect.height() - mHeight) / 2;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + nTop,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                emit AddButtonClicked(index);
            }
            for(int i = 0; i < 4; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth + mWidth + mSpacing + (mWidth + mSpacing) * i),
                                    option.rect.top() + nTop,  mWidth, mHeight);
                if (!button.rect.contains(MousePoint))
                    continue;
                if(i == 0)
                {
                    qDebug() << "MV";
                    emit MVButtonClicked(index);
                }
                else if(i == 1)
                {
                    emit LoveButtonClicked(index);
                }
                else if(i == 2)
                {
                    emit DeleteButtonClicked(index);
                }
                else if(i == 3)
                {
                    //菜单
                }

            }
        }
        else if(State == 2)
        {
            int PaintButtonWidth = 50;
            int PaintButtonHeight = 50;
            int PaintButtonPos = option.rect.left()  + mWidth;
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() ,
                                option.rect.top() + 15,  mWidth, mHeight);
            if(button.rect.contains(MousePoint))
            {
                emit AddButtonClicked(index);
            }

            QStyleOptionButton buttonPaint;
            buttonPaint.rect = QRect(PaintButtonPos,
                                     option.rect.top(),  PaintButtonWidth, PaintButtonHeight);
            if(buttonPaint.rect.contains(MousePoint))
            {
            }
            for(int i = 0; i < 5; i++)
            {
                QStyleOptionButton button;
                button.rect = QRect((SongNameWidth  + (mWidth + mSpacing) * i),
                                    SongTimeTop,  mWidth, mHeight);

                if (!button.rect.contains(MousePoint))
                    continue;

                if(i == 0)
                {
                    emit MVButtonClicked(index);
                }
                else if(i == 1)
                {
                    emit DownButtonClicked(index);
                }
                else if(i == 2)
                {
                    //我喜欢
                    emit LoveButtonClicked(index);
                }
                else if(i == 3)
                {
                    emit DeleteButtonClicked(index);
                }
                else if(i == 4)
                {
                    //菜单
                }

            }
        }
    }
    return 1;
    }

#endif
