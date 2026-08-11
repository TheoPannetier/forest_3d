
#pragma once
#include "Voxel.h"

using namespace std;

class VoxelArray {
public:
    VoxelArray(std::size_t width,
        std::size_t height,
        std::size_t depth)
        : width_(width),
        height_(height),
        depth_(depth)
    {
        matrix_.reserve(width * height * depth);

        for (std::size_t z = 0; z < depth; ++z) {
            for (std::size_t y = 0; y < height; ++y) {
                for (std::size_t x = 0; x < width; ++x) {
                   matrix_.emplace_back(CoordInt(x, y, z));
                }
            }
        }

    }

    Voxel& operator()(std::size_t x,
        std::size_t y,
        std::size_t z)
    {
        return matrix_[index(x, y, z)];
    }

    const Voxel& operator()(std::size_t x,
        std::size_t y,
        std::size_t z) const
    {
        return matrix_[index(x, y, z)];
    }

    void reset()
    {
        matrix_.clear();
    }

private:
    std::size_t index(std::size_t x,
        std::size_t y,
        std::size_t z) const
    {
        return z * width_ * height_
            + y * width_
            + x;
    }

    std::size_t width_, height_, depth_;
    std::vector<Voxel> matrix_;
};

