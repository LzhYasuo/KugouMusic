#include "Public_Str.h"
#include <QDebug>

#define GET_STR(x) #x


QString Public_Str::Get_Sty(Style_Css code)
{
    QString FirstPaint = ":/Top/Paint/TOP/";
    QString msg = "";
    switch(code.type)
    {
    case TopLogoLabelStyle:
    {
        msg = GET_STR
            (
                font: 75 15pt "Comic Sans MS";
            );
    }
    break;
    case TopButtonStyle:
    {

    }
    break;
    case BottomButtonStyle:
    {

    }
    break;
    case LeftButtonStyle:
    {

    }
    break;
    case PlayerSliderStyle:
    {
        msg  = GET_STR
            (
                QSlider::groove:horizontal
                {
                    border-radius:2px;height:3px;
                }

                QSlider::sub-page:horizontal
                {
                    background:rgb(255, 255, 160);
                }
                QSlider::add-page:horizontal
                {
                    background:rgb(200,200,209);
                }

                QSlider::handle:horizontal
                {
                    background:rgb(255, 255, 160);
                    width:8px;
                    border-radius:4px;
                    margin:-3px 0px -3px 0px
                }
            );
    }
    break;
    case SearchLineEditStyle:
    {
        msg = GET_STR
            (
                QLineEdit
                {
                    border-radius:12px;
                    background:rgb(255,255,255,180);
                }
            );
    }
    break;
    case MusisNameLabelStyle:
    {
        msg = GET_STR
            (
                font: 12pt "黑体" ;
                color:rgb(255,255,255);
            );
    }
    break;
    case MusicTimeLabelStyle:
    {
        msg = GET_STR
            (
                font: 10pt "黑体";
                color:rgb(255,255,255);
            );
    }
    break;
    case MusicPlayListNumButtonStyle:
    {
        msg = GET_STR
            (
                font: 11pt "黑体";
                color:rgb(255,255,255);
                border:none;
            );
    }
    break;
    case ScroallAreaStyle:
    {
        msg = GET_STR
            (
                QScrollBar{background:transparent; width:10px; padding-right: 2px;}
                QScrollBar::handle{background:rgb(180,180,180,150);border-radius:4px;}
                QScrollBar::handle:hover{background: rgb(150,150,150,150);}
                QScrollBar::add-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}
                QScrollBar::sub-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}
                QScrollBar::add-page:vertical{background:transparent;}
                QScrollBar::sub-page:vertical{background:transparent;}
            );
    }
    break;
    case NetWorkCollectButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton{font-size:16px;color:rgb(80,80,80);border: 1px solid rgb(229,229,229);background:rgb(240,240,240);}
                QPushButton:hover{color:rgb(30,30,30);border: 1px solid rgb(219,219,219);background:rgb(229,229,229);}
                QPushButton:pressed{color:rgb(80,80,80);border: 1px solid rgb(229,229,229);background:rgb(240,240,240);}
            );
    }
    break;
    case LeftPhoneMusicPageTopButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                font: 10pt;
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
                border-bottom:1px solid rgb(170,170,170);
                color:rgb(52,52,52);
            }
            QPushButton:checked
            {
                color:rgb(0,170,255);
            }
        );
    }
    break;
    case LeftPhoneMusicWireConnectButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton{border-image: url(:/Left/Paint/Left/wire_connect (1).png);}
               QPushButton:hover{border-image: url(:/Left/Paint/Left/wire_connect (2).png);}
               QPushButton:pressed{border-image: url(:/Left/Paint/Left/wire_connect (3).png);}
            );
    }
    break;
    case LeftPhoneMusicNetConnectButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton{border-image: url(:/Left/Paint/Left/net_connect (1).png);}
                QPushButton:hover{border-image: url(:/Left/Paint/Left/net_connect (2).png);}
                QPushButton:pressed{border-image: url(:/Left/Paint/Left/net_connect (3).png);}
            );
    }
    break;
    case RightTopButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton{border:none;color:rgb(52,52,52);font:13pt "黑体";}
                QPushButton:hover{color:rgb(0,170,255);}
                QPushButton:checked{border-bottom:2px solid rgb(0,170,255);color:rgb(0,170,255);}
            );
    }
    break;
    case RightSearchTopButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton{border:none;color:rgb(52,52,52);font:12pt "黑体";}
                QPushButton:hover{color:rgb(0,170,255);}
                QPushButton:checked{color:rgb(0,170,255);}
            );
    }
    break;
    case RightPlayAllButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton
                {
                background-color:rgb(0,170,255,80%);
                color:rgb(255,255,255);
                border:none;
                }
                QPushButton:hover
                {
                background-color:rgb(0,170,255,100%);
                }
            );
    }
    break;
    case ALLDownButtonStyle:
    {
        msg = GET_STR
            (
                QPushButton
                {
                border:1px solid rgb(100,100,100);
                color:rgb(60,60,60);
                font : 12px "黑体";
                }
                QPushButton:hover
                {
                border:1px solid rgb(0,170,255);
                color:rgb(0,170,255);
                }
            );
    }
    break;
    case VPlayerSliderStyle:
    {
        msg = GET_STR
            (

                QSlider::groove:vertical
                    {
                        border-radius:5px;
    width:3px;
                    }

                    QSlider::sub-page:vertical
                    {
                        background: #cbcbcb;
                    }
                    QSlider::add-page:vertical
                {
                    background:rgb(255, 255, 160);
                }

                QSlider::handle:vertical
                {
                    background:rgb(255, 255, 160);
                    height:8px;
                        border-radius:4px;
                    margin:0px -3px 0px -3px
                }
            );
    break;
    }
    case ViewSliderStyle:
    {
        msg = GET_STR
            (
                QTableView{ border:none;}
                QScrollBar{background:transparent; width:10px; padding-right: 2px;}
                QScrollBar::handle{background:rgb(180,180,180,150);border-radius:4px;}
                QScrollBar::handle:hover{background: rgb(150,150,150,150);}
                QScrollBar::add-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}
                QScrollBar::sub-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}
                QScrollBar::add-page:vertical{background:transparent;}
                QScrollBar::sub-page:vertical{background:transparent;}
            );
    }
    }

    return msg;
}

