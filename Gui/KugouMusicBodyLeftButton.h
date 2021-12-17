#ifndef _KUGOUMUSIC_BODY_LEFT_BUTTON_H_
#define _KUGOUMUSIC_BODY_LEFT_BUTTON_H_

#include "QPushButton"
#include "KugouBaseControl.h"

class KugouMusicBodyLeftButton : public QPushButton
{
    Q_OBJECT
public:
    KugouMusicBodyLeftButton(QString MusicName,QWidget* parent = nullptr);
    ~KugouMusicBodyLeftButton();

    void DeleteMusicNum();
    void AddMusicNum();

signals:
    void ShowButton();
    void HideButton();
    void ChangeName(QString);

protected:
    virtual bool eventFilter(QObject* obj,QEvent* event);

private:
    void InitWidget();

private:
    QString Name;
    int MusicNum;
};


#endif //_KUGOUMUSIC_BODY_LEFT_BUTTON_H_
