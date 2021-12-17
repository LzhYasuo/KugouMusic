#include "KugouMusicMain.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QWidgetAction>
#include <QTime>
#include <QDebug>
#include <QPixmap>
#include <QDir>

#include "NetWork/NetWorkHttp.h"
#include "Public/Public_Str.h"
#include "KugouMusicVoicme.h"
#include "KugouMusicBody.h"

KugouMusicMain::KugouMusicMain(QWidget *parent)
: KugouBaseControl(parent)
{
    VoiceWidget = new KugouMusicVoicme();
    VoiceWidget->installEventFilter(this);
    this->Init();
    this->setMinimumSize(1000,665);
    setMouseTracking(true);
}

KugouMusicMain::~KugouMusicMain()
{
    VoiceWidget->deleteLater();
}

void KugouMusicMain::Init()
{
    this->setObjectName("KugouMusicMain");
    QVBoxLayout* mLayout = Get_VLayout();

    QWidget* TopWidget = InitTopWidget();
    KugouMusicBody* MidWidget = new KugouMusicBody();
    QWidget* BottomWidget = InitBottomWidget( );

    mLayout->addWidget(TopWidget);
    mLayout->addWidget(MidWidget);
    mLayout->addWidget(BottomWidget);
    this->setLayout(mLayout);

    this->connect(MidWidget,&KugouMusicBody::ChangeImage,this,[=](QString imgae){
        QPixmap pixmap;
        pixmap.loadFromData(NetWorkHttp::Get()->GetReadAll(imgae));
//        controlBar->pushButton_albumPic->setIcon(QIcon(pixmap.scaled(50,50,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        pixmap.save(QDir::currentPath() + "/cover.jpg");
        this->setStyleSheet("#KugouMusicMain{background-image:url(cover.jpg);}");
    });
    this->connect(VoiceWidget,&KugouMusicVoicme::ChangeVolume,MidWidget,&KugouMusicBody::ChangeVolumeSignal);
    this->connect(MidWidget,&KugouMusicBody::PlayerStateChange,this,&KugouMusicMain::StartMusic);
    this->connect(MidWidget,&KugouMusicBody::ClearBottomInfo,this,&KugouMusicMain::ClearBottomInfo);
    this->connect(this,&KugouMusicMain::SearchSignal,MidWidget,&KugouMusicBody::SlotSearchSlot);
    this->connect(this,&KugouMusicMain::SeekPlay,MidWidget,&KugouMusicBody::SeekPlaySignal);
    this->connect(this,&KugouMusicMain::PreMusicSignal,MidWidget,&KugouMusicBody::PreMusicSignal);
    this->connect(this,&KugouMusicMain::NextMusicSignal,MidWidget,&KugouMusicBody::NextMusicSignal);
    this->connect(this,&KugouMusicMain::MusicModelSignal,MidWidget,&KugouMusicBody::MusicModelSlot);
    this->connect(MidWidget,&KugouMusicBody::LoveState,this,&KugouMusicMain::LoveStateSingal);
    this->connect(this,&KugouMusicMain::LoveClickeSignal,MidWidget,&KugouMusicBody::LoveClickeSignal);
    this->connect(this,&KugouMusicMain::DownCliKcedSignal,MidWidget,&KugouMusicBody::DownCliKcedSignal);
    this->connect(this,&KugouMusicMain::MusicModelClicked,this,[=](){
        PlayModel Model = MidWidget->Get_Model();
        const QString PlayList1Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel1ButtonStyle);
        const QString PlayList2Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel2ButtonStyle);
        const QString PlayList3Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel3ButtonStyle);
        const QString PlayList4Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel4ButtonStyle);
        const QString PlayList5Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel5ButtonStyle);
        if(Model == SignalMusicModel)
        {
            emit ChangePlayModelIcon(PlayList2Style);
        }
        else if(Model == SignalLoopMusicModel)
        {
            emit ChangePlayModelIcon(PlayList3Style);
        }
        else if(Model == OrderOfMusicModel)
        {
            emit ChangePlayModelIcon(PlayList4Style);
        }
        else if(Model == ListMusicModel)
        {
            emit ChangePlayModelIcon(PlayList5Style);
        }
        else
        {
            emit ChangePlayModelIcon(PlayList1Style);
        }
        emit MusicModelSignal();
    });
    this->connect(MidWidget,&KugouMusicBody::PlayNothing,this,[=](){
        QSlider* PlayerSlider = this->findChild<QSlider*>("PlayerSlider");
        PlayerSlider->setValue(0);
        QLabel* TimeLabel = this->findChild<QLabel*>("Music_Time");
        TimeLabel->setText("00:00/00:00");
    });
    this->connect(MidWidget,&KugouMusicBody::StartPlayerSignal,this,[=](int Duration){
        mDruation = Duration;
        QSlider* PlayerSlider = this->findChild<QSlider*>("PlayerSlider");
        PlayerSlider->setRange(0,Duration);
        PlayerSlider->setValue(0);
    });
    this->connect(MidWidget,&KugouMusicBody::UpdateSliderPosSignal,this,[=](qint64 value){
        QLabel* TimeLabel = this->findChild<QLabel*>("Music_Time");
        QSlider* PlayerSlider = this->findChild<QSlider*>("PlayerSlider");

        QTime t(0,0,0);
        t = t.addMSecs(value);
        StartTime = t.toString("hh:mm:ss");
        t.setHMS(0,0,0);
        t = t.addMSecs(mDruation);
        LastTime = t.toString("hh:mm:ss");

        TimeLabel->setText(StartTime + "/" + LastTime);
        //进度条拉进度
        PlayerSlider->setValue(value);
    });
    this->connect(this,&KugouMusicMain::PlayerChangeState,MidWidget,&KugouMusicBody::PlayerChangeStateSignal);
    this->connect(MidWidget,&KugouMusicBody::UpdatePlayerName,this,[=](QString Name){
        QLabel* NameLabel = this->findChild<QLabel*>("MusicName");
        NameLabel->setText(Name);
    });
}

