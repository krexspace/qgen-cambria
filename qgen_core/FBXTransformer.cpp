#include "FBXTransformer.h"

namespace qg {
	FbxVector4 toFbxVector4(const qvec3& v) {
		return FbxVector4(v.x, v.y, v.z);
	}

	FbxVector2 toFbxVector2(const qvec2& v) {
		return FbxVector2(v.x, v.y);
	}

	FbxNode* fbxTransform(const MeshStructure& ms, FbxScene* pScene, char* pName) {
		FbxMesh* lMesh = FbxMesh::Create(pScene, pName);

		long numFaces = ms.quadFaces.size();
		long numVerts = numFaces * 4;
		// Create control points.
		// FACE MAPPING
		lMesh->InitControlPoints(numVerts);
		FbxVector4* lControlPoints = lMesh->GetControlPoints();
		// NORMAL MAPPING
		// We want to have one normal for each vertex (or control point),
		// so we set the mapping mode to eByControlPoint.
		FbxGeometryElementNormal* lGeometryElementNormal = lMesh->CreateElementNormal();

		lGeometryElementNormal->SetMappingMode(FbxGeometryElement::eByControlPoint);

		// Set the normal values for every control point.
		lGeometryElementNormal->SetReferenceMode(FbxGeometryElement::eDirect);

		auto& nVec = lGeometryElementNormal->GetDirectArray();

		// MAP UVS
		// Create UV for Diffuse channel.
		FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV("DiffuseUV");
		FBX_ASSERT(lUVDiffuseElement != NULL);
		lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByControlPoint);
		lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eDirect);
		auto& uvVec = lUVDiffuseElement->GetDirectArray();

		long i = 0;
		for (auto qf: ms.quadFaces) {
			cout << i << endl;
			auto indices = qf.indices;
			auto vert1 = ms.verts[indices[0]];
			auto vert2 = ms.verts[indices[1]];
			auto vert3 = ms.verts[indices[2]];
			auto vert4 = ms.verts[indices[3]];
			
			auto v1 = toFbxVector4(vert1);
			auto v2 = toFbxVector4(vert2);
			auto v3 = toFbxVector4(vert3);
			auto v4 = toFbxVector4(vert4);

			lControlPoints[i++] = v1;
			lControlPoints[i++] = v2;
			lControlPoints[i++] = v3;
			lControlPoints[i++] = v4;

			auto norm1 = toFbxVector4(qf.normals[0]);
			auto norm2 = toFbxVector4(qf.normals[1]);
			auto norm3 = toFbxVector4(qf.normals[2]);
			auto norm4 = toFbxVector4(qf.normals[3]);
			nVec.Add(norm1);
			nVec.Add(norm2);
			nVec.Add(norm3);
			nVec.Add(norm4);

			auto uv1 = toFbxVector2(qf.uvs[0]);
			auto uv2 = toFbxVector2(qf.uvs[1]);
			auto uv3 = toFbxVector2(qf.uvs[2]);
			auto uv4 = toFbxVector2(qf.uvs[3]);
			uvVec.Add(uv1);
			uvVec.Add(uv2);
			uvVec.Add(uv3);
			uvVec.Add(uv4);
		}
		for (int i = 0; i < 24; i++) {
			cout << lControlPoints[i].mData[0] << ',' << lControlPoints[i].mData[1] << ',' << lControlPoints[i].mData[2] << endl;
		}
		//return lMesh;
		
		// create a FbxNode
		FbxNode* lNode = FbxNode::Create(pScene, pName);

		// set the node attribute
		lNode->SetNodeAttribute(lMesh);

		// set the shading mode to view texture
		lNode->SetShadingMode(FbxNode::eTextureShading);

		// rescale the cube
		lNode->LclScaling.Set(FbxVector4(0.3, 0.3, 0.3));

		// return the FbxNode
		return lNode;
		
	}
}