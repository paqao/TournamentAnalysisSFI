#include "League.h"
#include "../Fixtures/RoundRobinGenerator.h"
#include "../MatchResolvers/StandardMatchResolver.h"

namespace Experiments {
	Fixtures::IFixtureGenerator* League::GetFixtureGenerator(int index) {
		return new Fixtures::RoundRobinGenerator();
	}

	Tournaments::Model::Tournament* League::PrepareTestData(int index) {

		tournamentGenerator->SetPlayers(13+index);
		Tournament* data = tournamentGenerator->Generate();
		return data;
	}

	MatchResolvers::IMatchResolver* League::GetMatchResolver(int index) {
		return new MatchResolvers::StandardMatchResolver();
	}
}