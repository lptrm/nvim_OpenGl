#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace test {
class Test {
public:
  Test() {}
  virtual ~Test() {}
  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}
};

class TestMenu : public Test {
public:
  TestMenu(Test *&currentTestPointer);
  ~TestMenu();
  void OnImGuiRender() override;

  // Vorwärtsdeklaration der Funktionsschablone (keine Implementierung hier)

  template <typename T> void RegisterTest(const std::string &name) {
    std::cout << "Registering test " << name << std::endl;
    m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
  };

private:
  std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
  Test *&m_CurrentTest;
};
} // namespace test
