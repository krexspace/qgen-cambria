#pragma once

#include "BaseWrapper.h"
#include "MeshStructure.h"

using namespace std;

namespace qg {
	FbxNode* fbxTransform(const MeshStructure& ms, FbxScene* pScene, char* pName);

	FbxVector4 toFbxVector4(const qvec3& v);
	FbxVector2 toFbxVector2(const qvec2& v);
}