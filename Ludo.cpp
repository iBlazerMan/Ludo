#include "Ludo.h"

Ludo::Ludo(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LudoClass()) {
    ui->setupUi(this);

    // TODO: set player to 2 arbirarily, will be decided by main menu UI later
    this->numPlayer = 2;
    this->numRound = 0;

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

    // add dice to the board
    diceProxy = graphicsSceneBoard->addWidget(buttonDice);
    diceProxy->setPos(217, 215);

    connect(buttonDice, &QPushButton::clicked, this, &Ludo::playerRound);

    // create dot prompt
    QGraphicsPixmapItem* promptDot = new QGraphicsPixmapItem(QPixmap(":/Ludo/resource/dotBlack.png").scaled
        (10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    promptDot->setPos(200, 200);
    graphicsSceneBoard->addItem(promptDot);
    promptDot->setOpacity(0.6);
    promptDot->setVisible(false);
    // add shared dot prompt pointer to Piece class:
    Piece::promptDot = promptDot;
    // initialize shared signal emitter for Piece class:
    Piece::emitter = new SignalEmitter(this);

    // smooth rendering
    ui->graphicsViewBoard->setRenderHint(QPainter::SmoothPixmapTransform);
    // set the scene to the graphics view
    ui->graphicsViewBoard->setScene(graphicsSceneBoard);
    
    // create pieces based on # of players and pieces
    this->initializePieces();

    // set current pieces to blue piece vector
    this->piecesCurr = &piecesBlue;

    // signal connection
    connect(this, &Ludo::endRound, this, &Ludo::nextRound);
    connect(Piece::emitter, &SignalEmitter::endRound, this, &Ludo::nextRound);
}

Ludo::~Ludo()
{
    delete ui;
    // delete graphics scence display, also chain deletes all pieces, dice, and dot prompt
    delete this->graphicsSceneBoard;
}


void Ludo::playerRound() {
    // hide dice
    diceProxy->hide();

    // TODO: Change this to the selector
    //
    // roll a random number between 1 and 6
    int numRolled = QRandomGenerator::global()->bounded(1, 7);
    bool moveAvailable = false;
    
    // NEEDED?
    bool takeoffAvailable = true;

    // output number rolled to interaction log
    ui->interactionLog->setText("You rolled a " + QString::number(numRolled) + "!\n");

    // iterate through the piece vector and check if any pieces are available to move
    for (Piece* p : *this->piecesCurr) {
        // enable all pieces that can move
        if (p->getStatus() != ludoConstants::status::COMPLETED && 
            p->getStatus() != ludoConstants::status::GROUNDED) {
            // set piece to movable and update the number rolled
            p->setFlag(QGraphicsItem::ItemIsMovable);
            p->setMoveRolled(numRolled);
            // set movement available to true
            moveAvailable = true;
        }
        // enable takeoff when 6 is rolled
        else if (p->getStatus() == ludoConstants::status::GROUNDED &&
            numRolled == 6) {
            p->setFlag(QGraphicsItem::ItemIsMovable);
            takeoffAvailable = false;
            moveAvailable = true;
        }
    }

    // if no piece can be moved
    if (!moveAvailable) {
        QTimer::singleShot(1500, this, &Ludo::delayedEndRound);
        ui->interactionLog->setText(ui->interactionLog->text() + "\nNo move available!\n");
    }
}

void Ludo::delayedEndRound() {
    emit Ludo::endRound();
}

void Ludo::initializePieces() {
    // TODO: Change to proper initializing function based on player/pieces
    QPixmap pieceBlueIcon = QPixmap(":/Ludo/resource/piece_blue/piece_blue.png").scaled
    (21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    PieceBlue* pieceBlue1 = new PieceBlue(pieceBlueIcon, ludoConstants::tilesSpawnBlue[0]);
    this->graphicsSceneBoard->addItem(pieceBlue1);
    this->piecesBlue.push_back(pieceBlue1);

    PieceBlue* pieceBlue2 = new PieceBlue(pieceBlueIcon, ludoConstants::tilesSpawnBlue[1]);
    this->graphicsSceneBoard->addItem(pieceBlue2);
    this->piecesBlue.push_back(pieceBlue2);

    PieceBlue* pieceBlue3 = new PieceBlue(pieceBlueIcon, ludoConstants::tilesSpawnBlue[2]);
    this->graphicsSceneBoard->addItem(pieceBlue3);
    this->piecesBlue.push_back(pieceBlue3);

    PieceBlue* pieceBlue4 = new PieceBlue(pieceBlueIcon, ludoConstants::tilesSpawnBlue[3]);
    this->graphicsSceneBoard->addItem(pieceBlue4);
    this->piecesBlue.push_back(pieceBlue4);

    QPixmap pieceRedIcon = QPixmap(":/Ludo/resource/piece_red/piece_red.png").scaled
    (21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    PieceRed* pieceRed1 = new PieceRed(pieceRedIcon, ludoConstants::tilesSpawnRed[0]);
    this->graphicsSceneBoard->addItem(pieceRed1);
    this->piecesRed.push_back(pieceRed1);

    PieceRed* pieceRed2 = new PieceRed(pieceRedIcon, ludoConstants::tilesSpawnRed[1]);
    this->graphicsSceneBoard->addItem(pieceRed2);
    this->piecesRed.push_back(pieceRed2);

    PieceRed* pieceRed3 = new PieceRed(pieceRedIcon, ludoConstants::tilesSpawnRed[2]);
    this->graphicsSceneBoard->addItem(pieceRed3);
    this->piecesRed.push_back(pieceRed3);

    PieceRed* pieceRed4 = new PieceRed(pieceRedIcon, ludoConstants::tilesSpawnRed[3]);
    this->graphicsSceneBoard->addItem(pieceRed4);
    this->piecesRed.push_back(pieceRed4);
    
}


// TODO: Implement proper piece selector
void Ludo::nextRound() {
    // disable all currently movable pieces
    for (Piece* p : *this->piecesCurr) {
        p->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    // update to reference next player's vector of pieces
    if (this->numRound % 2 == 0) {
        this->piecesCurr = &this->piecesRed;
        ui->interactionLog->setText("Red's turn");
    }
    else if (this->numRound % 2 == 1) {
        this->piecesCurr = &this->piecesBlue;
        ui->interactionLog->setText("Blue's turn");
    }
    // increment round number
    ++numRound;
    // re-enable dice
    this->diceProxy->setVisible(true);

}
