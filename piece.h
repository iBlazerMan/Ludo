#pragma once

#include <QGraphicsPixmapItem>
#include <map>

#include "constants.h"
#include "Tile.h"
#include "SignalEmitter.h"

class Piece : public QGraphicsPixmapItem {

protected:
	int indexCurr, indexNext, moveRolled;
	QPointF coordCurr, coordNext;
	ludoConstants::status status;

public:
	static QGraphicsPixmapItem* promptDot;
	static SignalEmitter* emitter;

	using QGraphicsPixmapItem::QGraphicsPixmapItem;
	Piece(const QPixmap& icon, const QPointF& coordCurr = QPointF(0, 0), const int indexCurr = -1,
		const QPointF& coordNext = QPointF(0, 0), const int indexNext = -1, 
		const ludoConstants::status status = ludoConstants::status::GROUNDED, const int moveRolled = 0);

	void setIndexCurr(const int indexCurr);
	void setMoveRolled(const int moveRolled);
	void setStatus(const ludoConstants::status status);

	int getIndexCurr() const;
	int getMoveRolled() const;
	ludoConstants::status getStatus() const;
	
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
	
	
	virtual bool checkJump() = 0;

	// virtual void setToSpawn();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	// override mouse release and implement snapping into position logic
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	
};

// derived class fo
class PieceBlue : public Piece {

public:
	PieceBlue(const QPixmap& icon);
	char getColor() const override;
	QPointF getTakeoffTileCoord() const override;
	int getInitialTileIndex() const override;
	int getLastPublicTileIndex() const override;
	QPointF getFinalApproachTileCoord(const int& indexFinal) const override;
	bool checkJump() override;
};
