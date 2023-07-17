//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include <Color.hpp>
#include <core/SkFont.h>
#include <core/SkPaint.h>
#include <core/SkTextBlob.h>

class Paint {
private:
    SkPaint skPaint;
    SkFont skFont;
    SkTextBlobBuilder builder;
    sk_sp<SkTextBlob> textBlob;

public:
    Paint() {
        //builder.allocRun(skFont);
        textBlob = builder.make();
    }

    void setAntiAlias(bool aa) {
        skPaint.setAntiAlias(aa);
    }

    void setFontSize(float size) {
        skFont.setSize(size);
    }

    void setColor(Color color) {
        skPaint.setColor(color.toSkColor());
    }

    SkPaint toSkPaint() {
        return skPaint;
    }
};