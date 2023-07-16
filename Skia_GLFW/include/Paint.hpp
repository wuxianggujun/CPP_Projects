//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include <Color.hpp>

class Paint {
private:
    SkPaint skPaint;

public:
    Paint() {
        skPaint.setAntiAlias(true);
    }

    void setColor(Color color) {
        skPaint.setColor(color.toSkColor());
    }

    SkPaint toSkPaint() {
        return skPaint;
    }
};