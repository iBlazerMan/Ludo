#include "piece.h"

piece::piece(const QPixmap& icon) :
	QGraphicsPixmapItem{ icon } {};


void piece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	// get mouse release point
	QPointF release = this->pos();

	qreal distance;

	//TEST CASE DELETE LATER;
	bool match = false;

	for (const tile& t : ludoConstants::tilesPublic) {
		// calculate the distance between the mouse release point and the available tile
		distance = QLineF(release, t.getCoord()).length();
		if (distance < 20) {
			setPos(t.getCoord());
			match = true;
			break;
		}
	}

	if (!match) {
		setPos(87, 448);
	}

	// parent class implementation
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void piece::setIndex(const int index) {
	this->index = index;
}

void piece::setMoveRolled(const int moveRolled) {
	this->moveRolled = moveRolled;
}

void piece::setStatus(const ludoConstants::status status) {
	this->status = status;
}

int piece::getIndex() const {
	return index;
}

int piece::getMoveRolled() const {
	return moveRolled;
}

ludoConstants::status piece::getStatus() const {
	return status;
}