QString Public_Str::Get_Left_Sty(Style_Css code)
{
    QString msg = "";
    QVariantList var = code.value;
    if(var.size() < 3)
        return "";
    QString FirstValue = var.at(0).toString();
    QString SecondValue = var.at(1).toString();
    QString ThirdValue = var.at(2).toString();

    if(code.type == LeftButtonStyle)
    {
        msg = QString(GET_STR
                      (
                        QPushButton
                        {
                        background-image: url(%1);
                        background-repeat:no-repeat;
                        background-position:center center;
                        border:none;
                        }

                        QPushButton:hover
                        {
                        background-image: url(%2);
                        }
                        QPushButton:checked
                        {
                        background-image: url(%3);
                        }
                        )).arg(FirstValue).arg(SecondValue).arg(ThirdValue);
    }

    return msg;

}


QString Public_Str::CreateLeftButtonStyle(LeftButtonCss inedx)
{
    QString msg = "";
    Style_Css css;
    css.type = LeftButtonStyle;
    switch(inedx)
    {
    case localListButtonStyle:
    {
        css.value = Get_LeftVarValue("1");
    }
    break;
    case NetWorkButtonStyle:
    {
        css.value = Get_LeftVarValue("2");
    }
    break;
    case MusicRadioButtonStyle:
    {
        css.value = Get_LeftVarValue("3");
    }
    break;
    case PhoneButtonStyle:
    {
        css.value = Get_LeftVarValue("4");
    }
    break;
    case LocalMusicButtonStyle:
    {
        css.value = Get_LeftVarValue("5");
    }
    break;
    case ListUpdateButtonStyle:
    {
        css.value = Get_LeftVarValue("btn_grade");
    }
    break;
    case ListShareButtonStyle:
    {
        css.value = Get_LeftVarValue("btn_share");
    }
    break;
    case ListMenuButtonStyle:
    {
        css.value = Get_LeftVarValue("btn_menu");
    }
    break;
    }
    msg = Get_Left_Sty(css);

    return msg;
}

