//
// Created by WuXiangGuJun on 2023/7/16.
//
#pragma once

class Canvas;
// Shape.hpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(Canvas* canvas) = 0;
};