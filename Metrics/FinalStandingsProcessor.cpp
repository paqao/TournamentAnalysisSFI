#include "FinalStandingsProcessor.h"
#include <cstdlib>

namespace Metrics {
	void FinalStandingsProcessor::AddMetric(Tournament* data) {

		int playersCount = data->GetPlayers().size();
		
		double simpleSum = 0.0f;
		int points = data->results[0].Points;
		int wins = data->results[0].Wins;
		vector<PlayerResult> playersInPlace;

		for (int p = 0; p < playersCount; p++) {
			auto currentPlayer = data->results[p];
			if (currentPlayer.Rank < threshold) {
				double diff = 0.0f;
				auto expectedRank = currentPlayer.ReferencedPlayer->GetExpectedRank();
				auto rank = currentPlayer.Rank;
				auto maxRank = currentPlayer.MaxRank;
				if (expectedRank < maxRank + 1 && expectedRank >= rank) {
					diff = 0.0f;
				}
				else if (expectedRank >= maxRank) {
					diff = expectedRank - maxRank;
				}
				else if (expectedRank < rank) {
					diff = expectedRank - rank;
				}
				simpleSum += pow(abs(diff), 2);
			}
		}
		
		this->fileStream << sqrt(simpleSum / playersCount) << std::endl;
		this->fileStream.flush();
		cout << "Wyniki koncowe roznia sie o " << simpleSum << endl;
	}
}