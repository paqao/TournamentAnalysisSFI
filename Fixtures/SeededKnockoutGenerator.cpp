#include "SeededKnockoutGenerator.h"
#include "../Data/Player.h"
#include "../Data/Round.h"
#include "../Data/EmptyPlayer.h"

namespace Fixtures {

	bool SeededKnockoutGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* SeededKnockoutGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		if (round == 0) {
			std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
			int matchId = 0;
			auto roundItem = tournament->GetRounds()[0];

			int placedPlayers = 1;
			int playerMatches[MAX];
			int roundSize = players.size() / 2;
			int playerId = 1;
			int matchDistance = roundSize - 1;

			auto player = players[0];
			players.erase(players.begin()); 
			auto match = roundItem->Matches->at(0);
			playerMatches[0] = 0;
			match->Host = player;
			int roundPlayer = 0;
			int previousRoundPlaced = 1;

			while (placedPlayers < this->playersCount) {
				auto player = players[0];
				players.erase(players.begin());

				int rivalMatchId = playerMatches[previousRoundPlaced-roundPlayer-1];
				auto rivalMatch = roundItem->Matches->at(rivalMatchId);
				if (rivalMatch->Host != NULL) {
					int mineMatchId = rivalMatchId + matchDistance;
					auto mineMatch = roundItem->Matches->at(mineMatchId);
					mineMatch->Away = player;
					playerMatches[placedPlayers] = mineMatchId;
				}
				else {
					int mineMatchId = rivalMatchId - matchDistance;
					auto mineMatch = roundItem->Matches->at(mineMatchId);
					mineMatch->Host = player;
					playerMatches[placedPlayers] = mineMatchId;
				}

				roundPlayer++;
				placedPlayers++;
				playerId--;

				if (playerId == 0) {
					roundPlayer = 0;
					playerId = placedPlayers;
					roundSize = roundSize / 2;
					matchDistance = roundSize - 1;
					previousRoundPlaced = placedPlayers;
				}
			}

			while (players.size() > 0) {
				int index = rand() % players.size();
				auto player = players[index];
				players.erase(players.begin() + index);

				bool found = false;
				while(!found) {
					auto match = roundItem->Matches->at(matchId);
					if (match->Host == NULL) {
						match->Host = player;
						found = true;
					}
					else if (match->Away == NULL) {
						match->Away = player;
						found = true;
						matchId++;
					}
					else {
						matchId++;
					}
				}
			}

			return tournament->GetRounds()[round];
		}
		else {
			int matchId = 0;
			auto previousRound = tournament->GetRounds()[round - 1];
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

	void SeededKnockoutGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
		std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		int count = tournament->tournamentConfiguration.expectedRounds;
		int matchesInRound = (players.size() + 1) / 2;
		for (int r = 0; r < count; r++) {
			Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);

			for (int i = 0; i < matchesInRound; i++) {
				Tournaments::Model::Match* match = new Tournaments::Model::Match();
				round->Matches->push_back(match);
			}
			matchesInRound /= 2;
			tournament->AddRound(round);
		}
	}
}