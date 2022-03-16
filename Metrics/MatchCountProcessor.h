
#pragma once

#include <iostream>
#include "IMetricProcessor.h"
#include "../Data/Tournament.h"

using namespace std;
using namespace Tournaments::Model;

namespace Metrics {
	class MatchCountProcessor : public IMetricProcessor<Tournament> {
	public:
		MatchCountProcessor() {

		}

		void AddMetric(Tournament* data);
	};
}