
#pragma once
#include "Vox.h"

using namespace std;

template<typename T>
class Grid3D {
public:
    Grid3D(std::size_t width,
        std::size_t height,
        std::size_t depth)
        : width_(width),
        height_(height),
        depth_(depth),
        data_(width* height* depth)
    {
    }

    T& operator()(std::size_t x,
        std::size_t y,
        std::size_t z)
    {
        return data_[index(x, y, z)];
    }

    const T& operator()(std::size_t x,
        std::size_t y,
        std::size_t z) const
    {
        return data_[index(x, y, z)];
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
    std::vector<T> data_;
};

