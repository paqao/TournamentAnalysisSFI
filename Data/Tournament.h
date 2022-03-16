#include <string>
#include <vector>
#include "Player.h"
#include "Round.h"
#include "TournamentConfig.h"
#include <cmath>

#pragma once

const int MAX = 1024;

namespace Tournaments {
	namespace Model {
		class Tournament {
		private:
			std::vector<Player*> _players;
			std::vector<Round*> _rounds;

		public:
			Tournaments::Model::TournamentConfig tournamentConfiguration;
			std::string Name;
			std::vector<Player*> GetPlayers() {
				return _players;
			}
			PlayerResult results[MAX];

			Tournament(std::string name, Tournaments::Model::TournamentConfig config) {
				Name = name;
				tournamentConfiguration = config;
			}

			~Tournament() {
				for each (auto player in _players)
				{
					delete player;
				}
				for each (auto round in _rounds)
				{
					delete round;
				}
			}

			void AddPlayer(Player* player) {
				_players.push_back(player);
			}

			void AddRound(Round* round) {
				_rounds.push_back(round);
			}

			std::vector<Round*> GetRounds() {
				return _rounds;
			}

		};
	}
}