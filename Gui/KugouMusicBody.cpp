#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QListView>
#include <QListWidget>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent>

#include "KugouMusicLyrics.h"
#include "KugouMusicDown.h"
#include "KugouAVPlayer.h"
#include "KugouMusicBody.h"
#include "KugouMusicBodyLeftButton.h"
#include "KugouMusicLyrics.h"
#include "Data/PlayListData.h"
#include "Public/Public_Str.h"
#include "Model/SearchListView.h"
#include "Model/SearchHeaderView.h"
#include "Model/PlayListView.h"
#include "Model/MusicDownEndListView.h"
#include "Model/MusicDownView.h"
#include "NetWork/NetWorkHttp.h"

KugouMusicBody::KugouMusicBody(QWidget *parent)
    :KugouBaseControl (parent)
{
    this->Init();
    this->installEventFilter(this);
}

KugouMusicBody::~KugouMusicBody()
{

}

void KugouMusicBody::Init()
{
    QHBoxLayout* mHLayout = Get_HLayout();
    QWidget* LeftWidget = InitLeftWidget();
    LeftWidget->setObjectName("LeftWidget");
    LeftWidget->setFixedWidth(310);
    LeftWidget->setStyleSheet("#LeftWidget{border-right:1px solid rgb(170,170,170);}");
    QWidget* RightWidget = InitRightWidget();


    mHLayout->addWidget(LeftWidget);
    mHLayout->addWidget(RightWidget);
    this->setLayout(mHLayout);

}

QWidget *KugouMusicBody::InitLeftWidget()
{
    const QString LoaclListStyle = Public_Str::CreateLeftButtonStyle(localListButtonStyle);
    const QString NetWorkCollectStyle = Public_Str::CreateLeftButtonStyle(NetWorkButtonStyle);
    const QString MusicRadioStyle = Public_Str::CreateLeftButtonStyle(MusicRadioButtonStyle);
    const QString PhoneMusicStyle = Public_Str::CreateLeftButtonStyle(PhoneButtonStyle);
    const QString LocalMusicStyle = Public_Str::CreateLeftButtonStyle(LocalMusicButtonStyle);

    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = Get_VLayout();

    QWidget* ButtonWidget = new QWidget();
    ButtonWidget->setObjectName("ButtonWidget");
    ButtonWidget->setStyleSheet("QWidget#ButtonWidget{"
                                "border-right:1px solid rgb(170,170,170);"
                                "border-bottom:1px solid rgb(170,170,170);"
                                "}");
    QHBoxLayout* ButtonLayout = Get_HLayout();

    //本地列表
    QPushButton* btn_LocalList = Get_Button("","","",45,40);
    btn_LocalList->setStyleSheet(LoaclListStyle);

    //网络收藏
    QPushButton* btn_NetWorkCollect = Get_Button("","","",45,40);
    btn_NetWorkCollect->setStyleSheet(NetWorkCollectStyle);

    //音乐电台
    QPushButton* btn_MusicRadio = Get_Button("","","",45,40);
    btn_MusicRadio->setStyleSheet(MusicRadioStyle);

    //手机音乐管理
    QPushButton* btn_PhoneMusicMana = Get_Button("","","",45,40);
    btn_PhoneMusicMana->setStyleSheet(PhoneMusicStyle);

    //本地音乐
    QPushButton* btn_LocalMusic = Get_Button("","","",45,40);
    btn_LocalMusic->setStyleSheet(LocalMusicStyle);

    btn_LocalList->setCheckable(true);
    btn_LocalList->setAutoExclusive(true);

    btn_NetWorkCollect->setCheckable(true);
    btn_NetWorkCollect->setAutoExclusive(true);

    btn_MusicRadio->setCheckable(true);
    btn_MusicRadio->setAutoExclusive(true);

    btn_PhoneMusicMana->setCheckable(true);
    btn_PhoneMusicMana->setAutoExclusive(true);

    btn_LocalMusic->setCheckable(true);
    btn_LocalMusic->setAutoExclusive(true);

    btn_LocalList->click();

    ButtonLayout->addWidget(btn_LocalList);
    ButtonLayout->addWidget(btn_NetWorkCollect);
    ButtonLayout->addWidget(btn_MusicRadio);
    ButtonLayout->addWidget(btn_PhoneMusicMana);
    ButtonLayout->addWidget(btn_LocalMusic);
    ButtonWidget->setLayout(ButtonLayout);

    QStackedWidget* mSWidget = new QStackedWidget();
    mSWidget->addWidget(CreateLeftListWidget(LoaclListWidget));
    mSWidget->addWidget(CreateLeftListWidget(NetworkListWidget));
    mSWidget->addWidget(CreateLeftListWidget(MusicRadioListWidget));
    mSWidget->addWidget(CreateLeftListWidget(PhoneMusicWidget));
    mSWidget->addWidget(CreateLeftListWidget(LoaclMusicWidget));

    this->connect(btn_LocalList,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(0);});
    this->connect(btn_NetWorkCollect,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(1);});
    this->connect(btn_MusicRadio,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(2);});
    this->connect(btn_PhoneMusicMana,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(3);});
    this->connect(btn_LocalMusic,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(4);});

    this->connect(this,&KugouMusicBody::SwitchLeftPage,this,[=](int page){
            mSWidget->setCurrentIndex(page);
    });

    mLayout->addWidget(ButtonWidget);
    mLayout->addWidget(mSWidget);
    mWidget->setLayout(mLayout);

    return mWidget;
}

QWidget *KugouMusicBody::InitRightWidget()
{
    const QString TopButtonStyle = Public_Str::Get_Sty(Style_Css{RightTopButtonStyle});
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = Get_VLayout();

    QWidget* TopWidget = new QWidget();
    TopWidget->setFixedHeight(40);
    TopWidget->setStyleSheet("border-bottom:1px solid rgb(170,170,170);"
                             "background-color:rgb(255,255,255);");
    QHBoxLayout* TopLayout = Get_HLayout();

    //乐库
    QPushButton* btn_MusicLib = Get_Button("乐库","","",55,39);
    btn_MusicLib->setStyleSheet(TopButtonStyle);
    btn_MusicLib->setAutoExclusive(true);
    btn_MusicLib->setCheckable(true);

    //电台
    QPushButton* btn_Radio = Get_Button("电台","","",55,39);
    btn_Radio->setStyleSheet(TopButtonStyle);
    btn_Radio->setAutoExclusive(true);
    btn_Radio->setCheckable(true);

    //歌单
    QPushButton* btn_PlayList = Get_Button("歌单","","",55,39);
    btn_PlayList->setStyleSheet(TopButtonStyle);
    btn_PlayList->setAutoExclusive(true);
    btn_PlayList->setCheckable(true);

    //MV
    QPushButton* btn_MV = Get_Button("MV","","",55,39);
    btn_MV->setStyleSheet(TopButtonStyle);
    btn_MV->setAutoExclusive(true);
    btn_MV->setCheckable(true);

    //直播
    QPushButton* btn_Live = Get_Button("直播","","",55,39);
    btn_Live->setStyleSheet(TopButtonStyle);
    btn_Live->setAutoExclusive(true);
    btn_Live->setCheckable(true);

    //歌词
    QPushButton* btn_Lyrice = Get_Button("歌词","","",55,39);
    btn_Lyrice->setStyleSheet(TopButtonStyle);
    btn_Lyrice->setAutoExclusive(true);
    btn_Lyrice->setCheckable(true);
    btn_MusicLib->click();

    TopLayout->addStretch();
    TopLayout->addWidget(btn_MusicLib);
    TopLayout->addSpacing(20);
    TopLayout->addWidget(btn_Radio);
    TopLayout->addSpacing(20);
    TopLayout->addWidget(btn_PlayList);
    TopLayout->addSpacing(20);
    TopLayout->addWidget(btn_MV);
    TopLayout->addSpacing(20);
    TopLayout->addWidget(btn_Live);
    TopLayout->addSpacing(20);
    TopLayout->addWidget(btn_Lyrice);
    TopLayout->addStretch();
    TopWidget->setLayout(TopLayout);

    QStackedWidget* mSWidget = new QStackedWidget();
    mSWidget->addWidget(CreateRightListWidget(MusicLibWidget));
    mSWidget->addWidget(CreateRightListWidget(RadioWidget));
    mSWidget->addWidget(CreateRightListWidget(PlayListWidget));
    mSWidget->addWidget(CreateRightListWidget(MVWidget));
    mSWidget->addWidget(CreateRightListWidget(LiveWidget));
    mSWidget->addWidget(CreateRightListWidget(LyriceWidget));
    mSWidget->addWidget(CreateRightListWidget(SearchMusicWidget));
    mSWidget->addWidget(CreateRightListWidget(VoiceWidget));


    mLayout->addWidget(TopWidget);
    mLayout->addWidget(mSWidget);
    mWidget->setLayout(mLayout);

    this->connect(btn_MusicLib,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(0);});
    this->connect(btn_Radio,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(1);});
    this->connect(btn_PlayList,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(2);});
    this->connect(btn_MV,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(3);});
    this->connect(btn_Live,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(4);});
    this->connect(btn_Lyrice,&QPushButton::clicked,this,[=](){mSWidget->setCurrentIndex(Page);});
    this->connect(this,&KugouMusicBody::MVPageShow,this,[=](){
        mSWidget->setCurrentIndex(7);
    });

    this->connect(this,&KugouMusicBody::SearchWidgetChange,this,[=](QString Name){
        mSWidget->setCurrentIndex(6);
        SearchName = Name;
        emit ChangeName();
    });

    this->connect(this,&KugouMusicBody::ModelChange,this,[=](PlayType type){
        if(type == MusisPlayer)
        {
            Page = 5;
            btn_Lyrice->setText("歌词");
            if(mSWidget->currentIndex() == 7)
            {
                btn_Lyrice->click();
            }
        }
        else if(type == MVPlayer)
        {
            Page = 7;
            btn_Lyrice->setText("视频");
            btn_Lyrice->click();
        }
    });



    return mWidget;
}

