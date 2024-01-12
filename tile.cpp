#include "tile.h"

tile::tile(const char color, const QPointF& coord) :
	color{ color }, coord{ coord } {};

char tile::getColor() const {
	return color;
}

QPointF tile::getCoord() const {
	return coord;
}