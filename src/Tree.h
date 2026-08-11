#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Tree
{
public:
	Tree(float tree_id, float x, float y, int vox_x, int vox_y, float length, float diameter)
        : tree_id_(tree_id), x_(x), y_(y), voxX(vox_x), voxY(vox_y), length_(length), diameter_(diameter),
        xPositionBudMax(x), xPositionBudMin(x), yPositionBudMax(y), yPositionBudMin(y)
    {
    }
	int getID() const { return tree_id_; }

    float getBasalArea() const
    {
        float radius = diameter_ / 2.0f;
        return M_PI * radius * radius;
    }

    float getVolume() const
    {
        return length_ * getBasalArea();
    }

private:
	int tree_id_;
	int species_id_;
	float x_, y_;
	float length_;
	float diameter_;
	
    int voxX;
    int voxY;
	
    int age = 0;
	
    float diameterPrev = 0.0f;
    float heightPrev = 0.0f;
    
    float biomassInc = 0.0f;
    float dLTPot = 0.0f;
    float LInc = 0.0f;
    float crownRadius = 0.0f;
    
    float leafBiomass = 0.0f;
    float leafBiomassProduction = 0.0f;
    float leafBiomassLoss = 0.0f;
    
    float trunkBiomass = 0.0f;
    float branchBiomass1stOrder = 0.0f;
    float branchBiomass2ndOrder = 0.0f;
    
    float trunkBiomassProduction = 0.0f;
    float branchBiomass1stOrderProduction = 0.0f;
    float branchBiomass2ndOrderProduction = 0.0f;

    float trunkBiomassLoss = 0.0f;
    float branchBiomass1stOrderLoss = 0.0f;
    float branchBiomass2ndOrderLoss = 0.0f;

    float xPositionBudMax;
    float xPositionBudMin;
    float yPositionBudMax;
    float yPositionBudMin;
    
    float heightFirstBranching;
};
