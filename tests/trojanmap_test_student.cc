#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest, Test1) {
  // EXPECT_EQ(true, true);
  TrojanMap m;
  auto names = m.Autocomplete("ch");
  for(int i = 0; i < names.size(); i++){
    std::cout << names[i] << std::endl;
  }
}

