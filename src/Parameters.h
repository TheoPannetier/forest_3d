#pragma once

using namespace std;
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <cassert>
namespace fs = std::filesystem;

typedef pair<double, double> ParamRange;

/*
template <typename T> class ParamRange {
public:
	ParamRange(const T min, const T max) : range_{min, max}
	T min() const { return range_.first; }
	T max() const { return range_.second; }
private:
	pair<T, T> range_;
};
*/

struct GlobalParams {
	int nb_years, replicates, seed;
	size_t dim_x, dim_y, dim_z;
	int width_corridor, voxel_size;
	bool report_forest, report_light, report_mortality;
	bool report_shoots, report_trees, report_voxel;
	bool simulate_forest;
	int nb_threads;
};

struct PassParams {
	int al_max;
	ParamRange al_prod_max;
	ParamRange angle_first_order;
	ParamRange angle_sec_order;
	ParamRange beta_d;
	double beta_s;
	double branch_mort_mass_rate;
	double branch_mort_mass_exp;
	double branch_mort_method;
	double branch_mort_rnd_rate;
	double branches_collide;
	double carbon_overhead_costs;
	double cbl_ratio;
	double cbw_ratio;
	int dist_vox_light_cal;
	bool edge_c;
	double form_factor_wood;
	int h_sun;
	double i_max;
	double init_diameter;
	ParamRange internode_len_branch_max;
	ParamRange internode_len_branch_min;
	ParamRange internode_len_trunk_max;
	ParamRange internode_len_trunk_min;
	ParamRange k_int;
	double ld_branch;
	ParamRange ld_tree_dev;
	bool light_c;
	double light_ext_coeff;
	ParamRange light_thresh_apical;
	double lp_ratio;
	double min_leaf_area;
	double min_leaf_area_ratio;
	double mort_biomass_rate;
	double mort_biomass_exp;
	double mort_dist_freq;
	double mort_dist_rate;
	double mort_neigh_diameter;
	double mort_neigh_rate;
	ParamRange nb_seedling_per_ha;
	int nb_species;
	ParamRange phyllotaxis_first_order;
	short pipe_len_method;
	ParamRange pipe_reuse_fct;
	double respi_rate_wood;
	double safety_fct_trunk;
	ParamRange shortening_fct;
	double site_index;
	ParamRange sla;
	bool stochasticity;
	ParamRange stoch_angle_first_order_side;
	ParamRange stoch_angle_first_order_top;
	ParamRange stoch_angle_sec_order;
	ParamRange stoch_tropism_strength;
	ParamRange stoch_twisting;
	double stop_criterion;
	double tree_comp_dist;
	int tree_comp_num;
	double tree_mort_biomass;
	double tree_mort_carbon;
	double tree_mort_dist;
	double tree_mort_neigh;
	ParamRange tropism_strength;
	int nb_sunny_days;
	ParamRange wood_density;
};

class Parameters
{
public:
	Parameters(const fs::path& input_dir);
	GlobalParams get_global_params() const { return global_params_; }
	PassParams get_pass_params() const { return pass_params_; }

	/*
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
	*/

private:

	// Expected input file names
	const string input_file_global_{ "params_global.txt" };
	const string input_file_pass_{ "params_pass0.txt" };

	// Read and process inputs
	void read_global_parameters(const fs::path path_params_global);
	void check_global_parameters(vector<int>& input_vals) const;
	void read_pass_parameters(const fs::path path_params_pass);
	void check_pass_parameters(const vector<string>& param_names, const vector<double>& input_vals) const;

	// Parameter values
	GlobalParams global_params_;
	PassParams pass_params_;
};