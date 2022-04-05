#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest, Test1) {
  // EXPECT_EQ(true, true);
  // Test Autocomplete
  TrojanMap m;
  auto names = m.Autocomplete("ch");
  for(int i = 0; i < names.size(); i++){
    std::cout << names[i] << std::endl;
  }

  std::cout << "----------" << std::endl;
  // Test GetName:
  double name = m.GetPosition("122659207");
  std::cout << name << std::endl;
}

