#pragma once

using namespace std;
#include <string>

class Parameters
{
public:
	Parameters(const string& param_file);
private:
	int dim_x_, dim_y_, dim_z_;
};