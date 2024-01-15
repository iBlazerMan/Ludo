#include "tile.h"

Tile::Tile(const char color, const QPointF& coord) :
	color{ color }, coord{ coord } {};

char Tile::getColor() const {
	return color;
}

QPointF Tile::getCoord() const {
	return coord;
}