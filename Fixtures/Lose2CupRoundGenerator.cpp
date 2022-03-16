#include "Lose2CupRoundGenerator.h"
#include "../Data/Player.h"
#include "../Data/Round.h"
#include "../Data/EmptyPlayer.h"

namespace Fixtures {

	bool Lose2CupRoundGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* Lose2CupRoundGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		return NULL;
	}

	void Lose2CupRoundGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
		int matches = (tournament->GetPlayers().size() + 1) / 2;
		int it = 2;

		int r = 0;
		while (matches >= 1) {

			Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);

			for (int i = 0; i < matches; i++) {
				Tournaments::Model::Match* match = new Tournaments::Model::Match();
				round->Matches->push_back(match);
			}

			it++;
			if (it > 2) {
				matches = matches / 2;
				it = 0;
			}
			tournament->AddRound(round);
			r++;
		}


		Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);
		Tournaments::Model::Match* match = new Tournaments::Model::Match();
		round->Matches->push_back(match);
		tournament->AddRound(round);
	}
}