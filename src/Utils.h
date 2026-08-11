#pragma once

struct CoordFloat {
	float x, y, z;
};

struct CoordInt {
	int x, y, z;
};

bool operator==(CoordInt c1, CoordInt c2);

constexpr CoordInt coord_not_found(-9, -9, -9); //default value
