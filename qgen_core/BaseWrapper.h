#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <limits>
#include <iostream>
#include <string>
#include <chrono>

// COMMON STL HEADERS
#include <array>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <string>

// TODO check usage
#define GLM_FORCE_PURE
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/matrix_transform.hpp"
// glm::inverseTranspose
#include "glm/gtc/matrix_inverse.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"
// glm::to_string
#include "glm/gtx/string_cast.hpp"

#include "glm/gtx/rotate_vector.hpp"

// FBX SDK
#include <fbxsdk.h>