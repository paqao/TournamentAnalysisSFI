#pragma once
#include "../Powers/IPowerResolver.h"

namespace Tournaments {
	namespace Model {
		class EmptyPlayer : public Player {
		private:
			Powers::IPowerResolver* _powerResolver;

			int index;
			int expectedRank;

		public:
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

			bool isValid() {
				return false;
			}

			EmptyPlayer(int max) : Player(max, NULL) {
				expectedRank = 0;
			}
		};
	}
}