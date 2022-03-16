#pragma once
#include "Match.h"
#include <vector>

namespace Tournaments {
	namespace Model {
		class Round {
		private:
			int _id;
		public:
			Round(int id) {
				Matches = new std::vector<Match*>();
				_id = id;
			}

			~Round() {
				for each (auto match in *Matches)
				{
					delete match;
				}
				delete Matches;
			}

			int GetId() {
				return _id;
			}

			std::vector<Match*>* Matches;

			void Revert() {
				for (int m = 0; m < Matches->size(); m++) {
					Match* match = Matches->at(m);

					Player* tmp = match->Host;
					match->Host = match->Away;
					match->Away = tmp;
				}
			}
		};
	}
}