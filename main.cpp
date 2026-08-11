// forest_3d.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "src/Utils.h"
#include "src/Voxel.h"
#include "src/VoxelArray.h"
using namespace std;

int main()
{
	const int dim_x = 30, dim_y = 30, dim_z = 30;
	VoxelArray vox_matrix(dim_x, dim_y, dim_z);

	cout << "Hello CMake." << endl;
	return 0;
}
