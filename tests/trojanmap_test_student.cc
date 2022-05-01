#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <algorithm>
#include <string>
#include <typeinfo>

TEST(TrojanMapStudentTest, AutoComplete){
  std::cout << "=====AutoComplete=====" <<std::endl;
  TrojanMap m;
  // Thers's same initial in the data
  std::string initial = "ch";
  auto res1 = m.Autocomplete(initial);
  std::vector<std::string> ans1 = { "Chinese Street Food", "Chase", "Chucks Chicken & Waffles", "Cheebos Burger", "Chevron", "Chase Plaza Heliport", 
  "Chipotle", "Chevron 2", "Church of Christ", "Chevron 1", "Chick-fil-A" };
  for (auto a: ans1){
    std::cout << a << std::endl;
  }
  

  // Thers's no same initial in the data
  auto res2 = m.Autocomplete("xu");
  std::vector<std::string> ans2 = {};
  EXPECT_EQ(res2, ans2);

  // Test No initial input
  auto res3 = m.Autocomplete("");
  std::vector<std::string> ans3 = {};
  EXPECT_EQ(res3, ans3);
}

TEST(TrojanMapStudentTest, FindPosition) {
  TrojanMap m;
  
  // Test Chick-fil-A
  auto position = m.GetPosition("Chick-fil-A");
  std::pair<double, double> gt1(34.0167334, -118.2825307); // groundtruth for "Chick-fil-A"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Ralphs");
  std::pair<double, double> gt2(34.0317653, -118.2908339); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("Target");
  std::pair<double, double> gt3(34.0257016, -118.2843512); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}

TEST(TrojanMapStudentTest, EditDistance) {
  TrojanMap m;
  std::cout << "=====EditDistance=====" <<std::endl;
  // Test CalculateEditDistance.
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  EXPECT_EQ(m.CalculateEditDistance("abc", "adc"), 1);
}

TEST(TrojanMapStudentTest, ShortestPath){
  std::cout << "=====ShortestPath=====" <<std::endl;
  TrojanMap m;
  // Thers's same initial in the data
  auto resB1 = m.CalculateShortestPath_Bellman_Ford("Ralphs","Target");
  auto resD1 = m.CalculateShortestPath_Dijkstra("Ralphs","Target");
  std::vector<std::string> ans1 = {
     "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131", "7645318201","6813416130","6813416129","123318563",
     "452688940","6816193777","123408705","6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011","6816193692",
     "6816193693","6816193694","4015377691","544693739","6816193696","6804883323","6807937309","6807937306","6816193698","4015377690","4015377689",
     "122814447","6813416159","6813405266","4015372488","4015372487","6813405229","122719216","6813405232","4015372486","7071032399","4015372485",
     "6813379479","6813379584","6814769289","5237417650"};
  EXPECT_EQ(resB1, ans1);
  EXPECT_EQ(resD1, ans1);

  //far distance
  auto resB2 = m.CalculateShortestPath_Bellman_Ford("Pizza King", "Ralphs");
  auto resD2 = m.CalculateShortestPath_Dijkstra("Pizza King", "Ralphs");
  std::vector<std::string> ans2 = {"6278441393", "2613073681","2613073688","2613073683","8410731069","1732243896","6792403557","6792403560","3642844524","1732243600",
"2613073699","2613073701","5249489005","1732243947","122670310","2613073700","122670308","2613073722","2613073691","122688464","2613073695","123289577","1615672692",
"123112737","2193439965","601390387","211752888","4009744690","122625129","122625127","123019477","123019475","1771091142","7229539444","5567736373","5567718503","6814958408",
"123209605","6814958406","4015203118","4015203119","1878026177","6805054066","1771091141","122827894","6805827732","6817053930","122827893","2613081563","123660671",
"1473199412","4583263530","6814958435","6816193787","6813405220","6813405219","6813405218","6813405217","6813405216","6813405215","6813405212","4015203133","4015203134",
"4015203136","123152294","6816193786","6816193785","6808069740","6813416155","6813416151","6813416152","6813416153","6813416154","6813416145","7232024780","6818427916","6818427917",
"6818427898","6818427892","6818427918","6818427919","6818427920","4380040148","4380040152","4380040153","4380040154", "2578244375"};
  EXPECT_EQ(resB2, ans2);
  EXPECT_EQ(resD2, ans2);

  auto resB3= m.CalculateShortestPath_Bellman_Ford("Honeybird", "Target");
  auto resD3 = m.CalculateShortestPath_Dijkstra("Honeybird", "Target");
    std::vector<std::string> ans3 = { "5567724155", "5237417654", "6814820016", "6814820009", "6814820019", "6814620880", "6813360960", "6813379480", 
    "6813360961", "6813379584", "6814769289", "5237417650" };
  EXPECT_EQ(resB3, ans3);
  EXPECT_EQ(resD3, ans3);
}

TEST(TrojanmapTest, CycleDetection) {
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

  // Test case 3
  std::vector<double> square3 = {-118.294, -118.289, 34.030, 34.020};
  auto sub3 = m.GetSubgraph(square3);
  bool result3 = m.CycleDetection(sub3, square3);
  EXPECT_EQ(result3, true);
}

// Test Topological sorting
TEST(TrojanMapTest, TopologicalSort){
  TrojanMap m;

  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs", "KFC"}, {"Ralphs", "Chick-fil-A"}, {"KFC", "Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt = {"Ralphs", "KFC", "Chick-fil-A"};
  EXPECT_EQ(result, gt);

  location_names = {"Ralphs", "Chipotle", "Parking Center"};
  dependencies = {{"Ralphs", "Chipotle"}, {"Ralphs", "Parking Center"}, {"Chipotle", "Parking Center"}};
  result = m.DeliveringTrojan(location_names, dependencies);
  gt = {"Ralphs", "Chipotle", "Parking Center"};
  EXPECT_EQ(result, gt);

  location_names = {"Ralphs", "Chipotle", "Parking Center", "Jefferson"};
  dependencies = {{"Ralphs", "Chipotle"}, {"Ralphs", "Parking Center"}, {"Chipotle", "Parking Center"}, {"Parking Center", "Jefferson"}};
  result = m.DeliveringTrojan(location_names, dependencies);
  gt = {"Ralphs", "Chipotle", "Parking Center", "Jefferson"};
  EXPECT_EQ(result, gt);
}

// Test TSP
// Brute-force
TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout << "end" << std::endl;
  std::cout << result.second.size() << std::endl;
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Backtracking
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

// 2-opt
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
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


TEST(TrojanMapStudentTest, FindNearby) {
  std::cout << "=====FindNearby=====" <<std::endl;
  TrojanMap m;
  
  // With attribute and the location
  auto res1 = m.FindNearby("supermarket", "Ralphs", 10, 10);
  std::vector<std::string> ans1 = {"5237417649", "6045067406", "7158034317"};
  EXPECT_EQ(res1, ans1);

  // With attribute but no location
  auto res2 = m.FindNearby("fast_food", "", 10, 10);
  std::vector<std::string> ans2 = { "6279600813", "3577173161", "5695236164", "4927493958", "3088547686", "6216810098", "5567724155", "5567733799", "9591449455", "4577908517" };
  EXPECT_EQ(res2, ans2);

  //No attribute and no location
  auto res3 = m.FindNearby("", "", 10, 10);
  std::vector<std::string> ans3 = {};
  EXPECT_EQ(res3, ans3);
}