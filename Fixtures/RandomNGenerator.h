#pragma once
#include "IFixturesGenerator.h"
#include "../Data/Tournament.h"

namespace Fixtures {
	class RandomNGenerator : public IFixtureGenerator {
	public:

		void GenerateFixtures(Tournaments::Model::Tournament* tournament);
		Tournaments::Model::Round* GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int roundId);
		bool IsRoundSensitive();
	};
}