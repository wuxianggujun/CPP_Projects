//
// Created by WuXiangGuJun on 2023/7/11.
//
#pragma once

template<typename T>
class Matrix final {
public:
    Matrix(int width, int height) : data_(std::unique_ptr<T[]>(new T[width * height])), width_(width), height_(height) {}

    void Fill(const T &value) {
        for (int i = 0; i < width_ * height_; i++) {
            GetByIndex(i) = value;
        }
    }

    T &Get(int x, int y) {
        return data_[x + y * width_];
    }

    const T &Get(int x, int y) const {
        return data_[x + y * width_];
    }

    T &GetByIndex(int index) {
        return data_.get()[index];
    }

    int MaxSize() const {
        return width_ * height_;
    }

    int Width() {
        return width_;
    }

    int Height() {
        return height_;
    }

    bool IsIn(int x, int y) const {
        return x >= 0 && x < width_ && y >= 0 && y < height_;
    }

private:
    std::unique_ptr<T[]> data_;
    int width_;
    int height_;
};


