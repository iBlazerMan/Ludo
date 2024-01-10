#include "Ludo.h"
#include <QtWidgets/QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ludo w;


    w.show();
    
    return a.exec();
}
