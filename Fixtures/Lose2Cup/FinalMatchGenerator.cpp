#include "FinalMatchGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool FinalMatchGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* FinalMatchGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		Tournaments::Model::Round* losersPar = tournament->GetRounds()[round - 1];
		Tournaments::Model::Round* winersPar = tournament->GetRounds()[round - 3];

		auto roundItem = tournament->GetRounds()[round];
		
		auto match = roundItem->Matches->at(matchId);

		auto homeWinner = winersPar->Matches->at(0);
		auto awayWinner = losersPar->Matches->at(0);
		match->Host = homeWinner->Winner();
		match->Away = awayWinner->Winner();

		return roundItem;
	}

	void FinalMatchGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {

	}
}