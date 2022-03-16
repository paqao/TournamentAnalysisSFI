
#pragma once
#include <vector>
#include "Experiment.h"
#include "Experiment.h"
#include "../Data/Tournament.h"
#include "../Fixtures/IFixturesGenerator.h"
#include "../MatchResolvers/IMatchResolver.h"
#include "../Metrics/FinalStandingsProcessor.h"
#include "../Metrics/OrderMetricProcessor.h"
#include "../Metrics/MatchCountProcessor.h"
#include "../Fixtures/KnockoutGenerator.h"
#include "../Fixtures/SeededKnockoutGenerator.h"

namespace Experiments {

	class SeededCup : public IExperiment {
	private:
		Fixtures::IFixtureGenerator* fixtureGenerator;
		Fixtures::IFixtureGenerator* initialFixtureGenerator;

	public:
		SeededCup(int bestPlayersCount, int totalPlayers, int countLimit) : IExperiment() {
			//this->metrics->push_back(new Metrics::MatchCountProcessor());
			ExperimentName = "seeded_cup_" + std::to_string(bestPlayersCount) + "_from_" + std::to_string(totalPlayers) + "_limit_" + std::to_string(countLimit);
			this->metrics.push_back(new Metrics::FinalStandingsProcessor(ExperimentName, countLimit));

			this->tournamentGenerator = new Generators::TournamentGenerator();
			this->tournamentGenerator->SetPlayers(totalPlayers);
			this->fixtureGenerator = new Fixtures::KnockoutGenerator();
			this->initialFixtureGenerator = new Fixtures::SeededKnockoutGenerator(bestPlayersCount);
		}

		~SeededCup() {

			if (tournamentGenerator != NULL) {
				delete tournamentGenerator;
				tournamentGenerator = NULL;
			}
			if (fixtureGenerator != NULL) {
				delete fixtureGenerator;
				fixtureGenerator = NULL;
			}
			if (initialFixtureGenerator != NULL) {
				delete initialFixtureGenerator;
				initialFixtureGenerator = NULL;
			}
		}

		Tournaments::Model::Tournament* PrepareTestData(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index);

		MatchResolvers::IMatchResolver* GetMatchResolver(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data);

		void CalculateResults(Tournaments::Model::Tournament* data);
	};
}