QWidget *KugouMusicBody::CreateLeftListWidget(LeftMusicList index)
{
    QWidget* mWidget = nullptr;

    switch (index)
    {
    case LoaclListWidget:
    {
#if 1
        const QString AearStyle = Public_Str::Get_Sty(Style_Css{ScroallAreaStyle});
        QWidget* Widget = new QWidget();
        QHBoxLayout* mLayout = Get_HLayout();

        QScrollArea* Area = new QScrollArea();
//        this->connect(Area->verticalScrollBar(),&QScrollBar::valueChanged,this,[=](int value){
//            qDebug() << value;
//        });
        Area->setStyleSheet(AearStyle);
        QWidget* AearWidget = new QWidget;
//        AearWidget->setMaximumHeight(400);
        QVBoxLayout* AearLayout = Get_VLayout();

        QWidget* View1 = CreateLeftWidgetButtonList("默认列表",0);
//        QWidget* View2 = CreateLeftWidgetButtonList("最近播放");

        AearLayout->addWidget(View1);
//        AearLayout->addWidget(View2);
        AearLayout->addStretch();
        AearWidget->setLayout(AearLayout);
        Area->setWidget(AearWidget);

        Area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


        mLayout->addWidget(Area);
        mLayout->addStretch();
        Widget->setLayout(mLayout);

        mWidget = Widget;
#else
        QWidget* Widget = new QWidget();

        QVBoxLayout* AearLayout = Get_VLayout();

        QWidget* View1 = CreateLeftWidgetButtonList("默认列表");
        QWidget* View2 = CreateLeftWidgetButtonList("最近播放");

        AearLayout->addWidget(View1);
        AearLayout->addWidget(View2);
        AearLayout->addStretch();

        Widget->setLayout(AearLayout);

        mWidget = Widget;
#endif
    }
    break;
    case NetworkListWidget:
    {
        const QString TextStyle = "font:15pt;color:rgb(52,52,52);";
        const QString Text1Style = "font:10pt;color:rgb(51,51,51);";
        const QString Text2Style = "font:12pt ""黑体"";color:rgb(0,0,0);";
        const QString UseButtonStyle = Public_Str::Get_Sty(Style_Css{NetWorkCollectButtonStyle});
        const QString WidgetLineStyle = "border-bottom:1px solid rgb(170,170,170,125);";
        const QString WarnningStyle = "font: 10pt;color:rgb(40,40,40);";

        QWidget* Widget = new QWidget();
        QVBoxLayout* mLayout = Get_VLayout();

        QLabel* lbl_Paint = Get_Label();
        lbl_Paint->setFixedHeight(95);
        lbl_Paint->setPixmap(QPixmap(":/Left/Paint/Left/lab_backups.png"));

        QLabel* lbl_Text = Get_Label("云端备份,多屏同步",0,20);
        lbl_Text->setStyleSheet(TextStyle);

        int num = 0;
        QWidget* TextWidget = new QWidget();
        TextWidget->setFixedHeight(15);
        QHBoxLayout* TextLayout = Get_HLayout();
        QLabel* lbl_Text1 = Get_Label("您的列表有");
        lbl_Text1->setStyleSheet(Text1Style);
        QLabel* lbl_Text2 = Get_Label(QString("%1").arg(num));
        lbl_Text2->setStyleSheet(Text2Style);
        QLabel* lbl_Text3 = Get_Label("首歌曲未设置备份");
        lbl_Text3->setStyleSheet(Text1Style);
        TextLayout->addStretch();
        TextLayout->addWidget(lbl_Text1);
        TextLayout->addSpacing(5);
        TextLayout->addWidget(lbl_Text2);
        TextLayout->addSpacing(5);
        TextLayout->addWidget(lbl_Text3);
        TextLayout->addStretch();
        TextWidget->setLayout(TextLayout);

        QPushButton* btn_Use = Get_Button("马上使用","","",170,35);
        btn_Use->setStyleSheet(UseButtonStyle);

        QWidget* WidgetLine = new QWidget();
        WidgetLine->setStyleSheet(WidgetLineStyle);
        WidgetLine->setFixedSize(250,1);

        QLabel* lbl_Qrcode = Get_Label("",85,85);
        lbl_Qrcode->setPixmap(QPixmap(":/Left/Paint/Left/lab_2DC.png"));

        QLabel* lbl_DownText = Get_Label("扫一扫下载手机酷狗",130,20);
        lbl_DownText->setStyleSheet(WarnningStyle);

        mLayout->addSpacing(25);
        mLayout->addWidget(lbl_Paint);
        mLayout->addSpacing(15);
        mLayout->addWidget(lbl_Text);
        mLayout->addSpacing(1);
        mLayout->addWidget(TextWidget);
        mLayout->addSpacing(3);
        mLayout->addWidget(btn_Use,0,Qt::AlignHCenter);
        mLayout->addSpacing(10);
        mLayout->addWidget(WidgetLine,0,Qt::AlignHCenter);
        mLayout->addSpacing(20);
        mLayout->addWidget(lbl_Qrcode,0,Qt::AlignHCenter);
        mLayout->addSpacing(5);
        mLayout->addWidget(lbl_DownText,0,Qt::AlignHCenter);
        mLayout->addSpacing(30);

        Widget->setLayout(mLayout);

        mWidget = Widget;
    }
    break;
    case MusicRadioListWidget:
    {
        QWidget* Widget = new QWidget();


        mWidget = Widget;
    }
    break;
    case PhoneMusicWidget:
    {
        const QString ChangePageStyle = Public_Str::Get_Sty(Style_Css{LeftPhoneMusicPageTopButtonStyle});
        QWidget* Widget = new QWidget();
        QVBoxLayout* mLayout = Get_VLayout();

        QWidget* ButtonWidget = new QWidget();
        ButtonWidget->setFixedHeight(35);
        QHBoxLayout* ButtonLayout = Get_HLayout();
        QPushButton* btn_kuGouPlay = Get_Button("酷狗Play","酷狗Play","",0,35,0,0,ChangePageStyle);
        QPushButton* btn_PhonePassMusic = Get_Button("手机传歌","","手机传歌",0,35,0,0,ChangePageStyle);
        btn_kuGouPlay->setAutoExclusive(true);
        btn_kuGouPlay->setCheckable(true);
        btn_PhonePassMusic->setAutoExclusive(true);
        btn_PhonePassMusic->setCheckable(true);
        btn_kuGouPlay->click();
        ButtonLayout->addWidget(btn_kuGouPlay);
        ButtonLayout->addWidget(btn_PhonePassMusic);
        ButtonWidget->setLayout(ButtonLayout);


        QStackedWidget* mSWidget = new QStackedWidget();

        //第一界面
        const QString TextStyle = "font:14pt ""黑体"";color:rgb(52,52,52);";
        const QString Text1Style = "font:10pt ""黑体"";color:rgb(170,170,170);";
        const QString Text2Style = "font:12pt;color:rgb(52,52,52);";
        const QString WarnningStyle = "font: 10pt ""黑体"";color:rgb(160,160,160);";
        QWidget* SecondWidget = new QWidget();
        QVBoxLayout* SecondLayout = Get_VLayout();

        QLabel* lbl_SPaint = Get_Label("",150,80);
        lbl_SPaint->setPixmap(QPixmap(":/Left/Paint/Left/Paint.png"));

        QLabel* lbl_STitle = Get_Label("酷狗设备 Play起来",170,20);
        lbl_STitle->setStyleSheet(TextStyle);

        QLabel* lbl_Warnning = Get_Label("手机选择音乐播放-轻松控制酷狗PC",220,15);
        lbl_Warnning->setStyleSheet(Text1Style);

        QLabel* lbl_QRCode = Get_Label("",125,125);
        lbl_QRCode->setPixmap(QPixmap(":/Left/Paint/Left/QRCode.png"));

        QLabel* lbl_QrCodeWarnning = Get_Label("打开手机酷狗音乐扫一扫",155,15);
        lbl_QrCodeWarnning->setStyleSheet(WarnningStyle);

        SecondLayout->addStretch();
        SecondLayout->addWidget(lbl_SPaint,0,Qt::AlignHCenter);
        SecondLayout->addSpacing(35);
        SecondLayout->addWidget(lbl_STitle,0,Qt::AlignHCenter);
        SecondLayout->addSpacing(10);
        SecondLayout->addWidget(lbl_Warnning,0,Qt::AlignHCenter);
        SecondLayout->addSpacing(55);
        SecondLayout->addWidget(lbl_QRCode,0,Qt::AlignHCenter);
        SecondLayout->addSpacing(30);
        SecondLayout->addWidget(lbl_QrCodeWarnning,0,Qt::AlignHCenter);
        SecondLayout->addStretch();
        SecondWidget->setLayout(SecondLayout);

        //第二页面
        const QString ThirdTitleSize = "color:rgb(68,68,68);";
        const QString WireConnectStyle = Public_Str::Get_Sty(Style_Css{LeftPhoneMusicWireConnectButtonStyle});
        const QString NetConnectStyle = Public_Str::Get_Sty(Style_Css{LeftPhoneMusicNetConnectButtonStyle});
        QWidget* ThirdWidget = new QWidget();
        QVBoxLayout* ThirdLayout = Get_VLayout();

        QFont font;
        font.setFamily("黑体");
        font.setPixelSize(18);
        QLabel* lbl_Title = Get_Label("请连接手机后进行传歌",190,20,ThirdTitleSize);
        lbl_Title->setFont(font);

        QPushButton* btn_LineConnect = Get_Button("","","",200,100,0,0,WireConnectStyle);

        QPushButton* btn_WifeConnect = Get_Button("","","",200,100,0,0,NetConnectStyle);

        ThirdLayout->addSpacing(35);
        ThirdLayout->addWidget(lbl_Title,0,Qt::AlignHCenter);
        ThirdLayout->addSpacing(50);
        ThirdLayout->addWidget(btn_LineConnect,0,Qt::AlignHCenter);
        ThirdLayout->addSpacing(30);
        ThirdLayout->addWidget(btn_WifeConnect,0,Qt::AlignHCenter);
        ThirdLayout->addStretch();
        ThirdWidget->setLayout(ThirdLayout);

        //第四界面
        const QString FButtonStyle = "border:none;color:rgb(120,120,120);font:9pt;";
        const QString FTitleStyle = "font:14pt ""黑体"";color:rgb(52,52,52);";
        const QString FTextSStyle = "font:10pt ""黑体"";color:rgb(52,52,52);";
        QWidget* FourWidget = new QWidget();
        QVBoxLayout* FourLayout = new QVBoxLayout();

        //返回
        QPushButton* btn_FButton = Get_Button("返回","","",60,15,0,0,FButtonStyle);

        //图片
        QLabel* lbl_Paint = Get_Label("",240,95);
        lbl_Paint->setPixmap(QPixmap(":/Left/Paint/Left/wirePaint.png"));


        QWidget* TextWidget = new QWidget();
        QVBoxLayout* TextLayout = Get_VLayout();
        //标题
        QLabel* lbl_FTitle = Get_Label("使用数据线连接",0,20,FTitleStyle);

        //标签与按钮
        QHBoxLayout* Text1Layout = Get_HLayout();
        QLabel* lbl_Text1 = Get_Label("1.Android手机请打开USB调式模式",0,15,FTextSStyle);
        QPushButton* btn_Question = Get_Button("",":/Left/Paint/Left/btn_question.png","",20,20,20,20,"border:none;");
        btn_Question->installEventFilter(this);
        btn_Question->setObjectName("btn_Question");
        Text1Layout->addWidget(lbl_Text1);
        Text1Layout->addWidget(btn_Question);
        Text1Layout->addStretch();

        //标签
        QLabel* lbl_Text2 = Get_Label("2.Phone请在连接后信任该电脑",0,15,FTextSStyle);

        //标签
        QLabel* lbl_Text3 = Get_Label("3.移动存储设备直接接入即可",0,15,FTextSStyle);

        TextLayout->addLayout(Text1Layout);
        TextLayout->addSpacing(15);
        TextLayout->addWidget(lbl_Text2,0,Qt::AlignLeft);
        TextLayout->addSpacing(15);
        TextLayout->addWidget(lbl_Text3,0,Qt::AlignLeft);
        TextWidget->setLayout(TextLayout);

        FourLayout->addSpacing(5);
        FourLayout->addWidget(btn_FButton,0,Qt::AlignLeft);
        FourLayout->addSpacing(65);
        FourLayout->addWidget(lbl_Paint,0,Qt::AlignHCenter);
        FourLayout->addSpacing(20);
        FourLayout->addWidget(lbl_FTitle,0,Qt::AlignHCenter);
        FourLayout->addSpacing(5);
        FourLayout->addWidget(TextWidget,0,Qt::AlignHCenter);
        FourLayout->addStretch();

        FourWidget->setLayout(FourLayout);

        //第五界面
        const QString FiveTitleStyle = "font:14pt ""黑体"";";
        const QString FiveTextStyle = "font:10pt ""黑体"";color:rgb(52,52,52); ";
        const QString FiveQuestionStyle = "font:10pt ""黑体"";color:rgb(52,52,52);border:none;border-bottom:1px solid rgb(0,0,0);";
        QWidget* FiveWidget = new QWidget();
        QVBoxLayout* FiveLayout = new QVBoxLayout();

        //返回
        QPushButton* btn_FiveReturn = Get_Button("返回","","",60,15,0,0,FButtonStyle);

        //标题
        QLabel* lbl_FiveTitle = Get_Label("使用【酷狗音乐】扫码连接",0,0,FiveTitleStyle);

        //图片
        QLabel* lbl_FivePaint = Get_Label("",115,115);
        QPixmap Pixmap(":/Left/Paint/Left/fivePaint.png");
        lbl_FivePaint->setPixmap(QPixmap(Pixmap));

        QWidget* FiveTextWidget = new QWidget();
        QVBoxLayout* FiveTextLayout = Get_VLayout();

        //
        QLabel* lbl_FiveText1 = Get_Label("1.手机和电脑在同一wifi下",0,15,FiveTextStyle);

        QHBoxLayout* FiveText2Layout = Get_HLayout();
        QLabel* lbl_FiveText2 = Get_Label("2.使用手机酷狗扫描二维码,",0,15,FiveTextStyle);
        QPushButton* btn_FiveQuestion = Get_Button("如何扫描?","","",0,15,0,0,FiveQuestionStyle);
        btn_FiveQuestion->setObjectName("btn_FiveQuestion");
        btn_FiveQuestion->installEventFilter(this);
        FiveText2Layout->addWidget(lbl_FiveText2);
        FiveText2Layout->addWidget(btn_FiveQuestion);

        FiveTextLayout->addStretch();
        FiveTextLayout->addWidget(lbl_FiveText1,0,Qt::AlignLeft);
        FiveTextLayout->addSpacing(10);
        FiveTextLayout->addLayout(FiveText2Layout);
        FiveTextLayout->addStretch();
        FiveTextWidget->setLayout(FiveTextLayout);

        FiveLayout->addSpacing(5);
        FiveLayout->addWidget(btn_FiveReturn,0,Qt::AlignLeft);
        FiveLayout->addSpacing(70);
        FiveLayout->addWidget(lbl_FiveTitle,0,Qt::AlignHCenter);
        FiveLayout->addSpacing(25);
        FiveLayout->addWidget(lbl_FivePaint,0,Qt::AlignHCenter);
        FiveLayout->addSpacing(10);
        FiveLayout->addWidget(FiveTextWidget,0,Qt::AlignHCenter);
        FiveLayout->addStretch();
        FiveWidget->setLayout(FiveLayout);

        //第六界面
        const QString SixTitleStyle = "font: 14pt ""黑体""; color:rgb(0,0,0);";
        QWidget* SixWidget = new QWidget();
        QVBoxLayout* SixLayout = new QVBoxLayout();
        //返回
        QPushButton* btn_SixReturn = Get_Button("返回","","",60,15,0,0,FButtonStyle);

        QLabel* lbl_SixText = Get_Label("如何打开手机USB调试",0,20,SixTitleStyle);

        QLabel* btn_SixPaint = Get_Label("",220,330);
        btn_SixPaint->setPixmap(QPixmap(":/Left/Paint/Left/sixPaint.png"));
        SixLayout->addSpacing(5);
        SixLayout->addWidget(btn_SixReturn,0,Qt::AlignLeft);
        SixLayout->addSpacing(2);
        SixLayout->addWidget(lbl_SixText,0,Qt::AlignHCenter);
        SixLayout->addSpacing(30);
        SixLayout->addWidget(btn_SixPaint,0,Qt::AlignHCenter);
        SixLayout->addStretch();
        SixWidget->setLayout(SixLayout);

        //第七界面
        const QString SevenTitleStyle = "font: 14pt ""黑体""; color:rgb(0,0,0);";
        QWidget* SevenWidget = new QWidget();
        QVBoxLayout* SevenLayout = Get_VLayout();
        //返回
        QPushButton* btn_SevenReturn = Get_Button("返回","","",60,15,0,0,FButtonStyle);

        QLabel* lbl_SevenText = Get_Label("手机酷狗扫码连接",0,20,SevenTitleStyle);

        QLabel* btn_SevenPaint = Get_Label("",220,360);
        btn_SevenPaint->setPixmap(QPixmap(":/Left/Paint/Left/SevenPaint.png"));
        SevenLayout->addSpacing(5);
        SevenLayout->addWidget(btn_SevenReturn,0,Qt::AlignLeft);
        SevenLayout->addSpacing(2);
        SevenLayout->addWidget(lbl_SevenText,0,Qt::AlignHCenter);
        SevenLayout->addSpacing(20);
        SevenLayout->addWidget(btn_SevenPaint,0,Qt::AlignHCenter);
        SevenLayout->addStretch();
        SevenWidget->setLayout(SevenLayout);


        //逐个添加
        mSWidget->addWidget(SecondWidget);
        mSWidget->addWidget(ThirdWidget);
        mSWidget->addWidget(FourWidget);
        mSWidget->addWidget(FiveWidget);
        mSWidget->addWidget(SixWidget);
        mSWidget->addWidget(SevenWidget);

        mLayout->addWidget(ButtonWidget);
        mLayout->addWidget(mSWidget);
        Widget->setLayout(mLayout);

        this->connect(btn_kuGouPlay,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(0);
        });
        this->connect(btn_PhonePassMusic,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(1);
        });
        this->connect(btn_LineConnect,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(2);
        });
        this->connect(btn_WifeConnect,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(3);
        });
        this->connect(btn_FButton,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(1);
        });
        this->connect(btn_FiveReturn,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(1);
        });
        this->connect(btn_Question,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(4);
        });
        this->connect(btn_FiveQuestion,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(5);
        });
        this->connect(btn_SixReturn,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(2);
        });
        this->connect(btn_SevenReturn,&QPushButton::clicked,this,[=](){
            mSWidget->setCurrentIndex(3);
        });

        mWidget = Widget;
    }
    break;
    case LoaclMusicWidget:
    {
        const QString ChangePageStyle = Public_Str::Get_Sty(Style_Css{LeftPhoneMusicPageTopButtonStyle});
        QWidget* Widget = new QWidget();
        QVBoxLayout* mVLayout = Get_VLayout();

        QWidget* ButtonWidget = new QWidget();
        ButtonWidget->setFixedHeight(35);
        QHBoxLayout* ButtonLayout = Get_HLayout();
        QPushButton* btn_MyDown = Get_Button("酷狗Play","酷狗Play","",0,35,0,0,ChangePageStyle);
        QPushButton* btn_LocalAdd = Get_Button("手机传歌","","手机传歌",0,35,0,0,ChangePageStyle);
        ButtonLayout->addWidget(btn_MyDown);
        ButtonLayout->addWidget(btn_LocalAdd);
        ButtonWidget->setLayout(ButtonLayout);

        QVBoxLayout* DowningLayout = new QVBoxLayout();
        KugouMusicBodyLeftButton* btn_Downing = new KugouMusicBodyLeftButton("下载中");
        MusicDownTableView* ViewDowning = new MusicDownTableView();
        DowningLayout->addWidget(btn_Downing);
        DowningLayout->addWidget(ViewDowning);

        QVBoxLayout* DownedLayout = new QVBoxLayout();
        KugouMusicBodyLeftButton* btn_Downed = new KugouMusicBodyLeftButton("已下载");
        MusicDownEndTableView* ViewDowned = new MusicDownEndTableView();
        DownedLayout->addWidget(btn_Downed);
        DownedLayout->addWidget(ViewDowned);

        mVLayout->addWidget(ButtonWidget);
        mVLayout->addLayout(DowningLayout);
        mVLayout->addLayout(DownedLayout);
        mVLayout->addStretch();
        Widget->setLayout(mVLayout);

/*        ViewDowned->setStyleSheet("border:1px solid rgb(170,170,170);");
        ViewDowning->setStyleSheet("border:1px solid rgb(170,170,170);")*/;
        this->connect(this,&KugouMusicBody::SignalMusicModelSignal,ViewDowned,&MusicDownEndTableView::SignalMusicModelSlot);
        this->connect(this,&KugouMusicBody::OrderOfMusicModelSignal,ViewDowned,&MusicDownEndTableView::OrderOfMusicModelSlot);
        this->connect(this,&KugouMusicBody::ListMusicModelSignal,ViewDowned,&MusicDownEndTableView::ListMusicModelSlot);
        this->connect(this,&KugouMusicBody::RandomMusicModelSignal,ViewDowned,&MusicDownEndTableView::RandomMusicModelSlot);
        this->connect(this,&KugouMusicBody::LoveClickeSignal,ViewDowned,&MusicDownEndTableView::SetLoveState);

        this->connect(this,&KugouMusicBody::PreMusicSignal,this,[=](){
            MusicDownOrderRamdom PlayModel;
            if(Model == RandomMusicModel)
            {
                PlayModel = MusicDownRamdom;
            }
            else
            {
                PlayModel = MusicDownOrder;
            }
            ViewDowned->SwitchMusicMV(PlayModel,MusicDownPre);
        });
        this->connect(this,&KugouMusicBody::NextMusicSignal,this,[=](){
            MusicDownOrderRamdom PlayModel;
            if(Model == RandomMusicModel)
            {
                PlayModel = MusicDownRamdom;
            }
            else
            {
                PlayModel = MusicDownOrder;
            }
            ViewDowned->SwitchMusicMV(PlayModel,MusicDownNext);
        });
        ViewDowned->AddDBDataList(PlayListData::Get()->GetMusicDownData());

        this->connect(ViewDowned,&MusicDownEndTableView::ChangeDBLove,this,[=](QString FilePath,bool isLove,bool isLine){
            PlayListData::Get()->MoiftyMusicDownData(isLove,FilePath);
            if(isLine)
                emit LoveState(isLove);
        });
        this->connect(ViewDowned,&MusicDownEndTableView::DeleteDB,this,[=](QString FilePath){
            PlayListData::Get()->RemoveMusicDownData(FilePath);
        });
        this->connect(ViewDowned,&MusicDownEndTableView::AddMusicDownDB,this,[=](QVariantList List){
            PlayListData::Get()->AddMusicDownData(List);
        });
        this->connect(ViewDowned,&MusicDownEndTableView::PlayNothing,this,&KugouMusicBody::PlayNothing);
        this->connect(this,&KugouMusicBody::ClearDownNowPlayRow,ViewDowned,&MusicDownEndTableView::ClearDownNowPlayRow);
        this->connect(ViewDowned,&MusicDownEndTableView::PlayUrl,this,[=](QString NameSinger,QString Url, bool isLove,bool isMV){
            emit ClearNowPlayRow();
            if(isMV)
                emit PlayListPlayMV(NameSinger,Url,isLove);
            else
                emit PlayListPlay(NameSinger,Url,isLove);
        });
        this->connect(NetWorkHttp::Get(),&NetWorkHttp::WriteOk,ViewDowning,&MusicDownTableView::SendData);
        this->connect(ViewDowning,&MusicDownTableView::SendDownEndData,ViewDowned,&MusicDownEndTableView::AddListData);

        this->connect(NetWorkHttp::Get(),&NetWorkHttp::UpdateInfo,this,[=](QVariantList var){
            qDebug() << var;
            ViewDowning->AddListData(var);
        });
        this->connect(NetWorkHttp::Get(),&NetWorkHttp::updateProgress,ViewDowning,&MusicDownTableView::SlotUpdateProgress);

        this->connect(btn_Downing,&QPushButton::clicked,this,[=](){
            if(ViewDowning->isHidden())
                ViewDowning->show();
            else
                ViewDowning->hide();
        });
        this->connect(btn_Downed,&QPushButton::clicked,this,[=](){
            if(ViewDowned->isHidden())
                ViewDowned->show();
            else
                ViewDowned->hide();
        });

        mWidget = Widget;
    }
    break;
    }

    return mWidget;
}

