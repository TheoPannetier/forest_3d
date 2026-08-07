// forest_3d.cpp : Defines the entry point for the application.
//


#include <iostream>
#include "VoxArray.h"
#include "Vox.h"
using namespace std;

int main()
{
	const int dim_x = 30, dim_y = 30, dim_z = 30;
	Grid3D<Vox> vox_matrix(dim_x, dim_y, dim_z);
	for (int x = 0; x < dim_x; x++) {
		for (int y = 0; y < dim_y; y++) {
			for (int z = 0; z < dim_z; z++) {
				vox_matrix(x, y, z) = Vox(x, y, z);
			}
		}
	}

	cout << "Hello CMake." << endl;
	return 0;
}
