// class for every tile on the board, contains the coordinate and the color of the tile. 
// All tiles are intialized in constants.h and are not meant to be changed, thus no setters are provided.
// a custom class is chosen instead of other data types to facilitate future expansions.

#pragma once

#include <QPointF>

class Tile {
	char color;
	QPointF coord;

public:
	Tile(const char color, const QPointF& coord);
	char getColor() const;
	QPointF getCoord() const;
};