bool KugouMusicMain::eventFilter(QObject *obj, QEvent *event)
{
    QSlider* mSlider = this->findChild<QSlider*>("PlayerSlider");
    QPushButton* btn_Voice = this->findChild<QPushButton*>("btn_Voice");
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(obj == mSlider)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            int dur = mSlider->maximum() - mSlider->minimum();
            int pos = mSlider->minimum() + dur * ((double)mouseEvent->x() / mSlider->width());
            if(pos != mSlider->sliderPosition())
            {
                mSlider->setValue(pos);
            }
            emit SeekPlay(mSlider->value());
        }
    }
    if(obj == btn_Voice)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            QPoint gpos = mapToGlobal(QPoint(-5,this->height() - 110 - 60) + QPoint(btn_Voice->x(),btn_Voice->y()));
            VoiceWidget->move(gpos);
            VoiceWidget->setFocus();
            VoiceWidget->show();
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            VoiceWidget->hide();
        }
    }
    if(obj == VoiceWidget)
    {
        if(event->type() == QEvent::Enter)
        {
            VoiceWidget->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            VoiceWidget->hide();
        }
    }
    return KugouBaseControl::eventFilter(obj,event);
}

QWidget *KugouMusicMain::InitTopWidget()
{
    const QString Logo_Style = Public_Str::Get_Sty(Style_Css{TopLogoLabelStyle});
    const QString PreButtonStyle = Public_Str::CreateTopButtonStyle(TopReturnButtonStyle);
    const QString RefushButtonStyle = Public_Str::CreateTopButtonStyle(TopRefreshButtonStyle);
    const QString SearchButtonStyle = Public_Str::CreateTopButtonStyle(TopSearchButtonStyle);
    const QString ToolButtonStyle = Public_Str::CreateTopButtonStyle(TopToolButtonStyle);
    const QString MessageBoxButtonStyle = Public_Str::CreateTopButtonStyle(TopMessageButtonStyle);
    const QString SkipButtonStyle = Public_Str::CreateTopButtonStyle(TopSkinButtonStyle);
    const QString SetupButtonStyle = Public_Str::CreateTopButtonStyle(TopSetUpButtonStyle);
    const QString PhoneButtonStyle = Public_Str::CreateTopButtonStyle(TopPhoneButtonStyle);
    const QString LeftButtonStyle = Public_Str::CreateTopButtonStyle(TppLeftHideButtonStyle);
    const QString MinButtonStyle = Public_Str::CreateTopButtonStyle(TopMinButtonStyle);
    const QString ExitButtonStyle = Public_Str::CreateTopButtonStyle(TopExitButtonStyle);
    const QString SearchEditStyle = Public_Str::Get_Sty(Style_Css{SearchLineEditStyle});

    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("TopWidget");
    mWidget->setStyleSheet("QWidget#TopWidget{background-color:rgb(0,170,255);}");
    mWidget->setFixedHeight(50);
    QHBoxLayout* mHLayout = Get_HLayout();
    //LOGO
    QLabel* lbl_Logo = Get_Label("MyMusic",100,0,Logo_Style);
    lbl_Logo->setText("MyMusic");

    //上一级
    QPushButton* btn_Pre = Get_Button("","","",25,30);
    btn_Pre->setStyleSheet(PreButtonStyle);

    //刷新
    QPushButton* btn_Refush = Get_Button("","","",25,30);
    btn_Refush->setStyleSheet(RefushButtonStyle);

    //搜索栏
    QLineEdit* Edit_Search = new QLineEdit();
    Edit_Search->setMinimumSize(260,25);
    Edit_Search->setStyleSheet(SearchEditStyle);

    //搜索按钮
    QPushButton* btn_Search = Get_Button();
    btn_Search->setStyleSheet(SearchButtonStyle);

    QWidgetAction* action = new QWidgetAction(Edit_Search);
    action->setDefaultWidget(btn_Search);
    Edit_Search->addAction(action, QLineEdit::TrailingPosition);

    //工具
    QPushButton* btn_Tool = Get_Button("","","",25,30);
    btn_Tool->setStyleSheet(ToolButtonStyle);

    //消息中心
    QPushButton* btn_info = Get_Button("","","",25,30);
    btn_info->setStyleSheet(MessageBoxButtonStyle);

    //换装
    QPushButton* btn_Skip = Get_Button("","","",25,30);
    btn_Skip->setStyleSheet(SkipButtonStyle);

    //设置
    QPushButton* btn_Set_UP = Get_Button("","","",25,30);
    btn_Set_UP->setStyleSheet(SetupButtonStyle);

    QWidget* WidgetLine = new QWidget();
    WidgetLine->setStyleSheet("border-Left:1px solid rgb(255,255,255,100);");
    WidgetLine->setFixedSize(1,15);

    //开启遥控器
    QPushButton* btn_Remote = Get_Button("","","",25,30);
    btn_Remote->setStyleSheet(PhoneButtonStyle);

    //隐藏音乐库
    QPushButton* btn_Hide = Get_Button("","","",25,30);
    btn_Hide->setStyleSheet(LeftButtonStyle);

    //最小化
    QPushButton* btn_Min = Get_Button("","","",25,30);
    btn_Min->setStyleSheet(MinButtonStyle);

    //关闭
    QPushButton* btn_Close = Get_Button("","","",25,30);
    btn_Close->setStyleSheet(ExitButtonStyle);


    mHLayout->addSpacing(5);
    mHLayout->addWidget(lbl_Logo);
    mHLayout->addSpacing(200);
    mHLayout->addWidget(btn_Pre);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Refush);
    mHLayout->addSpacing(14);
    mHLayout->addWidget(Edit_Search);
    mHLayout->addStretch();
    mHLayout->addWidget(btn_Tool);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_info);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Skip);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Set_UP);
    mHLayout->addSpacing(10);
    mHLayout->addWidget(WidgetLine);
    mHLayout->addSpacing(10);
    mHLayout->addWidget(btn_Remote);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Hide);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Min);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Close);
    mHLayout->addSpacing(5);

    mWidget->setLayout(mHLayout);


    this->connect(btn_Search,&QPushButton::clicked,this,[=](){
        emit SearchSignal(Edit_Search->text());
    });
    this->connect(Edit_Search,&QLineEdit::returnPressed,this,[=](){
        btn_Search->click();
    });


    return mWidget;
}

