#include "KugouMusicDown.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

KugouMusicDown::KugouMusicDown(QString NameSinger,QString MusicUrl,QString MVUrl,QString Time,QWidget *parent)
    :QDialog (parent),
      mNameSinger(NameSinger),
      mMusicUrl(MusicUrl),
      mMVUrl(MVUrl),
      mTime(Time)
{
    this->Init();
}

KugouMusicDown::~KugouMusicDown()
{

}

void KugouMusicDown::Init()
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* TopWidget = new QWidget();
    TopWidget->setObjectName("TopWidget");
    TopWidget->setStyleSheet("#TopWidget{background-color:rgb(0,170,255);}");
    TopWidget->setFixedSize(595,35);
    QHBoxLayout* TopLayout = new QHBoxLayout();
    TopLayout->setSpacing(0);
    TopLayout->setContentsMargins(5,0,5,0);

    QLabel* lbl_Down = new QLabel();
    lbl_Down->setStyleSheet("color:rgb(220,220,220);font:10pt;");
    lbl_Down->setText("下载窗口");
    QPushButton* btn_Exit = new QPushButton();
    btn_Exit->setFixedSize(35,35);
    btn_Exit->setStyleSheet("border:none;font: 12pt ""Microsoft YaHei UI"";color:rgb(255,255,255);");;
    btn_Exit->setText("X");
    TopLayout->addWidget(lbl_Down);
    TopLayout->addStretch();
    TopLayout->addWidget(btn_Exit);
    TopWidget->setLayout(TopLayout);

    QWidget* BottomWidget = new QWidget();
    BottomWidget->setObjectName("BottomWidget");
    BottomWidget->setStyleSheet("#BottomWidget{background-color:rgb(255,255,255);}");
    BottomWidget->setFixedSize(595,255);
    QVBoxLayout* BottomLayout = new QVBoxLayout();
    BottomLayout->setSpacing(0);
    BottomLayout->setContentsMargins(20,0,0,0);

    QLabel* lbl_MusicNameSinger = new QLabel();
    lbl_MusicNameSinger->setStyleSheet("font:15pt ""黑体"";color:rgb(52,52,52);");
    lbl_MusicNameSinger->setText(mNameSinger);

    QWidget* BMidWidget = new QWidget();
    QHBoxLayout* BMidLayout = new QHBoxLayout();
    BMidLayout->setSpacing(0);
    BMidLayout->setContentsMargins(0,0,0,0);
    QLabel* lbl_ChooseMusic = new QLabel();
    lbl_ChooseMusic->setText("选择下载:");
    lbl_ChooseMusic->setFixedWidth(60);
    lbl_ChooseMusic->setStyleSheet("color:rgb(170,170,170);font:9pt;");
    QRadioButton* btn_ChooseMusic = new QRadioButton();
    btn_ChooseMusic->setStyleSheet("color:rgb(170,170,170);font:9pt;");
    btn_ChooseMusic->setText("下载音乐");
    btn_ChooseMusic->click();
    QRadioButton* btn_ChooseMV = new QRadioButton();
    btn_ChooseMV->setStyleSheet("color:rgb(170,170,170);font:9pt;");
    btn_ChooseMV->setText("下载MV");
    BMidLayout->addWidget(lbl_ChooseMusic);
    BMidLayout->addSpacing(30);
    BMidLayout->addWidget(btn_ChooseMusic);
    BMidLayout->addSpacing(30);
    BMidLayout->addWidget(btn_ChooseMV);
    BMidLayout->addStretch();
    BMidWidget->setLayout(BMidLayout);

    QWidget* BBottomWidget = new QWidget();
    QHBoxLayout* BBottomLayout = new QHBoxLayout();
    BBottomLayout->setSpacing(0);
    BBottomLayout->setContentsMargins(0,0,0,0);
    QLabel* DownAddr = new QLabel();
    DownAddr->setFixedWidth(60);
    DownAddr->setText("下载地址: ");
    DownAddr->setStyleSheet("color:rgb(170,170,170);font:9pt;");
    QLineEdit* AddrEdit = new QLineEdit();
    AddrEdit->setFixedSize(275,25);
    AddrEdit->setStyleSheet("color:rgb(52,52,52);border:1px solid rgb(170,170,170);font:9pt;");
    AddrEdit->setEnabled(false);
    QPushButton* btn_Addr = new QPushButton();
    btn_Addr->setFixedSize(60,25);
    btn_Addr->setText("更改地址");
    btn_Addr->setStyleSheet("QPushButton{border:1px solid rgb(170,170,170,100);}"
                            "QPushButton:hover{border:1px solid rgb(0,170,255,100);}");
    BBottomLayout->addWidget(DownAddr);
    BBottomLayout->addSpacing(30);
    BBottomLayout->addWidget(AddrEdit);
    BBottomLayout->addSpacing(30);
    BBottomLayout->addWidget(btn_Addr);
    BBottomLayout->addStretch();
    BBottomWidget->setLayout(BBottomLayout);

    QPushButton* btn_Down = new QPushButton();
    btn_Down->setStyleSheet("QPushButton{color:rgb(240,240,240);background-color:rgb(0,200,255,200);}"
                            "QPushButton:hover{background-color:rgb(0,200,255,220)}");
    btn_Down->setFixedSize(165,35);
    btn_Down->setText("立即下载");

//    BottomLayout->addStretch();
    BottomLayout->addSpacing(20);
    BottomLayout->addWidget(lbl_MusicNameSinger);
    BottomLayout->addSpacing(25);
    BottomLayout->addWidget(BMidWidget);
    BottomLayout->addSpacing(50);
    BottomLayout->addWidget(BBottomWidget);
    BottomLayout->addSpacing(35);
    BottomLayout->addWidget(btn_Down,0,Qt::AlignCenter);
    BottomLayout->addStretch();
    BottomWidget->setLayout(BottomLayout);

    mLayout->addWidget(TopWidget);
    mLayout->addWidget(BottomWidget);

    this->connect(btn_Addr,&QPushButton::clicked,this,[=](){
        QString msg = QFileDialog::getExistingDirectory(this,"选择下载路径",QDir::currentPath());
        if(!msg.isEmpty())
        {
            AddrEdit->setText(msg);
        }

    });
    this->connect(btn_Down,&QPushButton::clicked,this,[=](){
        if(AddrEdit->text().isEmpty())
        {
            QMessageBox::information(this,"错误","没有选择下载路径");
        }
        if(btn_ChooseMusic->isChecked())
        {
            QString FileName = "/" + mNameSinger + ".mp3";
            emit MusicDown(AddrEdit->text() + FileName,mMusicUrl,mTime);
        }
        else if(btn_ChooseMV->isChecked())
        {
            QString FileName = "/" + mNameSinger + ".mkv";
            qDebug() << FileName;
            emit MVDown(AddrEdit->text() + FileName,mMVUrl,mTime);
        }
        accept();
    });
    this->connect(btn_Exit,&QPushButton::clicked,this,[=](){
            this->close();
    });


    this->setLayout(mLayout);
}
