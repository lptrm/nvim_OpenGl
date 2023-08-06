#pragma once

#include "Renderer.h"
#include "Test.h"
#include "imgui/imgui.h"

namespace test {
class TestClearColor : public Test {
private:
  float m_ClearColor[4];

public:
  TestClearColor();
  ~TestClearColor();
  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace test
