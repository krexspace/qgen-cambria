#include "CoreTester.h"

#include "catch.h"

#include "BaseWrapper.h"

#include "MeshStructure.h"

using namespace std;
using namespace qg;

TEST_CASE("qvec3 sets, hashing, sorting, comparison etc", "[qvec3_1]") {
	// Note that unordered sets use hash, where as sets use <
	// order for qvec3 is not important, 
	// uniqueness is critical for merging verts
	SECTION("sets - order and uniqueness") {
		// ORDERED SET
		set<qvec3> qset1{
			{1.0,2.0019,1.0},
			{1.0,2.0011,1.0},
			{1.0,2.001111,1.0}
		};
		set<qvec3> qset2{
			{1.0,2.0019,1.0},
			{1.0,2.0001,1.0},
			{1.0,2.001111,1.0}
		};
		// UNORDERED SET
		unordered_set<qvec3> qset3{
			{1.0,2.0019,1.0},
			{1.0,2.0011,1.0},
			{1.0,2.001111,1.0}
		};
		unordered_set<qvec3> qset4{
			{1.0,2.0019,1.0},
			{1.0,2.0001,1.0},
			{1.0,2.001111,1.0}
		};
		if (VERT_PRECISION == 1000) {
			REQUIRE(qset1.size() == 2);
			REQUIRE(qset2.size() == 3);
			REQUIRE(qset3.size() == 2);
			REQUIRE(qset4.size() == 3);

			// SET COUNT AND FIND TESTS
			auto iter2 = qset2.find(qvec3({ 1.0,2.0019,1.0 }));
			REQUIRE(iter2 != qset2.end());
			REQUIRE(qset2.count(qvec3({ 1.0,2.0019,1.0 })) == 1);
			REQUIRE(qset2.count(qvec3({ 1.0,2.0015,1.0001 })) == 1);
			REQUIRE(qset2.count(qvec3({ 1.1,2.0015,1.0001 })) == 0);
			REQUIRE(qset1.count(qvec3({ 1.0,2.0011,1.0 })) == 1);
		}
		if (VERT_PRECISION == 1) {
			REQUIRE(qset1.size() == 1);
			REQUIRE(qset2.size() == 1);
			REQUIRE(qset3.size() == 1);
			REQUIRE(qset4.size() == 1);
		}
		std::for_each(qset1.begin(), qset1.end(), [](qvec3 n) { cout << n.to_string() << endl; });
	}

	SECTION("comparison operators") {
		qvec3 v1 { 1.0,2.01,3.0 };
		qvec3 v2 { 1.0,2.01,3.1 };
		
		if (VERT_PRECISION > 10) {
			REQUIRE(!(v1 == v2));
			REQUIRE(v1 != v2);
			REQUIRE(v1 < v2);
			REQUIRE(!(v1 > v2));
		}
		else {
			REQUIRE((v1 == v2));
			REQUIRE(!(v1 != v2));
			REQUIRE(!(v1 < v2));
			REQUIRE(!(v1 > v2));
		}	
	}
}

TEST_CASE("qvec3 map lookup tests", "[qvec3_2]") {
	// Note that unordered sets use hash, where as sets use <
	// order for qvec3 is not important, 
	// uniqueness is critical for merging verts
	SECTION("maps lookup and key uniqueness") {
		// ORDERED SET
		map<qvec3, int> qmap1{
			{ { 1.0,2.0019,1.0 }, 0 },
			{ { 1.0,2.0011,1.0 }, 1 },
			{ { 1.0,2.001111,1.0 }, 2 }
		};
		for (const auto& pair1 : qmap1) {
			qvec3 key = pair1.first;
			std::cout << "1:map elem: " << key.to_string() << ':' << pair1.second  << endl;
		}
		REQUIRE(qmap1.size() == 2);
		REQUIRE(qmap1[qvec3({ 1.0,2.002,1.0 })] == 0);
		REQUIRE(qmap1[qvec3({ 1.0,2.001,1.0 })] == 1);
		// Note that the 4th decimal place is ignored for this 
		// key selection
		qmap1[qvec3({ 1.0,2.0013,1.0 })] = 4;

		for (const auto& pair1 : qmap1) {
			qvec3 key = pair1.first;
			std::cout << "2:map elem: " << key.to_string() << ':' << pair1.second << endl;
		}
		REQUIRE(qmap1[qvec3({ 1.0,2.001,1.0 })] == 4);
		// size remains the same
		REQUIRE(qmap1.size() == 2);
	}
}