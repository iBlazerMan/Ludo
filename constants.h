#pragma once

#include <vector>

#include "tile.h"


namespace ludoConstants {
	// vector of all coordinates of 
	extern const std::vector<tile> tilesPublic;

	extern const std::vector<tile> tilesFinalBlue;

	extern const std::vector<tile> tilesFinalGreen;

	extern const std::vector<tile> tilesFinalRed;

	extern const std::vector<tile> tilesFinalYellow;

	enum tileFlight;

	enum class status {
		GROUNDED,
		TAKING_OFF,
		AIRBORNE,
		FINAL_APPROACH,
		COMPLETED
	};
}

