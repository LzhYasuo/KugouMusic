#include "KugouMusicRadio.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>

//KugouMusicRadio::KugouMusicRadio(QWidget *parent)
//    :QPushButton (parent)
//{
//    this->Init();
//}

KugouMusicRadio::KugouMusicRadio(QString Paint, QString MusicName, QString Title, QWidget *parent)
    :QPushButton (parent),
      mPaint(Paint),
      mMusicName(MusicName),
      mTitle(Title)
{
      this->Init();
}

KugouMusicRadio::~KugouMusicRadio()
{

}

bool KugouMusicRadio::eventFilter(QObject *o, QEvent *e)
{
    if(o == this)
    {
        if(e->type() == QEvent::HoverEnter)
        {
            emit HoverEnterState();
        }
        else if(e->type() == QEvent::HoverLeave)
        {
            emit HoverLeaveState();
        }
    }
    return QPushButton::eventFilter(o,e);
}

void KugouMusicRadio::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QPushButton* btn_Paint = new QPushButton();

    QVBoxLayout* RightLayout = new QVBoxLayout();
    RightLayout->setSpacing(0);
    RightLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout* TopLayout = new QHBoxLayout();
    TopLayout->setSpacing(0);
    TopLayout->setContentsMargins(0,0,0,0);

    QLabel* lbl_Title = new QLabel();

    QPushButton* btn_Play = new QPushButton();

    QPushButton* btn_PlayNextMusic = new QPushButton();

    QPushButton* btn_Delete = new QPushButton();

    TopLayout->addWidget(lbl_Title);
    TopLayout->addStretch();
    TopLayout->addWidget(btn_Play);
    TopLayout->addWidget(btn_PlayNextMusic);
    TopLayout->addWidget(btn_Delete);

    QLabel* lbl_MusicName = new QLabel();

    RightLayout->addLayout(TopLayout);
    RightLayout->addWidget(lbl_MusicName);

    mLayout->addWidget(btn_Paint);
    mLayout->addLayout(RightLayout);

    this->setLayout(mLayout);

}

