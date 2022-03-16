# CMakeList.txt : CMake project for TournamentAnalysis, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TournamentAnalysis")

# Add source to this project's executable.
add_executable (TournamentAnalysis "TournamentAnalysis.cpp" "TournamentAnalysis.h" "Metrics/IMetricProcessor.h" "Metrics/OrderMetricProcessor.h"  "Data/Tournament.h"  "Data/Player.h" "Data/Match.h" "Helpers/PlayerGenerator.h" "Powers/IPowerResolver.h" "Powers/ConstantPower.h" "Data/Round.h" "MatchResolvers/IMatchResolver.h" "Data/MatchResult.h" "MatchResolvers/StandardMatchResolver.h" "Fixtures/IFixturesGenerator.h" "Fixtures/RoundRobinGenerator.h" "Fixtures/RoundRobinGenerator.cpp" "Metrics/FinalStandingsProcessor.h" "Metrics/FinalStandingsProcessor.cpp" "Data/EmptyPlayer.h" "Experiments/Experiment.h" "Experiments/Cup.h" "Experiments/League.h" "Experiments/League.cpp" "Metrics/MatchCountProcessor.h" "Metrics/MatchCountProcessor.cpp" "Fixtures/KnockoutGenerator.h" "Fixtures/KnockoutGenerator.cpp" "Experiments/Cup.cpp" "Experiments/SeededCup.h" "Fixtures/SeededKnockoutGenerator.h" "Experiments/SeededCup.cpp" "Fixtures/SeededKnockoutGenerator.cpp" "Experiments/Lose2Cup.h" "Experiments/Lose2Cup.cpp"  "Fixtures/Lose2CupRoundGenerator.h" "Fixtures/Lose2CupRoundGenerator.cpp" "Fixtures/Lose2Cup/WinnerLadderGenerator.h" "Fixtures/Lose2Cup/WinnerLadderGenerator.cpp" "Fixtures/Lose2Cup/FirstLosersGenerator.h" "Fixtures/Lose2Cup/FirstLosersGenerator.cpp" "Fixtures/Lose2Cup/MergedRoundGenerator.h" "Fixtures/Lose2Cup/MergedRoundGenerator.cpp" "Fixtures/Lose2Cup/LoserLadderGenerator.h" "Fixtures/Lose2Cup/LoserLadderGenerator.cpp" "Fixtures/Lose2Cup/FinalMatchGenerator.cpp" "Fixtures/Lose2Cup/FinalMatchGenerator.h" "Fixtures/RandomNGenerator.h" "Fixtures/RandomNGenerator.cpp" "Experiments/NGames.h" "Experiments/NGames.cpp" "Experiments/Swiss.h" "Experiments/Swiss.cpp" "Fixtures/SwissSystem/SwissFirstRound.cpp" "Fixtures/SwissSystem/SwissGenerator.cpp" "Fixtures/SwissSystem/SwissGenerator.h"    )

# TODO: Add tests and install targets if needed.
