#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <algorithm>
#include <string>


TEST(TrojanMapStudentTest, Test1) {
  // EXPECT_EQ(true, true);
  // Test Autocomplete
  TrojanMap m;
  // auto names = m.Autocomplete("ch");
  // for(int i = 0; i < names.size(); i++){
  //   std::cout << names[i] << std::endl;
  // }

  // std::cout << "----------" << std::endl;
  // // Test GetName:
  // std::string name = m.GetName("150934188");
  // // Test GetLat
  // double lat = m.GetLat("150934188");
  // // Test GetLon
  // double lon = m.GetLon("150934188");
  // // Test GetID
  // std::string id = m.GetID("Jefferson/USC");
  // std::cout << name << std::endl;
  // std::cout << lat << std::endl;
  // std::cout << lon << std::endl;
  // std::cout << id << std::endl;

  // std::cout<< "---------" << std::endl;

  // // Test GetClosestName.
  // std::string str1 = m.FindClosestName("Ralp");
  // std::cout << str1 << std::endl;

  // // Test CalculateEditDistance.
  // std::string str2 = m.FindClosestName("Rolph");
  // std::cout << str2 << std::endl;

  std::cout << "---------" << std::endl;

  // Test CalculateShortestPath_Dijkstra
  std::string start = "CAVA";
  std::string end = "Target";
  // std::vector<std::string> result = m.CalculateShortestPath_Dijkstra(start, end);
  // for(int i = 0; i < result.size(); i++){
  //   std::cout << result[i] << std::endl;
  // }

  // // Test CalculateShortestPath_Bellman_Ford
  // std::vector<std::string> result1 = m.CalculateShortestPath_Bellman_Ford(start, end);
  // for(int i = 0; i < result1.size(); i++){
  //   std::cout << result1[i] << std::endl;
  // }]

  std::string file = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_locations.csv";
  std::vector<std::string> result = m.ReadLocationsFromCSVFile(file);
  for(int i = 0; i < result.size(); i++){
      std::cout << result[i] << std::endl;
    }

}
  

  
TEST(TrojanmapTest, cyclDetection) {
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


TEST(Trojanmaptest, Cycledetection) {
    TrojanMap m;
    std::string file = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_dependencies.csv";
    std::vector<std::vector<std::string>> dependencies = m.ReadDependenciesFromCSVFile(file);
    for(int i = 0; i < dependencies.size(); i++){
      for(int j = 0; j < dependencies[i].size(); j++){
        std::cout << dependencies[i][j] << std::endl;
      }
    }


  std::cout << "-----------------" << std::endl;
    std::string loc = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_locations.csv";
    std::vector<std::string> locations = m.ReadLocationsFromCSVFile(loc);
    for(int i = 0; i < locations.size(); i++){
      std::cout << locations[i] << std::endl;
    }


  // testing DeliveringTrojan
  // std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  // std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"}};
  std::vector<std::string> topo_result = m.DeliveringTrojan(locations, dependencies);
  std::vector<std::string> gt ={"Ralphs","Chick-fil-A", "KFC"};
  EXPECT_EQ(topo_result, gt);

}


// TEST(TrajanMapJudyTest, Test2) {
  
// }

