//
// Created by WuXiangGuJun on 2023/7/16.
//
#pragma once

class Canvas;

class Shape {
protected:
    Paint paint;
public:
    virtual ~Shape() = default;

    virtual void initPaint() {
        paint.setColor(SK_ColorBLACK);
        paint.setAntiAlias(true);
    }

    SkPaint getPaint() {
        return paint.toSkPaint();
    }

    virtual void draw(Canvas *canvas) = 0;
};