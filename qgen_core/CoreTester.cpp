#include "CoreTester.h"

#include "catch.h"

#include "BaseWrapper.h"

#include "MeshStructure.h"

using namespace std;
using namespace qg;

TEST_CASE("qvec3 sets and maps, hashing, sorting, comparison etc", "[qvec3]") {
	// Note that unordered sets use hash, where as sets use <
	SECTION("collection datasets") {
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