#include "KugouBaseControl.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

KugouBaseControl::KugouBaseControl(QWidget *parent)
    :QWidget (parent)
{

}

KugouBaseControl::KugouBaseControl()
{

}

KugouBaseControl::~KugouBaseControl()
{

}

QPushButton *KugouBaseControl::Get_Button(QString text, QString Icon, QString ToolText, int width, int height, int IconWidth, int IconHeight, QString style)
{
    QPushButton* btn = new QPushButton();
    if(!text.isEmpty())
        btn->setText(text);
    if(!Icon.isEmpty())
    {
        btn->setIcon(QIcon(Icon));
        btn->setIconSize(QSize(IconWidth,IconHeight));
    }
    if(!ToolText.isEmpty())
        btn->setToolTip(ToolText);
    if(width != 0)
        btn->setFixedWidth(width);
    if(height != 0)
        btn->setFixedHeight(height);
    btn->setStyleSheet(style);

    return btn;
}

QLabel *KugouBaseControl::Get_Label(QString text, int Width, int height, QString style, Qt::Alignment Align)
{
    QLabel* lbl = new QLabel();
    if(!text.isEmpty())
        lbl->setText(text);
    if(Width != 0)
        lbl->setFixedWidth(Width);
    if(height != 0)
        lbl->setFixedHeight(height);
    lbl->setAlignment(Align);
    lbl->setStyleSheet(style);
    return lbl;
}

QHBoxLayout *KugouBaseControl::Get_HLayout(int left, int right, int top, int bottom, int Spaceing)
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(Spaceing);
    mLayout->setContentsMargins(left,top,right,bottom);

    return mLayout;
}

QVBoxLayout *KugouBaseControl::Get_VLayout(int left, int right, int top, int bottom, int Spaceing)
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(Spaceing);
    mLayout->setContentsMargins(left,top,right,bottom);

    return mLayout;
}
