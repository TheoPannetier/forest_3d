#pragma once

using namespace std;
#include "Parameters.h"
#include "VoxelArray.h"

class Simulation 
{
public:
	Simulation(const Parameters& params);
	void run();
private:
	void step_();
	void compute_light_();
	void resolve_dispersal_();
	void resolve_growth_();
	void resolve_mortality_();
	void run_reports_();
	Parameters params_;
	VoxelArray vox_matrix_;
	bool single_tree_mode = false; // TODO: static?
};