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

TEST(Trojanmaptest, Cycledetection){
    TrojanMap m;
    std::string file = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_dependencies.csv";
    std::vector<std::vector<std::string>> result = m.ReadDependenciesFromCSVFile(file);
    for(int i = 0; i < result.size(); i++){
      for(int j = 0; j < result[i].size(); j++){
        std::cout << result[i][j] << std::endl;
      }
    }
}

// TEST(TrajanMapJudyTest, Test2) {
  
// }
