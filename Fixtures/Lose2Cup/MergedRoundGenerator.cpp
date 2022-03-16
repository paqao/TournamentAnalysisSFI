#include "MergedRoundGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool MergedRoundGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* MergedRoundGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		Tournaments::Model::Round* losersPar = tournament->GetRounds()[round - 2];
		Tournaments::Model::Round* winersPar = tournament->GetRounds()[round - 1];
		bool reversed = false;
		if (round % 2 == 0) {
			reversed = true;
		}

		auto roundItem = tournament->GetRounds()[round];

		int allMatches = roundItem->Matches->size();
		while (matchId < allMatches) {
			auto match = roundItem->Matches->at(matchId);

			Tournaments::Model::Match* loserMatch = NULL;
			if (reversed) {
				loserMatch = losersPar->Matches->at(allMatches-matchId-1);
			}
			else {
				loserMatch = losersPar->Matches->at(matchId);
			}
			auto winer = winersPar->Matches->at(matchId);

			if (reversed) {
				match->Host = loserMatch->Loser();
				match->Away = winer->Winner();
			}
			else {

				match->Host = winer->Winner();
				match->Away = loserMatch->Loser();
			}
			matchId++;
		}

		return roundItem;
	}

	void MergedRoundGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {

	}
}