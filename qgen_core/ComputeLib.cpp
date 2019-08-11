#include "ComputeLib.h"


namespace qg {
	// TEMP SAMPLE lambda
	/*
	auto scaleVariator = [](const SpreaderInput& p) {
		return 1.0f;
	};
	*/

	vector<glm::vec3> positionRadialSpreader(const SpreaderInput p, const ScaleVariatorLambda scale_variator_lambda) {
		const float PI = M_PI;
		const int C = p.count;
		float deltaAngle = PI * 2 * p.direction / C;

		vector<glm::vec3> pos_list;
		// initialize to x displacement along radius
		glm::vec3 next_pos(p.radius, p.step_index * p.step_delta, 0.0f);
		SpreaderInput p1 = p; //copy
		for (int i = 1; i <= C; i++) {
			p1.radial_index = i;
			float scaleFactor = scale_variator_lambda(p1);
			glm::vec3 scaled_pos = next_pos * scaleFactor;
			pos_list.push_back(scaled_pos);
			next_pos = glm::rotateY(next_pos, deltaAngle);
		}
		return pos_list;
	}
}