//
// Created by WuXiangGuJun on 2023/7/16.
//
#include "SkiaIncludes.hpp"
#include "Canvas.hpp"

class CanvasBuilder {
public:
    static std::unique_ptr<Canvas> build(int width, int height) {
        auto context = CreateGrDirectContext();
        if (!context) {
            throw std::runtime_error("Failed to create context");
        }
        auto surface = CreateSurface(context, width, height);
        if (!surface) {
            throw std::runtime_error("Failed to create surface");
        }
        SkCanvas *skCanvas = surface->getCanvas();

        auto canvas = std::make_unique<Canvas>(skCanvas);
        return canvas;
    }

    static std::unique_ptr<SkCanvas> buildSkCanvas(int width, int height) {
        auto context = CreateGrDirectContext();
        if (!context) {
            throw std::runtime_error("Failed to create context");
        }
        auto surface = CreateSurface(context, width, height);
        if (!surface) {
            throw std::runtime_error("Failed to create surface");
        }
        SkCanvas *skCanvas = surface->getCanvas();
        auto canvas = std::unique_ptr<SkCanvas>(skCanvas);
        return canvas;
    }


private:

    static GrDirectContext *CreateGrDirectContext() {
        auto interface = GrGLMakeNativeInterface();
        return GrDirectContext::MakeGL(interface).release();
    }

    static SkSurface *CreateSurface(GrDirectContext *grDirectContext, int width, int height) {
        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        GrBackendRenderTarget renderTarget(width, height, 0, 0, framebufferInfo);

        SkSurface *skSurface = SkSurface::MakeFromBackendRenderTarget(grDirectContext, renderTarget,
                                                                      kBottomLeft_GrSurfaceOrigin,
                                                                      kRGBA_8888_SkColorType,
                                                                      nullptr, nullptr).release();
        if (skSurface == nullptr) {
            abort();
        }
        return skSurface;
    }
};



