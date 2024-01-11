#include "piece.h"

piece::piece(const QPixmap& icon) :
	QGraphicsPixmapItem{ icon } {};


void piece::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	// get mouse release point
	QPointF release = this->pos();

	//TEST CASE DELETE LATER
	QPointF testPoint = QPointF(239, 447);

	// calculate the distance between the mouse release point and the available tile
	qreal distance = QLineF(release, testPoint).length();

	if (distance < 20) {
		setPos(testPoint);
	}
	else {
		setPos(87, 448);
	}


	// parent class implementation
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}	