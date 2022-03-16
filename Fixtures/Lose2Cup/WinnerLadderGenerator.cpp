#include "WinnerLadderGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool WinnerLadder::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* WinnerLadder::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		Tournaments::Model::Round* previousRound = NULL;
		if (round == 1) {
			previousRound = tournament->GetRounds()[0];
		}
		else{
			previousRound = tournament->GetRounds()[round - 3];
		}
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

	void WinnerLadder::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
	
	}
}