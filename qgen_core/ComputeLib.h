#pragma once

#include "BaseWrapper.h"

using namespace std;
#include <functional>

namespace qg {
	
	// constant stepper model
	struct SpreaderInput { int count; float radius; int radial_index; int step_index; float step_delta;  int direction; };

	typedef function<float(SpreaderInput)> ScaleVariatorLambda;

	vector<glm::vec3> positionRadialSpreader(const SpreaderInput p, const ScaleVariatorLambda scale_variator_lambda);
}