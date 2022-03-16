#include "SwissGenerator.h"
#include "../../Data/Player.h"
#include "../../Data/Round.h"
#include "../../Data/EmptyPlayer.h"
#include<cstdlib>
#include<queue>
#include<iostream>

using namespace std;

namespace Fixtures {
	struct Matching {
		int HomeId;
		int AwayId;
	};
	struct SwissEntry {
		Tournaments::Model::Player* ReferencedPlayer;
		int Wins;
		int Loses;
		int Draws;
		double Points;
		int Rank;
		int MaxRank;
		int Home;
		int Away;
		int ColorStreak;
		int ColorStreakCount;
		bool CantHome;
		bool CantAway;
		int Color;
		int PreferedColor;
		int Rivals[40];
	};

	int swissEntrySortPlayers(const SwissEntry* arg1, const SwissEntry* arg2)
	{
		if (arg1->Points > arg2->Points)
			return -1;

		if (arg1->Points < arg2->Points)
			return 1;

		if (arg1->Wins > arg2->Wins)
			return -1;

		if (arg1->Wins < arg2->Wins)
			return 1;

		double power1 = arg1->ReferencedPlayer->GetPower();
		double power2 = arg2->ReferencedPlayer->GetPower();
		if (power1 > power2)
			return -1;

		if (power2 > power1)
			return 1;

		return 0;
	}

	bool SwissGenerator::IsRoundSensitive() {
		return true;
	}

	int CanCompete(SwissEntry player1, SwissEntry player2) {
		
		if ((player1.CantHome || player2.CantAway) && (player1.CantAway || player2.CantHome))
			return 0;

		if (player2.PreferedColor == 2 && !player1.CantAway && !player2.CantHome) {
			return 2;
		}

		if (player2.PreferedColor == 1 && !player1.CantHome && !player2.CantAway) {
			return 1;
		}

		if (!player1.CantAway && !player2.CantHome) {
			return 2;
		}

		if (!player1.CantHome && !player2.CantAway) {
			return 1;
		}

		return 0;
	}

