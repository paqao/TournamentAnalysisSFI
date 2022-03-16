
#pragma once
#include <vector>
#include "../Metrics/IMetricProcessor.h"
#include "../Helpers/PlayerGenerator.h"
#include "../Helpers/TournamentGenerator.h"
#include "../Data/Tournament.h"
#include "../Fixtures/IFixturesGenerator.h"
#include "../MatchResolvers/IMatchResolver.h"

namespace Experiments {

	class IExperiment {
	protected:
		std::vector<Metrics::IMetricProcessor<Tournaments::Model::Tournament>*> metrics;
		Generators::PlayerGenerator* playerGenerator;
		Generators::TournamentGenerator* tournamentGenerator;
		int repeatCount = 1500;
		std::string ExperimentName;

	public:
		IExperiment() {
			playerGenerator = NULL;
			tournamentGenerator = NULL;
		}

		~IExperiment() {
			if (metrics.size() > 0) {
				for each (auto metric in metrics)
				{
					delete metric;
				}
			}
		
		}

		void RunExperiment() {
			for (int c = 0; c < repeatCount; c++) {
				auto data = PrepareTestData(c);

				auto matchResolver = GetMatchResolver(c);
				auto fixtureGenenrator = GetFixtureGenerator(c);
				if (fixtureGenenrator->IsRoundSensitive()) {
					int count = 0;
					fixtureGenenrator->GenerateFixtures(data);
					while (count < data->GetRounds().size()) {
						auto roundfixtureGenerator = GetFixtureGenerator(c, count, data);
						auto round = roundfixtureGenerator->GenerateFixturesForRound(data, count);
						matchResolver->SolveRound(round);
						count++;
					}
				}
				else {
					fixtureGenenrator->GenerateFixtures(data);
					matchResolver->SolveTournament(data);
				}

				CalculateResults(data);
				for (int i = 0; i < metrics.size(); i++) {
					Metrics::IMetricProcessor<Tournaments::Model::Tournament>* processor = metrics[i];
					processor->AddMetric(data);
				}

				delete matchResolver;
				delete data;
			}
		}

		virtual Tournaments::Model::Tournament* PrepareTestData(int index) = 0;

		virtual Fixtures::IFixtureGenerator* GetFixtureGenerator(int index) = 0;

		virtual Fixtures::IFixtureGenerator* GetFixtureGenerator(int index, int round, Tournaments::Model::Tournament* data) = 0;

		virtual MatchResolvers::IMatchResolver* GetMatchResolver(int index) = 0;

		virtual int RoundMultiplier() {
			return 1;
		}

		virtual void CalculateResults(Tournaments::Model::Tournament* data) = 0;

		void RepeatFor(int count = 1) {
			repeatCount = count;
		}
	};
}