QWidget *KugouMusicBody::CreateRightListWidget(RightMusicList index)
{
    QWidget* mWidget = nullptr;
    switch(index)
    {
        //乐库
    case MusicLibWidget:
    {
        QWidget* Widget = new QWidget();

        mWidget = Widget;
    }
    break;
        //电台
    case RadioWidget:
    {
        QWidget* Widget = new QWidget();
#if 0
        QWidget* PageWidget = new QWidget();
        QHBoxLayout* PageLayout = Get_HLayout();

        QPushButton* btn_PublicRadio = Get_Button();

        QPushButton* btn_OrgasmRadio = Get_Button();

        QPushButton* btn_RealRadio = Get_Button();
        PageLayout->addWidget(btn_PublicRadio);
        PageLayout->addWidget(btn_OrgasmRadio);
        PageLayout->addWidget(btn_RealRadio);
        PageWidget->setLayout(PageLayout);

        QWidget* TypeWidget = new QWidget();
        QHBoxLayout* TypeLayout = Get_HLayout();

        QPushButton* btn_Recommended = Get_Button();
        QPushButton* btn_DJ = Get_Button();
        QPushButton* btn_Language = Get_Button();
        QPushButton* btn_Theme = Get_Button();
        QPushButton* btn_Scenario = Get_Button();
        QPushButton* btn_Mood = Get_Button();
        QPushButton* btn_Style = Get_Button();
        QPushButton* btn_Crowd = Get_Button();
        QPushButton* btn_Children = Get_Button();
        QPushButton* btn_Musical = Get_Button();

        TypeLayout->addWidget(btn_Recommended);
        TypeLayout->addWidget(btn_DJ);
        TypeLayout->addWidget(btn_Language);
        TypeLayout->addWidget(btn_Theme);
        TypeLayout->addWidget(btn_Scenario);
        TypeLayout->addWidget(btn_Mood);
        TypeLayout->addWidget(btn_Style);
        TypeLayout->addWidget(btn_Crowd);
        TypeLayout->addWidget(btn_Children);
        TypeLayout->addWidget(btn_Musical);
        TypeWidget->setLayout(TypeLayout);

#endif
        mWidget = Widget;
    }
    break;
        //歌单
    case PlayListWidget:
    {
        QWidget* Widget = new QWidget();

        mWidget = Widget;
    }
    break;
        //MV
    case MVWidget:
    {
        QWidget* Widget = new QWidget();

        mWidget = Widget;
    }
    break;
        //直播
    case LiveWidget:
    {
        QWidget* Widget = new QWidget();

        mWidget = Widget;
    }
    break;
        //歌词
    case LyriceWidget:
    {
        QWidget* Widget = new QWidget();
        Widget->setObjectName("LyricsWidget");
        Widget->setStyleSheet("#LyricsWidget{background-color:rgb(44,169,255);}");
        QHBoxLayout* mLayout = Get_HLayout();
        KugouMusicLyrics* LyricsWidget = new KugouMusicLyrics();

        mLayout->addWidget(LyricsWidget);
        Widget->setLayout(mLayout);

        this->connect(this,&KugouMusicBody::MusicSongLyricsTime,LyricsWidget,&KugouMusicLyrics::MusicSongLyricsTimeSlot);
        this->connect(this,&KugouMusicBody::UpdateLyrics,LyricsWidget,&KugouMusicLyrics::StartMove);
        this->connect(this,&KugouMusicBody::SeekLyrics,LyricsWidget,&KugouMusicLyrics::SeekLyrics);
        this->connect(this,&KugouMusicBody::ClearLyricsWidget,LyricsWidget,&KugouMusicLyrics::ClearLyrics);
        mWidget = Widget;
    }
    break;
        //搜索
    case SearchMusicWidget:
    {
        const QString TopButtonStyle = Public_Str::Get_Sty(Style_Css{RightSearchTopButtonStyle,});
        const QString PlayAllStyle = Public_Str::Get_Sty(Style_Css{RightPlayAllButtonStyle,});
        const QString AddPlayStyle = Public_Str::Get_Sty(Style_Css{ALLDownButtonStyle,});
        const QString AearStyle = Public_Str::Get_Sty(Style_Css{ViewSliderStyle});
        const QString SearchNameStyle = "font:10pt; color:rgb(0,170,255);";
        const QString SearchTextStyle = "font:10pt; color:rgb(170,170,170);";
        QWidget* Widget = new QWidget();
        QVBoxLayout* mLayout = Get_VLayout();

        QWidget* TopWidget = new QWidget();
        TopWidget->setObjectName("TopWidget");
        TopWidget->setStyleSheet("#TopWidget{border-bottom:1px solid rgb(170,170,170);}");
        TopWidget->setFixedHeight(35);
        QHBoxLayout* TopLayout = Get_HLayout();

        QPushButton* btn_SignalMusic = Get_Button("单曲","","",70,35);
        QPushButton* btn_PlayList = Get_Button("歌单","","",70,35);
        QPushButton* btn_MV = Get_Button("MV","","",70,35);
        QPushButton* btn_Album = Get_Button("专辑","","",70,35);
        QPushButton* btn_Lyrics = Get_Button("歌词","","",70,35);

        btn_SignalMusic->setStyleSheet(TopButtonStyle);
        btn_PlayList->setStyleSheet(TopButtonStyle);
        btn_MV->setStyleSheet(TopButtonStyle);
        btn_Album->setStyleSheet(TopButtonStyle);
        btn_Lyrics->setStyleSheet(TopButtonStyle);
        btn_SignalMusic->setAutoExclusive(true);
        btn_SignalMusic->setCheckable(true);
        btn_PlayList->setAutoExclusive(true);
        btn_PlayList->setCheckable(true);
        btn_MV->setAutoExclusive(true);
        btn_MV->setCheckable(true);
        btn_Album->setAutoExclusive(true);
        btn_Album->setCheckable(true);
        btn_Lyrics->setAutoExclusive(true);
        btn_Lyrics->setCheckable(true);
        btn_SignalMusic->click();


        TopLayout->addStretch();
        TopLayout->addWidget(btn_SignalMusic);
        TopLayout->addSpacing(20);
        TopLayout->addWidget(btn_PlayList);
        TopLayout->addSpacing(20);
        TopLayout->addWidget(btn_MV);
        TopLayout->addSpacing(20);
        TopLayout->addWidget(btn_Album);
        TopLayout->addSpacing(20);
        TopLayout->addWidget(btn_Lyrics);
        TopLayout->addStretch();
        TopWidget->setLayout(TopLayout);

        QWidget* MidWidget = new QWidget();
        MidWidget->setFixedHeight(45);
        QHBoxLayout* MidLayout = Get_HLayout();

        QWidget* WarnningWidget = new QWidget();
        QHBoxLayout* WarnningLayout = Get_HLayout(10);
        QLabel* lbl_Warnning = Get_Label("搜索到",0,0,SearchTextStyle);
        QLabel* lbl_MusicName = Get_Label("",0,0,SearchNameStyle);
        QLabel* lbl_Warnning1 = Get_Label("的相关曲目",0,0,SearchTextStyle);
        WarnningLayout->addWidget(lbl_Warnning);
        WarnningLayout->addSpacing(3);
        WarnningLayout->addWidget(lbl_MusicName);
        WarnningLayout->addSpacing(3);
        WarnningLayout->addWidget(lbl_Warnning1);
        WarnningWidget->setLayout(WarnningLayout);

        this->connect(this,&KugouMusicBody::ChangeName,this,[=](){
            lbl_MusicName->setText(" " + SearchName + " ");
        });

        QPushButton* btn_PlayAll = Get_Button("播放全部","","",70,25);
        btn_PlayAll->setStyleSheet(PlayAllStyle);
        QPushButton* btn_Add = Get_Button("添加","","",40,25);
        btn_Add->setStyleSheet(AddPlayStyle);
        QPushButton* btn_Down = Get_Button("下载","","",40,25);
        btn_Down->setStyleSheet(AddPlayStyle);

        MidLayout->addWidget(WarnningWidget);
        MidLayout->addStretch();
        MidLayout->addWidget(btn_PlayAll);
        MidLayout->addSpacing(10);
        MidLayout->addWidget(btn_Add);
        MidLayout->addSpacing(10);
        MidLayout->addWidget(btn_Down);
        MidLayout->addSpacing(10);
        MidWidget->setLayout(MidLayout);

        SearchHeadTableView* View = new SearchHeadTableView();
        View->setFixedHeight(30);
        SearchTableView* View1 = new SearchTableView();
        View1->setStyleSheet(AearStyle);
        View1->setObjectName("SearchTableView");
        this->connect(View1,&SearchTableView::AddPlayList,this,&KugouMusicBody::PlayListDataSignal);
#if 0
//        this->connect(View1,&SearchTableView::DoubleClickedSong,this,&KugouMusicBody::PlaySongSignal);
//        this->connect(View1,&SearchTableView::MVClicked,this,&KugouMusicBody::MVClickSignal);
//        this->connect(View1,&SearchTableView::NowPlayerMusicName,this,&KugouMusicBody::NowPlayerMusicName)
//        SearchTableView* View1 = new SearchTableView(15);
//        View->stackUnder(View1);
#endif


        mLayout->addWidget(TopWidget);
        mLayout->addWidget(MidWidget);
        mLayout->addWidget(View);
        mLayout->addWidget(View1);
        Widget->setLayout(mLayout);
        mWidget = Widget;
    }
    break;
        //视频
    case VoiceWidget:
    {
        const QString MVNameStyle = "color:rgb(255,255,255);";
        const QString MVTimeStyle = "color:rgb(170,170,170);";
        const QString MVSliderStyle = Public_Str::Get_Sty(Style_Css{PlayerSliderStyle});
        const QString MVExitStyle = Public_Str::CreateMVPageStyle(MVExitButtonStyle);
        const QString MVPreStyle = Public_Str::CreateMVPageStyle(MVPreButtonStyle);
        const QString MVNextStyle = Public_Str::CreateMVPageStyle(MVNextButtonStyle);
        const QString MVStartStyle = Public_Str::CreateMVPageStyle(MVStartButtonStyle);
        const QString MVStopStyle = Public_Str::CreateMVPageStyle(MVStopButtonStyle);

        QWidget* Widget = new QWidget();
        QVBoxLayout* mHLayout = Get_VLayout();

        QWidget* TopWidget = new QWidget();
        TopWidget->setObjectName("TopWidget");
        TopWidget->setStyleSheet("#TopWidget{background-color:rgb(50,50,50);}");
        TopWidget->setFixedHeight(30);
        QHBoxLayout* TopLayout = Get_HLayout(10,10);

        QLabel* NameText = Get_Label();
        NameText->setStyleSheet(MVNameStyle);
        QPushButton* btn_Exit = Get_Button("","","",15,15);
        btn_Exit->setStyleSheet(MVExitStyle);

        TopLayout->addWidget(NameText);
        TopLayout->addStretch();
        TopLayout->addWidget(btn_Exit);
        TopWidget->setLayout(TopLayout);

        KugouAVPlayer* avPalyer = new KugouAVPlayer();
        avPalyer->setObjectName("avPalyer");

        QWidget* BottomWidget = new QWidget();
        BottomWidget->setObjectName("BottomWidget");
        BottomWidget->setStyleSheet("#BottomWidget{background-color:rgb(50,50,50);}");
        BottomWidget->setFixedHeight(60);
        QVBoxLayout* BottomLayout = Get_VLayout();

        QSlider* MVPlayerSlide = new QSlider(Qt::Horizontal);
        MVPlayerSlide->setObjectName("MVPlayerSlide");
        MVPlayerSlide->setStyleSheet(MVSliderStyle);
        MVPlayerSlide->setFixedHeight(12);
        MVPlayerSlide->installEventFilter(this);

        QHBoxLayout* BottomHLayout = new QHBoxLayout();
        QPushButton* btn_PreMV = Get_Button("","","",15,20);
        btn_PreMV->setStyleSheet(MVPreStyle);

        QPushButton* btn_MVStartStop = Get_Button("","","",20,25);
        btn_MVStartStop->setStyleSheet(MVStartStyle);

        QPushButton* btn_NextMV = Get_Button("","","",15,20);
        btn_NextMV->setStyleSheet(MVNextStyle);

        QLabel* btn_MVTime = Get_Label("00:00/00:00",200);
        btn_MVTime->setStyleSheet(MVTimeStyle);

        BottomHLayout->addSpacing(10);
        BottomHLayout->addWidget(btn_PreMV);
        BottomHLayout->addSpacing(15);
        BottomHLayout->addWidget(btn_MVStartStop);
        BottomHLayout->addSpacing(15);
        BottomHLayout->addWidget(btn_NextMV);
        BottomHLayout->addSpacing(20);
        BottomHLayout->addWidget(btn_MVTime);
        BottomHLayout->addStretch();

        BottomLayout->addWidget(MVPlayerSlide);
        BottomLayout->addLayout(BottomHLayout);
        BottomWidget->setLayout(BottomLayout);


        mHLayout->addWidget(TopWidget);
        mHLayout->addWidget(avPalyer);
        mHLayout->addWidget(BottomWidget);
        Widget->setLayout(mHLayout);

        this->connect(this,&KugouMusicBody::ChangeVolumeSignal,this,[=](double Value){
            avPalyer->SetVoiume(Value);
        });
        this->connect(avPalyer,&KugouAVPlayer::PlayEndof,this,[=](QString url){
            int PlayType = 0;
            if(Type == MusisPlayer)
            {
                PlayType = 0;
            }
            else
                PlayType = 1;
            switch (Model)
            {
            case SignalMusicModel:
            {
                Type = MusisPlayer;
                emit ClearLyricsWidget();
                emit ModelChange(Type);
                emit SignalMusicModelSignal(PlayType);
                emit ClearBottomInfo();
            }
            break;
            case SignalLoopMusicModel:
            {
                avPalyer->Play("");
                avPalyer->Play(url);
            }
            break;
            case OrderOfMusicModel:
            {
                emit OrderOfMusicModelSignal(PlayType);
            }
            break;
            case ListMusicModel:
            {
                emit ListMusicModelSignal(PlayType);
            }
            break;
            case RandomMusicModel:
            {
                emit RandomMusicModelSignal(PlayType);
            }
            break;
            }
        });
        this->connect(avPalyer,&KugouAVPlayer::Get_PlayerState,this,[=](bool State){
            if(State)
            {
                btn_MVStartStop->setStyleSheet(MVStartStyle);
            }
            else
            {
                btn_MVStartStop->setStyleSheet(MVStopStyle);
            }
            emit PlayerStateChange(State);
        });
        this->connect(this,&KugouMusicBody::PlayListPlay,this,[=](QString Name,QString Url,bool isLove){
            avPalyer->Play("");
            Type = MusisPlayer;
            avPalyer->SetDoubleClicked();
            avPalyer->Play(Url);
            emit UpdatePlayerName(Name);
            emit ModelChange(Type);
            emit LoveState(isLove);
        });
        this->connect(this,&KugouMusicBody::PlayListPlayMV,this,[=](QString SingerName,QString Url,bool isLove){
            Type = MVPlayer;
            if(!Url.isEmpty())
            {
                avPalyer->Play("");
                avPalyer->SetDoubleClicked();
                NameText->setText(SingerName);
                UpdatePlayerName(SingerName);
                avPalyer->Play(Url);
                emit MVPageShow();
                emit ModelChange(Type);
                emit LoveState(isLove);
            }
        });
        this->connect(this,&KugouMusicBody::PlayNothing,this,[=](){
            emit ModelChange(MusisPlayer);
            avPalyer->Play("");
            emit ClearBottomInfo();
        });
        this->connect(btn_MVStartStop,&QPushButton::clicked,this,[=](){
            avPalyer->SetPause();
        });
        this->connect(MVPlayerSlide,&QSlider::sliderMoved,this,[=](int value){
            avPalyer->Seek(value);
        });
        this->connect(avPalyer,&KugouAVPlayer::StartPlayer,this,[=](int value){
            mDruation = value;
            MVPlayerSlide->setRange(0,value);
            emit StartPlayerSignal(value);
        });
        this->connect(avPalyer,&KugouAVPlayer::UpdateSliderPos,this,[=](qint64 value){
            QTime t(0,0,0);
            t = t.addMSecs(value);
            StartTime = t.toString("hh:mm:ss");
            t.setHMS(0,0,0);
            t = t.addMSecs(mDruation);
            LastTime = t.toString("hh:mm:ss");
            t.setHMS(0,0,0);
            t = t.addMSecs(value);
            LyricsTime = t.toString("mm:ss:zzz");

            btn_MVTime->setText(StartTime + "/" + LastTime);
            MVPlayerSlide->setValue(value);
            emit UpdateLyrics(LyricsTime);
            emit UpdateSliderPosSignal(value);
        });
        this->connect(this,&KugouMusicBody::SeekPlaySignal,this,[=](int value){
            avPalyer->Seek(value);
            QTime t(0,0,0);
            t = t.addMSecs(value);
            LyricsTime = t.toString("mm:ss:zzz");
            if(Type == MusisPlayer)
                emit SeekLyrics(LyricsTime);
        });
        this->connect(this,&KugouMusicBody::SeekPlay,this,[=](int value){
            avPalyer->Seek(value);
            QTime t(0,0,0);
            t = t.addMSecs(value);
            LyricsTime = t.toString("mm:ss:zzz");
            if(Type == MusisPlayer)
                emit SeekLyrics(LyricsTime);
        });
        this->connect(this,&KugouMusicBody::PlayerChangeStateSignal,this,[=](){
            avPalyer->SetPause();
        });

#if 0
this->connect(this,&KugouMusicBody::PlaySongSignal,this,[=](QString hash,QString alubm_id,QString Name){
    QString url = NetWorkHttp::Get()->SongGetJson(hash,alubm_id);
    avPalyer->Play(url);
    emit ModelChange(MusisPlayer);
    emit UpdatePlayerName(Name);
});
this->connect(this,&KugouMusicBody::MVClickSignal,this,[=](QString MVHash,QString SingerName){
    QString url = NetWorkHttp::Get()->MVGetJson(MVHash);
    if(!url.isEmpty())
    {
        NameText->setText(SingerName);
        UpdatePlayerName(SingerName);
        avPalyer->Play(url);
        emit ModelChange(MVPlayer);
        emit MVPageShow();
    }
});
#endif

        mWidget = Widget;
    }
    break;
    }
    return mWidget;
}

