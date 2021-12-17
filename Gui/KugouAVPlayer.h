#ifndef KUGOU_AV_PLAYER
#define KUGOU_AV_PLAYER

#include <QtAV>
#include <QtAVWidgets>
#include <QOpenGLWidget>

class KugouAVPlayer : public QOpenGLWidget
{
    Q_OBJECT

signals:
    void StartPlayer(int);
    void UpdateSliderPos(qint64);
    void Get_PlayerState(bool);
    void PlayEndof(QString);
public:
    KugouAVPlayer(QWidget* parent = nullptr);
    ~KugouAVPlayer();

    void Play(QString url);
    int Get_Duration();
    void Seek(qint64);
    void SetPause();
    void SetVoiume(double value);
    void SetDoubleClicked();
    void SetDoubleClickedfasle();

//    int Get_PlayerState();

    void AddMusic();
    void SubMusic();

private:
    void Init();
    void AVInit();
    QtAV::VideoOutput* m_IO;
    QtAV::AVPlayer* m_Player;
    QtAV::AudioOutput* m_Audio;
    int mDuration;
    bool PlayerState = true;

    QString mUrl = "";

    int DoubleClicked = 0;
    QList<QStringList> PlayerList;
};



#endif //KUGOU_AV_PLAYER
