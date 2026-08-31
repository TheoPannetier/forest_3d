#include "Parameters.h"

//#include <filesystem>
//namespace fs = std::filesystem;

Parameters::Parameters(const fs::path& input_dir)
{
	const fs::path path_params_global{ input_dir / input_file_global_ };
	const fs::path path_params_pass{ input_dir / input_file_pass_ };
	if (!(fs::exists(path_params_global) && fs::exists(path_params_pass))) {
		throw logic_error("Input directory must contain input files "
			+ input_file_global_ + " and " + input_file_pass_);
	}

	read_global_parameters(path_params_global);	
	read_pass_parameters(path_params_pass);

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
	GlobalParams pg;
	pg.nb_years = input_vals[0];
	pg.replicates = input_vals[1];
	pg.seed = input_vals[2];
	pg.dim_x = input_vals[3];
	pg.dim_y = input_vals[4];
	pg.dim_z = input_vals[5];
	pg.width_corridor = input_vals[6];
	pg.voxel_size = input_vals[7];
	pg.report_forest = input_vals[8] == 1;
	pg.report_light = input_vals[9] == 1;
	pg.report_mortality = input_vals[10] == 1;
	pg.report_shoots = input_vals[11] == 1;
	pg.report_trees = input_vals[12] == 1;
	pg.report_voxel = input_vals[13] == 1;
	pg.simulate_forest = input_vals[14] == 1;
	pg.nb_threads = input_vals[15];
	global_params_ = pg;
}

