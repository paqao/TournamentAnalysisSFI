#include "RoundRobinGenerator.h"
#include "../Data/Player.h"
#include "../Data/Round.h"
#include "../Data/EmptyPlayer.h"

namespace Fixtures {

	bool RoundRobinGenerator::IsRoundSensitive() {
		return false;
	}

	Tournaments::Model::Round* RoundRobinGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int roundId) {
		return tournament->GetRounds()[roundId];
	}

	void RoundRobinGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
		std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		int count = players.size();

		if (count % 2 == 1) {
			players.push_back(new Tournaments::Model::EmptyPlayer(players.size()));
			count = players.size();
		}

		int rowCount = count / 2;

		int top[MAX];
		int bottom[MAX];
		Tournaments::Model::Player* firstPlayer = players[0];
		for (int i = 1; i <= rowCount - 1; i++) {
			top[i - 1] = players[i]->Index();
		}

		int index = rowCount - 1;
		for (int i = rowCount; i <= count - 1; i++) {
			bottom[index] = players[i]->Index();
			index--;
		}

		int additionalMemory = 0;
		for (int r = 0; r < count - 1; r++) {
			Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);
			Tournaments::Model::Match* match = new Tournaments::Model::Match();
			match->Host = firstPlayer;
			match->Away = players[bottom[0]];
			round->Matches->push_back(match);
			for (int m = 0; m < rowCount - 1; m++) {
				match = new Tournaments::Model::Match();
				match->Host = players[top[m]];
				match->Away = players[bottom[m + 1]];
				round->Matches->push_back(match);
			}
			if (r % 2 == 1) {
				round->Revert();
			}
			tournament->AddRound(round);

			additionalMemory = top[rowCount - 2];
			for (int i = rowCount - 2; i > 0; i--) {
				top[i] = top[i - 1];
			}
			top[0] = bottom[0];
			for (int i = 0; i < rowCount; i++) {
				bottom[i] = bottom[i + 1];
			}
			bottom[rowCount - 1] = additionalMemory;
		}
	}
}