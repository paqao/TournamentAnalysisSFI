// TournamentAnalysis.cpp : Defines the entry point for the application.
//

#include "TournamentAnalysis.h"
#include "Experiments/League.h"
#include "Experiments/Cup.h"
#include "Experiments/SeededCup.h"
#include "Experiments/Lose2Cup.h"
#include "Experiments/NGames.h"
#include "Experiments/Swiss.h"

using namespace std;
using namespace Tournaments::Model;

int main()
{
	//auto leagueExperiment = new Experiments::League();
	//leagueExperiment->RunExperiment();
	srand(time(NULL));
	
	/*auto cupExperiment = new Experiments::Cup(1024, 128);
	cupExperiment->RunExperiment();
	delete cupExperiment;*/
	/*cupExperiment = new Experiments::Cup(1024, 64);
	cupExperiment->RunExperiment();
	delete cupExperiment;
	cupExperiment = new Experiments::Cup(1024, 128);
	cupExperiment->RunExperiment();
	delete cupExperiment;
	cupExperiment = new Experiments::Cup(1024, 256);
	cupExperiment->RunExperiment();
	delete cupExperiment;
	cupExperiment = new Experiments::Cup(1024, 512);
	cupExperiment->RunExperiment();
	delete cupExperiment;*/
	//auto ngames = new Experiments::NGames(1024, 128);
	//ngames->RunExperiment();
	//delete ngames;
	auto swiss = new Experiments::Swiss(128, 128);
	swiss->RunExperiment();
	delete swiss;
	/*auto lose2CupExperiment = new Experiments::Lose2Cup(1024, 128);
	lose2CupExperiment->RunExperiment();
	delete lose2CupExperiment;
	lose2CupExperiment = new Experiments::Lose2Cup(1024, 64);
	lose2CupExperiment->RunExperiment();
	delete lose2CupExperiment;
	lose2CupExperiment = new Experiments::Lose2Cup(1024, 32);
	lose2CupExperiment->RunExperiment();
	delete lose2CupExperiment;
	lose2CupExperiment = new Experiments::Lose2Cup(1024, 16);
	lose2CupExperiment->RunExperiment();
	delete lose2CupExperiment;*/
	/*auto seededCupExperiment = new Experiments::SeededCup(128, 1024, 16);
	seededCupExperiment->RunExperiment();
	delete seededCupExperiment;*/

	return 0;
}
