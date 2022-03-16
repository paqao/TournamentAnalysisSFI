#include "RandomNGenerator.h"
#include "../Data/Player.h"
#include "../Data/Round.h"
#include "../Data/EmptyPlayer.h"

namespace Fixtures {

	bool RandomNGenerator::IsRoundSensitive() {
		return true;
	}

	Tournaments::Model::Round* RandomNGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		int matchId = 0;
		auto roundItem = tournament->GetRounds()[round];
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

		return roundItem;
	}

	void RandomNGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
		std::vector<Tournaments::Model::Player*>* players = new std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		int count = ceil(log2(tournament->GetPlayers().size()));
		int matchesInRound = tournament->GetPlayers().size() / 2; 
		for (int r = 0; r < count; r++) {
			Tournaments::Model::Round* round = new Tournaments::Model::Round(r + 1);

			for (int i = 0; i < matchesInRound; i++) {
				Tournaments::Model::Match* match = new Tournaments::Model::Match();
				round->Matches->push_back(match);
			}

			tournament->AddRound(round);
		}
		delete players;
	}
}