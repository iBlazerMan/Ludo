#include "piece.h"

QGraphicsPixmapItem* Piece::promptDot = nullptr;
SignalEmitter* Piece::emitter = nullptr;
SoundEffectPlayer* Piece::soundManager = nullptr;
int Piece::numRolled = 0;

Piece::Piece(const QPixmap& icon, const int ID, const QPointF& coordCurr, const int indexCurr, const QPointF& coordNext, 
		const int indexNext, const ludoConstants::status status, const unsigned int indexSF) :
		QGraphicsPixmapItem{ icon }, ID{ ID },  coordCurr{ coordCurr }, indexCurr{ indexCurr }, coordNext{ coordNext },
		indexNext{ indexNext }, status{ status }, indexSF{ indexSF } {};

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
		// case 2: piece is grounded, set status to taking off
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
		
		// reset SF index to normal move
		this->indexSF = SoundEffectPlayer::move;

		// check knockback
		emit emitter->checkKnockback(this, true);

		// check jump and flight
		if (!this->checkFlight()) {
			this->checkJump();
		}	

		// play sound effect
		Piece::soundManager->playSoundEffect(this->indexSF);

		// emit round end signal
		emit Piece::emitter->endRound();
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
			this->indexNext = this->getInitialTileIndex() + this->numRolled - 1;
			this->coordNext = ludoConstants::tilesPublic[indexNext].getCoord();
		}
		// case 3: piece is airborne
		else if (pieceStatus == ludoConstants::status::AIRBORNE) {
			// piece reaching final approach
			if (this->indexCurr <= this->getLastPublicTileIndex() &&
				(this->indexCurr + this->numRolled) > this->getLastPublicTileIndex()) {
				int indexFinalApproach = this->indexCurr + this->numRolled - this->getLastPublicTileIndex() + 100 - 1;
				this->coordNext = this->getFinalApproachTileCoord(indexFinalApproach);
				this->indexNext = indexFinalApproach;
			}
			// otherwise
			else {
				this->indexNext = (this->indexCurr + this->numRolled) % ludoConstants::tilesPublic.size();
				this->coordNext = ludoConstants::tilesPublic[indexNext].getCoord();
			}
		}
		// case 4: piece is in final approach
		else if (pieceStatus == ludoConstants::status::FINAL_APPROACH) {
			// piece overshot
			if ((this->indexCurr + this->numRolled) > 105) {
				indexNext = 105 * 2 - this->indexCurr - this->numRolled;
			}
			// otherwise 
			else {
				this->indexNext = (this->indexCurr + this->numRolled);
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

void Piece::setNumRolled(const int numRolled) {
	Piece::numRolled = numRolled;
}

void Piece::setStatus(const ludoConstants::status status) {
	this->status = status;
}

int Piece::getIndexCurr() const {
	return this->indexCurr;
}


ludoConstants::status Piece::getStatus() const {
	return this->status;
}

QPointF Piece::getCoordCurr() const {
	return this->coordCurr;
}

int Piece::getNumRolled() {
	return Piece::numRolled;
}

void Piece::animate(const int animationDuration) {
	// initialize timeline and animation objects
	QTimeLine* animationTimeLine = new QTimeLine(animationDuration);
	animationTimeLine->setFrameRange(0, 500);
	animationTimeLine->setEasingCurve(QEasingCurve::InOutQuad);
	QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
	animation->setItem(this);
	animation->setTimeLine(animationTimeLine);

	// set source and destination of animation
	animation->setPosAt(0, this->coordCurr);
	animation->setPosAt(1, this->coordNext);

	// cleanup when animation is completed
	QObject::connect(animationTimeLine, &QTimeLine::finished, animationTimeLine, &QObject::deleteLater);
	QObject::connect(animationTimeLine, &QTimeLine::finished, animation, &QObject::deleteLater);

	// since animation is called when performing a jump or a flight, check knockback when the animation is over
	//		uses a lambda function that emits the checkKnockback signal
	QObject::connect(animationTimeLine, &QTimeLine::finished, [this]()
		{emit emitter->checkKnockback(this, false); });

	animationTimeLine->start();

	// update piece coord and index once animation completes
	this->coordCurr = this->coordNext;
	this->indexCurr = this->indexNext;
}

void Piece::checkKnockback(std::vector<std::vector<Piece*>*> opponentPieces, bool firstCheck) {\
	// reset the SF index on the second call (in case where the first call performed a knockback and a 
	// flight/jump but the new tile the piece lands on does not perform another knockback, a second
	// knockback sound effect should not be played
	if (this->indexSF == SoundEffectPlayer::knockback) {
		this->indexSF = SoundEffectPlayer::move;
	}
	// if the piece is on a public tile
	if (this->indexCurr >= 0 && this->indexCurr <= 51) {
		for (std::vector<Piece*>* otherColorPieces : opponentPieces) {
			for (Piece* p : *otherColorPieces) {
				// set opponent piece back to spawn if it is on the same tile
				if (p->indexCurr == this->indexCurr) {
					p->setToSpawn();
					// set SF index to knockback
					this->indexSF = SoundEffectPlayer::knockback;
				}
			}
		}
	}
	// play sound effect if it is not the first check performed and the sound effect played is 
	// the knockback SF
	if (!firstCheck && this->indexSF == SoundEffectPlayer::knockback) {
		Piece::soundManager->playSoundEffect(this->indexSF);
	}
}


PieceBlue::PieceBlue(const QPixmap& icon, const int ID, const QPointF& coordCurr, const int indexCurr, 
	const QPointF& coordNext, const int indexNext, const ludoConstants::status status, const unsigned int indexSF) :
	Piece{ icon, ID, coordCurr, indexCurr, coordNext, indexNext, status, indexSF} {
		this->setToSpawn();
}

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
				// set SF index to jump if current sound effect is not knockback
				// knockback SF has priority and jump SF is not played if a knockback is performed
				if (this->indexSF != SoundEffectPlayer::knockback) {
					this->indexSF = SoundEffectPlayer::jump;
				}
				this->animate(500);
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
		// set SF index to flight if current sound effect is not knockback
		// knockback SF has priority and flight SF is not played if a knockback is performed
		if (this->indexSF != SoundEffectPlayer::knockback) {
			this->indexSF = SoundEffectPlayer::flight;
		}
		this->animate(1000);
		return true;
	}
	return false;
}

