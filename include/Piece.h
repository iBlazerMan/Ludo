#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QSoundEffect>

#include "constants.h"
#include "Tile.h"
#include "SignalEmitter.h"
#include "SoundEffectPlayer.h"

class Piece : public QGraphicsPixmapItem {

protected:
	// piece's current tile's index
	//		set to -1 when the piece is in its spawn / takeoff tile
	//		set to 0 - 51 when the piece is airborne 
	//		set to 100 - 104 when the piece is in final approach
	//		set to 105 when the piece is completed
	int indexCurr;
	// piece's next available tile's index
	int indexNext;
	// piece's ID, used to set spawn of the piece
	//		set to 0 - 3, first piece initialized is set to 0, increment by 1 for each subsequence piece
	//		each color has its own set of index
	int ID;
	// piece's sound effect index, used to determine the sound effect played after making a move
	//		should always be assigned using SoundEffetPlayer::sfIndex
	//		see SoundEffectPlayer.h for documentation
	unsigned int indexSF;
	// piece's current coordinate
	QPointF coordCurr;
	// piece's next avaiable tile's coordinate
	QPointF coordNext;
	// piece's status
	ludoConstants::status status;

	// number of the dice roll, determines how many steps a piece can be moved, static
	static int numRolled;

public:
	static QGraphicsPixmapItem* promptDot;
	static SignalEmitter* emitter;
	static SoundEffectPlayer* soundManager;

	using QGraphicsPixmapItem::QGraphicsPixmapItem;
	Piece(const QPixmap& icon, const int ID, const QPointF& coordCurr, const int indexCurr, const QPointF& coordNext, const int indexNext,
		const ludoConstants::status status, const unsigned int indexSF);

	void setIndexCurr(const int indexCurr);
	static void setNumRolled(const int numRolled);
	void setStatus(const ludoConstants::status status);

	int getIndexCurr() const;
	ludoConstants::status getStatus() const;
	QPointF getCoordCurr() const;
	static int getNumRolled();

	// performs an animation from coordCurr to CoordNext and update the piece to coordNext and indexNext
	//		also responsible for checking if knockback is available after the piece is moved to the new tile
	//		since the knockback should only be performed when the animation finishes
	void animate(const int duration);

	// retrieve the color of the piece, pure virtual
	virtual char getColor() const = 0;

	// retrieve the coordinate of the takeoff tile, pure virtual
	virtual QPointF getTakeoffTileCoord() const = 0;

	// retrieve the index of the first tile the piece lands on upon taking off, pure virtual 
	virtual int getInitialTileIndex() const = 0;

	// retrieve the index of the last tile the piece must reach before entering final approach, pure virtual
	virtual int getLastPublicTileIndex() const = 0;

	// retrieve the coordinate of the corresponding final approach tile with the index given, pure virtual
	virtual QPointF getFinalApproachTileCoord(const int& indexFinal) const = 0;

	// check if a jump is available and performs the jump if applicable, pure virtual
	virtual bool checkJump() = 0;

	// check if a flight is available and performs the flight if applicable, pure virtual
	virtual bool checkFlight() = 0;

	// set the piece to its starting position, pure virtual
	virtual void setToSpawn() = 0;

	// check if knockback is available and performs the knockback on other piece(s) if applicable
	//		- method must be called from the checkKnockback signal in order to pass in the other piece 
	//		vectors as parameter
	//		- the boolean firstCheck is used to determine whether a sound effect should be played since the 
	//		an additional knockback SF is played if a piece jumps/flys to a new tile and performs another 
	//		knockback, defaulted to true and set to false when calling checkKnockback a second time in a 
	//		round after a jump/fly
	void checkKnockback(std::vector<std::vector<Piece*>*> opponentPieces, const bool firstCheck = true);

protected:
	// override mouse press to calculate available position and show dot prompt
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	// override mouse release and implement snapping into position logic
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	
};

// derived classes of each colored piece from abstracr piece parent class
class PieceBlue : public Piece {

public:
	PieceBlue(const QPixmap& icon, const int ID, const QPointF& coordCurr = QPointF(0, 0), const int indexCurr = -1,
		const QPointF& coordNext = QPointF(0, 0), const int indexNext = -1,
		const ludoConstants::status status = ludoConstants::status::GROUNDED, 
		const unsigned int indexSF = SoundEffectPlayer::move);
	char getColor() const override;
	QPointF getTakeoffTileCoord() const override;
	int getInitialTileIndex() const override;
	int getLastPublicTileIndex() const override;
	QPointF getFinalApproachTileCoord(const int& indexFinal) const override;
	bool checkJump() override;
	bool checkFlight() override;
	void setToSpawn() override;
};

class PieceRed : public Piece {

public:
	PieceRed(const QPixmap& icon, const int ID, const QPointF& coordCurr = QPointF(0, 0), const int indexCurr = -1,
		const QPointF& coordNext = QPointF(0, 0), const int indexNext = -1,
		const ludoConstants::status status = ludoConstants::status::GROUNDED,
		const unsigned int indexSF = SoundEffectPlayer::move);
	char getColor() const override;
	QPointF getTakeoffTileCoord() const override;
	int getInitialTileIndex() const override;
	int getLastPublicTileIndex() const override;
	QPointF getFinalApproachTileCoord(const int& indexFinal) const override;
	bool checkJump() override;
	bool checkFlight() override;
	void setToSpawn() override;
};
