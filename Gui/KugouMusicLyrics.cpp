#include "KugouMusicLyrics.h"
#include <QHBoxLayout>
#include <QDebug>
#include "kugouMusicLyricsLabel.h"

KugouMusicLyrics::KugouMusicLyrics(QWidget *parent)
    :KugouBaseControl (parent)
{
    this->Init();
    this->setObjectName("KugouMusicLyrics");
    this->setStyleSheet("#KugouMusicLyrics{background-color:rgb(0,50,255);}");
}

KugouMusicLyrics::~KugouMusicLyrics()
{

}

void KugouMusicLyrics::ClearLyrics()
{
    this->ClearWidget();
}

void KugouMusicLyrics::MusicSongLyricsTimeSlot(QStringList Lyrics,QStringList LyricsTime)
{
    ClearWidget();
    mLyrics = Lyrics;
    mLyricsTime = LyricsTime;
    emit ColorChoose();
    QList<KugouMusicLyricsLabel*> lblList = this->findChildren<KugouMusicLyricsLabel*>();
    mMax = Lyrics.size();
    for(int i = 5; i < lblList.size(); i++)
    {
        if(mSeek < mMax)
        {
            lblList.at(i)->SetNullLabelInfo(mLyrics.at(mSeek),mLyricsTime.at(mSeek));
            mSeek++;
        }
    }

}

void KugouMusicLyrics::SeekLyrics(QString value)
{
    mux.lock();
    int nSeek = -1;
    for(int i = 0; i < mLyricsTime.size(); i++)
    {
        if(mLyricsTime.at(i) < value)
        {
            if(i == mLyrics.size() - 1)
            {
                nSeek = i;
                break;
            }
            if(mLyricsTime.at(i + 1) > value)
            {
                nSeek = i;
            }
        }
    }
    if(nSeek == -1)
        return;
    mSeek = nSeek;
    qDebug() << "-----------------------------1";
    qDebug() << mSeek;
    qDebug() << mLyrics.size();
    QList<KugouMusicLyricsLabel*> lblList = this->findChildren<KugouMusicLyricsLabel*>();
    for(int i = 4; i >= 0 ; i--)
    {
        if(mSeek - (5 - i) >= 0)
        {
            lblList.at(4 - (4 - i))->SetNullLabelInfo(mLyrics.at(mSeek - (5 - i)),mLyricsTime.at(mSeek - (5 - i)));
        }
        else
        {
            lblList.at(4 - (4 - i))->SetNullLabelInfo("","");
        }
    }
    for(int i = 5; i < lblList.size(); i++)
    {
        if(mSeek < mMax)
        {
            lblList.at(i)->SetNullLabelInfo(mLyrics.at(mSeek),mLyricsTime.at(mSeek));
            mSeek++;
        }
        else
        {
            lblList.at(i)->SetNullLabelInfo("","");
        }
    }
    mux.unlock();
}

void KugouMusicLyrics::StartMove(QString value)
{
    mux.lock();
    QList<KugouMusicLyricsLabel*> lblList = this->findChildren<KugouMusicLyricsLabel*>();
    if(value > lblList.at(5)->Get_Time())
    {
        for(int i = 0; i < lblList.size(); i++)
        {
            if(i == lblList.size() - 1)
            {
                if(mSeek < mMax)
                {
                    lblList.at(i)->SetNullLabelInfo(mLyrics.at(mSeek),mLyricsTime.at(mSeek));
                    mSeek++;
                }
                else
                {
                    lblList.at(i)->SetNullLabelInfo("","");
                }
            }
            else
            {
                if(mSeek < mMax)
                {
                    lblList.at(i)->SetLabelInfo(lblList.at(i + 1));
                }
            }
        }
    }
    mux.unlock();
}

void KugouMusicLyrics::Init()
{
    const QString TopBottomStyle = "Color:rgb(255,255,255,120); font: 12pt ""黑体""; ";
    const QString MidStyle = "background-color:rgb(255,255,255,100);Color:rgb(214,187,119);font : 15pt ""黑体"" ";
    const QString Mid1Style = "Color:rgb(214,187,119);font : 15pt ""黑体"" ";
    const QString OtherStyle = "Color:rgb(255,255,255);font: 13pt ""黑体"" ";

    QVBoxLayout* mLayout = Get_VLayout();

    KugouMusicLyricsLabel* lbl = new KugouMusicLyricsLabel();;
    lbl->setStyleSheet(TopBottomStyle);
    lbl->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_1 = new KugouMusicLyricsLabel();;
    lbl_1->setStyleSheet(OtherStyle);
    lbl_1->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_2 = new KugouMusicLyricsLabel();;
    lbl_2->setStyleSheet(OtherStyle);
    lbl_2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_3 = new KugouMusicLyricsLabel();;
    lbl_3->setStyleSheet(OtherStyle);
    lbl_3->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_4 = new KugouMusicLyricsLabel();;
    lbl_4->setStyleSheet(Mid1Style);
    lbl_4->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_5 = new KugouMusicLyricsLabel();;
    lbl_5->setStyleSheet(OtherStyle);
    lbl_5->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_6 = new KugouMusicLyricsLabel();;
    lbl_6->setStyleSheet(OtherStyle);
    lbl_6->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_7 = new KugouMusicLyricsLabel();;
    lbl_7->setStyleSheet(OtherStyle);
    lbl_7->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_8 = new KugouMusicLyricsLabel();;
    lbl_8->setStyleSheet(OtherStyle);
    lbl_8->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    KugouMusicLyricsLabel* lbl_9 = new KugouMusicLyricsLabel();;
    lbl_9->setStyleSheet(TopBottomStyle);
    lbl_9->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

//    KugouMusicLyricsLabel* lbl_10 = new KugouMusicLyricsLabel();;

    mLayout->addWidget(lbl);
    mLayout->addWidget(lbl_1);
    mLayout->addWidget(lbl_2);
    mLayout->addWidget(lbl_3);
    mLayout->addWidget(lbl_4);
    mLayout->addWidget(lbl_5);
    mLayout->addWidget(lbl_6);
    mLayout->addWidget(lbl_7);
    mLayout->addWidget(lbl_8);
    mLayout->addWidget(lbl_9);

    this->connect(this,&KugouMusicLyrics::ColorChoose,this,[=](){
        lbl_4->setStyleSheet(MidStyle);
    });
    this->connect(this,&KugouMusicLyrics::ColorNoChoose,this,[=](){
        lbl_4->setStyleSheet(Mid1Style);
    });

    this->setLayout(mLayout);
}

void KugouMusicLyrics::ClearWidget()
{
    QList<KugouMusicLyricsLabel*> lbl_List = this->findChildren<KugouMusicLyricsLabel*>();
    for(int i = 0; i < lbl_List.size(); i++)
    {
        lbl_List.at(i)->Clear();
    }
    mLyrics.clear();
    mLyricsTime.clear();
    mSeek = 0;
    emit ColorNoChoose();
}
