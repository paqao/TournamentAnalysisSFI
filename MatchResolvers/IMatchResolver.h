#pragma once
#include "../Powers/IPowerResolver.h"
#include "../Data/MatchResult.h"
#include "../Data/Match.h"

namespace MatchResolvers {
	class IMatchResolver {
	public:
		virtual Tournaments::Model::MatchResult SolveMatch(Tournaments::Model::Match* match, Powers::IPowerResolver* host, Powers::IPowerResolver* guest) = 0;

		virtual void SolveTournament(Tournaments::Model::Tournament* data) = 0;

		virtual void SolveRound(Tournaments::Model::Round* round) = 0;
	};
}
