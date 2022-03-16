#pragma once
#include "IFixturesGenerator.h"
#include "../Data/Tournament.h"

namespace Fixtures {
	class SeededKnockoutGenerator : public IFixtureGenerator {
	private:
		int playersCount;
	public:
		SeededKnockoutGenerator(int playersCount_) {
			playersCount = playersCount_;
		}
		void GenerateFixtures(Tournaments::Model::Tournament* tournament);
		Tournaments::Model::Round* GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int roundId);
		bool IsRoundSensitive();
	};
}