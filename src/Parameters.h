#pragma once

using namespace std;
#include <string>
#include<vector>

class Parameters
{
public:
	Parameters(const string& param_file);
	size_t get_dim_x() const { return dim_x_; }
	size_t get_dim_y() const { return dim_y_; }
	size_t get_dim_z() const { return dim_z_; }
	int get_nb_years() const { return nb_years_; }
	double get_stop_criterion() const { return stop_criterion_; }

private:
	size_t dim_x_, dim_y_, dim_z_;
	int nb_years_;
	double stop_criterion_;
};