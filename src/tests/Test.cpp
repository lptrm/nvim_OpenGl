#include "Test.h"
#include "TestClearColor.h"
#include "imgui/imgui.h"
namespace test {
TestMenu::TestMenu(Test *&currentTestPointer)
    : m_CurrentTest(currentTestPointer) {
  std::cout << "TestMenu::TestMenu()" << std::endl;
}
TestMenu::~TestMenu() { std::cout << "TestMenu::~TestMenu()" << std::endl; }
void TestMenu::OnImGuiRender() {
  for (auto &test : m_Tests) {
    if (ImGui::Button(test.first.c_str())) {
      m_CurrentTest = test.second();
    }
  }
}
template <typename T> void TestMenu::RegisterTest(const std::string &name) {
  std::cout << "Registering test " << name << std::endl;
  m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
}

// Spezialisierungen der Funktionsschablone (wenn erforderlich)
template void
TestMenu::RegisterTest<test::TestClearColor>(const std::string &name);
// Weitere Spezialisierungen falls notwendig...
} // namespace test
