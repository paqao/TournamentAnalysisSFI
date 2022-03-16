#pragma once
#include "Player.h"
#include "MatchResult.h"

namespace Tournaments {
	namespace Model {
		class Match {
		public:
			Player* Host;
			Player* Away;
			Tournaments::Model::Result HostResult;
			Tournaments::Model::Result AwayResult;

			bool isEmpty() {
				return !Host->isValid() || !Away->isValid();
			}

			~Match() {
				Host = NULL;
				Away = NULL;
			}

			Player* Winner() {
				if (this->HostResult == Result::Win) {
					return Host;
				}
				if (this->AwayResult == Result::Win) {
					return Away;
				}
				return NULL;
			}

			Player* Loser() {
				if (this->HostResult == Result::Win) {
					return Away;
				}
				if (this->AwayResult == Result::Win) {
					return Host;
				}
				return NULL;
			}
		};
	}
}