QString Public_Str::CreateBottomButtonStyle(BottomButtonCss index)
{
    QString msg = "";
    Style_Css css;
    css.type = BottomButtonStyle;
    switch(index)
    {
    case BottomPreButtonStyle:
    {
        css.value = Get_BottomVarValue("1");
    }
    break;
    case BottomPlayButtonStyle:
    {
        css.value = Get_BottomVarValue("2");
    }
    break;
    case BottomStopButtonStyle:
    {
        css.value = Get_BottomVarValue("3");
    }
    break;
    case BottomNextButtonStyle:
    {
        css.value = Get_BottomVarValue("4");
    }
    break;
    case BottomLoveNButtonStyle:
    {
        css.value = Get_BottomVarValue("5");
    }
    break;
    case BottomLoveYButtonStyle:
    {
        css.value = Get_BottomVarValue("6");
    }
    break;
    case BottomDownNButtonStyle:
    {
        css.value = Get_BottomVarValue("7");
    }
    break;
    case BottomDownYButtonStyle:
    {
        css.value = Get_BottomVarValue("8");
    }
    break;
    case BottomPlayModel1ButtonStyle:
    {
        css.value = Get_BottomVarValue("9");
    }
    break;
    case BottomPlayModel2ButtonStyle:
    {
        css.value = Get_BottomVarValue("10");
    }
    break;
    case BottomPlayModel3ButtonStyle:
    {
        css.value = Get_BottomVarValue("11");
    }
    break;
    case BottomPlayModel4ButtonStyle:
    {
        css.value = Get_BottomVarValue("12");
    }
    break;
    case BottomPlayModel5ButtonStyle:
    {
        css.value = Get_BottomVarValue("13");
    }
    break;
    case BottomMoreButtonStyle:
    {
        css.value = Get_BottomVarValue("14");
    }
    break;
    case BottomVoiceButtonStyle:
    {
        css.value = Get_BottomVarValue("15");
    }
    break;
    case BottomVoice1ButtonStyle:
    {
        css.value = Get_BottomVarValue("16");
    }
    break;
    case BottomVoie2ButtonStyle:
    {
        css.value = Get_BottomVarValue("17");
    }
    break;
    case BottomLyricsButtonStyle:
    {
        css.value = Get_BottomVarValue("18");
    }
    break;
    case BottomPlayListButtonStyle:
    {
        css.value = Get_BottomVarValue("19");
    }
    break;
    }
    msg = Get_Paint_Sty(BottomButtonStyle,css);
    return msg;
}

QString Public_Str::CreateTopButtonStyle(TopButtonCss type)
{
    QString msg = "";
    Style_Css css;
    css.type = TopButtonStyle;
    switch(type)
    {
    case TopReturnButtonStyle:
    {
        css.value = Get_TopVarValue("1");
    }
    break;
    case TopRefreshButtonStyle:
    {
        css.value = Get_TopVarValue("2");
    }
    break;
    case TopSearchButtonStyle:
    {
        css.value = Get_TopVarValue("3");
    }
    break;
    case TopToolButtonStyle:
    {
        css.value = Get_TopVarValue("4");
    }
    break;
    case TopMessageButtonStyle:
    {
        css.value = Get_TopVarValue("5");
    }
    break;
    case TopSkinButtonStyle:
    {
        css.value = Get_TopVarValue("6");
    }
    break;
    case TopSetUpButtonStyle:
    {
        css.value = Get_TopVarValue("7");
    }
    break;
    case TopPhoneButtonStyle:
    {
        css.value = Get_TopVarValue("8");
    }
    break;
    case TppLeftHideButtonStyle:
    {
        css.value = Get_TopVarValue("9");
    }
    break;
    case TopMinButtonStyle:
    {
        css.value = Get_TopVarValue("10");
    }
    break;
    case TopExitButtonStyle:
    {
        css.value = Get_TopVarValue("11");
    }
    break;
    }

    msg = Get_Paint_Sty(TopButtonStyle,css);
    return msg;
}

