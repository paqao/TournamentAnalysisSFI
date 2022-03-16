#include "MatchCountProcessor.h"
#include <cstdlib>

namespace Metrics {
	const int MAX = 32;

	void MatchCountProcessor::AddMetric(Tournament* data) {
		int count = 0;

		auto rounds = data->GetRounds();

		for (int i = 0; i < rounds.size(); i++) {

			cout << "round " << i << endl;
			Tournaments::Model::Round* round = rounds[i];

			int matchCount = round->Matches->size();
			for (int m = 0; m < matchCount; m++) {
				Tournaments::Model::Match* match = round->Matches->at(m);

				if (!match->isEmpty()) {
					count++;
					cout << "match " << match->Host->Index() << " vs. " << match->Away->Index() << endl;
				}
			}

		}

		cout << "Wszystkich meczow jest " << count << " dla n = " << data->GetPlayers().size() << endl;
	}
}