#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QTimer>
#include <string>
#include "ui_Ludo.h"

#include "Piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LudoClass; };
QT_END_NAMESPACE

class Ludo : public QMainWindow
{
    Q_OBJECT

public:
    Ludo(QWidget *parent = nullptr);
    ~Ludo();

signals:
    void endRound();

public slots:
    void playerRound();
    void nextRound();
    void checkKnockBack(Piece* p, bool firstCheck);

private slots:
    void delayedEndRound();

private:
    // Qt UI class
    Ui::LudoClass *ui;
    // round number, used to determine which color's round it is
    unsigned int numRound;
    // number of players, used for piece generation and determine which color's round it is
    int numPlayer;
    // piece containers for all 4 colors
    std::vector<Piece*> piecesBlue, piecesGreen, piecesRed, piecesYellow;
    // pointer to the pieces container
    std::vector<Piece*>* piecesCurr;
    // game board, has ownership to 
    QGraphicsScene* graphicsSceneBoard;
    // clickable dice widget
    QGraphicsProxyWidget* diceProxy;

    // initialize and setup pieces based on the number of players
    void initializePieces();
};
