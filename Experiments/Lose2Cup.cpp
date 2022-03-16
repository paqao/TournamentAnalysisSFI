#include "Lose2Cup.h"
#include "../Fixtures/RoundRobinGenerator.h"
#include "../MatchResolvers/StandardMatchResolver.h"
#include "../Fixtures/KnockoutGenerator.h"
#include "../Fixtures/Lose2Cup/WinnerLadderGenerator.h"
#include "../Fixtures/Lose2Cup/FirstLosersGenerator.h"
#include "../Fixtures/Lose2Cup/MergedRoundGenerator.h"
#include "../Fixtures/Lose2Cup/LoserLadderGenerator.h"
#include "../Fixtures/Lose2Cup/FinalMatchGenerator.h"

namespace Experiments {
	Fixtures::IFixtureGenerator* Lose2Cup::GetFixtureGenerator(int index) {
		return this->initialFixtureGenerator;
	}

	Tournaments::Model::Tournament* Lose2Cup::PrepareTestData(int index) {
		auto data = tournamentGenerator->Generate();
		return data;
	}

	MatchResolvers::IMatchResolver* Lose2Cup::GetMatchResolver(int index) {
		return new MatchResolvers::StandardMatchResolver();
	}

	void Lose2Cup::CalculateResults(Tournaments::Model::Tournament* data) {
		int roundCount = data->GetRounds().size();
		int roundId = roundCount - 2;
		auto rounds = data->GetRounds();
		int playersCount = data->GetPlayers().size();

		auto players = data->GetPlayers();
		for (int i = 0; i < playersCount; i++) {
			data->results[i].Draws = 0;
			data->results[i].Wins = 0;
			data->results[i].Loses = 0;
			data->results[i].ReferencedPlayer = players[i];
		}

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

		auto finalRound = rounds[roundCount - 1]->Matches->at(0);
		data->results[finalRound->Winner()->Index()].Rank = 1;
		data->results[finalRound->Winner()->Index()].MaxRank = 1;
		data->results[finalRound->Loser()->Index()].Rank = 2;
		data->results[finalRound->Loser()->Index()].MaxRank = 2;
		int rank = 3;
		int realRank = 3;
		while (roundId > 0) {
			
			if (roundId % 3 == 1) {
				roundId--;
				continue;
			}

			Tournaments::Model::Round* round = rounds[roundId];
			int losersCount = round->Matches->size();
			for (int m = 0; m < losersCount; m++) {
				Tournaments::Model::Match* match = round->Matches->at(m);
				auto loser = match->Loser();
				data->results[loser->Index()].Rank = rank;
				data->results[loser->Index()].MaxRank = rank + losersCount;
				realRank++;
			}
			rank = realRank;
			roundId--;
		}
	}

	Fixtures::IFixtureGenerator* Lose2Cup::GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data) {
		if (round == 0) {
			return new Fixtures::KnockoutGenerator();
		}
		if (round == 2) {
			return new Fixtures::FirstLosersGenerator();
		}
		int roundsCount = data->GetRounds().size() - 1;
		if (round == roundsCount ) {
			return new Fixtures::FinalMatchGenerator();
		}
		if (round % 3 == 2) {
			return new Fixtures::LoserLadderGenerator();
		}
		if (round % 3 == 1) {
			return new Fixtures::WinnerLadder();
		}
		if (round % 3 == 0) {
			return new Fixtures::MergedRoundGenerator();
		}
	}
}