#include "Simulation.h"
#include <iostream>

Simulation::Simulation(const Parameters& params) :
	params_(params)
{
	//const int dim_x = 30, dim_y = 30, dim_z = 30;
	vox_matrix_ = VoxelArray(params.get_dim_x(), params.get_dim_y(), params.get_dim_z());
}

void Simulation::run()
{
	const int nb_years = params_.get_nb_years();
	const double stop_basal_area = params_.get_stop_criterion();
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