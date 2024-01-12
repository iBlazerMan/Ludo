#include "Ludo.h"

Ludo::Ludo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LudoClass())
{
    ui->setupUi(this);

    

    // initialize graphics scene to display the board and pieces
    graphicsSceneBoard = new QGraphicsScene(this);
    // set size and background of the board
    graphicsSceneBoard->setSceneRect(0, 0, 500, 500);
    graphicsSceneBoard->setBackgroundBrush(QBrush(QPixmap(":/Ludo/resource/board.jfif")));

    // create dice
    QPushButton* buttonDice = new QPushButton();
    buttonDice->setIcon(QIcon(":/Ludo/resource/dice/diceIso.png"));
    buttonDice->setIconSize(QSize(64, 64));
    buttonDice->setFixedSize(64, 64);
    buttonDice->setStyleSheet("background-color: transparent; border: none;");
    buttonDice->setCursor(Qt::PointingHandCursor);

    connect(buttonDice, &QPushButton::clicked, qApp, &QApplication::quit);
    
    // add dice to the board
    diceProxy = graphicsSceneBoard->addWidget(buttonDice);
    diceProxy->setPos(210, 210);

    // smooth rendering
    ui->graphicsViewBoard->setRenderHint(QPainter::SmoothPixmapTransform);

    // set the scene to the graphics view
    ui->graphicsViewBoard->setScene(graphicsSceneBoard);
    
    // adding blue piece
    QPixmap pieceBlueOriginal(":/Ludo/resource/piece_blue/piece_blue.png");
    QPixmap pieceBlue = pieceBlueOriginal.scaled(21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    piece* pieceBlue1 = new piece(pieceBlue);
    pieceBlue1->setPos(87, 448);
    pieceBlue1->setFlag(QGraphicsItem::ItemIsMovable);
    graphicsSceneBoard->addItem(pieceBlue1);   
    
}

Ludo::~Ludo()
{
    delete ui;
}

void Ludo::playerRound() {
    // hide dice
    diceProxy->hide();

    std::vector<piece*>& playerPieces = piecesBlue;

    // roll a random number between 1 and 6
    int numRolled = QRandomGenerator::global()->bounded(1, 7);
    bool moveAvailable = false;
    bool takeoffAvailable = true;

    // FINISH TOMORROW
    // iterate through the piece vector and check if any pieces are available to move
    for (piece* p : playerPieces) {
        if ((p->getStatus() != ludoConstants::status::COMPLETED)) {
            // set piece to movable and update the 
            p->setFlag(QGraphicsItem::ItemIsMovable);
            p->setMoveRolled(numRolled);
            // set movement available to true
            moveAvailable = true;
        }
    }

}
