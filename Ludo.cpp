#include "Ludo.h"

Ludo::Ludo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LudoClass())
{
    ui->setupUi(this);

    // initialize a graphics scene to display the board and pieces
    QGraphicsScene* graphicsSceneBoard = new QGraphicsScene(this);
    // set background to the board
    graphicsSceneBoard->setSceneRect(0, 10, 500, 500);
    graphicsSceneBoard->setBackgroundBrush(QBrush(QPixmap(":/Ludo/resource/board.jfif")));
    
    // adding blue piece
    QPixmap pieceBlueOriginal(":/Ludo/resource/piece_blue/piece_blue.png");
    QPixmap pieceBlue = pieceBlueOriginal.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem* pieceBlue1 = new QGraphicsPixmapItem(pieceBlue);
    pieceBlue1->setPos(97, 457);
    pieceBlue1->setFlag(QGraphicsItem::ItemIsMovable);
    graphicsSceneBoard->addItem(pieceBlue1);
    

    // set the scene to the graphics view
    ui->graphicsViewBoard->setScene(graphicsSceneBoard);
    
}

Ludo::~Ludo()
{
    delete ui;
}
