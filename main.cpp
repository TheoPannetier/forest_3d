// forest_3d.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "src/Parameters.h"
#include "src/Simulation.h"
#include "src/Utils.h"
#include "src/Voxel.h"
#include "src/VoxelArray.h"
using namespace std;

int main()
{
	// TODO: RNG
	// TODO: read parameters

	const string path_to_project;
	Parameters p(path_to_project);
	Simulation s(p);
	s.run();
	cout << "Simulation completed." << endl;
	return 0;
}
