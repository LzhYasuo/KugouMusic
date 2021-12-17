#ifndef _KugouMusicLyricsLabel_H_
#define _KugouMusicLyricsLabel_H_

#include <QLabel>

class KugouMusicLyricsLabel : public QLabel
{
    Q_OBJECT
public:
    KugouMusicLyricsLabel(QWidget* parent = nullptr);
    ~KugouMusicLyricsLabel();

    void Clear();
    QString Get_Text() const {return mText;}
    QString Get_Time() const {return mTime;}
    void SetNullLabelInfo(QString,QString);
    void SetLabelInfo(KugouMusicLyricsLabel*);

private:
    QString mText;
    QString mTime;
};

#endif //_KugouMusicLyricsLabel_H_
