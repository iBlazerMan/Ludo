#pragma once

#include <vector>
#include <QPointF>

#include "Tile.h"


namespace ludoConstants {
	// total number of pulic tiles
	extern const int totalTilePublic;

	// coordinates of takeoff waiting tiles
	extern const QPointF COORD_TAKEOFF_BLUE;
	extern const QPointF COORD_TAKEOFF_GREEN;
	extern const QPointF COORD_TAKEOFF_RED;
	extern const QPointF COORD_TAKEOFF_YELLOW;

	// coordinates of all public tiles
	extern const std::vector<Tile> tilesPublic;

	// coordinates of all final approach tiles
	extern const std::vector<QPointF> tilesFinalBlue;
	extern const std::vector<QPointF> tilesFinalGreen;
	extern const std::vector<QPointF> tilesFinalRed;
	extern const std::vector<QPointF> tilesFinalYellow;

	// coordinate of all hanger tiles 
	extern const std::vector<QPointF> tilesSpawnBlue;
	extern const std::vector<QPointF> tilesSpawnGreen;
	extern const std::vector<QPointF> tilesSpawnRed;
	extern const std::vector<QPointF> tilesSpawnYellow;

	// indexes of all tiles involved in a flight
	enum tileFlightIndex {
		FLIGHT_YELLOW_DEPART = 4,
		FLIGHT_BLUE_DEPART = 17,
		FLIGHT_GREEN_DEPART = 30,
		FLIGHT_RED_DEPART = 43,
		FLIGHT_YELLOW_ARRIVE = 16,
		FLIGHT_BLUE_ARRIVE = 29,
		FLIGHT_GREEN_ARRIVE = 42,
		FLIGHT_RED_ARRIVE = 3
	};

	// indexes of all color pieces' first tile they travel to upon taking off
	enum tileInitialIndex {
		INITIAL_BLUE = 0,
		INITIAL_GREEN = 13,
		INITIAL_RED = 26,
		INITIAL_YELLOW = 39
	};

	enum tileLastPublicIndex {
		LAST_PUBLIC_GREEN = 10,
		LAST_PUBLIC_RED = 23,
		LAST_PUBLIC_YELLOW = 36,
		LAST_PUBLIC_BLUE = 49
	};

	// custom class of pieces' status
	enum class status {
		GROUNDED,
		TAKING_OFF,
		AIRBORNE,
		FINAL_APPROACH,
		COMPLETED
	};
}
