#include "KugouMusicVoicme.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QMouseEvent>
#include <qDebug>
#include <Public/Public_Str.h>

KugouMusicVoicme::KugouMusicVoicme(QWidget *parent)
    :KugouBaseControl (parent)
{
    this->setWindowFlags(this->windowFlags() |Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->Init();
    this->setFixedSize(30,110);
    this->setObjectName("KugouVoicme");
    this->setStyleSheet("#KugouVoicme{background-color:rgb(52,52,52);}");
}

KugouMusicVoicme::~KugouMusicVoicme()
{

}

void KugouMusicVoicme::Set_Voieme()
{
    QSlider* mSlider = this->findChild<QSlider*>("mSlider");
    if(mSlider->value() > 0)
    {
        mValue = mSlider->value();
        mSlider->setValue(0.0);
    }
    else
    {
        mSlider->setValue(mValue);
    }
    emit ChangeVolume(mSlider->value());
    emit VoiceIconChange(mSlider->value());
}

void KugouMusicVoicme::Init()
{
    const QString SliderStyle = Public_Str::Get_Sty(Style_Css{VPlayerSliderStyle,});
    QVBoxLayout* mLayout = Get_VLayout();
    QSlider* mSlider = new QSlider();
    mSlider->setFixedSize(30,110);
    mSlider->setRange(0,100);
    mSlider->setValue(50);
    mSlider->setStyleSheet(SliderStyle);
    mSlider->setObjectName("mSlider");
    mSlider->installEventFilter(this);
    mLayout->addWidget(mSlider);

    this->connect(mSlider,&QSlider::sliderMoved,this,[=](int value){
        qDebug() << value;
        mValue = value;
        emit VoiceIconChange(value);
        emit ChangeVolume(value);
    });
    this->setLayout(mLayout);
}

bool KugouMusicVoicme::eventFilter(QObject *watched, QEvent *event)
{
    QSlider* mSlider = this->findChild<QSlider*>("mSlider");
    if(watched == mSlider)
    {
        QMouseEvent* Mouse_event = static_cast<QMouseEvent*>(event);
        if(event->type() == QEvent::MouseButtonPress)
        {
            int dur = mSlider->maximum() - mSlider->minimum();
            double pos = mSlider->minimum() + dur * ((double)Mouse_event->y() / (double)mSlider->height());
            double Value = mSlider->maximum() - pos;
            if(Value != mSlider->sliderPosition())
            {
                mValue = Value;
                mSlider->setValue(Value);
                emit ChangeVolume(Value);
                emit VoiceIconChange(Value);
            }
        }
    }
    return KugouBaseControl::eventFilter(watched,event);
}
