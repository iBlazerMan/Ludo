#pragma once

#include <QGraphicsPixmapItem>
#include <map>

#include "constants.h"
#include "tile.h"

class piece : public QGraphicsPixmapItem {
	int index, moveRolled;
	ludoConstants::status status;

public:
	

	using QGraphicsPixmapItem::QGraphicsPixmapItem;
	static QGraphicsPixmapItem* promptDot;
	piece(const QPixmap& icon);

	void setIndex(const int index);
	void setMoveRolled(const int moveRolled);
	void setStatus(const ludoConstants::status status);

	int getIndex() const;
	int getMoveRolled() const;
	ludoConstants::status getStatus() const;

	
	// set to pure virtual method later
	/*
	virtual void checkJump();
	virtual void setToSpawn(const std::vector<piece> pieces);
	*/

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	// override mouse release and implement snapping into position logic
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
	
};

// derived class fo
class pieceBlue : public piece {

};
