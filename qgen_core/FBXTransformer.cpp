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
			
			cout << "FACE " << i << endl;
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


			lMesh->BeginPolygon(-1, -1, -1, false);

			//for (long iFaceIndex : qf.indices) {
			//	// Control point index
			//	lMesh->AddPolygon(iFaceIndex);
			//}

			for (int j = 0; j < 4; j++) {
				// Control point index
				lMesh->AddPolygon(i-4 + j);
			}
		
			lMesh->EndPolygon();
		}
		//========================TEMP===============
		/*int j;
		i = 0;
		FbxVector4 lControlPoint0(-50, 0, 50);
		FbxVector4 lControlPoint1(50, 0, 50);

		FbxVector4 lControlPoint2(50, 100, 50);
		FbxVector4 lControlPoint3(-50, 100, 50);
		FbxVector4 lControlPoint4(-50, 0, -50);
		FbxVector4 lControlPoint5(50, 0, -50);
		FbxVector4 lControlPoint6(50, 100, -50);
		FbxVector4 lControlPoint7(-50, 100, -50);*/

		//FbxVector4 lNormalXPos(1, 0, 0);
		//FbxVector4 lNormalXNeg(-1, 0, 0);
		//FbxVector4 lNormalYPos(0, 1, 0);
		//FbxVector4 lNormalYNeg(0, -1, 0);
		//FbxVector4 lNormalZPos(0, 0, 1);
		//FbxVector4 lNormalZNeg(0, 0, -1);
		//// We want to have one normal for each vertex (or control point),
		//// so we set the mapping mode to eByControlPoint.
		//FbxGeometryElementNormal* lGeometryElementNormal = lMesh->CreateElementNormal();

		//lGeometryElementNormal->SetMappingMode(FbxGeometryElement::eByControlPoint);

		//// Set the normal values for every control point.
		//lGeometryElementNormal->SetReferenceMode(FbxGeometryElement::eDirect);

		//auto& nVec = lGeometryElementNormal->GetDirectArray();
		//nVec.Add(lNormalZPos);
		//nVec.Add(lNormalZPos);
		//nVec.Add(lNormalZPos);
		//nVec.Add(lNormalZPos);

		//nVec.Add(lNormalXPos);
		//nVec.Add(lNormalXPos);
		//nVec.Add(lNormalXPos);
		//nVec.Add(lNormalXPos);

		//nVec.Add(lNormalZNeg);
		//nVec.Add(lNormalZNeg);
		//nVec.Add(lNormalZNeg);
		//nVec.Add(lNormalZNeg);

		//nVec.Add(lNormalXNeg);
		//nVec.Add(lNormalXNeg);
		//nVec.Add(lNormalXNeg);
		//nVec.Add(lNormalXNeg);

		//nVec.Add(lNormalYPos);
		//nVec.Add(lNormalYPos);
		//nVec.Add(lNormalYPos);
		//nVec.Add(lNormalYPos);

		//nVec.Add(lNormalYNeg);
		//nVec.Add(lNormalYNeg);
		//nVec.Add(lNormalYNeg);

		//nVec.Add(lNormalYNeg);

		//// Array of polygon vertices.
		//int lPolygonVertices[] = {
		//	0, 1, 2, 3,
		//	4, 5, 6, 7,
		//	8, 9, 10, 11,
		//	12, 13, 14, 15,
		//	16, 17, 18, 19,
		//	20, 21, 22, 23
		//};

		// Create UV for Diffuse channel.
		/*FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV("DiffuseUV");
		FBX_ASSERT(lUVDiffuseElement != NULL);
		lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
		lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

		FbxVector2 lVectors0(0, 0);
		FbxVector2 lVectors1(1, 0);
		FbxVector2 lVectors2(1, 1);
		FbxVector2 lVectors3(0, 1);

		auto& uvVec = lUVDiffuseElement->GetDirectArray();
		uvVec.Add(lVectors0);
		uvVec.Add(lVectors1);
		uvVec.Add(lVectors2);
		uvVec.Add(lVectors3);
*/
		//Now we have set the UVs as eIndexToDirect reference and in eByPolygonVertex  mapping mode
		//we must update the size of the index array.
		// TODO QG auto&
		//lUVDiffuseElement->GetIndexArray().SetCount(24);

		//// Create polygons. Assign texture and texture UV indices.
		//for (i = 0; i < 6; i++)
		//{
		//	// all faces of the cube have the same texture
		//	lMesh->BeginPolygon(-1, -1, -1, false);

		//	for (j = 0; j < 4; j++)

		//	{
		//		// Control point index
		//		lMesh->AddPolygon(lPolygonVertices[i * 4 + j]);

		//		// update the index array of the UVs that map the texture to the face
		//		//lUVDiffuseElement->GetIndexArray().SetAt(i * 4 + j, j);
		//	}

		//	lMesh->EndPolygon();
		//}
		//===========================================
		for (int n = 0; n < 24; n++) {
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