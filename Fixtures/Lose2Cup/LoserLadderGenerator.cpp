#include "LoserLadderGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool LoserLadderGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* LoserLadderGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		Tournaments::Model::Round* previousRound = tournament->GetRounds()[round - 2];
		
		auto roundItem = tournament->GetRounds()[round];

		while (matchId < roundItem->Matches->size()) {
			auto match = roundItem->Matches->at(matchId);

			auto homeWinner = previousRound->Matches->at(2 * matchId);
			auto awayWinner = previousRound->Matches->at(2 * matchId + 1);
			match->Host = homeWinner->Winner();
			match->Away = awayWinner->Winner();
			matchId++;
		}

		return roundItem;
	}

	void LoserLadderGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {

	}
}