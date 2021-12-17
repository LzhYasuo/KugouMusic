#ifndef KUGOU_MUSIC_RADIO_H_
#define KUGOU_MUSIC_RADIO_H_

#include "QPushButton"

class KugouMusicRadio : public QPushButton
{
    Q_OBJECT
public:
    KugouMusicRadio(QString Paint,QString MusicName,QString Title,QWidget* parent = nullptr);
    ~KugouMusicRadio();

signals:
    void HoverEnterState();
    void HoverLeaveState();
    void ClickedState();

protected:
    bool eventFilter(QObject *o, QEvent *e);

private:
    void Init();
private:
    QString mPaint;
    QString mMusicName;
    QString mTitle;

};

#endif //KUGOU_MUSIC_RADIO_H_