QString Public_Str::CreateMVPageStyle(MVPageCss index)
{
    QString msg = "";
    Style_Css css;
    css.type = MVPageStyle;
    switch(index)
    {
    case MVExitButtonStyle:
        css.value = Get_MVVarValue("btn_MVExit");
        break;
    case MVPreButtonStyle:
        css.value = Get_MVVarValue("btn_MVPre");
        break;
    case MVNextButtonStyle:
        css.value = Get_MVVarValue("btn_MVNext");
        break;
    case MVStartButtonStyle:
        css.value = Get_MVVarValue("btn_Start");
        break;
    case MVStopButtonStyle:
        css.value = Get_MVVarValue("btn_MVStop");
        break;
    }

    msg = Get_MVSty(css);
    return msg;
}

QString Public_Str::Get_MVSty(Style_Css code)
{
    QString msg = "";
    QVariantList var = code.value;
    if(var.size() < 2)
        return "";
    QString FirstValue = var.at(0).toString();
    QString SecondValue = var.at(1).toString();

    if(code.type == MVPageStyle)
    {
        msg = QString(GET_STR
                      (
                          QPushButton
                          {
                              background-image: url(%1);
                              background-repeat:no-repeat;
                              background-position:center center;
                              border:none;
                          }

                          QPushButton:hover
                          {
                              background-image: url(%2);
                          }
                            )).arg(FirstValue).arg(SecondValue);
    }

    return msg;
}

QString Public_Str::Get_Paint_Sty(Style_Type type,Style_Css code)
{
    QString msg = "";
    QVariantList var = code.value;
    if(var.size() < 3)
        return "";
    QString FirstValue = var.at(0).toString();
    QString SecondValue = var.at(1).toString();
    QString ThirdValue = var.at(2).toString();

    if(code.type == type)
    {
        msg = QString(GET_STR
            (
                QPushButton
                {
                    background-image: url(%1);
                    background-repeat:no-repeat;
                    background-position:center center;
                    border:none;
                }

                QPushButton:hover
                {
                    background-image: url(%2);
                }
                QPushButton:pressed
                {
                    background-image: url(%3);
                }
            )).arg(FirstValue).arg(SecondValue).arg(ThirdValue);
    }

    return msg;
}

QVariantList Public_Str::Get_TopVarValue(QString index)
{
    QVariantList var;
    var.push_back(QString(":/Top/Paint/TOP/%1.png").arg(index));
    var.push_back(QString(":/Top/Paint/TOP/%1_hover.png").arg(index));
    var.push_back(QString(":/Top/Paint/TOP/%1_press.png").arg(index));

    return var;
}


QVariantList Public_Str::Get_BottomVarValue(QString index)
{
    QVariantList var;
    var.push_back(QString(":/Bottom/Paint/Bottom/%1.png").arg(index));
    var.push_back(QString(":/Bottom/Paint/Bottom/%1_hover.png").arg(index));
    var.push_back(QString(":/Bottom/Paint/Bottom/%1_press.png").arg(index));

    return var;
}

QVariantList Public_Str::Get_LeftVarValue(QString index)
{
    QVariantList var;
    var.push_back(QString(":/Left/Paint/Left/%1.png").arg(index));
    var.push_back(QString(":/Left/Paint/Left/%1_hover.png").arg(index));
    var.push_back(QString(":/Left/Paint/Left/%1_press.png").arg(index));

    return var;
}

QVariantList Public_Str::Get_MVVarValue(QString index)
{
    QVariantList var;
    var.push_back(QString(":/MVPaint/Paint/MVPaint/%1.png").arg(index));
    var.push_back(QString(":/MVPaint/Paint/MVPaint/%1_hover.png").arg(index));

    return var;
}
