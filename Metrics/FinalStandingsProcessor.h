
#pragma once

#include <iostream>
#include "IMetricProcessor.h"
#include "../Data/Tournament.h"
#include <ctime>
#include <fstream>

using namespace std;
using namespace Tournaments::Model;

namespace Metrics {
	class FinalStandingsProcessor : public IMetricProcessor<Tournament> {
	
	private:
		std::fstream fileStream;
		int threshold;

	public:
		FinalStandingsProcessor(std::string experimentName, int threshold_) {
			time_t now = time(0);

			// convert now to string form
			char* dt = ctime(&now);
			threshold = threshold_;

			fileStream.open("standings_" + experimentName + ".csv", ios::out);
		}

		~FinalStandingsProcessor() {
			fileStream.close();
		}

		void AddMetric(Tournament* data);

		void SetThreshold(int threshold_) {
			threshold = threshold_;
		}
	};
}