	Tournaments::Model::Round* SwissGenerator::GenerateFixturesForRound(Tournaments::Model::Tournament* tournament, int round) {
		std::vector<Tournaments::Model::Player*> players = std::vector<Tournaments::Model::Player*>(tournament->GetPlayers());
		SwissEntry entries[MAX];

		int playersCount = players.size();
		for (int i = 0; i < playersCount; i++) {
			entries[i].Draws = 0;
			entries[i].Wins = 0;
			entries[i].Loses = 0;
			entries[i].ReferencedPlayer = players[i];
			entries[i].Home = 0;
			entries[i].Away = 0;
			entries[i].PreferedColor = 0;
			entries[i].CantHome = false;
			entries[i].CantAway = false;
			entries[i].Color = 0;
		}

		auto rounds = tournament->GetRounds();

		for (int i = 0; i < rounds.size(); i++) {
			Tournaments::Model::Round* round = rounds[i];

			int matchCount = round->Matches->size();
			for (int m = 0; m < matchCount; m++) {
				Tournaments::Model::Match* match = round->Matches->at(m);

				int host = 0;
				int away = 0;
				for (int p = 0; p < playersCount; p++) {
					if (match->Host == entries[p].ReferencedPlayer) {
						host = p;
						entries[p].Home += 1;
						if (entries[p].ColorStreak == 1) {
							entries[p].ColorStreak += 1;
						}
						else {
							entries[p].ColorStreak = 1;
							entries[p].ColorStreakCount = 1;
						}
					}
					if (match->Away == entries[p].ReferencedPlayer) {
						away = p;
						entries[p].Away += 1;
						if (entries[p].ColorStreak == 2) {
							entries[p].ColorStreak += 1;
						}
						else {
							entries[p].ColorStreak = 2;
							entries[p].ColorStreakCount = 1;
						}
					}
				}

				entries[away].Rivals[i] = host;
				entries[host].Rivals[i] = away;
				switch (match->AwayResult) {
				case (Tournaments::Model::Result::Draw):
				{
					entries[away].Draws = entries[away].Draws + 1;
					break;
				}
				case (Tournaments::Model::Result::Lose):
				{
					entries[away].Loses = entries[away].Loses + 1;
					break;
				}
				case (Tournaments::Model::Result::Win):
				{
					entries[away].Wins = entries[away].Wins + 1;
					break;
				}
				}

				switch (match->HostResult) {
				case (Tournaments::Model::Result::Draw):
				{
					entries[host].Draws = entries[host].Draws + 1;
					break;
				}
				case (Tournaments::Model::Result::Lose):
				{
					entries[host].Loses = entries[host].Loses + 1;
					break;
				}
				case (Tournaments::Model::Result::Win):
				{
					entries[host].Wins = entries[host].Wins + 1;
					break;
				}
				}
			}
		}

		for (int p = 0; p < playersCount; p++) {
			entries[p].Points = tournament->tournamentConfiguration.PointsPerWin * entries[p].Wins +
				tournament->tournamentConfiguration.PointsPerDraw * entries[p].Draws +
				tournament->tournamentConfiguration.PointsPerLose * entries[p].Loses;
		}

		qsort(entries, playersCount, sizeof(SwissEntry), (int(*)(const void*, const void*)) swissEntrySortPlayers);

		int left = playersCount;
		int black = 0;
		int white = 0;

		for (int i = 0; i < playersCount; i++) {
			if (entries[i].Home == entries[i].Away + 2) {
				entries[i].CantHome = true;
				entries[i].Color = 2;
				black++;
				left--;
				entries[i].PreferedColor = 2;
			}
			else if (entries[i].Away == entries[i].Home + 2) {
				entries[i].CantAway = true;
				entries[i].PreferedColor = 1;
				entries[i].Color = 1;
				white++;
				left--;
			}
			else if (entries[i].ColorStreakCount >= this->nAllowedRespectiveColors) {
				if (entries[i].ColorStreak == 1) {
					entries[i].CantHome = true;
					entries[i].PreferedColor = 2;
				}
				else {
					entries[i].CantAway = true;
					entries[i].PreferedColor = 1;
				}
			}
			else if (entries[i].Home > entries[i].Away) {
				entries[i].PreferedColor = 2;
			}
			else if (entries[i].Away > entries[i].Home) {
				entries[i].PreferedColor = 1;
			}
			else {
				if (entries[i].ColorStreak == 1) {
					entries[i].PreferedColor = 2;
				}
				else {
					entries[i].PreferedColor = 1;
				}
			}
		}

		int half = playersCount / 2;
		vector<Matching> rivalIds;
		bool foundSolution = false;
		vector<int> indices;
		vector<bool> used;
		vector<bool> host;
		for (int i = 0; i < half; i++) {
			Matching match;
			rivalIds.push_back(match);
		}
		for (int i = 0; i < playersCount; i++) {
			indices.push_back(i + 1);
			used.push_back(false);
			host.push_back(false);
		}
		while (!foundSolution) {
			for (int i = 0; i < playersCount; i++) {
				used[i] = false;
				host[i] = false;
			}
			int pairings = 0;
			int usedPlayers = 0;
			int match = 0;

			while (pairings != half) {
				int firstIndex = -1;
				
				for (int i = 0; i < playersCount; i++) {
					if (!used[i]) {
						host[i] = true;
						used[i] = true;
						firstIndex = i;
						usedPlayers++;
						break;
					}
				}
				int checkPlayer = indices[firstIndex];
				for (int i = checkPlayer; i < playersCount; i++) {
					if (used[i])
						continue;

					bool alreadyMet = false;
					for (int j = 0; j < round; j++) {
						if (entries[i].Rivals[j] == entries[firstIndex].ReferencedPlayer->Index()) {
							alreadyMet = true;
							break;
						}
					}
					if (alreadyMet)
						continue;

					int result = CanCompete(entries[i], entries[firstIndex]);
					if (result > 0) {
						used[i] = true;
						indices[firstIndex] = i;
						usedPlayers++;
						if (result == 2) {
							rivalIds[match].HomeId = firstIndex;
							rivalIds[match].AwayId = i;
						}
						else {
							rivalIds[match].HomeId = i;
							rivalIds[match].AwayId = firstIndex;
						}
						match++;
						break;
					}
				}
				pairings++;
			}

			if (usedPlayers == playersCount) {
				foundSolution = true;
				break;
			}

			for (int i = playersCount - 1; i >= 0; i--) {
				std::cout << i << std::endl;
				if (host[i]) {
					indices[i] = indices[i] + 1;
					if (indices[i] > playersCount - 1) {
						indices[i] = i + 1;
						continue;
					}
					break;
				}
			}
		}
		
		
		auto roundItem = tournament->GetRounds()[round];

		for (int i = 0; i < half; i++) {
			auto matching = rivalIds[i];
			auto match = roundItem->Matches->at(i);

			match->Host = entries[matching.HomeId].ReferencedPlayer;
			match->Away = entries[matching.AwayId].ReferencedPlayer;
		}

		return roundItem;
	}

	void SwissGenerator::GenerateFixtures(Tournaments::Model::Tournament* tournament) {
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