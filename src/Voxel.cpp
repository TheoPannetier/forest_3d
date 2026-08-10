#include "Voxel.h"

Voxel::Voxel(int x, int y, int z) : x_(x), y_(y), z_(z)
{
}

void Voxel::addTree(Tree* t)
{
	trees.push_back(t);
}

Tree* Voxel::getTree(const int i)
{
	return trees[i];
}

int Voxel::getTreeCount()
{
	return trees.size();
}

void Voxel::removeTree(Tree* t)
{
	auto it = std::find(trees.begin(), trees.end(), t);
	if (it != trees.end()) {
		std::size_t i = std::distance(trees.begin(), it);
		this->removeTree(i);
	}
}

void Voxel::removeTree(const int i)
{
	trees[i] = std::move(trees.back()); // swap and pop
	trees.pop_back();
}

void Voxel::reset()
{
	light = 0.0f;
	leafArea = 0.0f;
	trees.clear();
	branches.clear();
	leafAreaBranches.clear();
	BProdTotNew.clear();
}

float Voxel::getLeafArea()
{
	return leafArea;
}

void Voxel::sumLeafArea()
{
	leafArea = 0; // reset value
	for (auto& b : branches)
	{
		leafArea += getLeafAreaAxis(b->getID());
	}
}

void Voxel::addBranch(Branch* b, float leafArea)
{
	auto it = find(branches.begin(), branches.end(), b);
	if (it == branches.end()) {
		branches.push_back(b);
		leafAreaBranches.emplace(b->getID(), leafArea);
	}
}

void Voxel::removeBranch(Branch* b)
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

Branch* Voxel::getBranch(int i)
{
	return branches[i];
}

int Voxel::getBranchCount()
{
	return branches.size();
}

float Voxel::getLeafAreaAxis(int branchId)
{
	auto it = leafAreaBranches.find(branchId);
	if (it != leafAreaBranches.end()) {
		return it->second;
	}
	else {
		string err_msg = "No leaf area element found for branch " + to_string(branchId);
		throw runtime_error(err_msg);
	}
}

void Voxel::setLeafAreaAxis(int branchId, float leafArea)
{
	auto it = leafAreaBranches.find(branchId);
	if (it == leafAreaBranches.end()) {
		leafAreaBranches.emplace(branchId, leafArea);
	}
	else {
		it->second = leafArea;
	}
}

bool Voxel::isRelated(Branch* b)
{
	auto it = find(branches.begin(), branches.end(), b);
	return it != branches.end();
}

void Voxel::setBProdTot(Branch* b, float BProdTot)
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

float Voxel::getBProdTot(Branch* b)
{
	return BProdTotNew.at(b->getID());
}

void Voxel::removeBProdTot(Branch* b)
{
	int id = b->getID();
	if (BProdTotNew.find(id) != BProdTotNew.end()) {
		BProdTotNew.erase(id);
	}
}