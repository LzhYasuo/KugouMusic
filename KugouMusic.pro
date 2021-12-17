#-------------------------------------------------
#
# Project created by QtCreator 2021-05-07T14:43:49
#
#-------------------------------------------------

QT       += core gui sql network avwidgets opengl concurrent

Release:LIBS += -L$$quote(C:\Qt\5.9.8\mingw53_32\lib) -L$$quote(C:\Users\Administrator\Desktop\QtAV-depends-windows-x86+x64\lib)  -lQt5AV  -lQt5AVWidgets
Debug:LIBS +=-L$$quote(C:\Qt\5.9.8\mingw53_32\lib) -L$$quote(C:\Users\Administrator\Desktop\QtAV-depends-windows-x86+x64\lib) -lQt5AVd  -lQt5AVWidgetsd

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KugouMusic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        Gui/KugouMusicMain.cpp \
    Model/SearchListView.cpp \
    Model/SearchModelDelegate.cpp \
    Gui/KugouBaseControl.cpp \
    Gui/KugouMusicBody.cpp \
    Data/PlayListData.cpp \
    Data/PlayListDB.cpp \
    Public/Public_Str.cpp \
    Gui/KugouMusicBodyLeftButton.cpp \
    Gui/KugouMusicRadio.cpp \
    NetWork/NetWorkHttp.cpp \
    Model/SearchHeadDelegate.cpp \
    Model/SearchHeaderView.cpp \
    Gui/KugouAVPlayer.cpp \
    Model/PlayListModelDelegate.cpp \
    Model/PlayListView.cpp \
    Gui/KugouMusicVoicme.cpp \
    Model/MusicDownModelDelegate.cpp \
    Model/MusicDownView.cpp \
    Model/MusicDownEndListView.cpp \
    Model/MusicDownEndModelDelegate.cpp \
    Gui/KugouMusicDown.cpp \
    Gui/KugouMusicLyrics.cpp \
    Gui/kugouMusicLyricsLabel.cpp

HEADERS += \
        Gui/KugouMusicMain.h \
    Model/SearchListView.h \
    Model/SearchModelDelegate.h \
    Gui/KugouBaseControl.h \
    Gui/KugouMusicBody.h \
    Data/PlayListData.h \
    Data/PlayListDB.h \
    Public/Public_Str.h \
    Gui/KugouMusicBodyLeftButton.h \
    Gui/KugouMusicRadio.h \
    NetWork/NetWorkHttp.h \
    Model/SearchHeadDelegate.h \
    Model/SearchHeaderView.h \
    Gui/KugouAVPlayer.h \
    Model/PlayListModelDelegate.h \
    Model/PlayListView.h \
    Gui/KugouMusicVoicme.h \
    Model/MusicDownModelDelegate.h \
    Model/MusicDownView.h \
    Model/MusicDownEndListView.h \
    Model/MusicDownEndModelDelegate.h \
    Gui/KugouMusicDown.h \
    Gui/KugouMusicLyrics.h \
    Gui/kugouMusicLyricsLabel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    paint.qrc
