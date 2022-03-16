#include "FirstLosersGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool FirstLosersGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* FirstLosersGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		Tournaments::Model::Round* previousRound = tournament->GetRounds()[0];

		auto roundItem = tournament->GetRounds()[round];

		while (matchId < roundItem->Matches->size()) {
			auto match = roundItem->Matches->at(matchId);

			auto homeWinner = previousRound->Matches->at(2 * matchId);
			auto awayWinner = previousRound->Matches->at(2 * matchId + 1);
			match->Host = homeWinner->Loser();
			match->Away = awayWinner->Loser();
			matchId++;
		}

		return roundItem;
	}

	void FirstLosersGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {

	}
}