#include "KugouAVPlayer.h"
#include <QHBoxLayout>
#include <QMessageBox>

using namespace QtAV;

KugouAVPlayer::KugouAVPlayer(QWidget* parent)
    :QOpenGLWidget (parent)
{
    AVInit();
    this->Init();
}

KugouAVPlayer::~KugouAVPlayer()
{

}

void KugouAVPlayer::Play(QString url)
{
    mUrl = url;
    if(m_Player != nullptr)
    {
        m_Player->play(mUrl);
    }
}

int KugouAVPlayer::Get_Duration()
{
    return mDuration;
}

void KugouAVPlayer::Seek(qint64 value)
{
    m_Player->seek(value);
}

void KugouAVPlayer::SetPause()
{
    PlayerState = !PlayerState;
    m_Player->pause(PlayerState);

    emit Get_PlayerState(PlayerState);
}

void KugouAVPlayer::SetVoiume(double value)
{
    value /= 100.0;
    m_Audio->setVolume(value);
}

//int KugouAVPlayer::Get_PlayerState()
//{
//    return PlayerState;
//}

void KugouAVPlayer::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    mLayout->addWidget(m_IO->widget());

    this->setLayout(mLayout);
}

void KugouAVPlayer::SetDoubleClickedfasle()
{
    DoubleClicked--;
}

void KugouAVPlayer::SetDoubleClicked()
{
    DoubleClicked++;
}

void KugouAVPlayer::AVInit()
{
    qDebug() << "AVInit";
    Widgets::registerRenderers();

    m_Player = new QtAV::AVPlayer(this);
    m_IO = new VideoOutput(this);

    //设置间隔时间(ms单位)
    m_Player->setNotifyInterval(100);
    //设置视频在最后一帧停止
    m_Player->setMediaEndAction(MediaEndAction_Default);
    //设置跳转帧类型
    m_Player->setSeekType(AccurateSeek);
    //得到音频输出接口
    m_Audio = m_Player->audio();

    m_Player->setRenderer(m_IO);

    m_Audio->setVolume(0.5);

    this->connect(m_Player,&AVPlayer::positionChanged,this,[=](qint64 value){
        emit UpdateSliderPos(value);
    });
    this->connect(m_Player,&AVPlayer::started,this,[=](){
        mDuration = m_Player->duration();
        emit StartPlayer(mDuration);
    });
    this->connect(m_Player,&AVPlayer::stopped,this,[=](){
        qDebug() << DoubleClicked;
        DoubleClicked -= 1;
        if(DoubleClicked == 0)
        {
            emit PlayEndof(mUrl);
//            isDoubleClicked = true;
        }
//        else
//        {
//            DoubleClicked--;
//        }

        PlayerState = true;
        m_Player->pause(PlayerState);
        Get_PlayerState(PlayerState);
    });
    this->connect(m_Player,&AVPlayer::stateChanged,this,[=](QtAV::AVPlayer::State state){
        if(state == 1)
        {
            PlayerState = false;
            DoubleClicked = 1;
        }
        else if(state == 2)
        {
            PlayerState = true;
        }
        emit Get_PlayerState(PlayerState);
    });
    this->connect(m_Player,&AVPlayer::error,this,[=](const QtAV::AVError& e){
        QMessageBox::warning(nullptr,"",e.ffmpegErrorString());
    });
//    this->connect()

//    m_Player->setVideoDecoderPriority(QStringList() << "FFmpeg");
//    connect(ObjImg,&VideoImg::SendOneFrameImg,this,&QtavPlayer::GetOneFrameImg);
}
