#include "piece.h"

QGraphicsPixmapItem* piece::promptDot = nullptr;

piece::piece(const QPixmap& icon) :
	QGraphicsPixmapItem{icon} {

};


void piece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

	// hide prompt after movement
	promptDot->setVisible(false);

	
	// get mouse release point
	QPointF release = this->pos();

	qreal distance = QLineF(release, this->coordNext).length();

	// if piece movement is confirmed
	if (distance <= 20) {
		// case 1: piece is at the last tile, set status to completed
		if (this->indexNext == 105) {
			this->status = ludoConstants::status::COMPLETED;
		}
		// case 2: piece is grounded, set status to takeing off
		else if (this->status == ludoConstants::status::GROUNDED) {
			this->status = ludoConstants::status::TAKING_OFF;
		}
		// case 3: piece is taking off, set status to airborne
		else if (this->status == ludoConstants::status::TAKING_OFF) {
			this->status = ludoConstants::status::AIRBORNE;
		}
		// case 4: piece is airborne and enters final approach, set status to final approach
		else if (this->status == ludoConstants::status::FINAL_APPROACH && this->indexNext >= 100) {
			this->status = ludoConstants::status::FINAL_APPROACH;
		}

		// set coordsCurr to coordsNext, indexCurr to indexNext
		this->indexCurr = this->indexNext;
		this->coordCurr = this->coordNext;
		
		// move piece to new coord
		this->setPos(coordCurr);

		// emit round end signal
		emit endRound();
	}
	// piece movement not confirmed
	else {
		this->setPos(coordCurr);
	}
	
	// parent class implementation
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void piece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	
	ludoConstants::status pieceStatus = this->getStatus();

	// case 1: piece is grounded and ready to take off
	if (pieceStatus == ludoConstants::status::GROUNDED) {
		this->coordNext = this->getTakeoffTileCoord();
	}
	// case 2: piece is on the takeoff square
	else if (pieceStatus == ludoConstants::status::TAKING_OFF) {
		this->indexNext = this->getInitialTileIndex() + this->moveRolled - 1;
		this->coordNext = ludoConstants::tilesPublic[indexNext].getCoord();
	}
	// case 3: piece is airborne
	else if (pieceStatus == ludoConstants::status::AIRBORNE) {
		// piece reaching final approach
		if (this->indexCurr <= this->getLastPublicTileIndex() &&
			(this->indexCurr + this->moveRolled) > this->getLastPublicTileIndex()) {
			int indexFinalApproach = this->indexCurr + this->moveRolled - this->getLastPublicTileIndex() + 100 - 1;
			this->coordNext = this->getFinalApproachTileCoord(indexFinalApproach);
			this->indexNext = indexFinalApproach;
		}
		else {
			this->indexNext = (this->indexCurr + this->moveRolled) % ludoConstants::tilesPublic.size();
			this->coordNext = ludoConstants::tilesPublic[indexNext].getCoord();
		}
	}
	// case 4: piece is in final approach
	else if (pieceStatus == ludoConstants::status::FINAL_APPROACH) {
		// piece overshot
		if ((this->indexCurr + this->moveRolled) > 105) {
			indexNext = 105 * 2 - this->indexCurr - this->moveRolled;
		}
		else {
			this->indexNext = (this->indexCurr + this->moveRolled);
		}
		this->coordNext = this->getFinalApproachTileCoord(indexNext);
	}
	// does not need to check if piece is complete since complete piece cannot be set to movable

	// set the prompt to the next coordinate and make it visible
	promptDot->setPos(this->coordNext.x() + 5, this->coordNext.y() + 5);
	promptDot->setVisible(true);

	// parent class implementation
	QGraphicsPixmapItem::mousePressEvent(event);	
}

void piece::setIndexCurr(const int indexCurr) {
	this->indexCurr = indexCurr;
}

void piece::setMoveRolled(const int moveRolled) {
	this->moveRolled = moveRolled;
}

void piece::setStatus(const ludoConstants::status status) {
	this->status = status;
}

int piece::getIndexCurr() const {
	return indexCurr;
}

int piece::getMoveRolled() const {
	return moveRolled;
}

ludoConstants::status piece::getStatus() const {
	return status;
}



pieceBlue::pieceBlue(const QPixmap& icon) :
	piece{ icon } {};

char pieceBlue::getColor() const {
	return 'b';
}

QPointF pieceBlue::getTakeoffTileCoord() const {
	return ludoConstants::COORD_TAKEOFF_BLUE;
}

int pieceBlue::getInitialTileIndex() const {
	return ludoConstants::INITIAL_BLUE;
}

int pieceBlue::getLastPublicTileIndex() const {
	return ludoConstants::LAST_PUBLIC_BLUE;
}

QPointF pieceBlue::getFinalApproachTileCoord(const int& indexFinal) const {
	return ludoConstants::tilesFinalBlue[indexFinal - 100];
}