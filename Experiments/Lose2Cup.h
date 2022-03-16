
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
#include "../Fixtures/Lose2CupRoundGenerator.h"

namespace Experiments {

	class Lose2Cup : public IExperiment {
	private:
		Fixtures::IFixtureGenerator* winnerRoundGenerator;
		Fixtures::IFixtureGenerator* loserGroupGenerator;
		Fixtures::IFixtureGenerator* initialFixtureGenerator;

	public:
		Lose2Cup(int totalPlayers, int countLimit) : IExperiment() {
			//this->metrics.push_back(new Metrics::MatchCountProcessor());
			ExperimentName = "up_to_2_loses_cup_from_" + std::to_string(totalPlayers) + "_limit_" + std::to_string(countLimit);
			this->metrics.push_back(new Metrics::FinalStandingsProcessor(this->ExperimentName, countLimit));

			this->tournamentGenerator = new Generators::TournamentGenerator();
			this->tournamentGenerator->SetPlayers(totalPlayers);
			initialFixtureGenerator = new Fixtures::Lose2CupRoundGenerator();
		//	this->fixtureGenerator = new Fixtures::KnockoutGenerator();
		}

		~Lose2Cup() {
			if (this->tournamentGenerator != NULL) {
				delete this->tournamentGenerator;
				this->tournamentGenerator = NULL;
			}
		/*	if (fixtureGenerator != NULL) {
				delete fixtureGenerator;
				fixtureGenerator = NULL;
			}*/
		}

		Tournaments::Model::Tournament* PrepareTestData(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data);

		MatchResolvers::IMatchResolver* GetMatchResolver(int index);

		void CalculateResults(Tournaments::Model::Tournament* data);

		int RoundMultiplier() {
			return 2;
		}
	};
}