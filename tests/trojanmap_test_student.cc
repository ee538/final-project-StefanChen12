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
  std::string name = m.GetName("150934188");
  // Test GetLat
  double lat = m.GetLat("150934188");
  // Test GetLon
  double lon = m.GetLon("150934188");
  // Test GetID
  std::string id = m.GetID("Jefferson/USC");
  std::cout << name << std::endl;
  std::cout << lat << std::endl;
  std::cout << lon << std::endl;
  std::cout << id << std::endl;

  std::cout<< "---------" << std::endl;

  // Test GetClosestName.
  std::string str1 = m.FindClosestName("Ralp");
  std::cout << str1 << std::endl;

  // Test CalculateEditDistance.
  std::string str2 = m.FindClosestName("Rolph");
  std::cout << str2 << std::endl;

  std::cout << "---------" << std::endl;

  // // Test CalculateShortestPath_Dijkstra
  std::string start = "CAVA";
  std::string end = "Honeybird";
  // std::vector<std::string> result = m.CalculateShortestPath_Dijkstra(start, end);
  // for(int i = 0; i < result.size(); i++){
  //   std::cout << result[i] << std::endl;
  // }
  // std::string s = m.GetID(start); // start
  // std::string v = m.GetID(end); // end
  // double res = m.CalculateDistance(s , v);


  std::vector<std::string> result1 = m.CalculateShortestPath_Bellman_Ford(start, end);
  for(int i = 0; i < result1.size(); i++){
    std::cout << result1[i] << std::endl;
  }
}

TEST(TrojanmapTest, cyclDetection){
   TrojanMap m;
  
  // Test case 1
  std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);
}

// TEST(TrajanMapJudyTest, Test2) {
  
// }