QWidget *KugouMusicBody::CreateLeftWidgetButtonList(QString Name,int id)
{
#if 0
    QWidget* mWidget = new QWidget();

    QVBoxLayout* mLayout = Get_VLayout();
    KugouMusicBodyLeftButton* btn = new KugouMusicBodyLeftButton(Name);

    QScrollArea* area = new QScrollArea();
    QListWidget* View = new QListWidget();
    View->setFixedWidth(310);
//    View->setf(99 * 17);
    View->setStyleSheet("border:none;");
    area->setWidget(View);

    mLayout->addWidget(btn);
    mLayout->addWidget(area);
    mLayout->addStretch();
    mWidget->setLayout(mLayout);

    this->connect(btn,&QPushButton::clicked,this,[=](){
        if(area->isHidden())
        {
            area->show();
        }
        else
        {
            area->hide();
        }
    });

    for(int i = 0; i < 99; i++)
    {
        View->addItem(QString::number(i));
    }

//    area->setFixedHeight(6666);
    return mWidget;
#else
    QWidget* mWidget = new QWidget();
    mWidget->setMinimumHeight(40);

    QVBoxLayout* mLayout = Get_VLayout();
    KugouMusicBodyLeftButton* btn = new KugouMusicBodyLeftButton(Name);
    btn->raise();
    PlayListView* View = new PlayListView(id);
    View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    View->setFixedWidth(310);
    View->setFixedHeight(999);
    View->setStyleSheet("border:none;");
    mLayout->addWidget(btn);
    mLayout->addWidget(View);

    mWidget->setLayout(mLayout);

    this->connect(View,&PlayListView::DownButtonClicked,this,[=](QString NameSinger,QString Music,QString MV,QString Time){
        KugouMusicDown* Down = new KugouMusicDown(NameSinger,Music,MV,Time);
        this->connect(Down,&KugouMusicDown::MusicDown,this,[=](QString name,QString MusicUrl,QString Time){
            emit SwitchLeftPage(4);
            NetWorkHttp::Get()->DownSongOrMv(false,MusicUrl,name,Time);
        });
        this->connect(Down,&KugouMusicDown::MVDown,this,[=](QString name,QString MusicUrl,QString Time){
            emit SwitchLeftPage(4);
            NetWorkHttp::Get()->DownSongOrMv(true,MusicUrl,name,Time);
        });
        Down->exec();
    });

    QList<QVariantList> var = PlayListData::Get()->GetDBTableData(id);
    for(int i = 0; i < var.size(); i++)
    {
        QVariantList List;
        List.push_back(var.at(i).at(0));
        List.push_back(var.at(i).at(1));
        List.push_back(var.at(i).at(2));
        List.push_back(var.at(i).at(3));
        List.push_back(var.at(i).at(4));
        List.push_back(var.at(i).at(5));
        View->AddInitData(List);
    }
    this->connect(this,&KugouMusicBody::PreMusicSignal,this,[=](){
        Ramdom_Order PlayModel = Order;
        int MusicType = 0;
        if(Type == MusisPlayer)
            MusicType = 0;
        else
            MusicType = 1;
        if(Model == RandomMusicModel)
        {
            PlayModel = Ramdom;
        }
        else
        {
            PlayModel = Order;
        }
        View->SwitchMusicMV(MusicType,PlayModel,Pre);
    });
    this->connect(this,&KugouMusicBody::NextMusicSignal,this,[=](){
        Ramdom_Order PlayModel = Order;
        int MusicType = 0;
        if(Type == MusisPlayer)
            MusicType = 0;
        else
            MusicType = 1;
        if(Model == RandomMusicModel)
        {
            PlayModel = Ramdom;
        }
        else
        {
            PlayModel = Order;
        }
        View->SwitchMusicMV(MusicType,PlayModel,Next);
    });
    this->connect(this,&KugouMusicBody::SignalMusicModelSignal,View,&PlayListView::SignalMusicModelSlot);
    this->connect(this,&KugouMusicBody::OrderOfMusicModelSignal,View,&PlayListView::OrderOfMusicModelSlot);
    this->connect(this,&KugouMusicBody::ListMusicModelSignal,View,&PlayListView::ListMusicModelSlot);
    this->connect(this,&KugouMusicBody::RandomMusicModelSignal,View,&PlayListView::RandomMusicModelSlot);

    this->connect(View,&PlayListView::PlayNothing,this,&KugouMusicBody::PlayNothing);
    this->connect(this,&KugouMusicBody::DownCliKcedSignal,View,&PlayListView::SetDownState);
    this->connect(this,&KugouMusicBody::LoveClickeSignal,View,&PlayListView::SetLoveState);
    this->connect(View,&PlayListView::ChangeDBLove,this,[=](int m_ID,QString Hash,bool isLove,bool isLine){
        PlayListData::Get()->MoiftyTableDataLove(m_ID,Hash,isLove);
        if(isLine)
            emit LoveState(isLove);
    });
    this->connect(View,&PlayListView::AddForSql,this,[=](int m_ID,QVariantList var){
        PlayListData::Get()->AddDBTableData(m_ID,var);
    });
    this->connect(View,&PlayListView::DeleteDB,this,[=](int m_ID,QString key){
        emit ClearLyricsWidget();
        PlayListData::Get()->DeleteTableData(m_ID,key);
    });
    this->connect(this,&KugouMusicBody::ClearNowPlayRow,View,&PlayListView::ClearNowPlayRow);
    this->connect(View,&PlayListView::MusicSongLyricsTime,this,&KugouMusicBody::MusicSongLyricsTime);
    this->connect(View,&PlayListView::PlayListPlayMV,this,&KugouMusicBody::PlayListPlayMV);
    this->connect(View,&PlayListView::PlayListPlayMV,this,&KugouMusicBody::ClearDownNowPlayRow);
    this->connect(View,&PlayListView::PlayListPlayMusic,this,&KugouMusicBody::PlayListPlay);
    this->connect(View,&PlayListView::PlayListPlayMusic,this,&KugouMusicBody::ClearDownNowPlayRow);
    this->connect(this,&KugouMusicBody::PlayListDataSignal,this,[=](bool isMV,QVariantList List){
        QString Hash = List.at(3).toString();
        QString Album_ID = List.at(4).toString();
        QString MVHash = List.at(5).toString();
        QString Musicurl;
        QString MVUrl;
        QStringList MusicLyrics;
        QStringList MusicLyricsTime;
        QString img;
        if(!Hash.isEmpty())
        {
            QVariantList List = NetWorkHttp::Get()->SongGetJson(Hash,Album_ID);

            if(List.size() >= 3)
            {
                MusicLyrics = List.at(0).toStringList();
                MusicLyricsTime = List.at(1).toStringList();
                Musicurl = List.at(2).toString();
                img = List.at(3).toString();
            }
        }
        qDebug() << MusicLyrics.size() << MusicLyricsTime.size();
        if(!MVHash.isEmpty())
        {
            MVUrl = NetWorkHttp::Get()->MVGetJson(MVHash);
        }

        QVariantList var;
        var.push_back(List.at(0));
        var.push_back(List.at(1));
        var.push_back(List.at(2));
        var.push_back(Musicurl);
        var.push_back(MVUrl);
        var.push_back(false);
        var.push_back(MusicLyrics);
        var.push_back(MusicLyricsTime);
        View->AddMusicData(isMV,var);

        emit ChangeImage(img);
    });

    this->connect(btn,&QPushButton::clicked,this,[=](){
        if(View->isHidden())
        {
            View->show();
        }
        else
        {
            View->hide();
        }
    });

    return mWidget;
#endif
}

