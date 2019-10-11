#include "MeshStructure.h"

namespace qg {

	// ======================= MESH STRUCTURE ====================== //

	//void MeshStructure::addFace(const QuadFaceDTO& qface) {
	//	//qface
	//}
	//void MeshStructure::addFaceBatch(const vector<QuadFaceDTO> faceList) {

	//}
	//void MeshStructure::MeshStructure::deleteFace(long faceIndex) {

	//}
	// Atomic operation
	void MeshStructure::dropVerts(vector<int> indices) {
		std::set<int> index_set(indices.begin(), indices.end());
		
		// Use a reverse iterator
		std::set<int>::reverse_iterator rit;
		for (rit = index_set.rbegin(); rit != index_set.rend(); ++rit) {
			verts.erase(verts.begin() + *rit);
		}

		// Update face index map
		dropVerts_update_indexFaceIndexList_map(indices);
	}

	void MeshStructure::dropVerts_update_indexFaceIndexList_map(vector<int> indices) {
		for (int ix : indices) {
			indexFaceIndexList_map.erase(ix);
		}
	}

	void MeshStructure::rebuild_indexFaceIndexList_map() {
		indexFaceIndexList_map.clear(); // Erase all
		int qf_index = 0;
		for (auto qf : quadFaces) {
			for (int ix : qf.indices) {
				auto pos = indexFaceIndexList_map.find(ix);
				if (pos == indexFaceIndexList_map.end()) {
					// Add new list
					vector<int> face_index_vec;
					face_index_vec.push_back(qf_index);
					indexFaceIndexList_map[ix] = face_index_vec;
				}
				else {
					// List is existing, append index 
					vector<int> face_index_vec = pos->second;
					face_index_vec.push_back(qf_index);
				}
			}
			++qf_index;
		}
	}
#define DUPLICATE_VERT_CHECK true
	void MeshStructure::rebuild_vert_index_reverse_map() {
		vert_index_reverse_map.clear(); // Erase all
		int vert_index = 0;
		for (auto v : verts) {
			// If vertex is already there, something is wrong with the data,
			// or vertex is a duplicate
			// TODO: Check if needed or made optional
			if (DUPLICATE_VERT_CHECK && vert_index_reverse_map.count(v)) {
				throw std::runtime_error("Duplicate vertex found at index " + vert_index);
			}
			else {
				// Beautiful logic! Key is a vert object
				vert_index_reverse_map[v] = vert_index;
			}
			++vert_index;
		}
	}
	// ====================== end MESH STRUCTURE =================== //

}