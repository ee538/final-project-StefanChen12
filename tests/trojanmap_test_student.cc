#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <algorithm>
#include <string>


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
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  std::cout << "---------" << std::endl;

  // Test CalculateShortestPath_Dijkstra

  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);


  // std::string start = "CAVA";
  // std::string end = "Target";

  // // Test CalculateShortestPath_Bellman_Ford
  // std::vector<std::string> result1 = m.CalculateShortestPath_Bellman_Ford(start, end);
  // for(int i = 0; i < result1.size(); i++){
  //   std::cout << result1[i] << std::endl;
  // }]


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
  std::vector<std::string> topo_result = m.DeliveringTrojan(locations, dependencies);
  std::vector<std::string> gt ={"Ralphs","Chick-fil-A", "KFC"};
  EXPECT_EQ(topo_result, gt);

}


// // TEST(TrajanMapJudyTest, Test2) {
  
// // }