void PieceBlue::setToSpawn() {
	// set coordCurr to corresponding spawn tile and set index to -1
	this->coordCurr = ludoConstants::tilesSpawnBlue[this->ID];
	this->indexCurr = -1;
	this->coordNext = this->coordCurr;
	this->indexNext = this->indexCurr;
	this->setPos(this->coordCurr);
	// set status to grounded
	this->status = ludoConstants::status::GROUNDED;
}

PieceRed::PieceRed(const QPixmap& icon, const int ID, const QPointF& coordCurr, const int indexCurr,
	const QPointF& coordNext, const int indexNext, const ludoConstants::status status, const unsigned int indexSF) :
	Piece{ icon, ID, coordCurr, indexCurr, coordNext, indexNext, status, indexSF } {
		this->setToSpawn();
}

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
	// if the tile is red and is not the final tile before final approach
	if (this->indexCurr >= 0 && this->indexCurr < ludoConstants::tilesPublic.size() &&
		ludoConstants::tilesPublic[this->indexCurr].getColor() == 'r' &&
		this->indexCurr != ludoConstants::LAST_PUBLIC_RED) {
		// for loop to find the next red tile
		for (int i = indexCurr + 1; ; ++i) {
			// check if index surpass last tile, reset to following tile with index 0
			if (i == ludoConstants::tilesPublic.size()) {
				i = 0;
			}
			// next same-color tile found
			if (ludoConstants::tilesPublic[i].getColor() == 'r') {
				this->indexNext = i;
				this->coordNext = ludoConstants::tilesPublic[i].getCoord();
				// set SF index to jump if current sound effect is not knockback
				// knockback SF has priority and jump SF is not played if a knockback is performed
				if (this->indexSF != SoundEffectPlayer::knockback) {
					this->indexSF = SoundEffectPlayer::jump;
				}
				this->animate(500);
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
		// set SF index to flight if current sound effect is not knockback
		// knockback SF has priority and flight SF is not played if a knockback is performed
		if (this->indexSF != SoundEffectPlayer::knockback) {
			this->indexSF = SoundEffectPlayer::flight;
		}
		this->animate(1000);
		return true;
	}
	return false;
}

void PieceRed::setToSpawn() {
	// set coordCurr to corresponding spawn tile and set index to -1
	this->coordCurr = ludoConstants::tilesSpawnRed[this->ID];
	this->indexCurr = -1;
	this->coordNext = this->coordCurr;
	this->indexNext = this->indexCurr;
	this->setPos(this->coordCurr);
	// set status to grounded
	this->status = ludoConstants::status::GROUNDED;
}
