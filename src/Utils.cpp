#include "Utils.h"

bool operator==(CoordInt c1, CoordInt c2)
{
	return (c1.x == c2.x && c1.y && c2.y && c1.z == c2.z);
};