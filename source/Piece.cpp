#include "piece.h"

QGraphicsPixmapItem* Piece::promptDot = nullptr;
SignalEmitter* Piece::emitter = nullptr;

Piece::Piece(const QPixmap& icon, const QPointF& coordCurr, const int indexCurr, const QPointF& coordNext, 
		const int indexNext, const ludoConstants::status status, const int moveRolled) :
		QGraphicsPixmapItem{ icon }, coordCurr{ coordCurr }, indexCurr{ indexCurr }, coordNext{ coordNext },
		indexNext{ indexNext }, status{ status }, moveRolled{ moveRolled } {
	this->setPos(coordCurr);
};

// drop and snap logic
void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

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
		else if (this->status == ludoConstants::status::AIRBORNE && this->indexNext >= 100) {
			this->status = ludoConstants::status::FINAL_APPROACH;
		}

		// set coordsCurr to coordsNext, indexCurr to indexNext
		this->indexCurr = this->indexNext;
		this->coordCurr = this->coordNext;

		// move piece to new coord
		this->setPos(coordCurr);
		
		// check jumpa and flight
		if (!this->checkFlight()) {
			this->checkJump();
		}		

		// emit round end signal
		emit emitter->endRound();
	}
	// piece movement not confirmed
	else {
		this->setPos(coordCurr);
	}
	
	// parent class implementation
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (this->flags() & QGraphicsItem::ItemIsMovable) {
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
			// otherwise
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
			// otherwise 
			else {
				this->indexNext = (this->indexCurr + this->moveRolled);
			}
			this->coordNext = this->getFinalApproachTileCoord(indexNext);
		}
		// does not need to check if piece is complete since complete piece cannot be set to movable

		// set the prompt to the next coordinate and make it visible
		promptDot->setPos(this->coordNext.x() + 5, this->coordNext.y() + 5);
		promptDot->setVisible(true);
	}
	// parent class implementation
	QGraphicsPixmapItem::mousePressEvent(event);	
}

void Piece::setIndexCurr(const int indexCurr) {
	this->indexCurr = indexCurr;
}

void Piece::setMoveRolled(const int moveRolled) {
	this->moveRolled = moveRolled;
}

void Piece::setStatus(const ludoConstants::status status) {
	this->status = status;
}

int Piece::getIndexCurr() const {
	return indexCurr;
}

int Piece::getMoveRolled() const {
	return moveRolled;
}

ludoConstants::status Piece::getStatus() const {
	return status;
}

QPointF Piece::getCoordCurr() const {
	return coordCurr;
}

void Piece::animate(const int animationDuration) {
	QTimeLine* animationTimeLine = new QTimeLine(animationDuration);
	animationTimeLine->setFrameRange(0, 500);
	animationTimeLine->setEasingCurve(QEasingCurve::InOutQuad);

	QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
	animation->setItem(this);
	animation->setTimeLine(animationTimeLine);

	animation->setPosAt(0, this->coordCurr);
	animation->setPosAt(1, this->coordNext);

	QObject::connect(animationTimeLine, &QTimeLine::finished, animationTimeLine, &QObject::deleteLater);
	QObject::connect(animationTimeLine, &QTimeLine::finished, animation, &QObject::deleteLater);

	animationTimeLine->start();
}

PieceBlue::PieceBlue(const QPixmap& icon, const QPointF& coordCurr, const int indexCurr, 
	const QPointF& coordNext, const int indexNext, const ludoConstants::status status, const int moveRolled) :
	Piece{ icon, coordCurr, indexCurr, coordNext, indexNext, status, moveRolled } {}

char PieceBlue::getColor() const {
	return 'b';
}

QPointF PieceBlue::getTakeoffTileCoord() const {
	return ludoConstants::COORD_TAKEOFF_BLUE;
}

int PieceBlue::getInitialTileIndex() const {
	return ludoConstants::INITIAL_BLUE;
}

int PieceBlue::getLastPublicTileIndex() const {
	return ludoConstants::LAST_PUBLIC_BLUE;
}

