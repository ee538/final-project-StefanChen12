#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <algorithm>
#include <string>

// Auto Complete
TEST(TrojanMapStudentTest, Autocomplete) {
  TrojanMap m;
  //1
  auto names1 = m.Autocomplete("ch");
  std::cout << "ch:  " << std::endl;
  for(int i = 0; i < names1.size(); i++){
    std::cout << names1[i] << std::endl;
  }
  std::cout<< "---------" << std::endl;

  //2
  auto names2 = m.Autocomplete("ta");
  std::cout << "ta:  " << std::endl;
  for(int i = 0; i < names2.size(); i++){
    std::cout << names2[i] << std::endl;
  }
  std::cout<< "---------" << std::endl;

  //3
  auto names3 = m.Autocomplete("po");
  std::cout << "po:  " << std::endl;
  for(int i = 0; i < names3.size(); i++){
    std::cout << names3[i] << std::endl;
  }
  std::cout << "--------" << std::endl;
}

//GetPosition
TEST(TrojanMapStudentTest, GetPosition) {
  TrojanMap m;

  auto position1 = m.GetPosition("Chase Plaza Heliport");
  std::pair<double, double> ans1(34.0372348,-118.2589630);
  EXPECT_EQ(ans1, position1);

  auto position2 = m.GetPosition("Tap Two Blue");
  std::pair<double, double> ans2(34.0311992,-118.2736016);
  EXPECT_EQ(ans2, position2);

  auto position3 = m.GetPosition("  ");
  std::pair<double, double> ans3(-1, -1);
  EXPECT_EQ(ans3, position3);

  std::cout << "--------" << std::endl;
}

// the answer were wrong
TEST(TropjanMapStudentTest, EditDistance){
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  EXPECT_EQ(m.CalculateEditDistance("a", "abcd"), 3);
  std::cout << "--------" << std::endl;
}

TEST(TrojanMapStudentTest,  ShortestPath){
TrojanMap m;
std::vector<std::string> ans{
     "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441", 
     "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259", 
     "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572", 
     "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
     "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060", 
     "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463", 
     "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962", 
     "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576", 
     "6813379548", "4015372476",  "4015372474", "4015372468", "4015372463", "6819179749", "1732243544", 
     "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
     "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"}; // Expected path
  auto path1 = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");

  EXPECT_EQ(path1, ans);

//
  auto path2 = m.CalculateShortestPath_Dijkstra("Burger Factory", "Ralphs");
  for (auto a: path2){
    std::cout<< a <<std::endl;
  }
  // std::vector<std::string> gt2{
  //     "7695616467", "5237417649", "9591449485", "6814769290", "6814820018", "6814820010", "6814820015", "9591449515", "6813379419", "6047234443", "6813379418", "6045054380", "6813379385", "6813379474", "6813379475", "6818390144", "6818390145", "6813405201", "6813405202", "6813405203", "6813405204", "6813405205", "6813405206", "6813405207", "6813405208", "6813405209", "6813405210", "6813405211", "6813405259", "6813405260", "123152294", "6816193786", "6813416157", "6813405226", "123096999", "6813405227", "122719268", "7811301934", "122719270", "122719273", "1771004834", "1771004860", "122719048", "122719050", "122719053", "122719056", "4015203138", "4015203139", "123178708", "703112358", "123178710", "703112359", "123019326", "2514542014", "2514541989", "2514541994", "2514541963", "2514542196", "2514541718", "2514541689", "703112384", "122625019", "703112365", "6807615077", "703112381", "1717938395", "1717938335", "703112376", "7466004085", "1717938421", "4009734483", "1717938410", "6807396826", "4009734484", "6807396835", "1717938336", "6793018809", "4009734482", "4059513787", "1717938387", "5621075844", "6805895749", "1717938350", "6805865365", "7384983927", "6807396813", "6807396816", "7384983933", "6792211674", "122737114", "6807396817", "1717938545", "8221360810"};
  // path = m.CalculateShortestPath_Dijkstra("Workshop Salon & Boutique", "Adams & Cimarron");
  // EXPECT_EQ(path, gt2);

//Bellman-Ford implementation


// Dijkstra implementation
// Plot two paths, and measure and report time spent by two algorithms.


}


