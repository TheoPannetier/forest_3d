#pragma once

using namespace std;
#include<vector>
#include<unordered_map>
#include "Tree.h"
#include "Branch.h"

class Vox
{
public:
	
	Vox(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void addTree(Tree* t)
	{
		trees.push_back(t);
	}

	Tree* getTree(const int i)
	{
		return trees[i];
	}

	int getTreeCount()
	{
		return trees.size();
	}

	void removeTree(Tree* t)
	{
		auto it = std::find(trees.begin(), trees.end(), t);
		if (it != trees.end()) {
			std::size_t i = std::distance(trees.begin(), it);
			this->removeTree(i);
		}
	}

	void removeTree(const int i)
	{
		trees[i] = std::move(trees.back()); // swap and pop
		trees.pop_back();
	}

	void reset()
	{
		light = 0.0f;
		leafArea = 0.0f;
		trees.clear();
		branches.clear();
		leafAreaBranches.clear();
		BProdTotNew.clear();
	}

	float getLeafArea()
	{
		return leafArea;
	}

	float sumLeafArea()
	{
		leafArea = 0; // reset value
		for (auto& b : branches)
		{
			leafArea += getLeafAreaAxis(b->getID());
		}
	}

	void addBranch(Branch* b, float leafArea)
	{
		auto it = find(branches.begin(), branches.end(), b);
		if (it == branches.end()) {
			branches.push_back(b);
			leafAreaBranches.emplace(b->getID(), leafArea);
		}
	}

	void removeBranch(Branch* b)
	{
		auto it = std::find(branches.begin(), branches.end(), b);
		if (it != branches.end()) {
			std::size_t i = std::distance(branches.begin(), it);
			branches[i] = std::move(branches.back()); // swap and pop
			branches.pop_back();
			int id = b->getID();
			leafAreaBranches.erase(id);
			BProdTotNew.erase(id);
		}
	}

	Branch* getBranch(int i)
	{
		return branches[i];
	}

	int getBranchCount()
	{
		return branches.size();
	}

	float getLeafAreaAxis(int branchId)
	{
		auto it = leafAreaBranches.find(branchId);
		if (it != leafAreaBranches.end()) {
			return it->second;
		}
		else {
			throw runtime_error();
		}
	}

	void setLeafAreaAxis(int branchId, float leafArea)
	{
		auto it = leafAreaBranches.find(branchId);
		if (it == leafAreaBranches.end()) {
			leafAreaBranches.emplace(branchId, leafArea);
		}
		else {
			it->second = leafArea;
		}
	}

	bool isRelated(Branch* b)
	{
		auto it = find(branches.begin(), branches.end(), b);
		return it != branches.end();
	}

	void setBProdTot(Branch* b, float BProdTot)
	{
		int branchId = b->getID();
		auto it = BProdTotNew.find(branchId);
		if (it == BProdTotNew.end()) {
			BProdTotNew.emplace(branchId, BProdTot);
		}
		else {
			it->second = BProdTot;
		}
	}

	float getBProdTot(Branch* b)
	{
		return BProdTotNew.at(b->getID());
	}

	void removeBProdTot(Branch* b)
	{
		int id = b->getID();
		if (BProdTotNew.find(id) != BProdTotNew.end()) {
			BProdTotNew.erase(id);
		}
	}

	private:
		int x, y, z;

		float light = 0.0f;      // normalized amount of light available in this voxel
		float leafArea = 0.0f;   // total leaf area in this voxel

		vector<Tree*> trees; 						// list of trees in this voxel
		vector<Branch*> branches;					// list of axes in this voxel
		unordered_map<int, float> leafAreaBranches;	// leaf area of a specific axis found in this voxel
		unordered_map<int, float> BProdTotNew;		// total biomass produced for branches in this voxel

		float GR;
};


static VoxBase[][][] getVoxArray(int x, int y, int z)
{
	VoxBase voxels[][][] = new VoxBase[x][y][z];

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			for (int k = 0; k < z; ++k)
			{
				voxels[i][j][k] = new VoxBase(i, j, k);
			}
		}
	}

	return voxels;
}

static void resetVoxels(VoxBase[][][] voxs)
{
	//reset voxels
	for (int i = 0; i < voxs.length; ++i)
	{
		for (int j = 0; j < voxs[i].length; ++j)
		{
			for (int k = 0; k < voxs[i][j].length; ++k)
			{
				voxs[i][j][k].reset();
			}
		}
	}
}