QPointF PieceBlue::getFinalApproachTileCoord(const int& indexFinal) const {
	return ludoConstants::tilesFinalBlue[indexFinal - 100];
}

// TODO: incorporate animation using QPropertyAnimation
//
bool PieceBlue::checkJump() {
	// if the tile is blue and is not the final tile before final approach
	if (this->indexCurr >= 0 && this->indexCurr < ludoConstants::tilesPublic.size() &&
		ludoConstants::tilesPublic[this->indexCurr].getColor() == 'b' &&
		this->indexCurr != ludoConstants::LAST_PUBLIC_BLUE) {
		// for loop to find the next blue tile
		for (int i = indexCurr + 1; ; ++i) {
			// check if index surpass last tile, reset to following tile with index 0
			if (i == ludoConstants::tilesPublic.size()) {
				i = 0;
			}
			// next same-color tile found
			if (ludoConstants::tilesPublic[i].getColor() == 'b') {
				this->indexNext = i;
				this->coordNext = ludoConstants::tilesPublic[i].getCoord();
				this->animate(500);
				this->indexCurr = this->indexNext;
				this->coordCurr = this->coordNext;
				break;
			}
		}
		return true;
	}
	return false;
}

bool PieceBlue::checkFlight() {
	if (this->indexCurr == ludoConstants::FLIGHT_BLUE_DEPART) {
		this->indexNext = ludoConstants::FLIGHT_BLUE_ARRIVE;
		this->coordNext = ludoConstants::tilesPublic[this->indexNext].getCoord();
		this->animate(1000);
		this->indexCurr = this->indexNext;
		this->coordCurr = this->coordNext;
		return true;
	}
	return false;
}

PieceRed::PieceRed(const QPixmap& icon, const QPointF& coordCurr, const int indexCurr,
	const QPointF& coordNext, const int indexNext, const ludoConstants::status status, const int moveRolled) :
	Piece{ icon, coordCurr, indexCurr, coordNext, indexNext, status, moveRolled } {}

char PieceRed::getColor() const {
	return 'r';
}

QPointF PieceRed::getTakeoffTileCoord() const {
	return ludoConstants::COORD_TAKEOFF_RED;
}

int PieceRed::getInitialTileIndex() const {
	return ludoConstants::INITIAL_RED;
}

int PieceRed::getLastPublicTileIndex() const {
	return ludoConstants::LAST_PUBLIC_RED;
}

QPointF PieceRed::getFinalApproachTileCoord(const int& indexFinal) const {
	return ludoConstants::tilesFinalRed[indexFinal - 100];
}

bool PieceRed::checkJump() {
	// if the tile is blue and is not the final tile before final approach
	if (this->indexCurr >= 0 && this->indexCurr < ludoConstants::tilesPublic.size() &&
		ludoConstants::tilesPublic[this->indexCurr].getColor() == 'r' &&
		this->indexCurr != ludoConstants::LAST_PUBLIC_RED) {
		// for loop to find the next blue tile
		for (int i = indexCurr + 1; ; ++i) {
			// check if index surpass last tile, reset to following tile with index 0
			if (i == ludoConstants::tilesPublic.size()) {
				i = 0;
			}
			// next same-color tile found
			if (ludoConstants::tilesPublic[i].getColor() == 'r') {
				this->indexNext = i;
				this->coordNext = ludoConstants::tilesPublic[i].getCoord();
				this->animate(500);
				this->indexCurr = this->indexNext;
				this->coordCurr = this->coordNext;
				break;
			}
		}
		return true;
	}
	return false;
}

bool PieceRed::checkFlight() {
	if (this->indexCurr == ludoConstants::FLIGHT_RED_DEPART) {
		this->indexNext = ludoConstants::FLIGHT_RED_ARRIVE;
		this->coordNext = ludoConstants::tilesPublic[this->indexNext].getCoord();
		this->animate(1000);
		this->indexCurr = this->indexNext;
		this->coordCurr = this->coordNext;
		return true;
	}
	return false;
}