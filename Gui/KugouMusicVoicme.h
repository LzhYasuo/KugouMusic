#ifndef _KUGOU_MUSIC_VOICME_H_
#define _KUGOU_MUSIC_VOICME_H_

#include "KugouBaseControl.h"

class KugouMusicVoicme : public KugouBaseControl
{
    Q_OBJECT
public:
    KugouMusicVoicme(QWidget* parent = nullptr);
    ~KugouMusicVoicme();

public slots:
    void Set_Voieme();

signals:
    void ChangeVolume(double value);
    void VoiceIconChange(int);
private:
    void Init();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    int mValue;
};


#endif //_KUGOU_MUSIC_VOICME_H_