bool KugouMusicBody::eventFilter(QObject *o, QEvent *e)
{
    QPushButton* btn_Question = this->findChild<QPushButton*>("btn_Question");
    QPushButton* btn_FiveQuestion = this->findChild<QPushButton*>("btn_FiveQuestion");
    if(o == btn_Question)
    {
        if(e->type() == QEvent::HoverEnter)
        {
             this->setCursor(Qt::PointingHandCursor);
        }
        else if(e->type() == QEvent::HoverLeave)
        {
             this->setCursor(Qt::ArrowCursor);
        }
    }
    if(o == btn_FiveQuestion)
    {
        if(e->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
        }
        else if(e->type() == QEvent::HoverLeave)
        {
            this->setCursor(Qt::ArrowCursor);
        }
    }
    QSlider* mSlider = this->findChild<QSlider*>("MVPlayerSlide");
    if(o == mSlider)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
            int dur = mSlider->maximum() - mSlider->minimum();
            int pos = mSlider->minimum() + dur * ((double)mouseEvent->x() / mSlider->width());
            if(pos != mSlider->sliderPosition())
            {
                mSlider->setValue(pos);
            }
            emit SeekPlay(mSlider->value());
        }
    }
    return KugouBaseControl::eventFilter(o,e);
}


void KugouMusicBody::SlotSearchSlot(QString name)
{
    emit SearchWidgetChange(name);

    QList<QVariantList> List = NetWorkHttp::Get()->SearchGetJson(name);

    SearchTableView* View = this->findChild<SearchTableView*>("SearchTableView");
    View->AddTableList(List);
}

void KugouMusicBody::MusicModelSlot()
{
    if(Model == SignalMusicModel)
    {
        Model = SignalLoopMusicModel;
    }
    else if(SignalLoopMusicModel == Model)
    {
        Model = OrderOfMusicModel;
    }
    else if(OrderOfMusicModel == Model)
    {
        Model = ListMusicModel;
    }
    else if(ListMusicModel == Model)
    {
        Model = RandomMusicModel;
    }
    else
    {
        Model = SignalMusicModel;
    }
}


//void KugouMusicBody::PlaySong(QString hash, QString alubm_id,QString Name)
//{
//    emit PlaySongSignal(hash,alubm_id,Name);

//}