QWidget *KugouMusicMain::InitBottomWidget()
{
    const QString PreMusicStyle = Public_Str::CreateBottomButtonStyle(BottomPreButtonStyle);
    const QString StartMusicStyle = Public_Str::CreateBottomButtonStyle(BottomPlayButtonStyle);
    const QString StopMusicStyle = Public_Str::CreateBottomButtonStyle(BottomStopButtonStyle);
    const QString NextMusicStyle = Public_Str::CreateBottomButtonStyle(BottomNextButtonStyle);
    const QString LoveNStyle = Public_Str::CreateBottomButtonStyle(BottomLoveNButtonStyle);
    const QString LoveYStyle = Public_Str::CreateBottomButtonStyle(BottomLoveYButtonStyle);
    const QString DownNStyle = Public_Str::CreateBottomButtonStyle(BottomDownNButtonStyle);
    const QString DownYStyle = Public_Str::CreateBottomButtonStyle(BottomDownYButtonStyle);
    const QString MoreStyle = Public_Str::CreateBottomButtonStyle(BottomMoreButtonStyle);
    const QString PlayList1Style = Public_Str::CreateBottomButtonStyle(BottomPlayModel1ButtonStyle);
    const QString Voice1Style = Public_Str::CreateBottomButtonStyle(BottomVoiceButtonStyle);
    const QString Voice2Style = Public_Str::CreateBottomButtonStyle(BottomVoice1ButtonStyle);
    const QString Voice3Style = Public_Str::CreateBottomButtonStyle(BottomVoie2ButtonStyle);
    const QString LyicesStyle = Public_Str::CreateBottomButtonStyle(BottomLyricsButtonStyle);
    const QString PlayListStyle = Public_Str::CreateBottomButtonStyle(BottomPlayListButtonStyle);
    const QString PlayListNumStyle = Public_Str::Get_Sty(Style_Css{MusicPlayListNumButtonStyle,});


    QWidget* mWidget = new QWidget();
    mWidget->setObjectName("BottomWidget");
    mWidget->setStyleSheet("QWidget#BottomWidget{background-color:rgb(0,170,255);}");
    mWidget->setFixedHeight(65);

    QHBoxLayout* mHLayout = new QHBoxLayout();

    //上一首
    QPushButton* btn_PreMusic = Get_Button("","","",35,35);
    btn_PreMusic->setStyleSheet(PreMusicStyle);

    //暂停播放
    QPushButton* btn_Start_Stop = Get_Button("","","",45,45);
    btn_Start_Stop->setStyleSheet(StartMusicStyle);

    //下一首
    QPushButton* btn_NextMusic = Get_Button("","","",35,35);
    btn_NextMusic->setStyleSheet(NextMusicStyle);

    //进度条 歌名 歌时间
    QWidget* MusicSliderNameTimeWidget = InitBottomMusicSlider();

    //我喜欢
    QPushButton* btn_Love = Get_Button("","","",25,30);
    btn_Love->setStyleSheet(LoveNStyle);

    //下载
    QPushButton* btn_Down = Get_Button("","","",25,30);
    btn_Down->setStyleSheet(DownNStyle);

    //更多
    QPushButton* btn_More = Get_Button("","","",25,30);
    btn_More->setStyleSheet(MoreStyle);

    //播放顺序
    QPushButton* btn_PlayerModel = Get_Button("","","",25,30);
    btn_PlayerModel->setStyleSheet(PlayList1Style);

    //声音
    QPushButton* btn_Voice = Get_Button("","","",25,30);
    btn_Voice->setObjectName("btn_Voice");
    btn_Voice->setStyleSheet(Voice2Style);
    btn_Voice->installEventFilter(this);

    //词
    QPushButton* btn_Lyrics = Get_Button("","","",25,30);
    btn_Lyrics->setStyleSheet(LyicesStyle);

    //播放列表
    QHBoxLayout* mLayout = Get_HLayout();

    QPushButton* btn_PlayList = Get_Button("","","",25,30);
    btn_PlayList->setStyleSheet(PlayListStyle);
    QPushButton* btn_PlayListNum = Get_Button("0","","",25,30,0,0,PlayListNumStyle);
    mLayout->addWidget(btn_PlayList);
    mLayout->addWidget(btn_PlayListNum);

    mHLayout->addSpacing(7);
    mHLayout->addWidget(btn_PreMusic);
    mHLayout->addSpacing(12);
    mHLayout->addWidget(btn_Start_Stop);
    mHLayout->addSpacing(12);
    mHLayout->addWidget(btn_NextMusic);
    mHLayout->addSpacing(15);
    mHLayout->addWidget(MusicSliderNameTimeWidget);
    mHLayout->addSpacing(10);
    mHLayout->addWidget(btn_Love);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Down);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_More);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_PlayerModel);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Voice);
    mHLayout->addSpacing(3);
    mHLayout->addWidget(btn_Lyrics);
    mHLayout->addSpacing(3);
    mHLayout->addLayout(mLayout);
    mHLayout->addSpacing(3);

    mWidget->setLayout(mHLayout);

    this->connect(this,&KugouMusicMain::ClearBottomInfo,this,[=](){
            btn_Love->setStyleSheet(LoveNStyle);
    });
    this->connect(btn_Voice,&QPushButton::clicked,VoiceWidget,&KugouMusicVoicme::Set_Voieme);
    this->connect(VoiceWidget,&KugouMusicVoicme::VoiceIconChange,this,[=](int Voicme){
        if(Voicme == 0)
        {
            btn_Voice->setStyleSheet(Voice3Style);
        }
        else if(Voicme > 0 && Voicme < 31)
        {
            btn_Voice->setStyleSheet(Voice1Style);
        }
        else
        {
            btn_Voice->setStyleSheet(Voice2Style);
        }
    });
    this->connect(this,&KugouMusicMain::LoveStateSingal,this,[=](bool isLove){
        if(isLove)
            btn_Love->setStyleSheet(LoveYStyle);
        else
            btn_Love->setStyleSheet(LoveNStyle);
    });
    this->connect(btn_Down,&QPushButton::clicked,this,&KugouMusicMain::DownCliKcedSignal);
    this->connect(btn_PreMusic,&QPushButton::clicked,this,&KugouMusicMain::PreMusicSignal);
    this->connect(btn_NextMusic,&QPushButton::clicked,this,&KugouMusicMain::NextMusicSignal);
    this->connect(btn_PlayerModel,&QPushButton::clicked,this,&KugouMusicMain::MusicModelClicked);
    this->connect(btn_Love,&QPushButton::clicked,this,&KugouMusicMain::LoveClickeSignal);
    this->connect(this,&KugouMusicMain::ChangePlayModelIcon,this,[=](const QString Icon){
        btn_PlayerModel->setStyleSheet(Icon);
    });
    this->connect(this,&KugouMusicMain::StartMusic,this,[=](bool State){
        if(!State)
        {
            btn_Start_Stop->setStyleSheet(StopMusicStyle);
        }
        else
        {
            btn_Start_Stop->setStyleSheet(StartMusicStyle);
        }
    });
    this->connect(btn_Start_Stop,&QPushButton::clicked,this,[=](){
        emit PlayerChangeState();
    });

    return mWidget;
}

