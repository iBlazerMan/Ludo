#include "constants.h"

namespace ludoConstants {
		
	const int totalTilePublic = 52;

	const QPointF COORD_TAKEOFF_BLUE = QPointF(136, 465);

	const QPointF COORD_TAKEOFF_GREEN = QPointF(14, 137);

	const QPointF COORD_TAKEOFF_RED = QPointF(342, 17);

	const QPointF COORD_TAKEOFF_YELLOW = QPointF(462, 345);



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

	const std::vector<QPointF>tilesFinalBlue = {
		QPointF(239, 405),
		QPointF(239, 377),
		QPointF(239, 349),
		QPointF(239, 322),
		QPointF(239, 295),
		QPointF(239, 266)
	};

	const std::vector<QPointF>tilesFinalGreen = {
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF()
	};

	const std::vector<QPointF>tilesFinalRed = {
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF(),
		QPointF()
	};
	
}
