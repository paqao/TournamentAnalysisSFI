#pragma once
#include "IMatchResolver.h"

namespace MatchResolvers {
	class StandardMatchResolver : public IMatchResolver {
	public:
		StandardMatchResolver() {

		}

		Tournaments::Model::MatchResult SolveMatch(Tournaments::Model::Match* match, Powers::IPowerResolver* host, Powers::IPowerResolver* guest) {
			Tournaments::Model::MatchResult* matchResult = new Tournaments::Model::MatchResult();

			if (match->isEmpty()) {
				matchResult->empty = true;
				if (match->Away->isValid()) {
					matchResult->AwayResult = Tournaments::Model::Win;
				}
				else {
					matchResult->HomeResult = Tournaments::Model::Win;
				}
				return *matchResult;
			}

			double powerHome = host->GetPower();
			double powerGuest = guest->GetPower();

			double result = powerHome - powerGuest;
			if (result == 0) {
				matchResult->ScoreAway = 0.5f;
				matchResult->ScoreHome = 0.5f;
				matchResult->AwayResult = Tournaments::Model::Draw;
				matchResult->HomeResult = Tournaments::Model::Draw;
			}
			else if (result > 0) {
				matchResult->ScoreHome = 1.0f;
				matchResult->ScoreAway = 0.0f;
				matchResult->AwayResult = Tournaments::Model::Lose;
				matchResult->HomeResult = Tournaments::Model::Win;
			}
			else {
				matchResult->ScoreAway = 1.0f;
				matchResult->ScoreHome = 0.0f;
				matchResult->AwayResult = Tournaments::Model::Win;
				matchResult->HomeResult = Tournaments::Model::Lose;
			}

			return *matchResult;
		}

		void SolveTournament(Tournaments::Model::Tournament* data) {
			auto rounds = data->GetRounds();
			for (int r = 0; r < rounds.size(); r++) {
				auto round = rounds[r];
				SolveRound(round);
			}
		}

		void SolveRound(Tournaments::Model::Round* round) {
			auto matches = round->Matches;

			for (int m = 0; m < matches->size(); m++) {
				auto match = matches->at(m);

				auto result = SolveMatch(match, match->Host->GetPowerResolver(), match->Away->GetPowerResolver());
				match->AwayResult = result.AwayResult;
				match->HostResult = result.HomeResult;
			}
		}
	};
}
