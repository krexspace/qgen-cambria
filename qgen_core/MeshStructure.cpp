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

	void MeshStructure::dropVerts(vector<int> indices) {
		std::set<int> index_set(indices.begin(), indices.end());
		
		// Use a reverse iterator
		std::set<int>::reverse_iterator rit;
		for (rit = index_set.rbegin(); rit != index_set.rend(); ++rit) {
			verts.erase(verts.begin() + *rit);
		}			
	}

	void MeshStructure::dropVerts_update_indexFaceIndexList_map(vector<int> indices) {

	}

	void MeshStructure::rebuild_indexFaceIndexList_map() {
		indexFaceIndexList_map.clear(); // Erase all
		int qf_index = 0;
		for (auto qf : quadFaces) {
			for (int ix : qf.indices) {
				auto pos = indexFaceIndexList_map.find(ix);
				if (pos == indexFaceIndexList_map.end()) {
					vector<int> face_index_vec;
					face_index_vec.push_back(qf_index);
					indexFaceIndexList_map[ix] = face_index_vec;
				}
				else {
					vector<int> face_index_vec = pos->second;
					face_index_vec.push_back(qf_index);
				}
			}
			++qf_index;
		}
	}
	// ====================== end MESH STRUCTURE =================== //

}