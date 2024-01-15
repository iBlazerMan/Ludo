#include "Ludo.h"
#include <QtWidgets/QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ludo w;

    // set window fixed size
    w.setFixedSize(720, 600);

    // disable maximize button
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);

    w.show();
    
    return a.exec();
}
