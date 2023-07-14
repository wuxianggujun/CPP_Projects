//
// Created by WuXiangGuJun on 2023/7/13.
//
#pragma once

#include <glad/glad.h>
#include <memory>
#include <core/SkCanvas.h>
#include <core/SkSurface.h>
#include <gpu/GrBackendSurface.h>
#include <gpu/GrDirectContext.h>
#include <gpu/gl/GrGLInterface.h>
#include <core/SkCanvas.h>
#include <core/SkColorSpace.h>
#include <core/SkSurface.h>

#include "Paint.hpp"
#include "Color.hpp"


class Canvas {
private:
    GrDirectContext *grDirectContext;
    SkSurface *skSurface;
    SkCanvas *skCanvas;

public:
    Canvas(int width, int height) {
        auto interface = GrGLMakeNativeInterface();
        grDirectContext = GrDirectContext::MakeGL(interface).release();

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        SkColorType colorType = kRGBA_8888_SkColorType;
        GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);
        skSurface = SkSurface::MakeFromBackendRenderTarget(grDirectContext, backendRenderTarget,
                                                           kBottomLeft_GrSurfaceOrigin, colorType,
                                                           nullptr, nullptr).release();
        if (skSurface == nullptr) abort();
        skCanvas = skSurface->getCanvas();
    }

    void draw() {
        SkPaint skPaint;
        skPaint.setAntiAlias(true);
        skPaint.setColor(SK_ColorBLUE);
        skCanvas->drawRect({100, 200, 300, 500}, skPaint);

        skCanvas->flush();
        grDirectContext->flushAndSubmit();
    }

    void flush(){
        skCanvas->flush();
    }


    void clear(Color color) {
        skCanvas->clear(color.toSkColor());
    }



};
