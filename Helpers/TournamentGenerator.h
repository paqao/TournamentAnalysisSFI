#include "PlayerGenerator.h"
#include "../Data/Tournament.h"
#include "../Data/Player.h"
#include "../Powers/IPowerResolver.h"
#include "../Powers/ConstantPower.h"
#include "../Data/TournamentConfig.h"

#pragma once
namespace Generators {
	class TournamentGenerator {
	private:
		int playersCount = 0;

	public:
		TournamentGenerator() {
		}

		~TournamentGenerator() {

		}

		Tournaments::Model::Tournament* Generate() {
			Tournaments::Model::TournamentConfig* config = new Tournaments::Model::TournamentConfig();
			config->PointsPerWin = 1.0f;
			config->PointsPerLose = 0.0f;
			config->PointsPerDraw = 0.5f;
			config->expectedRounds = (int) log2(playersCount);

			Tournaments::Model::Tournament* tournament = new Tournaments::Model::Tournament("test", *config);
			for (int i = 0; i < playersCount; i++) {
				Powers::ConstantPower* tmpPower = new Powers::ConstantPower(2000 - i * 10.0f);

				Tournaments::Model::Player* player = new Tournaments::Model::Player(i, tmpPower);
				player->SetExpectedRank(i + 1);
				tournament->AddPlayer(player);
			}
			
			return tournament;
		}

		void SetPlayers(int count) {
			this->playersCount = count;
		}
	};
}
