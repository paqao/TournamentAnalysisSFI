#pragma once
namespace Tournaments {
	namespace Model {

		enum Result {
			NotPlayed = 0,
			Win = 1,
			Lose = 2,
			Draw = 3
		};

		class MatchResult {
		public:
			double ScoreHome;
			double ScoreAway;
			Result HomeResult;
			Result AwayResult;

			bool empty;
		};

	
	}
}