void Parameters::check_global_parameters(vector<int>& input_vals) const {

	// TODO: currently throws at the first incorrect parameter.
	// instead should collect all incorrect parameters and throw a single error with all incorrect values.

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

void Parameters::read_pass_parameters(const fs::path path_params_pass) {

	const vector<string> exptd_params_pass{
		"ALMax", "ALProdMax_Min", "ALProdMax_Max",
		"AngleFirstOrderSideView_Min", "AngleFirstOrderSideView_Max",
		"AngleSecondOrderTopView_Min", "AngleSecondOrderTopView_Max", 
		"BetaD_Min", "BetaD_Max", "BetaS",
		"BranchMortMassRate", "BranchMortMassScalingExponent", 
		"BranchMortMethod", "BranchMortRandomRate",
		"BrCollide", "CarbonOverheadCosts",
		"CBLratio", "CBWratio", "DistanceVoxelLightCal", "EdgeC",
		"FormFactorWood", "Hsun", "Imax", "InitialDiameter",
		"InternodeLengthBranchMax_Min", "InternodeLengthBranchMax_Max",
		"InternodeLengthBranchMin_Min", "InternodeLengthBranchMin_Max", 
		"InternodeLengthTrunkMax_Min", "InternodeLengthTrunkMax_Max", 
		"InternodeLengthTrunkMin_Min", "InternodeLengthTrunkMin_Max",
		"KInt_Min", "KInt_Max",
		"LDBranch", "LDTreeDev_Min", "LDTreeDev_Max", 
		"LightC", "LightExtinctionCoeff",
		"LightThreshApical_Min", "LightThreshApical_Max",
		"LPratio", "MinLeafArea", "MinLeafAreaRatio",
		"MortalityBiomassRate", "MortalityBiomassScalingExponent",
		"MortalityDisturbanceFrequency", "MortalityDisturbanceRate", 
		"MortalityNeighMinDiameter", "MortalityNeighRate",
		"NumberSeedlingPerHa_Min", "NumberSeedlingPerHa_Max",
		"NumberSpecies", 
		"PhyllotaxisFirstOrder_Min", "PhyllotaxisFirstOrder_Max",
		"PipeLengthMethod", 
		"PipeReuseFactor_Min", "PipeReuseFactor_Max", 
		"RespirationRateWood", "SafetyFactorTrunk", 
		"ShorteningFactor_Min", "ShorteningFactor_Max", 
		"SiteIndex", "SLA_Min", "SLA_Max",
		"Stochasticity",
		"StochasticityAngleFirstOrderSideView_Min",
		"StochasticityAngleFirstOrderSideView_Max",
		"StochasticityAngleFirstOrderTopView_Min",
		"StochasticityAngleFirstOrderTopView_Max",
		"StochasticityAngleSecondOrderTopView_Min",
		"StochasticityAngleSecondOrderTopView_Max",
		"StochasticityTropismStrength_Min",
		"StochasticityTropismStrength_Max",
		"StochasticityTwisting_Min",
		"StochasticityTwisting_Max",
		"StopCriterionBasalArea",
		"TreeCompetitionDist", "TreeCompetitionNum",
		"TreeMortBiomass", "TreeMortCarbon",
		"TreeMortDist", "TreeMortNeigh",
		"TropismStrength_Min", "TropismStrength_Max",
		"Tyear",
		"WoodDensity_Min", "WoodDensity_Max"
	};

	string input_param;
	vector<double> input_vals(exptd_params_pass.size());

	// Read input file
	ifstream ifs_pass{ path_params_pass };
	if (!ifs_pass.is_open()) {
		throw logic_error("Cannot open " + input_file_pass_);
	}
	for (int i = 0; i < exptd_params_pass.size(); i++) {
		ifs_pass >> input_param >> input_vals[i];
		// Check parameter name validity
		if (input_param != exptd_params_pass[i]) {
			throw logic_error("Incorrect parameter name in " + input_file_pass_
				+ " on line " + to_string(i) + ": "
				+ input_param + " should be " + exptd_params_pass[i]
			);
		}
	}
	ifs_pass.close();
	ifs_pass.clear();

	// Parameter value validity
	check_pass_parameters(exptd_params_pass, input_vals);
	
	// Assign input values
	PassParams pp;
	pp.al_max = input_vals[0];
	pp.al_prod_max = ParamRange(input_vals[1], input_vals[2]);
	pp.angle_first_order = ParamRange(input_vals[3], input_vals[4]);
	pp.angle_sec_order = ParamRange(input_vals[1], input_vals[2]);
	pp.beta_d = ParamRange(input_vals[1], input_vals[2]);
	pp.beta_s = input_vals[0];
	pp.branch_mort_mass_rate = input_vals[0];
	pp.branch_mort_mass_exp = input_vals[0];
	pp.branch_mort_method = input_vals[0];
	pp.branch_mort_rnd_rate = input_vals[0];
	pp.branches_collide = input_vals[0];
	pp.carbon_overhead_costs = input_vals[0];
	pp.cbl_ratio = input_vals[0];
	pp.cbw_ratio = input_vals[0];
	pp.dist_vox_light_cal = input_vals[0];
	pp.edge_c = input_vals[0];
	pp.form_factor_wood = input_vals[0];
	pp.h_sun = input_vals[0];
	pp.i_max = input_vals[0];
	pp.init_diameter = input_vals[0];
	pp.internode_len_branch_max = ParamRange(input_vals[1], input_vals[2]);
	pp.internode_len_branch_min = ParamRange(input_vals[1], input_vals[2]);
	pp.internode_len_trunk_max = ParamRange(input_vals[1], input_vals[2]);
	pp.internode_len_trunk_min = ParamRange(input_vals[1], input_vals[2]);
	pp.k_int = ParamRange(input_vals[1], input_vals[2]);
	pp.ld_branch = input_vals[0];
	pp.ld_tree_dev = ParamRange(input_vals[1], input_vals[2]);
	pp.light_c = input_vals[0];
	pp.light_ext_coeff = input_vals[0];
	pp.light_thresh_apical = ParamRange(input_vals[1], input_vals[2]);
	pp.lp_ratio = input_vals[0];
	pp.min_leaf_area = input_vals[0];
	pp.min_leaf_area_ratio = input_vals[0];
	pp.mort_biomass_rate = input_vals[0];
	pp.mort_biomass_exp = input_vals[0];
	pp.mort_dist_freq = input_vals[0];
	pp.mort_dist_rate = input_vals[0];
	pp.mort_neigh_diameter = input_vals[0];
	pp.mort_neigh_rate = input_vals[0];
	pp.nb_seedling_per_ha = ParamRange(input_vals[1], input_vals[2]);
	pp.nb_species = input_vals[0];
	pp.phyllotaxis_first_order = ParamRange(input_vals[1], input_vals[2]);
	pp.pipe_len_method = input_vals[0];
	pp.pipe_reuse_fct = ParamRange(input_vals[1], input_vals[2]);
	pp.respi_rate_wood = input_vals[0];
	pp.safety_fct_trunk = input_vals[0];
	pp.shortening_fct = ParamRange(input_vals[1], input_vals[2]);
	pp.site_index = input_vals[0];
	pp.sla = ParamRange(input_vals[1], input_vals[2]);
	pp.stochasticity = input_vals[0];
	pp.stoch_angle_first_order_side = ParamRange(input_vals[1], input_vals[2]);
	pp.stoch_angle_first_order_top = ParamRange(input_vals[1], input_vals[2]);
	pp.stoch_angle_sec_order = ParamRange(input_vals[1], input_vals[2]);
	pp.stoch_tropism_strength = ParamRange(input_vals[1], input_vals[2]);
	pp.stoch_twisting = ParamRange(input_vals[1], input_vals[2]);
	pp.stop_criterion = input_vals[0];
	pp.tree_comp_dist = input_vals[0];
	pp.tree_comp_num = input_vals[0];
	pp.tree_mort_biomass = input_vals[0];
	pp.tree_mort_carbon = input_vals[0];
	pp.tree_mort_dist = input_vals[0];
	pp.tree_mort_neigh = input_vals[0];
	pp.tropism_strength = ParamRange(input_vals[1], input_vals[2]);
	pp.nb_sunny_days = input_vals[0];
	pp.wood_density = ParamRange(input_vals[1], input_vals[2]);
	pass_params_ = pp;

}

void Parameters::check_pass_parameters(const vector<string>& param_names, const vector<double>& input_vals) const 
{
	assert(param_names.size() == input_vals.size());
	map<string, double> input_map;
	for (int i = 0; i < param_names.size(); ++i) {
		input_map.emplace(param_names[i], input_vals[i]);
	}

	// TRUE/FALSE parameters
	const set<string> bool_params{ "EdgeC", "BrCollide", 
		"PipeLengthMethod", "Stochasticity", 
		"TreeMortBiomass", "TreeMortCarbon",
		"TreeMortDist", "TreeMortNeigh"
	};
	for (string p : bool_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && (it->second != 0L && it->second != 1L))
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be either 0 or 1.");
		}
	}

	// Proportion/fraction parameters
	const set<string> prop_params{ "BranchMortMassRate", "BranchMortRandomRate",
		"MortalityBiomassRate", "MortalityDisturbanceRate", "MortalityNeighRate",
		"PipeReuseFactor_Min", "PipeReuseFactor_Max", "SafetyFactorTrunk", "SiteIndex",
		"ShorteningFactor_Min", "ShorteningFactor_Max", "FormFactorWood"
	};
	for (string p : prop_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && !(it->second >= 0.0f && it->second <= 1.0f))
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be between 0 and 1.");
		}
	}

	const set<string> positive_params{ 
		"ALMax", "ALProdMax_Min", "ALProdMax_Max",
		"BetaD_Min", "BetaD_Max", "BetaS",
		"BranchMortMassScalingExponent",
		"CBLratio", "CBWratio", "DistanceVoxelLightCal",
		"Imax", "InitialDiameter",
		"LDBranch", "LDTreeDev_Min", "LDTreeDev_Max",
		"LightExtinctionCoeff",
		"MortalityBiomassScalingExponent",
		"MortalityDisturbanceFrequency", 
		"MortalityNeighMinDiameter", 
		"RespirationRateWood", 
		"TreeCompetitionDist"
	};
	for (string p : positive_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && it->second < 0.0f)
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be positive or zero.");
		}
	}

	const set<string> strictly_positive_params{ 
		"CarbonOverheadCosts",
		"InternodeLengthBranchMax_Min", "InternodeLengthBranchMax_Max",
		"InternodeLengthBranchMin_Min", "InternodeLengthBranchMin_Max",
		"InternodeLengthTrunkMax_Min", "InternodeLengthTrunkMax_Max",
		"InternodeLengthTrunkMin_Min", "InternodeLengthTrunkMin_Max",
		"KInt_Min", "KInt_Max",
		"LightThreshApical_Min", "LightThreshApical_Max",
		"LPratio", "MinLeafArea", "MinLeafAreaRatio",
		"NumberSeedlingPerHa_Min", "NumberSeedlingPerHa_Max",
		"SLA_Min", "SLA_Max",
		"StopCriterionBasalArea",
		"WoodDensity_Min", "WoodDensity_Max"
	};
	for (string p : strictly_positive_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && it->second <= 0.0f)
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be strictly positive.");
		}
	}

	const set<string> angle_params{ 
		"AngleFirstOrderSideView_Min", "AngleFirstOrderSideView_Max",
		"AngleSecondOrderTopView_Min", "AngleSecondOrderTopView_Max"
	};
	for (string p : angle_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && !(it->second >= 0.0f && it->second <= 180.0f))
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be between 0 and 180 degrees.");
		}
	}

	const set<string> above_one_params{
		"NumberSpecies", 
		"PhyllotaxisFirstOrder_Min", "PhyllotaxisFirstOrder_Max"
	};
	for (string p : above_one_params) {
		for (auto it = input_map.find(p); it != input_map.end(); ++it) {
			if (it->first == p && it->second < 1L)
				throw logic_error(it->first + " is " + to_string(it->second) + ", should be at least 1.");
		}
	}

	// Specific values
	for (auto it = input_map.find("TreeCompetitionNum"); it != input_map.end(); ++it) {
		if (!(it->second >= 0L && it->second <= 8L))
			throw logic_error(it->first + " is " + to_string(it->second) + ", should be between 0 and 8.");
	}
	for (auto it = input_map.find("BranchMortMethod"); it != input_map.end(); ++it) {
		if ((it->second != 0L && it->second != 1L && it->second != 2L))
			throw logic_error(it->first + " is " + to_string(it->second) + ", should be either 0, 1 or 2.");
	}
	for (auto it = input_map.find("LightC"); it != input_map.end(); ++it) {
		if ((it->second != 1L && it->second != 2L && it->second != 3L))
			throw logic_error(it->first + " is " + to_string(it->second) + ", should be either 1, 2 or 3.");
	}
	for (auto it = input_map.find("Hsun"); it != input_map.end(); ++it) {
		if (!(it->second >= 0L && it->second <= 24L))
			throw logic_error(it->first + " is " + to_string(it->second) + ", should be between 0 and 24 hours.");
	}
	for (auto it = input_map.find("Tyear"); it != input_map.end(); ++it) {
		if (!(it->second >= 0L && it->second <= 365L))
			throw logic_error(it->first + " is " + to_string(it->second) + ", should be between 0 and 365 days.");
	}

	// These params can be negative, AFAICS any value goes so no check
	const set<string> anything_params{
		"StochasticityAngleFirstOrderSideView_Min",
		"StochasticityAngleFirstOrderSideView_Max",
		"StochasticityAngleFirstOrderTopView_Min",
		"StochasticityAngleFirstOrderTopView_Max",
		"StochasticityAngleSecondOrderTopView_Min",
		"StochasticityAngleSecondOrderTopView_Max",
		"StochasticityTropismStrength_Min",
		"StochasticityTropismStrength_Max",
		"StochasticityTwisting_Min",
		"StochasticityTwisting_Max",
		"TropismStrength_Min", "TropismStrength_Max"
	};

	// TODO: also check min <= max for all pairs

}