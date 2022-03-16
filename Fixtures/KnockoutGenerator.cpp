#include "KnockoutGenerator.h"
#include "../Data/Player.h"
#include "../Data/Round.h"
#include "../Data/EmptyPlayer.h"

namespace Fixtures {

	bool KnockoutGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* KnockoutGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		if (round == 0) {
			std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
			int matchId = 0;
			auto roundItem = tournament->GetRounds()[0];
			while (players.size() > 0) {
				auto match = roundItem->Matches->at(matchId);
				int index = rand() % players.size();
				match->Host = players[index];
				players.erase(players.begin() + index);
				index = rand() % players.size();
				match->Away = players[index];
				players.erase(players.begin() + index);
				matchId++;
			}

			return tournament->GetRounds()[round];
		}
		else {
			int matchId = 0;
			auto previousRound = tournament->GetRounds()[round-1];
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
	}

	void KnockoutGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
		std::vector<Tournaments::Model::Player*>* players = new std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		int count = tournament->tournamentConfiguration.expectedRounds;
		int matchesInRound = (players->size() + 1) / 2;
		for (int r = 0; r < count; r++) {
			Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);

			for (int i = 0; i < matchesInRound; i++) {
				Tournaments::Model::Match* match = new Tournaments::Model::Match();
				round->Matches->push_back(match);
			}
			matchesInRound /= 2;
			tournament->AddRound(round);
		}
		delete players;
	}
}