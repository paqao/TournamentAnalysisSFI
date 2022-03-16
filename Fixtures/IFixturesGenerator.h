#pragma once
#include "../Data/Tournament.h"

namespace Fixtures {
	class IFixtureGenerator {
	public:
		virtual void GenerateFixtures(Tournaments::Model::Tournament* tournament) = 0;
		virtual Tournaments::Model::Round* GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) = 0;
		virtual bool IsRoundSensitive() = 0;
	};
}