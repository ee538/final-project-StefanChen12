#include "trojanmap.h"
#include <algorithm>
#include <string>
#include <iomanip>
#include <set>
//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
    // if id does not exist, return -1
    if(data.count(id) > 0){
      Node node = data[id];
      double lat = node.lat;
      return lat;
    }
    else{
      return -1;
    }
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) { 
    if(data.count(id) > 0){
      Node node = data[id];
      double lon = node.lon;
      return lon;
    }
    else{
      return -1;
    }
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 

  if(data[id].name.compare("") == 0) return "NULL";
  else{
    Node node = data[id];
    std::string name = node.name;
    return name;
  }
}


/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {

  if (data.count(id) <= 0) {
    return std::vector<std::string>();
  }
  return data[id].neighbors;

}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {

  std::vector<std::string> results;
  
  std::unordered_map<std::string, Node>::iterator it;
  for ( it = data.begin(); it != data.end(); it++){
    std::string Node_name = it->second.name;

    if(it->second.name ==  name){
      return it -> first;
    }
  
  }
  return "";
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::string pos_id = GetID(name);
  
  std::pair<double, double> results(data[pos_id].lat, data[pos_id].lon);
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b){
  //first we have to get the Node object of these two names
  // then we get lat and lon of two nodes 
  // then we calculate the distance 
  std::pair<double, double> result1 = GetPosition(a);
  std::pair<double, double> result2 = GetPosition(b);
  int distance = 0;
  distance = pow(result1.first - result2.first, 2) + pow(result1.second - result2.second, 2);
  distance = pow(distance, 0.5);
  return distance;
}

int TrojanMap::Min(int x, int y, int z){
  return std::min(std::min(x, y), z);
}

