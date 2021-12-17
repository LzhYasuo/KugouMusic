#include "KugouMusicBodyLeftButton.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QLabel>

#include "Public/Public_Str.h"

KugouMusicBodyLeftButton::KugouMusicBodyLeftButton(QString MusicName,QWidget *parent)
    :QPushButton (parent),
      Name(MusicName)
{
    this->setObjectName("LeftButton");
    this->setStyleSheet("#LeftButton{background-color:rgb(0,0,0,0);"
                        "border:none;"
                        "border-bottom:1px solid rgb(170,170,170);}");
//                        "border-right:1px solid rgb(170,170,170);"
//                        "border-bottom:1px solid rgb(170,170,170);}");
    this->setFixedHeight(40);
    this->InitWidget();
    this->installEventFilter(this);
}

KugouMusicBodyLeftButton::~KugouMusicBodyLeftButton()
{

}

void KugouMusicBodyLeftButton::DeleteMusicNum()
{
    MusicNum -= 1;
    emit ChangeName(Name + "[" + QString::number(MusicNum) + "]");
}

void KugouMusicBodyLeftButton::AddMusicNum()
{
    MusicNum += 1;
    emit ChangeName(Name + "[" + QString::number(MusicNum) + "]");
}

bool KugouMusicBodyLeftButton::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            emit ShowButton();
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            emit HideButton();
        }
    }
    return QPushButton::eventFilter(obj,event);
}

void KugouMusicBodyLeftButton::InitWidget()
{
    const QString UpGradeStyle = Public_Str::CreateLeftButtonStyle(ListUpdateButtonStyle);
    const QString ShareStyle = Public_Str::CreateLeftButtonStyle(ListShareButtonStyle);
    const QString MenuStyle = Public_Str::CreateLeftButtonStyle(ListMenuButtonStyle);

    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    //图片
    QPushButton* btn_Paint = new QPushButton();
    btn_Paint->setStyleSheet("border:none;");
    btn_Paint->setFixedSize(16,16);
    btn_Paint->setIcon(QIcon(":/Left/Paint/Left/indicator_top.png"));

    //列表名称
    QLabel* lbl_MusicName = new QLabel();
    lbl_MusicName->setText(Name);

    //升级
    QPushButton* btn_Upgrade = new QPushButton();
    btn_Upgrade->setFixedSize(20,20);
    btn_Upgrade->setStyleSheet(UpGradeStyle);

    //分享
    QPushButton* btn_Share = new QPushButton();
        btn_Share->setFixedSize(20,20);
    btn_Share->setStyleSheet(ShareStyle);

    //菜单列表
    QPushButton* btn_MenuList = new QPushButton();
        btn_MenuList->setFixedSize(20,20);
    btn_MenuList->setStyleSheet(MenuStyle);

    mLayout->addWidget(btn_Paint);
    mLayout->addWidget(lbl_MusicName);
    mLayout->addWidget(btn_Upgrade);
    mLayout->addSpacing(10);
    mLayout->addWidget(btn_Share);
    mLayout->addSpacing(10);
    mLayout->addWidget(btn_MenuList);
    mLayout->addSpacing(15);

    btn_Upgrade->hide();
    btn_Share->hide();
    btn_MenuList->hide();
    this->connect(this,&KugouMusicBodyLeftButton::ShowButton,this,[=](){
        btn_Upgrade->show();
        btn_Share->show();
        btn_MenuList->show();
    });

    this->connect(this,&KugouMusicBodyLeftButton::HideButton,this,[=](){
        btn_Upgrade->hide();
        btn_Share->hide();
        btn_MenuList->hide();
    });

    this->setLayout(mLayout);
}
