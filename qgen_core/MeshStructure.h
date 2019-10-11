#pragma once

#include "BaseWrapper.h"
#include "GenericUtils.h"

using namespace std;
namespace qg {

	// MESH DATA
	struct qvec2 {
		float x;
		float y;
		//
		// operator== is not used by std::set. 
		// Elements a and b are considered equal iff !(a < b) && !(b < a)
		// Caution: x < rxs.x && y < rhs.y doesn't not work. Drops items in sets (ordered)
		bool operator<(const qvec2 &rhs) const {
			// First checks x, then y in that order
			return x != rhs.x?x<rhs.x: y < rhs.y;
		};
		//
		bool operator==(const qvec2 &rhs) const {
			return x == rhs.x && y == rhs.y;
		};
	};
#define VERT_PRECISION 1000
	struct qvec3 {
		float x;
		float y;
		float z;

		bool operator<(const qvec3 &rhs) const {
			// Rounded at n number of decimal places for eliminating float errors
			float r_x = std::floor(x * VERT_PRECISION);
			float r_y = std::floor(y * VERT_PRECISION);
			float r_z = std::floor(z * VERT_PRECISION);
			float r_rhs_x = std::floor(rhs.x * VERT_PRECISION);
			float r_rhs_y = std::floor(rhs.y * VERT_PRECISION);
			float r_rhs_z = std::floor(rhs.z * VERT_PRECISION);
			// First checks x, then y, then z in that order
			return r_x != r_rhs_x ? r_x < r_rhs_x : (r_y != r_rhs_y ? r_y < r_rhs_y : r_z < r_rhs_z);
		};
		bool operator==(const qvec3 &rhs) const {
			// Rounded at n number of decimal places for eliminating float errors
			float r_x = std::floor(x * VERT_PRECISION);
			float r_y = std::floor(y * VERT_PRECISION);
			float r_z = std::floor(z * VERT_PRECISION);
			float r_rhs_x = std::floor(rhs.x * VERT_PRECISION);
			float r_rhs_y = std::floor(rhs.y * VERT_PRECISION);
			float r_rhs_z = std::floor(rhs.z * VERT_PRECISION);
			return r_x == r_rhs_x && r_y == r_rhs_y && r_z == r_rhs_z;
		};
	};
	class QuadFace {
	public:
		// std::array used instead of c style arrays
		array<int, 4> indices;
		array<qvec2, 4> uvs; // four pairs
		array<qvec3, 4> normals; // four vector
		//long faceIndex; // Can be used to capture construction order
		//// Other possible
		//// markers
		//// vetex_colors
		//// group_info

		//bool operator<(const QuadFace &rhs) const {
		//	return faceIndex < rhs.faceIndex;
		//};
		//bool operator==(const QuadFace &rhs) const {
		//	return faceIndex == rhs.faceIndex;
		//};
	};
	struct QuadFaceDTO {
		qvec3 verts[4]; // four vector
		qvec2 uvs[4]; // four pairs
		qvec3 normals[4]; // four vector
		long faceIndex; // Can be used to capture construction order
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
	/*template<> struct hash<qg::QuadFace> {
	public:
		size_t operator()(const qg::QuadFace &s) const
		{
			std::size_t h = 0;
			qg::hash_combine(h, s.faceIndex);
			return h;
		}
	};*/
}

namespace qg {
	
	enum class VertGroupType { GROUP, EDGE, BORDER_EDGE };
	class VertGroup {
		vector<qvec3*> vertPointers;
		string name;
		VertGroupType type = VertGroupType::GROUP;
	};
	
	class FaceGroup {
		vector<QuadFace*> quadFacePointers;
		string name;
	};

	// Long indices range based
	// Contains the verts and the windin
	class MeshStructure {
	public	:
		
		/*
		ref: https://thispointer.com/map-vs-unordered_map-when-to-choose-one-over-another/
		Time complexity for searching elements in std::map is O(log n).Even in
		worst case it will be O(log n) because elements are stored internally as
		Balanced Binary Search tree(BST).

		Whereas, in std::unordered_map best case time complexity for
		searching is O(1).Where as, if hash code function is not good then,
		worst case complexity can be O(n) (In case all keys are in same bucket).
		*/
		void dropVerts(vector<int> indices);
	private:
		// ordered set of unique vertices
		vector<qvec3> verts; // Ordered Unique Vert List - ordered by x,y,z in that order
		vector<QuadFace> quadFaces; // Ordered Unique Face List - ordered by faceIndex

		map<qvec3, int> vert_index_reverse_map;
		map<int, vector<int>> indexFaceIndexList_map;

		void rebuild_vert_index_reverse_map();
		void rebuild_indexFaceIndexList_map();
		void dropVerts_update_indexFaceIndexList_map(vector<int> indices);
		/*
		// Named groups store
		unordered_map<string, VertGroup> vertGroupMap;
		unordered_map<string, FaceGroup> faceGroupMap;

		// Key mappping structure used for queries
		// Use this for reverse lookup of index by vert pointer
		;
		unordered_map<long, vector<string>> indexVertGroupNameMap;
		unordered_map<long, vector<string>> indexFaceGroupNameMap; // Check if required and correct
		
		// Class Methods
		void addFace(const QuadFaceDTO& qface);
		void addFaceBatch(const vector<QuadFaceDTO> faceList);
		void deleteFace(long faceIndex);
		*/
		// ATOMIC OPERATIONS //
		
		
	};
}
// end MESH DATA //