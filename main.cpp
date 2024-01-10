#include "Ludo.h"
#include <QtWidgets/QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ludo w;

    // find size of screen
    QRect screenDim = QApplication::primaryScreen()->geometry();
    int screenWidth = screenDim.width();
    int screenHeight = screenDim.height();

    int displayWidth = 

    w.show();
    
    return a.exec();
}
