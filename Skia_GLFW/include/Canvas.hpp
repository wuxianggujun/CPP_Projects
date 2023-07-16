//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include "SkiaIncludes.hpp"
#include "CanvasBuilder.hpp"
#include "Paint.hpp"
#include "Color.hpp"


class Canvas {
private:
    SkCanvas *skCanvas;

public:
    explicit Canvas(SkCanvas *canvas) : skCanvas(canvas) {
    }

    void draw() {
        Paint paint;
        paint.setColor(SK_ColorBLUE);
        drawRect({100, 200, 300, 500}, paint);
    }

    void drawRect(const SkRect &rect, Paint paint) {
        skCanvas->drawRect(rect, paint.toSkPaint());
    }


    void flush() {
        skCanvas->flush();
    }


    void clear(Color color) {
        skCanvas->clear(color.toSkColor());
    }


};
