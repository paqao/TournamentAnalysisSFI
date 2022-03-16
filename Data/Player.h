#pragma once
#include "../Powers/IPowerResolver.h"

namespace Tournaments {
	namespace Model {
		class Player {
		private:
			Powers::IPowerResolver* _powerResolver;

			int index;
			int expectedRank;

		public:

			virtual bool isValid() {
				return true;
			}

			int Index() {
				return index;
			}

			void SetExpectedRank(int rank) {
				expectedRank = rank;
			}

			int GetExpectedRank() {
				return expectedRank;
			}

			double GetPower() {
				return _powerResolver->GetPower();
			}

			Powers::IPowerResolver* GetPowerResolver() {
				return _powerResolver;
			}

			Player(int i, Powers::IPowerResolver* powerResolver) {
				index = i;
				_powerResolver = powerResolver;
				expectedRank = 0;
			}

			~Player() {
				delete _powerResolver;
			}
		};

		struct PlayerResult {
			Player* ReferencedPlayer;
			int Wins;
			int Loses;
			int Draws;
			int Points;
			int Rank;
			int MaxRank;
		};
	}
}