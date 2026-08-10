#include "../src/Voxel.h"

using namespace std;
#include "iostream"

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