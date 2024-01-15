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

    // add dice to the board
    diceProxy = graphicsSceneBoard->addWidget(buttonDice);
    diceProxy->setPos(210, 210);

    connect(buttonDice, &QPushButton::clicked, this, &Ludo::playerRound);

    // create dot prompt
    QGraphicsPixmapItem* promptDot = new QGraphicsPixmapItem(QPixmap(":/Ludo/resource/dotBlack.png").scaled
        (10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    promptDot->setPos(200, 200);
    graphicsSceneBoard->addItem(promptDot);
    promptDot->setOpacity(0.6);
    promptDot->setVisible(false);
    // add dot prompt pointer to piece class:
    Piece::promptDot = promptDot;

    // initialize shared signal emitter for Piece class:
    Piece::emitter = new SignalEmitter(this);

    // smooth rendering
    ui->graphicsViewBoard->setRenderHint(QPainter::SmoothPixmapTransform);

    // set the scene to the graphics view
    ui->graphicsViewBoard->setScene(graphicsSceneBoard);
    
    // TESTING: adding blue piece
    QPixmap pieceBlueIcon = QPixmap(":/Ludo/resource/piece_blue/piece_blue.png").scaled
        (21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    PieceBlue* pieceBlue1 = new PieceBlue(pieceBlueIcon);
    graphicsSceneBoard->addItem(pieceBlue1);   
    piecesBlue.push_back(pieceBlue1);

    connect(this, &Ludo::endRound, this, &Ludo::reset);
    connect(Piece::emitter, &SignalEmitter::endRound, this, &Ludo::reset);
}

Ludo::~Ludo()
{
    delete ui;
    // delete graphics scence display, also chain
    delete this->graphicsSceneBoard;

    delete Piece::promptDot;
}


void Ludo::playerRound() {
    // hide dice
    diceProxy->hide();

    // TODO: Change this to the selector
    // 
    std::vector<Piece*>& playerPieces = piecesBlue;

    // roll a random number between 1 and 6
    int numRolled = QRandomGenerator::global()->bounded(1, 7);
    bool moveAvailable = false;
    bool takeoffAvailable = true;

    // output number rolled to interaction log
    ui->interactionLog->setText("You rolled a " + QString::number(numRolled) + "!\n");

    // iterate through the piece vector and check if any pieces are available to move
    for (Piece* p : playerPieces) {
        // enable all pieces that can move
        if (p->getStatus() != ludoConstants::status::COMPLETED && 
            p->getStatus() != ludoConstants::status::GROUNDED) {
            // set piece to movable and update the 
            p->setFlag(QGraphicsItem::ItemIsMovable);
            p->setMoveRolled(numRolled);
            // set movement available to true
            moveAvailable = true;
        }
        // enable takeoff when 6 is rolled
        else if (p->getStatus() == ludoConstants::status::GROUNDED &&
            numRolled == 6 && takeoffAvailable) {
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


// TESTING
void Ludo::reset() {
    this->diceProxy->setVisible(true);
    for (Piece* p : piecesBlue) {
        p->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}
