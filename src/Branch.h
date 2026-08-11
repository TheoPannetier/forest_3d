#pragma once
using namespace std;

#include "Voxel.h"
#include "Utils.h"

class Branch
{
public:
	Branch(int tree_id, int branch_id, float length, float diameter, int order) 
		: treeId(tree_id), branchID(branch_id), length(length), diameter(diameter),
		lengthPrev(length), order(order)
	{
	}
	
	int getID() const { return branchID; }

	CoordInt getVox(int index) const { return voxels[index]; }

	CoordInt getVox(int x, int y, int z) const
	{
		CoordInt target_coord(x, y, z);
		auto it = find_if(voxels.begin(), voxels.end(), 
			[target_coord](CoordInt c) { return c == target_coord; });
		if (it != voxels.end()) return *it;
		return coord_not_found;
	}

	void addVox(int x, int y, int z)
	{
		if (getVox(x, y, z) == coord_not_found)
			voxels.push_back(CoordInt(x, y, z));
	}

	void removeVox(int x, int y, int z)
	{
		CoordInt target_coord(x, y, z);
		auto it = find_if(voxels.begin(), voxels.end(),
			[target_coord](CoordInt c) { return c == target_coord; });
		if (it != voxels.end()) {
			std::size_t i = std::distance(voxels.begin(), it);
			voxels[i] = std::move(voxels.back()); // swap and pop
			voxels.pop_back();
		}
	}

	int voxCount() const { return voxels.size(); }

	CoordFloat getPos() const { return pos; }
	void setPos(float x, float y, float z) { pos = CoordFloat(x, y, z);}

private:
	int branchID;
	int treeId;
	int order;
	float length;
	float diameter;
	float lengthPrev;
	float diameterPrev = 0.0f;
	float biomassInc = 0.0f;
	CoordFloat pos;
	float dLBPot = 0.0f;
	float LInc = 0.0f;
	float phylloCurr = 0.0f;
	int phylloRound = 0L;
	float leafBiomass = 0.0f;
	float leafBiomassProduction = 0.0f;
	float leafBiomassLoss = 0.0f;
	float branchBiomass = 0.0f;
	float branchBiomassProduction = 0.0f;
	float branchBiomassLoss = 0.0f;

	vector<CoordInt> voxels;
	float lastLateralPos; //position or length along branch where last lateral branch was inserted

};
