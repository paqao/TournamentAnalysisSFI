#include "SwissFirstRound.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"

namespace Fixtures {

	bool SwissFirstRound::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* SwissFirstRound::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		int matchId = 0;
		bool reversed = rand() % 2 == 0;
		int secondHalf = matchId + tournament->GetPlayers().size() / 2;

		auto roundItem = tournament->GetRounds()[round];

		while (matchId < roundItem->Matches->size()) {
			auto match = roundItem->Matches->at(matchId);

			auto beter = tournament->GetPlayers()[matchId];
			auto worse = tournament->GetPlayers()[secondHalf];

			if (reversed) {
				match->Host = worse;
				match->Away = beter;
			}
			else {
				match->Host = beter;
				match->Away = worse;
			}

			reversed = !reversed;
			
			matchId++;
			secondHalf++;
		}

		return roundItem;
	}

	void SwissFirstRound::GenerateFixtures(Tournaments::Model::Tournament* tournament) {

	}
}