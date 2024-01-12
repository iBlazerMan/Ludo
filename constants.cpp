#include "constants.h"

namespace ludoConstants {
	// vector of all coordinates of 
	const std::vector<tile> tilesPublic = {
		tile('y', QPointF(156, 434)),
		tile('b', QPointF(142, 405)),
		tile('g', QPointF(142, 378)),
		tile('r', QPointF(156, 350)),
		tile('y', QPointF(128, 322)),
		tile('b', QPointF(100, 336)),
		tile('g', QPointF(73, 336)),
		tile('r', QPointF(45, 322)),
		tile('y', QPointF(31, 294)),
		tile('b', QPointF(31, 267)),
		tile('g', QPointF(31, 239)),
		tile('r', QPointF(31, 211)),
		tile('y', QPointF()),
		tile('b', QPointF()),
		tile('g', QPointF()),
		tile('r', QPointF()),
		tile('y', QPointF()),
		tile('b', QPointF()),
		tile('g', QPointF()),
		tile('r', QPointF()),
		tile('y', QPointF()),
		tile('b', QPointF()),
		tile('g', QPointF()),
		tile('r', QPointF()),
	};

	const std::vector<tile>tilesFinalBlue = {
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
	};

	const std::vector<tile>tilesFinalGreen = {
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
	};

	const std::vector<tile>tilesFinalRed = {
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
		tile(' ', QPointF()),
	};

	enum tileFlight {
		FLIGHT_YELLOW = 4,
		FLIGHT_BLUE = 17,
		FLIGHT_GREEN,
		FLIGHT_RED
	};

}
