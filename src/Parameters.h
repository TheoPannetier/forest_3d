#pragma once

using namespace std;
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

class Parameters
{
public:
	Parameters(const fs::path& input_dir);
	int get_nb_years() const { return nb_years_; }
	int get_nb_rep() const { return replicates_; }
	int get_seed() const { return seed_; }
	size_t get_dim_x() const { return dim_x_; }
	size_t get_dim_y() const { return dim_y_; }
	size_t get_dim_z() const { return dim_z_; }
	int get_corridor_width() const { return width_corridor_; }
	bool report_forest() const { return report_forest_; }
	bool report_light() const { return report_light_; }
	bool report_mortality() const { return report_mortality_; }
	bool report_shoots() const { return report_shoots_; }
	bool report_trees() const { return report_trees_; }
	bool report_voxel() const { return report_voxel_; }
	bool is_forest_version() const { return simulate_forest_; }
	int get_nb_threads() const { return nb_threads_; }


	double get_stop_criterion() const { return stop_criterion_; }

private:

	// Expected input file names
	const string input_file_global_{ "params_global.txt" };
	const string input_file_pass_{ "params_pass0.txt" };

	// Read and process inputs
	void read_global_parameters(const fs::path path_params_global);
	void check_global_parameters(vector<int>& input_vals) const;

	// Global parameters
	int nb_years_, replicates_, seed_;
	size_t dim_x_, dim_y_, dim_z_;
	int width_corridor_, voxel_size_;
	bool report_forest_, report_light_, report_mortality_;
	bool report_shoots_, report_trees_, report_voxel_;
	bool simulate_forest_;
	int nb_threads_;

	// Pass parameters
	double stop_criterion_;
};