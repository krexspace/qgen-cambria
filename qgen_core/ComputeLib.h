#pragma once

#include "BaseWrapper.h"

using namespace std;
#include <functional>

namespace qg {
	struct SpreaderInput { int count; float radius; int index; int direction; };

	typedef function<float(SpreaderInput)> ScaleVariatorLambda;

	vector<glm::vec3> positionRadialSpreader(const SpreaderInput p, const ScaleVariatorLambda scale_variator_lambda);
}