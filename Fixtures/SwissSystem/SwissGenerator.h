#pragma once
#include "../IFixturesGenerator.h"
#include "../../Data/Tournament.h"

namespace Fixtures {
	class SwissGenerator : public IFixtureGenerator {
	private:
		int nAllowedRespectiveColors;
	public:
		SwissGenerator(int allowedRespectiveColor = 2){
			nAllowedRespectiveColors = allowedRespectiveColor;
		}
		void GenerateFixtures(Tournaments::Model::Tournament* tournament);
		Tournaments::Model::Round* GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int roundId);
		bool IsRoundSensitive();
	};
}