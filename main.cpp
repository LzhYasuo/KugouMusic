#include "Gui/KugouMusicMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KugouMusicMain w;
    w.show();

    return a.exec();
}
