
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
#include "../Fixtures/SwissSystem/SwissFirstRound.h"
#include "../Fixtures/SwissSystem/SwissGenerator.h"

namespace Experiments {

	class Swiss : public IExperiment {
	private:
		Fixtures::IFixtureGenerator* generator;
		Fixtures::IFixtureGenerator* firstRound;
		Fixtures::IFixtureGenerator* lastRound;

	public:
		Swiss(int totalPlayers, int countLimit) : IExperiment() {
			this->metrics.push_back(new Metrics::MatchCountProcessor());
			ExperimentName = "swiss_from_" + std::to_string(totalPlayers) + "_limit_" + std::to_string(countLimit);
			this->metrics.push_back(new Metrics::FinalStandingsProcessor(this->ExperimentName, countLimit));

			this->tournamentGenerator = new Generators::TournamentGenerator();
			this->tournamentGenerator->SetPlayers(totalPlayers);
			generator = new Fixtures::SwissGenerator(2);
			firstRound = new Fixtures::SwissFirstRound();
			lastRound = new Fixtures::SwissGenerator(3);
			repeatCount = 1;
			//	this->fixtureGenerator = new Fixtures::KnockoutGenerator();
		}

		~Swiss() {
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