#pragma once

namespace Tournaments {
	namespace Model {
		class TournamentConfig {
		public:
			double PointsPerWin;
			double PointsPerLose;
			double PointsPerDraw;
			int expectedRounds;
		};
	}
}