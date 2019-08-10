SET(CMAKE_MIN_REQ_VERSION 2.4)
cmake_minimum_required(VERSION ${CMAKE_MIN_REQ_VERSION})
INCLUDE("../CMakeSettings.txt")

FBX_PROJECT(QGEN_CORE .)
SET(FBX_TARGET_SOURCE
    "gen_core.cxx"
    "gen_core.h"
	"BaseWrapper.h"
	"ComputeLib.h"
	"ComputeLib.cpp"
)
ADD_EXECUTABLE(
    ${FBX_TARGET_NAME}
    ${FBX_TARGET_SOURCE}
)
SET_SAMPLES_GLOBAL_FLAGS()
