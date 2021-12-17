#ifndef _PUBLIC_STR_H_
#define _PUBLIC_STR_H_
#include <QVariant>
#include <QList>

enum Style_Type
{
    TopLogoLabelStyle,
    TopButtonStyle,
    BottomButtonStyle,
    LeftButtonStyle,
    PlayerSliderStyle,
    SearchLineEditStyle,
    MusisNameLabelStyle,
    MusicTimeLabelStyle,
    MusicPlayListNumButtonStyle,
    ScroallAreaStyle,
    NetWorkCollectButtonStyle,
    LeftPhoneMusicPageTopButtonStyle,
    LeftPhoneMusicWireConnectButtonStyle,
    LeftPhoneMusicNetConnectButtonStyle,
    RightTopButtonStyle,
    RightSearchTopButtonStyle,
    RightPlayAllButtonStyle,
    ALLDownButtonStyle,
    MVPageStyle,
    VPlayerSliderStyle,
    ViewSliderStyle,

};

enum TopButtonCss
{
    TopReturnButtonStyle,
    TopRefreshButtonStyle,
    TopSearchButtonStyle,
    TopToolButtonStyle,
    TopMessageButtonStyle,
    TopSkinButtonStyle,
    TopSetUpButtonStyle,
    TopPhoneButtonStyle,
    TppLeftHideButtonStyle,
    TopMinButtonStyle,
    TopExitButtonStyle,
};

enum BottomButtonCss
{
    BottomPreButtonStyle,
    BottomPlayButtonStyle,
    BottomStopButtonStyle,
    BottomNextButtonStyle,
    BottomLoveNButtonStyle,
    BottomLoveYButtonStyle,
    BottomDownNButtonStyle,
    BottomDownYButtonStyle,
    BottomPlayModel1ButtonStyle,
    BottomPlayModel2ButtonStyle,
    BottomPlayModel3ButtonStyle,
    BottomPlayModel4ButtonStyle,
    BottomPlayModel5ButtonStyle,
    BottomMoreButtonStyle,
    BottomVoiceButtonStyle,
    BottomVoice1ButtonStyle,
    BottomVoie2ButtonStyle,
    BottomLyricsButtonStyle,
    BottomPlayListButtonStyle,
};

enum LeftButtonCss
{
    localListButtonStyle,
    NetWorkButtonStyle,
    MusicRadioButtonStyle,
    PhoneButtonStyle,
    LocalMusicButtonStyle,
    ListUpdateButtonStyle,
    ListShareButtonStyle,
    ListMenuButtonStyle,

};

enum MVPageCss
{
    MVExitButtonStyle,
    MVPreButtonStyle,
    MVNextButtonStyle,
    MVStartButtonStyle,
    MVStopButtonStyle,
};

struct Style_Css
{
    Style_Type type;
    QList<QVariant> value;
};

class QString;
class Public_Str
{
public:
    static QString CreateLeftButtonStyle(LeftButtonCss);
    static QString CreateBottomButtonStyle(BottomButtonCss);
    static QString CreateTopButtonStyle(TopButtonCss);
    static QString CreateMVPageStyle(MVPageCss);
    static QString Get_MVSty(Style_Css);
    static QString Get_Sty(Style_Css);
    static QString Get_Left_Sty(Style_Css);
    static QString Get_Paint_Sty(Style_Type,Style_Css);
private:
    Public_Str();
    ~Public_Str();

    static QVariantList Get_TopVarValue(QString index);
    static QVariantList Get_BottomVarValue(QString index);
    static QVariantList Get_LeftVarValue(QString index);
    static QVariantList Get_MVVarValue(QString index);
};


#endif //_PUBLIC_STR_H_
