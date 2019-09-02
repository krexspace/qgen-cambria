#include "FBXTransformer.h"
#include "MeshStructure.h"

namespace qg {
	FbxNode* fbxTransform(MeshStructure& ms, FbxScene* pScene, char* pName) {
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
			auto indices = qf.indices;
			qvec3 vert1 = ms.verts[indices[0]];
			qvec3 vert2 = ms.verts[indices[1]];
			qvec3 vert3 = ms.verts[indices[2]];
			qvec3 vert4 = ms.verts[indices[3]];
			
			FbxVector4 v1 = toFbxVector4(vert1);
			FbxVector4 v2 = toFbxVector4(vert2);
			FbxVector4 v3 = toFbxVector4(vert3);
			FbxVector4 v4 = toFbxVector4(vert4);

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
	}
}