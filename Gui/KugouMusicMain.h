#ifndef KUGOUMUSICMAIN_H
#define KUGOUMUSICMAIN_H

#include "KugouBaseControl.h"

class KugouMusicVoicme;
class KugouMusicMain : public KugouBaseControl
{
Q_OBJECT

public:
KugouMusicMain(QWidget *parent = 0);
~KugouMusicMain();

private:
    QWidget* InitTopWidget();
    QWidget* InitBottomWidget();
    QWidget* InitBottomMusicSlider();
    void Init();

protected:
    bool eventFilter(QObject* ,QEvent*);

signals:
    void SearchSignal(QString name);
    void SeekPlay(int value);
    void StartMusic(bool);
    void PlayerChangeState();
    void LoveStateSingal(bool);
    void ClearBottomInfo();

    void PreMusicSignal();
    void NextMusicSignal();
    void LoveClickeSignal();
    void MusicModelClicked();
    void MusicModelSignal();
    void DownCliKcedSignal();

    void ChangePlayModelIcon(const QString);
private:
    QString LastTime = "00:00";
    QString StartTime = "00:00";
    int mDruation = 0;
    KugouMusicVoicme* VoiceWidget;
};

#endif // KUGOUMUSICMAIN_H