int TrojanMap::editDist(std::string str1, std::string str2, int m, int n){
  // If first string is empty, the only option is to insert all characters of second string into first
  // Create a table to store results of subproblems
    int dp[m + 1][n + 1];
 
    // Fill d[][] in bottom up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i == 0)
                dp[i][j] = j; // Min. operations = j
 
            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j == 0)
                dp[i][j] = i; // Min. operations = i
 
            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
 
            // If the last character is different, consider
            // all possibilities and find the minimum
            else
                dp[i][j]
                    = 1
                      + Min(dp[i][j - 1], // Insert
                            dp[i - 1][j], // Remove
                            dp[i - 1][j - 1]); // Replace
        }
    }
 
    return dp[m][n];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::unordered_map<std::string, Node>::iterator it;
  int dis = INT_MAX;
  int n = name.length();
  std::string closest_name;

  for(it = data.begin(); it != data.end(); it++){
    int m = it->second.name.length();
    if(m == 0) continue;
    int current_distance = editDist(it->second.name, name, m, n);
    if(current_distance < dis){
      // std::cout << current_distance << std::endl;
      closest_name = it->second.name;
      dis = current_distance;
      // std::cout << closest_name << std::endl;
    }
  }
  return closest_name;
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  
  std::unordered_map<std::string, Node>::iterator it;
  for ( it = data.begin(); it != data.end(); it++){
    std::string Node_name = it->second.name;
    // transform(Node_name.begin(), Node_name.end(), Node_name.begin(),::tolower);
    // transform(name.begin(), name.end(), name.begin(), ::tolower);
    if(Node_name.length() < name.length()) continue;
    // if(Node_name.find(name) == 0){
    //   results.push_back(Node_name);
    // }
    for(int i = 0; i < name.length(); i++){
      if(tolower(Node_name[i]) == tolower(name[i])){
        if(i == name.length() - 1){
          results.push_back(Node_name);
        }else{
          continue;
        }
      }
      else{
        break;
      }
    }
  }
  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
      std::cout << "=========================Dijkstra=======================" << std::endl;
      //StoreStartTime();
      // define a minimum heap.
      std::priority_queue<node, std::vector<node>, std::greater<node> > heap;
      std::vector<std::string> path;
      // Define a map to record all the node objects.
      std::unordered_map<std::string, node> Data;
      // an iterator for transforming Nodes in data into nodes in Data.
      std::unordered_map<std::string, Node>::iterator it;
      for(it = data.begin(); it != data.end(); it++){
        node new_node(false, INT_MAX, it->first, "", "", it->second.neighbors);
        Data[it->first] = new_node;
      }

      // Get ID of start and end node.
      std::string root_ID = GetID(location1_name);
      std::string end_ID = GetID(location2_name);

      // set the distance from start to start as 0.
      Data[root_ID].distance = 0;
      // set root as visited.
      Data[root_ID].visit = true;
      //push root into heap.
      heap.push(Data[root_ID]);

      while(!heap.empty()){
        // get id of the top node
        std::string origin = heap.top().id;
        for(auto neigh: Data[origin].neighbors){
        // for(auto neighbor : Data[neigh].neighbors){
        //   if(Data[neighbor].visit == 1){
        //     std::cout << Data[neighbor].id << std::endl;
        //   }
        // }
          
          for(auto neighbor: Data[neigh].neighbors){
            if(Data[neighbor].visit == false) continue;
          // std::cout << Data[neighbor].distance << std::endl;
          // std::cout << Data[neighbor].id << std::endl;
            else{
              if(Data[neigh].distance > CalculateDistance(neighbor, neigh) + Data[neighbor].distance){
              Data[neigh].prev = neighbor;
              Data[neigh].distance = CalculateDistance(neigh, neighbor) + Data[neighbor].distance;
              // std::cout << cur.distance;
              }
            }
          }
        if(Data[neigh].visit == false){
          heap.push(Data[neigh]);
          Data[neigh].visit = 1;
          }
        }
        heap.pop();
      } 


      std::string final_ID = end_ID;
      while(final_ID != root_ID){
        path.push_back(final_ID);
        final_ID = Data[final_ID].prev;
      }
      path.push_back(root_ID);
      reverse(path.begin(), path.end());

      double distance = Data[end_ID].distance;
      std::cout << "the distance is:" << distance << std::endl;
      //PrintAndGetDuration();
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */

std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
  std::string location1_name, std::string location2_name){
  std::cout << "=========================Bellman Ford=======================" << std::endl;

  //StoreStartTime();

  std::vector<std::string> path;
  std::string start = GetID(location1_name); // start
  std::string end = GetID(location2_name); // end


  std::unordered_map<std::string, node> Data;
  std::unordered_map<std::string, Node>::iterator it;

  for(it = data.begin(); it != data.end(); it++){
    node new_node(false, INT_MAX, it->first, "", "", it->second.neighbors);
    Data[it->first] = new_node;
  }

  double Final_distance;
  Data[end].distance = 0;
  Data[start].distance = INT_MAX;
  double pre_d = INT_MAX;
  int stop = 0;
  // for all nodes in path
  for (int i = 0; i <= Data.size() - 1; i++){ 
    pre_d = Data[start].distance;
    Final_distance = CalculateShortestPath_Bellman_Ford_Helper(start, i, end, Data);
    if (Final_distance != INT_MAX){

      if (Data[start].distance == pre_d)
        stop ++;
      if (stop == 1){
        break;
      }
      
      
    }
    
  }

  Data[end].back = "";
  Data[start].prev = "";

  while (start != ""){
    path.push_back(start);
    start = Data[start].back;
  }

  std::cout << "the distance is:" << Final_distance << std::endl;
  //PrintAndGetDuration();

return path;
}
  
