#include "kugouMusicLyricsLabel.h"

void KugouMusicLyricsLabel::SetLabelInfo(KugouMusicLyricsLabel * info)
{
   mText = info->Get_Text();
   mTime = info->Get_Time();
    this->setText(mText);
}

KugouMusicLyricsLabel::KugouMusicLyricsLabel(QWidget *parent)
    :QLabel (parent)
{

}

KugouMusicLyricsLabel::~KugouMusicLyricsLabel()
{

}

void KugouMusicLyricsLabel::Clear()
{
    mText = "";
    mTime = "";
    this->setText(mText);
}

void KugouMusicLyricsLabel::SetNullLabelInfo(QString Text, QString Time)
{
    mText = Text;
    mTime = Time;
    this->setText(mText);
}
