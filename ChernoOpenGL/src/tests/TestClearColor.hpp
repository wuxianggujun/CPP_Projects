//
// Created by WuXiangGuJun on 2023/7/15.
//

#pragma once

#include "Test.hpp"

namespace test {

    class TestClearColor: public Test {
    private:
        float m_ClearColor[4];

    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    };
};