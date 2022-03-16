#pragma once
#include "IPowerResolver.h"

namespace Powers {
	class ConstantPower : public IPowerResolver {
	private:
		double _power;

	public:
		ConstantPower(double power) {
			_power = power;
		}
		double GetPower() {
			return _power;
		}
	};
}