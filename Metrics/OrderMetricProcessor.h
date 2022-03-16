
#pragma once

#include <iostream>
#include "IMetricProcessor.h"
#include "../Data/Tournament.h"

using namespace std;
using namespace Tournaments::Model;

namespace Metrics {
	class OrderMetricProcessor : public IMetricProcessor<Tournament> {
	public:
		OrderMetricProcessor() {

		}

		void AddMetric(Tournament* data) {
			cout << "metryka" << data->Name << endl;
			std::vector<Tournaments::Model::Player*> players = data->GetPlayers();
			std::vector<Tournaments::Model::Round*> rounds= data->GetRounds();
			for (int i = 0; i < players.size(); i++) {
				Tournaments::Model::Player* player = players[i];
				if (player->isValid()) {
					cout << "gracz " << player->Index() << " moc:" << player->GetPower() << endl;
				}
			}

			cout << endl;

			for (int i = 0; i < rounds.size(); i++) {
				Tournaments::Model::Round* round = rounds[i];
				cout << "runda " << round->GetId() << endl;

				int matchCount = round->Matches->size();
				for (int m = 0; m < matchCount; m++) {
					Tournaments::Model::Match* match = round->Matches->at(m);

					if (match->Host->isValid()) {
						cout << "gracz " << match->Host->Index() << " (" << match->Host->GetPower() << " )";
					}
					cout << " vs ";

					if (match->Away->isValid()) {
						cout << "gracz " << match->Away->Index() << " (" << match->Away->GetPower() << " )";
					}
					cout << endl;
				}

				cout << endl;
			}
		}
	};
}