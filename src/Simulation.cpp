#include "Simulation.h"
#include <iostream>

Simulation::Simulation(const Parameters& params) :
	params_(params)
{
	const GlobalParams& gp = params.get_global_params();
	vox_matrix_ = VoxelArray(gp.dim_x, gp.dim_y, gp.dim_z);
}

void Simulation::run()
{
	const int nb_years = 3;
	const double stop_basal_area = 1000.0;
	double total_basal_area = 0.0f;
	bool stop_criterion_reached = false;

	for (int year = 0; year < nb_years && !stop_criterion_reached; year++)
	{

		cout << "Running year " << year + 1 << "\t/\t" << nb_years <<  endl;

		step_();

		//total_basal_area = sum trees diameters;
		stop_criterion_reached = total_basal_area < stop_basal_area;
		if (stop_criterion_reached)
			cout << "Basal area threshold exceeded, exiting simulation.\n";
	}
}

void Simulation::step_()
{
	compute_light_();

	resolve_dispersal_();

	resolve_growth_();

	resolve_mortality_();

	run_reports_();

}

void Simulation::compute_light_() 
{

}
void Simulation::resolve_dispersal_()
{

}

void Simulation::resolve_growth_()
{

}

void Simulation::resolve_mortality_()
{

}

void Simulation::run_reports_()
{

}