#include "constants.h"

namespace ludoConstants {
		
	const int totalTilePublic = 52;

	const QPointF COORD_TAKEOFF_BLUE = QPointF(136, 465);

	const QPointF COORD_TAKEOFF_GREEN = QPointF(14, 137);

	const QPointF COORD_TAKEOFF_RED = QPointF(342, 17);

	const QPointF COORD_TAKEOFF_YELLOW = QPointF(462, 345);

	const std::vector<Tile> tilesPublic = {
		Tile('y', QPointF(156, 434)),
		Tile('b', QPointF(142, 405)),
		Tile('g', QPointF(142, 378)),
		Tile('r', QPointF(156, 350)),
		Tile('y', QPointF(128, 322)),
		Tile('b', QPointF(100, 336)),
		Tile('g', QPointF(73, 336)),
		Tile('r', QPointF(45, 322)),
		Tile('y', QPointF(31, 294)),
		Tile('b', QPointF(31, 267)),
		Tile('g', QPointF(31, 239)),
		Tile('r', QPointF(31, 211)),
		Tile('y', QPointF(31, 183)),
		Tile('b', QPointF(45, 155)),
		Tile('g', QPointF(72, 142)),
		Tile('r', QPointF(100, 142)),
		Tile('y', QPointF(128, 156)),
		Tile('b', QPointF(155, 128)),
		Tile('g', QPointF(142, 100)),
		Tile('r', QPointF(142, 72)),
		Tile('y', QPointF(156, 45)),
		Tile('b', QPointF(183, 31)),
		Tile('g', QPointF(211, 31)),
		Tile('r', QPointF(239, 31)),
		Tile('y', QPointF(267, 31)),
		Tile('b', QPointF(294, 31)),
		Tile('g', QPointF(322, 45)),
		Tile('r', QPointF(336, 73)),
		Tile('y', QPointF(336, 100)),
		Tile('b', QPointF(322, 128)),
		Tile('g', QPointF(350, 156)),
		Tile('r', QPointF(378, 142)),
		Tile('y', QPointF(405, 142)),
		Tile('b', QPointF(433, 156)),
		Tile('g', QPointF(447, 184)),
		Tile('r', QPointF(447, 211)),
		Tile('y', QPointF(447, 239)),
		Tile('b', QPointF(447, 266)),
		Tile('g', QPointF(447, 294)),
		Tile('r', QPointF(433, 322)),
		Tile('y', QPointF(405, 336)),
		Tile('b', QPointF(377, 336)),
		Tile('g', QPointF(350, 322)),
		Tile('r', QPointF(322, 350)),
		Tile('y', QPointF(336, 377)),
		Tile('b', QPointF(336, 405)),
		Tile('g', QPointF(322, 433)),
		Tile('r', QPointF(294, 447)),
		Tile('y', QPointF(267, 447)),
		Tile('b', QPointF(239, 447)),
		Tile('g', QPointF(211, 447)),
		Tile('r', QPointF(183, 447)),
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
		QPointF(239, 73),
		QPointF(239, 100),
		QPointF(239, 128),
		QPointF(239, 156),
		QPointF(239, 182),
		QPointF(239, 211)
	};

	const std::vector<QPointF>tilesSpawnBlue = {
		QPointF(86, 447),
		QPointF(31, 447),
		QPointF(86, 391),
		QPointF(31, 391)
	};

	const std::vector<QPointF>tilesSpawnRed = {
		QPointF(391, 31),
		QPointF(447, 31),
		QPointF(391, 86),
		QPointF(447, 86)
	};
	
}
