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
		
		// ----------- MAP NORMALS -------------//
		// We want to have one normal for each vertex (or control point),
		// so we set the mapping mode to eByControlPoint.
		FbxGeometryElementNormal* lGeometryElementNormal = lMesh->CreateElementNormal();
		lGeometryElementNormal->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
		lGeometryElementNormal->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
		lGeometryElementNormal->GetIndexArray().SetCount(numVerts);
		auto& nVec = lGeometryElementNormal->GetDirectArray();

		// ------------- MAP UVS ------------//
		// Create UV for Diffuse channel.
		FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV("DiffuseUV");
		FBX_ASSERT(lUVDiffuseElement != NULL);
		lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
		lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
		lUVDiffuseElement->GetIndexArray().SetCount(numVerts);
		auto& uvVec = lUVDiffuseElement->GetDirectArray();

		assert(ms.verts.size() <= numVerts);
		// ------------- CREATE VERTS ARRAY ------------//
		long v = 0;
		for (auto vert : ms.verts) {
			lControlPoints[v++] = toFbxVector4(vert);
		}

		int i = 0;
		for (auto qf: ms.quadFaces) {

			cout << "FACE " << i/4 << endl;
			//auto indices = qf.indices;

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

			lMesh->BeginPolygon(-1, -1, -1, false);

			for (long iFaceIndex : qf.indices) {
				// Control point index
				lMesh->AddPolygon(iFaceIndex);
				lGeometryElementNormal->GetIndexArray().SetAt(i, i);
				lUVDiffuseElement->GetIndexArray().SetAt(i, i);
				++i; // Dont miss this critical counter which tracks everything!
			}
			lMesh->EndPolygon();
		}

		for (int n = 0; n < numVerts; n++) {
			cout << "VERTS " << lControlPoints[n].mData[0] << ',' << lControlPoints[n].mData[1] << ',' << lControlPoints[n].mData[2] << endl;
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