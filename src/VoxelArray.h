
#pragma once
#include "Voxel.h"

using namespace std;

class VoxelArray {
public:
    VoxelArray() {}; // compiler says default constructor is absolutely necessary

    VoxelArray(size_t width,
        size_t height,
        size_t depth)
        : width_(width),
        height_(height),
        depth_(depth)
    {
        matrix_.reserve(width * height * depth);

        for (size_t z = 0; z < depth; ++z) {
            for (size_t y = 0; y < height; ++y) {
                for (size_t x = 0; x < width; ++x) {
                   matrix_.emplace_back(CoordInt(x, y, z));
                }
            }
        }

    }

    Voxel& operator()(size_t x,
        size_t y,
        size_t z)
    {
        return matrix_[index(x, y, z)];
    }

    const Voxel& operator()(size_t x,
        size_t y,
        size_t z) const
    {
        return matrix_[index(x, y, z)];
    }

    void reset()
    {
        matrix_.clear();
    }

private:
    size_t index(size_t x,
        size_t y,
        size_t z) const
    {
        return z * width_ * height_
            + y * width_
            + x;
    }

    size_t width_, height_, depth_;
    vector<Voxel> matrix_;
};