double TrojanMap::CalculateShortestPath_Bellman_Ford_Helper(std::string s, int i, std::string v, std::unordered_map<std::string, node> &Data){
    double pre_d = Data[s].distance;

    if (i == 0){
      return(v == s) ? 0 :INT_MAX;
    }else{
      double d = INT_MAX;
      for (auto u : Data[v].neighbors){

        double dis = CalculateDistance(u,v);
        
        if (Data[u].distance > CalculateDistance(u,v) + Data[v].distance){
          
          Data[u].distance = (CalculateDistance(u,v) + Data[v].distance);
        }
        Data[u].back = v;
        d =  std::min(d, (CalculateShortestPath_Bellman_Ford_Helper(s, i-1, u, Data)+ dis));
      
    }
    // if (Data[s].distance != INT_MAX){
    //   if (Data[s].distance == pre_d){
    //     Data[s].stop = Data[s].stop+1;
    //   }

    //   if (Data[s].stop == 3){
    //     Data[s].stop = 0;
    //   return Data[s].distance;
    //   }
    // }
    return std::min(CalculateShortestPath_Bellman_Ford_Helper(s, i-1, v, Data), d);

    }

    
    
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  // record final min cost
  int final_min_cost = INT_MAX;
  // record the final min path
  std::vector<std::string> final_min_path;

  for(int i = 0; i < location_ids.size(); i++){
    //for each location, we calculate 
    std:vector<std::string> cur_path = {location_ids[i]};
    // record each min cost
    int min_cost = INT_MAX;
    // record min path for circle starting from each node
    std::vector<std::string> min_path;
    TSP_helper(location_ids[i], location_ids, location_ids[i], 0, cur_path, min_cost, min_path);
    if(min_cost < final_min_cost){
      final_min_cost = min_cost;
      for(int i = 0; i < min_path.size(); i++){
        final_min_path.push_back(min_path[i]);
      }
    }
  }
  std::pair<double, std::vector<std::vector<std::string>>> records(final_min_cost, final_min_path);
  return records;
}

void TSP_helper(std::string start, std::vector<std::string> &locations, std::string cur_node, int cur_cost,
                                   std::vector<std::string> &cur_path, int &min_cost, std::vector<std::string> &min_path){
  // if we are at a leaf, update min_cost and min_path;
  if(cur_path.size() == locations.size()){
    std::string cur_ID = GetID(cur_node);
    std::string start_ID = GetID(start);
    int final_cost = cur_cost + CalculateDistance(cur_ID, start_ID);
    if(final_cost < min_cost){
      min_cost = final_cost;
      // might have problems.
      min_path = cur_path;
    }
    return;
  }

  // Else evaluate all children.
  // loc is the name of the location
  for(auto loc : locations){
    // if the node has already been added into current path, then we igonre it.
    if(std::find(cur_path.begin(), cur_path.end(), loc) != cur_path.end()){
      continue;
    }
    std::string cur_id = GetID(cur_node);
    std::string neighbor_id = GetID(loc);
    cur_path.push_back(loc);
    TSP_helper(start, locations, loc, cur_cost + CalculateDistance(cur_id, neighbor_id), cur_path, min_cost, min_path);
    cur_path.pop_back();
  }
  
                                   }




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
// record final min cost
  int final_min_cost = INT_MAX;
  // record the final min path
  std::vector<std::string> final_min_path;

  for(int i = 0; i < location_ids.size(); i++){
    //for each location, we calculate 
    std:vector<std::string> cur_path = {location_ids[i]};
    // record each min cost
    int min_cost = INT_MAX;
    // record min path for circle starting from each node
    std::vector<std::string> min_path;
    TSP_helper(location_ids[i], location_ids, location_ids[i], 0, cur_path, min_cost, min_path);
    if(min_cost < final_min_cost){
      final_min_cost = min_cost;
      for(int i = 0; i < min_path.size(); i++){
        final_min_path.push_back(min_path[i]);
      }
    }
  }
  std::pair<double, std::vector<std::vector<std::string>>> records(final_min_cost, final_min_path);
  return records;
}

