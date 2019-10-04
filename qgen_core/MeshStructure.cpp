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
	// ====================== end MESH STRUCTURE =================== //

}