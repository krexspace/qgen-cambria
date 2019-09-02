#pragma once

#include "BaseWrapper.h"
#include "MeshStructure.h"

using namespace std;

namespace qg {
	FbxNode* fbxTransform(FbxScene* pScene, char* pName);

	FbxVector4 toFbxVector4(const qvec3& v) {
		return FbxVector4(v.x, v.y, v.z);
	}

	FbxVector2 toFbxVector2(const qvec2& v) {
		return FbxVector2(v.x, v.y);
	}
}