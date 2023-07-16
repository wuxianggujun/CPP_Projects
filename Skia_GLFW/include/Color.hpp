//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include <core/SkColor.h>

class Color {
public:
    SkColor value;

    // 内部声明
    static const Color white;

public:

    Color(SkColor skColor) : value(skColor) {

    }

    Color(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue) : value(SkColorSetARGB(alpha, red, green, blue)) {
    }

    uint8_t getAlpha() const {
        return SkColorGetA(value);
    }

    uint8_t getRed() const {
        return SkColorGetR(value);
    }

    uint8_t getGreen() const {
        return SkColorGetG(value);
    }

    uint8_t getBlue() const {
        return SkColorGetB(value);
    }

    SkColor toSkColor() const {
        return value;
    }

    static Color fromSkColor(SkColor skColor) {
        return {skColor};
    }
};

// 外部定义
inline const Color Color::white = {SK_ColorWHITE};