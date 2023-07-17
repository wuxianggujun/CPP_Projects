//
// Created by WuXiangGuJun on 2023/7/15.
//

#pragma once

#include "Test.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>

namespace test {

    class TestTexture2D : public Test {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_TranslationA, m_TranslationB;

    public:
        TestTexture2D();

        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    };
};