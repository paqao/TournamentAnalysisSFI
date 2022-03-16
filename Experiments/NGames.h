
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
#include "../Fixtures/RandomNGenerator.h"

namespace Experiments {

	class NGames : public IExperiment {
	private:
		Fixtures::IFixtureGenerator* generator;

	public:
		NGames(int totalPlayers, int countLimit) : IExperiment() {
			//this->metrics.push_back(new Metrics::MatchCountProcessor());
			ExperimentName = "nround_from_" + std::to_string(totalPlayers) + "_limit_" + std::to_string(countLimit);
			this->metrics.push_back(new Metrics::FinalStandingsProcessor(this->ExperimentName, countLimit));

			this->tournamentGenerator = new Generators::TournamentGenerator();
			this->tournamentGenerator->SetPlayers(totalPlayers);
			generator = new Fixtures::RandomNGenerator();
			//	this->fixtureGenerator = new Fixtures::KnockoutGenerator();
		}

		~NGames() {
			if (this->tournamentGenerator != NULL) {
				delete this->tournamentGenerator;
				this->tournamentGenerator = NULL;
			}
		}

		Tournaments::Model::Tournament* PrepareTestData(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data);

		MatchResolvers::IMatchResolver* GetMatchResolver(int index);

		void CalculateResults(Tournaments::Model::Tournament* data);

		int RoundMultiplier() {
			return 1;
		}
	};
}