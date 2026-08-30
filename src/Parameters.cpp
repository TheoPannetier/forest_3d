#include "Parameters.h"

Parameters::Parameters(const fs::path& input_dir)
{
	const fs::path path_params_global{ input_dir / input_file_global_ };
	const fs::path path_params_pass{ input_dir / input_file_pass_ };
	if (!(fs::exists(path_params_global) && fs::exists(path_params_pass))) {
		throw logic_error("Input directory must contain input files "
			+ input_file_global_ + " and " + input_file_pass_);
	}

	read_global_parameters(path_params_global);	

}

void Parameters::read_global_parameters(const fs::path path_params_global) {

	const vector<string> exptd_global_params{
		"Timesteps", "Replicates", "RandomSeed",
		"MaxX", "MaxY", "MaxZ", "WidthCorridor", "VoxelSize",
		"ReportForest", "ReportLight", "ReportMortality",
		"ReportShoots", "ReportTrees", "ReportVoxel",
		"SimulateForest", "ThreadCount"
	};
	string input_param;
	vector<int> input_vals(exptd_global_params.size());

	// Read input file
	ifstream ifs_global{ path_params_global };
	if (!ifs_global.is_open()) {
		throw logic_error("Cannot open " + input_file_global_);
	}
	for (int i = 0; i < exptd_global_params.size(); i++) {
		ifs_global >> input_param >> input_vals[i];
		// Check parameter name validity
		if (input_param != exptd_global_params[i]) {
			throw logic_error("Incorrect parameter name in " + input_file_global_
				+ " on line " + to_string(i) + ": "
				+ input_param + " should be " + exptd_global_params[i]
			);
		}
	}
	ifs_global.close();
	ifs_global.clear();

	// Parameter value validity
	check_global_parameters(input_vals);

	// Assign input values
	nb_years_ = input_vals[0];
	replicates_ = input_vals[1];
	seed_ = input_vals[2];
	dim_x_ = input_vals[3];
	dim_y_ = input_vals[4];
	dim_z_ = input_vals[5];
	width_corridor_ = input_vals[6];
	voxel_size_ = input_vals[7];
	report_forest_ = input_vals[8] == 1;
	report_light_ = input_vals[9] == 1;
	report_mortality_ = input_vals[10] == 1;
	report_shoots_ = input_vals[11] == 1;
	report_trees_ = input_vals[12] == 1;
	report_voxel_ = input_vals[13] == 1;
	simulate_forest_ = input_vals[14] == 1;
	nb_threads_ = input_vals[15];
}

void Parameters::check_global_parameters(vector<int>& input_vals) const {

	// Timesteps
	if (input_vals[0] < 1) {
		throw logic_error("Timesteps should be at least 1.");
	}
	// Replicates
	if (input_vals[1] < 1) {
		throw logic_error("Replicates should be at least 1.");
	}
	// RandomSeed
	if (input_vals[2] < 1) {
		throw logic_error("RandomSeed should be at least 1.");
	}
	// MaxX, MaxY, MaxZ
	if (input_vals[3] < 1) {
		throw logic_error("MaxX should be at least 1.");
	}
	if (input_vals[4] < 1) {
		throw logic_error("MaxY should be at least 1.");
	}
	if (input_vals[5] < 1) {
		throw logic_error("MaxZ should be at least 1.");
	}
	// WidthCorridor
	if (input_vals[6] < 0) {
		throw logic_error("WidthCorridor should not be negative.");
	}
	// VoxelSize
	if (input_vals[7] < 1) {
		throw logic_error("VoxelSize should be at least 1.");
	}
	// Reports
	if (input_vals[8] != 0 && input_vals[8] != 1) {
		throw logic_error("ReportForest should be either 0 or 1.");
	}
	if (input_vals[9] != 0 && input_vals[9] != 1) {
		throw logic_error("ReportLight should be either 0 or 1.");
	}
	if (input_vals[10] != 0 && input_vals[10] != 1) {
		throw logic_error("ReportMortality should be either 0 or 1.");
	}
	if (input_vals[11] != 0 && input_vals[11] != 1) {
		throw logic_error("ReportShoots should be either 0 or 1.");
	}
	if (input_vals[12] != 0 && input_vals[12] != 1) {
		throw logic_error("ReportTrees should be either 0 or 1.");
	}
	if (input_vals[13] != 0 && input_vals[13] != 1) {
		throw logic_error("ReportVoxel should be either 0 or 1.");
	}
	// SimulateForest
	if (input_vals[14] != 0 && input_vals[14] != 1) {
		throw logic_error("SimulateForest should be either 0 or 1.");
	}
	// ThreadCount
	if (input_vals[15] < 1) {
		throw logic_error("ThreadCount should be a positive number.");
	}
}
