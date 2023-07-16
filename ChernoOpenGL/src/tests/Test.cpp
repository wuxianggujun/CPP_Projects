//
// Created by WuXiangGuJun on 2023/7/15.
//

#include "Test.hpp"
#include <imgui.h>

namespace test {

    TestMenu::TestMenu(test::Test *&currentTestPointer) : m_CurrentTest(currentTestPointer) {

    }

    void TestMenu::OnImGuiRender() {
        for (auto &test: m_Tests) {
            if (ImGui::Button(test.first.c_str())) {
                m_CurrentTest = test.second();
            }
        }

    }


};

