
#pragma once
#include <vector>
#include "Experiment.h"
#include "../Data/Tournament.h"
#include "../Fixtures/IFixturesGenerator.h"
#include "../MatchResolvers/IMatchResolver.h"
#include "../Metrics/FinalStandingsProcessor.h"
#include "../Metrics/OrderMetricProcessor.h"
#include "../Metrics/MatchCountProcessor.h"

namespace Experiments {

	class League : public IExperiment {
	public:
		League() : IExperiment() {
			ExperimentName = "league";
			this->metrics.push_back(new Metrics::MatchCountProcessor());
			this->metrics.push_back(new Metrics::FinalStandingsProcessor(ExperimentName, 128));

			this->tournamentGenerator = new Generators::TournamentGenerator();
		}

		~League() {
			IExperiment::~IExperiment();
			delete tournamentGenerator;
		}

		Tournaments::Model::Tournament* PrepareTestData(int index);

		Fixtures::IFixtureGenerator* GetFixtureGenerator(int index);

		MatchResolvers::IMatchResolver* GetMatchResolver(int index);
	};
}