// TEST(TrojanMapStudentTest, Test1) {
//   TrojanMap m;
//   // Test GetName:
//   std::string name = m.GetName("150934188");
//   // Test GetLat
//   double lat = m.GetLat("150934188");
//   // Test GetLon
//   double lon = m.GetLon("150934188");
//   // Test GetID
//   std::string id = m.GetID("Jefferson/USC");
//   std::cout << name << std::endl;
//   std::cout << lat << std::endl;
//   std::cout << lon << std::endl;
//   std::cout << id << std::endl;

//   std::cout<< "---------" << std::endl;

//   // Test GetClosestName.
//   std::string str1 = m.FindClosestName("Ralp");
//   std::cout << str1 << std::endl;

//   // Test CalculateEditDistance.
//   std::string str2 = m.FindClosestName("Rolph");
//   std::cout << str2 << std::endl;
//   EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
//   EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
//   std::cout << "---------" << std::endl;

//   // Test CalculateShortestPath_Dijkstra
//   // Test from Ralphs to Chick-fil-A
//   auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
//   std::vector<std::string> gt{
//       "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
//       "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
//       "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
//       "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
//       "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
//       "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
//       "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
//       "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
//       "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
//       "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
//       "6814916515","6820935910","4547476733"}; // Expected path
//   // Print the path lengths
//   std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   EXPECT_EQ(path, gt);
  
//   // Reverse the input from Ralphs to Chick-fil-A
//   path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
//   std::reverse(gt.begin(),gt.end()); // Reverse the path

//   // Print the path lengths
//   std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   EXPECT_EQ(path, gt);

// ////////////////////////////////////////////////////////////////////////////////////////
//   // path = m.CalculateShortestPath_Bellman_Ford( "Chick-fil-A", "Ralphs");

//   // // Print the path lengths
//   // std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   // std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   // EXPECT_EQ(path, gt);
// }
  

  
// TEST(TrojanmapTest, cyclDetection) {
//    TrojanMap m;
  
//   // Test case 1
//   std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
//   auto sub1 = m.GetSubgraph(square1);
//   bool result1 = m.CycleDetection(sub1, square1);
//   EXPECT_EQ(result1, true);

//   // Test case 2
//   std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
//   auto sub2 = m.GetSubgraph(square2);
//   bool result2 = m.CycleDetection(sub2, square2);
//   EXPECT_EQ(result2, false);
// }



// TEST(Trojanmaptest, Cycledetection) {
//   // topological sort
//     TrojanMap m;
//     std::string file = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_dependencies.csv";
//     std::vector<std::vector<std::string>> dependencies = m.ReadDependenciesFromCSVFile(file);
//     for(int i = 0; i < dependencies.size(); i++){
//       for(int j = 0; j < dependencies[i].size(); j++){
//         std::cout << dependencies[i][j] << std::endl;
//       }
//     }


//   std::cout << "-----------------" << std::endl;
//     std::string loc = "/Users/stefan/Documents/EE538_Computational_Principles_for_Electrical_Engineering/Homeworks/Final/final-project-StefanChen12/input/topologicalsort_locations.csv";
//     std::vector<std::string> locations = m.ReadLocationsFromCSVFile(loc);
//     for(int i = 0; i < locations.size(); i++){
//       std::cout << locations[i] << std::endl;
//     }


//   // testing DeliveringTrojan
//   std::vector<std::string> topo_result = m.DeliveringTrojan(locations, dependencies);
//   std::vector<std::string> gt ={"Ralphs","Chick-fil-A", "KFC"};
//   EXPECT_EQ(topo_result, gt);
// }


// // // TEST(TrajanMapJudyTest, Test2) {
  
// // // }

TEST(Trojanmaptest, Dijkstra){
  TrojanMap m;
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  for(int i = 0; i < path.size(); i++){
    std::cout << path[i] << std::endl;
  }
}

TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout << "end" << std::endl;
  for(int i = 0; i < result.second.size(); i++){
    for(int j = 0; j < result.second[i].size(); j++){
      std::cout << result.second[i][j] << std::endl;
    }
  }
  std::cout << result.second.size() << std::endl;
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// TEST(Trojanmaptest, Dijkstra){
//   TrojanMap m;
//   auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
//   for(int i = 0; i < path.size(); i++){
//     std::cout << path[i] << std::endl;
//   }
// }

// TEST(TrojanMapTest, FindNearby)
// {
//   TrojanMap m;

//   auto result = m.FindNearby("supermarket", "Ralphs", 10, 10);
//   std::vector<std::string> ans{"Trader Joes", "Cal Mart Beer & Wine Food Store", "Food 4 Less"};
//   EXPECT_EQ(result, ans);

// }

