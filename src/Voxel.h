#pragma once

using namespace std;
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include "Tree.h"
#include "Branch.h"

class Voxel
{
public:
	
	Voxel(int x, int y, int z);

	void reset();

	void addTree(Tree* t);
	void removeTree(Tree* t);
	void removeTree(const int i);
	Tree* getTree(const int i);
	int getTreeCount();

	void addBranch(Branch* b, float leafArea);
	void removeBranch(Branch* b);
	Branch* getBranch(int i);
	bool isRelated(Branch* b);
	int getBranchCount();

	float getLeafArea();
	void sumLeafArea();

	float getLeafAreaAxis(int branchId);
	void setLeafAreaAxis(int branchId, float leafArea);

	void setBProdTot(Branch* b, float BProdTot);
	float getBProdTot(Branch* b);
	void removeBProdTot(Branch* b);

	private:
		int x_, y_, z_;

		float light = 0.0f;      // normalized amount of light available in this voxel
		float leafArea = 0.0f;   // total leaf area in this voxel

		vector<Tree*> trees; 						// list of trees in this voxel
		vector<Branch*> branches;					// list of axes in this voxel
		unordered_map<int, float> leafAreaBranches;	// leaf area of a specific axis found in this voxel
		unordered_map<int, float> BProdTotNew;		// total biomass produced for branches in this voxel
};

