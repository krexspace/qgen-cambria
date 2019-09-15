#include "BaseWrapper.h"
#include "MeshBuilder.h"

namespace qg {
	// A simple open mesh with 3 quads
	// If u can build this you can build anything!
	MeshStructure* buildDemoMesh() {
		MeshStructure* ms = new MeshStructure();

		vector<qvec3> vc;// = ms->verts; // vert cloud
		vector<QuadFace> qfList;// = ms->quadFaces; // vert cloud

		// Build the vert cloud
		qvec3 p = { 0.0f, 0.0f, 0.0f };
		vc.push_back(p);
		p.x += 100;
		//p.z += 50;
		vc.push_back(p);
		p.x += 100;
		//vc.push_back(p);
		p.x += 100;
		//vc.push_back(p);

		p = { 0.0f, 100.0f, 0.0f };
		vc.push_back(p);
		p.x += 100;
		//p.z += 50;
		vc.push_back(p);
		p.x += 100;
		//vc.push_back(p);
		p.x += 100;
		//vc.push_back(p);

		// Move to a util function
		for (auto pp : vc) {
			std::cout << "V " << pp.x << ',' << pp.y << ',' << pp.z << std::endl;
		}

		QuadFace qf;
		// Face 1
		qf.indices = { 0, 1, 2, 3 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f, 
			1.0f, 0.0f, 
			1.0f, 1.0f, 
			0.0f, 1.0f }; 
		qf.normals = { 
			0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 1.0f };
		qfList.push_back(qf);
		/*
		// Face 2
		qf.indices = { 1, 5, 6, 2 };
		qf.uvs = {
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f };
		qfList.push_back(qf);
		// Face 3
		qf.indices = { 2, 6, 7, 3 };
		qf.uvs = {
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f };
		qfList.push_back(qf);
		*/
		ms->verts = vc; //copy
		ms->quadFaces = qfList; //copy
		/*
		for (auto qf1 : ms->quadFaces) {
			std::cout << qf1.indices[0] << std::endl;
		}
		*/
		return ms;
	}

	MeshStructure* buildDemoMesh_Cube() {
		MeshStructure* ms = new MeshStructure();

		vector<qvec3> vc;// = ms->verts; // vert cloud
		vector<QuadFace> qfList;// = ms->quadFaces; // vert cloud

		// Build the vert cloud
		qvec3 p = { -50, 0, 50 };
		vc.push_back(p);
		p = { 50, 0, 50 };
		vc.push_back(p);
		p = { 50, 100, 50 };
		vc.push_back(p);
		p = { -50, 100, 50 };
		vc.push_back(p);
		p = { -50, 0, -50 };
		vc.push_back(p);
		p = { 50, 0, -50 };
		vc.push_back(p);
		p = { 50, 100, -50 };
		vc.push_back(p);
		p = { -50, 100, -50 };
		vc.push_back(p);

		
		// Move to a util function
		/*
		for (auto pp : vc) {
			std::cout << pp.x << ',' << pp.y << ',' << pp.z << std::endl;
		}
		*/

		QuadFace qf;
		// Face 1
		qf.indices = { 0, 1, 2, 3 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f };
		qfList.push_back(qf);

		// Face 2
		qf.indices = { 1, 5, 6, 2 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f };
		qfList.push_back(qf);

		// Face 3
		qf.indices = { 5, 4, 7, 6 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f };
		qfList.push_back(qf);

		// Face 4
		//qf.indices = { 4, 0, 3, 7 };
		//// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		//qf.uvs = {
		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f };
		//qf.normals = {
		//	-1.0f, 0.0f, 0.0f,
		//	-1.0f, 0.0f, 0.0f,
		//	-1.0f, 0.0f, 0.0f,
		//	-1.0f, 0.0f, 0.0f };
		//qfList.push_back(qf);

		//// Face 5
		//qf.indices = { 3, 2, 6, 7 };
		//// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		//qf.uvs = {
		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f };
		//qf.normals = {
		//	0.0f, 1.0f, 0.0f,
		//	0.0f, 1.0f, 0.0f,
		//	0.0f, 1.0f, 0.0f,
		//	0.0f, 1.0f, 0.0f };
		//qfList.push_back(qf);

		//// Face 6
		//qf.indices = { 1, 0, 4, 5 };
		//// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		//qf.uvs = {
		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f };
		//qf.normals = {
		//	0.0f, -1.0f, 0.0f,
		//	0.0f, -1.0f, 0.0f,
		//	0.0f, -1.0f, 0.0f,
		//	0.0f, -1.0f, 0.0f };
		//qfList.push_back(qf);
		
		ms->verts = vc; //copy
		ms->quadFaces = qfList; //copy
		/*
		for (auto qf1 : ms->quadFaces) {
			std::cout << qf1.indices[0] << std::endl;
		}
		*/
		return ms;
	}

	MeshStructure* buildDemoMesh_Cube2() {
		MeshStructure* ms = new MeshStructure();

		vector<qvec3> vc;// = ms->verts; // vert cloud
		vector<QuadFace> qfList;// = ms->quadFaces; // vert cloud

		// Build the vert cloud
		qvec3 p = { -50, 0, 50 };
		vc.push_back(p);
		p = { 50, 0, 50 };
		vc.push_back(p);
		p = { 50, 100, 50 };
		vc.push_back(p);
		p = { -50, 100, 50 };
		vc.push_back(p);
		p = { -50, 0, -50 };
		vc.push_back(p);
		p = { 50, 0, -50 };
		vc.push_back(p);
		p = { 50, 100, -50 };
		vc.push_back(p);
		p = { -50, 100, -50 };
		vc.push_back(p);


		// Move to a util function
		/*
		for (auto pp : vc) {
			std::cout << pp.x << ',' << pp.y << ',' << pp.z << std::endl;
		}
		*/

		QuadFace qf;
		// Face 1
		qf.indices = { 0, 1, 2, 3 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f };
		qfList.push_back(qf);

		// Face 2
		qf.indices = { 1, 5, 6, 2 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f };
		qfList.push_back(qf);

		// Face 3
		qf.indices = { 5, 4, 7, 6 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f };
		qfList.push_back(qf);

		// Face 4
		qf.indices = { 4, 0, 3, 7 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f };
		qfList.push_back(qf);

		// Face 5
		qf.indices = { 3, 2, 6, 7 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f };
		qfList.push_back(qf);

		// Face 6
		qf.indices = { 1, 0, 4, 5 };
		// same as { qvec2{0.0f, 1.0f} , qvec2{1.0f, 1.0f} , qvec2{2.0f, 1.0f} , qvec2{3.0f, 1.0f} };
		qf.uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f };
		qf.normals = {
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f };
		qfList.push_back(qf);

		ms->verts = vc; //copy
		ms->quadFaces = qfList; //copy
		/*
		for (auto qf1 : ms->quadFaces) {
			std::cout << qf1.indices[0] << std::endl;
		}
		*/
		return ms;
	}
}