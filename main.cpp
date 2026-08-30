// forest_3d.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <filesystem>
#include "src/Parameters.h"
#include "src/Simulation.h"
#include "src/Utils.h"
#include "src/Voxel.h"
#include "src/VoxelArray.h"
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{

	// Read project path
	fs::path project_dir{ argc > 1 ? argv[1] : fs::current_path()};
	if (!fs::exists(project_dir))
		cout << "Project directory " << project_dir << " does not exist." << endl;

	const fs::path input_dir{ project_dir / "inputs" };
	if (!fs::exists(input_dir)) {
		cout << input_dir << " does not exist. " << endl;
		return 1;
	}
	const fs::path path_params_global{ input_dir / "params_global.txt" };
	const fs::path path_params_pass{ input_dir / "params_pass0.txt" };
	if (!(fs::exists(path_params_global) && fs::exists(path_params_pass))) {
		cout << "Input directory must contain input files params_global.txt and params_pass0.txt" << endl;
		return 1;
	}
	const fs::path output_dir{ project_dir / "outputs" };
	if (!fs::exists(output_dir)) {
		fs::create_directory(output_dir);
	}

	// TODO: RNG
	// TODO: read parameters
	// 
	//Parameters p(path_to_project);
	//Simulation s(p);
	//s.run();
	cout << "Simulation completed." << endl;
	return 0;
}
