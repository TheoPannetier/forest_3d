using namespace std;
#include <iostream>
#include <string>

#include "../src/Voxel.h"
#include "../src/Branch.h"

#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(my_boost_test)
{
	cout << "Running BOOST TEST" << endl;
	Voxel v(1, 1, 1);
	Branch* b = new Branch;
	v.addBranch(b, 3.0f);
	BOOST_CHECK(v.getLeafAreaAxis(0) == 3.0f);
	delete b;
}

/*
int main()
{
	cout << "Running test!" << endl;

	Voxel v(1, 1, 1);
	Branch* b = new Branch;
	v.addBranch(b, 3.0f);

	bool test_ok = v.getBranch(0) == b && v.getLeafAreaAxis(0) == 3.0f;
	if (!test_ok) return 1;

	return 0;
}
*/