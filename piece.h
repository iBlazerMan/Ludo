#include <QGraphicsPixmapItem>
#include <map>

class piece : public QGraphicsPixmapItem {
public:
	using QGraphicsPixmapItem::QGraphicsPixmapItem;
	piece(const QPixmap& icon);

protected:
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};