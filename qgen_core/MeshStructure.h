#pragma once

#include "BaseWrapper.h"
#include "GenericUtils.h"

using namespace std;
namespace qg {

	// MESH DATA
	struct qvec2 {
		float x;
		float y;
		/*
		// Doesnt make sense here
		bool operator<(const qvec2 &rhs) const {
			return x < rhs.x && y < rhs.y;
		};
		*/
		bool operator==(const qvec2 &rhs) const {
			return x == rhs.x && y == rhs.y;
		};
	};

	struct qvec3 {
		float x;
		float y;
		float z;

		bool operator<(const qvec3 &rhs) const {
			return x < rhs.x && y < rhs.y && z < rhs.z;
		};
		bool operator==(const qvec3 &rhs) const {
			return x == rhs.x && y == rhs.y && z == rhs.z;
		};
	};
}

namespace std {
	template<> struct hash<qg::qvec2> {
	public:
		size_t operator()(const qg::qvec2 &s) const
		{
			std::size_t h = 0;
			qg::hash_combine(h, s.x);
			qg::hash_combine(h, s.y);
			return h;
		}
	};
	template<> struct hash<qg::qvec3> {
	public:
		size_t operator()(const qg::qvec3 &s) const
		{
			std::size_t h = 0;
			qg::hash_combine(h, s.x);
			qg::hash_combine(h, s.y);
			qg::hash_combine(h, s.z);
			return h;
		}
	};
}

namespace qg {
	
	enum class VertGroupType { GROUP, EDGE, BORDER_EDGE };
	class VertGroup {
		vector<qvec3*> vertPointers;
		string name;
		VertGroupType type = VertGroupType::GROUP;
	};
	class QuadFace {
	public:
		long indices[4] = { -1,-1,-1,-1 };
		qvec2 uvs[4]; // four pairs
		qvec3 normals[4]; // four vector
		// Other possible
		// markers
		// vetex_colors
		// group_info
	};
	class FaceGroup {
		vector<QuadFace*> quadFacePointers;
		string name;
	};
	// Int indices range based
	class MeshStructure {
	protected:
		vector<qvec3> verts; // Vert List
		vector<QuadFace> quadFaces; // Face List

		// Vert groups store
		unordered_map<string, VertGroup> vertGroupMap;
		unordered_map<string, FaceGroup> faceGroupMap;

		// Key mappping structure used for queries
		// Use this for reverse lookup of index by vert pointer
		unordered_map<long, vector<QuadFace*>> indexFacePointerMap;
		unordered_map<long, vector<string>> indexVertGroupNameinterMap;
		unordered_map<long, vector<string>> indexFaceGroupNameMap; // Check if required and correct
	public:
		void addFace(const QuadFace& qface);
		void addFaceBatch(const vector<QuadFace> faceList);
		void deleteFace(long faceIndex);
	};
}
	// end MESH DATA //