void TSP_helper_early_backtracking(std::string start, std::vector<std::string> &locations, std::string cur_node, int cur_cost,
                                   std::vector<std::string> &cur_path, int &min_cost, std::vector<std::string> &min_path){
  // if we are at a leaf, update min_cost and min_path;
  if(cur_path.size() == locations.size()){
    std::string cur_ID = GetID(cur_node);
    std::string start_ID = GetID(start);
    int final_cost = cur_cost + CalculateDistance(cur_ID, start_ID);
    if(final_cost < min_cost){
      min_cost = final_cost;
      // might have problems.
      min_path = cur_path;
    }
    return;
  }

  if(cur_cost > min_cost) return;
  // Else evaluate all children.
  // loc is the name of the location
  for(auto loc : locations){
    // if the node has already been added into current path, then we igonre it.
    if(std::find(cur_path.begin(), cur_path.end(), loc) != cur_path.end()){
      continue;
    }
    std::string cur_id = GetID(cur_node);
    std::string neighbor_id = GetID(loc);
    cur_path.push_back(loc);
    TSP_helper(start, locations, loc, cur_cost + CalculateDistance(cur_id, neighbor_id), cur_path, min_cost, min_path);
    cur_path.pop_back();
  }
  
                                   }




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;

  std::ifstream fp(locations_filename);
  std::string line;
  getline(fp, line);
  while(getline(fp, line)){
    //std::vector<std::string> data_line;
    std::string name;
    std::istringstream readstr(line);
    //for(int j = 0; j < 1; j++){
      getline(readstr, name);
    //  data_line.push_back(number);
    //}
    location_names_from_csv.push_back(name);
  }
  return location_names_from_csv;

}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::ifstream fp(dependencies_filename);
  std::string line;
  getline(fp, line);
  while(getline(fp, line)){
    std::vector<std::string> data_line;
    std::string number;
    std::istringstream readstr(line);
    for(int j = 0; j < 2; j++){
      getline(readstr, number, ',');
      data_line.push_back(number);
    }
    dependencies_from_csv.push_back(data_line);
  }
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;

  return result;                                                     
}




/**
 * inSquare: Give a id return whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  double Lon = GetLon(id);
  double Lat = GetLat(id);
  // std::cout << std::setprecision(20) << "longtitude:" << Lon << std::endl;
  // std::cout << std::setprecision(20) << "latitude:" << Lat << std::endl;
  return (Lon >= square[0] && Lon <= square[1] && Lat <= square[2] && Lat >= square[3]);
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  std::unordered_map<std::string, Node>::iterator it;
  for(it = data.begin(); it != data.end(); it++){
    std::string id = it->first;
    if(inSquare(id, square)){
      subgraph.push_back(it->first);
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  for(int i = 0; i < subgraph.size(); i++){
    std::set<std::string> visited;
    std::vector<std::string> neighbors = GetNeighborIDs(subgraph[i]);
    // put current node into visited.
    visited.insert(subgraph[i]);
    for(auto neigh : neighbors){
      if(!inSquare(neigh, square)) continue;
      else{
        if(isCyclic(neigh, visited, subgraph[i], square) == true) return true;
      }
    }
  }
  return false;
}


bool TrojanMap::isCyclic(std::string node, std::set<std::string> &visited, std::string parent, std::vector<double> &square) {
  visited.insert(node);
  for(auto neighbor : GetNeighborIDs(node)){
    // first we have to decide whether the node is within the subgraph
    if(!inSquare(neighbor, square)) continue;
    // if the neighbor of node is not visited
    if(!visited.count(neighbor)){
      if(isCyclic(neighbor, visited, node, square) == true) return true;
    }else{
      if(neighbor != parent) return true;
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}


bool node::operator<(const node& rhs) const{
      return (distance < rhs.distance);
  };

bool node::operator>(const node& rhs) const{
      return (distance > rhs.distance);
  };

bool node::operator==(const node& rhs) const{
      return (distance == rhs.distance);
  };
