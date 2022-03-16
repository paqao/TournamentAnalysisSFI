
#pragma once
namespace Metrics {

	template <class T>
	class IMetricProcessor {
	public:
		IMetricProcessor() {

		}

		virtual void AddMetric(T* inputData) = 0;
	};
}