//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include "SkiaIncludes.hpp"
#include "Paint.hpp"
#include "Color.hpp"
#include "Shape.hpp"
#include "CanvasBuilder.hpp"


class Canvas {
private:
    std::unique_ptr<SkCanvas> skCanvas;
    std::vector<Shape *> shapes;

public:
    explicit Canvas(SkCanvas *canvas) : skCanvas(canvas) {
    }

    Canvas(int width, int height) {
        skCanvas = CanvasBuilder::buildSkCanvas(width, height);
    }

    void draw(Shape *shape) {
        shapes.push_back(shape);
    }

    void drawRect(const SkRect &rect, Paint paint) {
        skCanvas->drawRect(rect, paint.toSkPaint());
    }

    Paint getPaint() {
        Paint paint;
        paint.setColor(SK_ColorBLUE);
        return paint;
    }

    void flush() {
        for (auto shape: shapes) {
            shape->draw(this);
        }
        skCanvas->flush();
    }


    void clear(Color color) {
        skCanvas->clear(color.toSkColor());
    }


};
