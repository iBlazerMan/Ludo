#include "Ludo.h"

Ludo::Ludo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LudoClass())
{
    ui->setupUi(this);
    

    
}

Ludo::~Ludo()
{
    delete ui;
}
