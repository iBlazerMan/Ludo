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
#include "SignalEmitter.h"
#include "constants.h"

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

private slots:
    void delayedEndRound();

private:
    Ui::LudoClass *ui;
    int numRound, numPlayer;
    std::vector<Piece*> piecesBlue, piecesGreen, piecesRed, piecesYellow;
    // TODO: possibly change to a vector that stores all vectors of pieces instead?
    std::vector<Piece*>* piecesCurr;
    QGraphicsScene* graphicsSceneBoard;
    QGraphicsProxyWidget* diceProxy;

    void initializePieces();
};