//进度条 歌名 歌时间
QWidget *KugouMusicMain::InitBottomMusicSlider()
{
    const QString SliderStyle = Public_Str::Get_Sty(Style_Css{PlayerSliderStyle,});
    const QString MusicNameStyle = Public_Str::Get_Sty(Style_Css{MusisNameLabelStyle,});
    const QString MusicTimeStyle = Public_Str::Get_Sty(Style_Css{MusicTimeLabelStyle,});
    QWidget* mWidget = new QWidget();

    QVBoxLayout* MusicSliderNameLayout = Get_VLayout();
    QHBoxLayout* MusicSliderTimeLayout = Get_HLayout();

    //歌名
    QLabel* MusicName = Get_Label("aaaa",0,0,"",Qt::AlignLeft | Qt::AlignVCenter);
    MusicName->setObjectName("MusicName");
    MusicName->setStyleSheet(MusicNameStyle);

    //进度条
    QSlider* mSlider = new QSlider(Qt::Horizontal);
    mSlider->installEventFilter(this);
    mSlider->setObjectName("PlayerSlider");
    mSlider->setStyleSheet(SliderStyle);

    this->connect(mSlider,&QSlider::sliderMoved,this,&KugouMusicMain::SeekPlay);

    //歌时间
    QLabel* Music_Time = Get_Label(StartTime + "/" + LastTime);
    Music_Time->setObjectName("Music_Time");
    Music_Time->setStyleSheet(MusicTimeStyle);

    MusicSliderTimeLayout->addWidget(mSlider);
    MusicSliderTimeLayout->addSpacing(10);
    MusicSliderTimeLayout->addWidget(Music_Time);

    MusicSliderNameLayout->addWidget(MusicName);
    MusicSliderNameLayout->addLayout(MusicSliderTimeLayout);

    mWidget->setLayout(MusicSliderNameLayout);

    this->connect(this,&KugouMusicMain::ClearBottomInfo,this,[=](){
        MusicName->setText("");
        mSlider->setValue(0);
        Music_Time->setText("00:00/00:00");
    });



    return mWidget;
}
