#include "SeededCup.h"
#include "../Fixtures/RoundRobinGenerator.h"
#include "../MatchResolvers/StandardMatchResolver.h"

namespace Experiments {

	int sortPlayersSeed(const PlayerResult* arg1, const PlayerResult* arg2)
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

	Fixtures::IFixtureGenerator* SeededCup::GetFixtureGenerator(int index) {
		return this->initialFixtureGenerator;
	}

	Fixtures::IFixtureGenerator* SeededCup::GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data) {
		return this->initialFixtureGenerator;
	}

	Tournaments::Model::Tournament* SeededCup::PrepareTestData(int index) {
		auto data = tournamentGenerator->Generate();
		return data;
	}

	MatchResolvers::IMatchResolver* SeededCup::GetMatchResolver(int index) {
		return new MatchResolvers::StandardMatchResolver();
	}


	void SeededCup::CalculateResults(Tournaments::Model::Tournament* data) {
		auto players = data->GetPlayers();
		int playersCount = players.size();
		for (int i = 0; i < playersCount; i++) {
			data->results[i].Draws = 0;
			data->results[i].Wins = 0;
			data->results[i].Loses = 0;
			data->results[i].ReferencedPlayer = players[i];
		}

		auto rounds = data->GetRounds();

		for (int i = 0; i < rounds.size(); i++) {
			Tournaments::Model::Round* round = rounds[i];

			int matchCount = round->Matches->size();
			for (int m = 0; m < matchCount; m++) {
				Tournaments::Model::Match* match = round->Matches->at(m);

				int host;
				int away;
				for (int p = 0; p < playersCount; p++) {
					if (match->Host == data->results[p].ReferencedPlayer) {
						host = p;
					}
					if (match->Away == data->results[p].ReferencedPlayer) {
						away = p;
					}
				}

				switch (match->AwayResult) {
				case (Result::Draw):
				{
					data->results[away].Draws = data->results[away].Draws + 1;
					break;
				}
				case (Result::Lose):
				{
					data->results[away].Loses = data->results[away].Loses + 1;
					break;
				}
				case (Result::Win):
				{
					data->results[away].Wins = data->results[away].Wins + 1;
					break;
				}
				}

				switch (match->HostResult) {
				case (Result::Draw):
				{
					data->results[host].Draws = data->results[host].Draws + 1;
					break;
				}
				case (Result::Lose):
				{
					data->results[host].Loses = data->results[host].Loses + 1;
					break;
				}
				case (Result::Win):
				{
					data->results[host].Wins = data->results[host].Wins + 1;
					break;
				}
				}
			}
		}

		for (int p = 0; p < playersCount; p++) {
			data->results[p].Points = data->tournamentConfiguration.PointsPerWin * data->results[p].Wins +
				data->tournamentConfiguration.PointsPerDraw * data->results[p].Draws +
				data->tournamentConfiguration.PointsPerLose * data->results[p].Loses;
		}


		qsort(data->results, playersCount, sizeof(PlayerResult), (int(*)(const void*, const void*)) sortPlayersSeed);

		int place = 1;
		int realPlace = 1;
		int points = data->results[0].Points;
		int wins = data->results[0].Wins;
		vector<PlayerResult> playersInPlace;
		data->results[0].Rank = 1;

		for (int p = 0; p < playersCount; p++) {
			auto currentPlayer = data->results[p];
			if (currentPlayer.Points != points || currentPlayer.Wins != points) {
				for each (auto playerToCalculate in playersInPlace)
				{
					data->results[playerToCalculate.ReferencedPlayer->Index()].Rank = place;
					data->results[playerToCalculate.ReferencedPlayer->Index()].MaxRank = realPlace - 1;
				}
				playersInPlace.clear();

				points = currentPlayer.Points;
				wins = currentPlayer.Wins;
				place = realPlace;
				currentPlayer.Rank = place;
				currentPlayer.MaxRank = realPlace;
				playersInPlace.push_back(currentPlayer);
			}
			else {
				currentPlayer.Rank = place;
				playersInPlace.push_back(currentPlayer);
			}
			realPlace++;
		}

		for each (auto playerToCalculate in playersInPlace)
		{
			data->results[playerToCalculate.ReferencedPlayer->Index()].Rank = place;
			data->results[playerToCalculate.ReferencedPlayer->Index()].MaxRank = realPlace - 1;
		}
	}
}