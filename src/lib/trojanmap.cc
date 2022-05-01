#include "trojanmap.h"
#include <algorithm>
#include <string>
#include <iomanip>
#include <set>
#include <map>
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
  std::unordered_map<std::string, Node>::iterator it;
  for ( it = data.begin(); it != data.end(); it++){
    std::string Node_name = it->second.name;

    if(it->second.name ==  name){
      std::pair<double, double> results(data[pos_id].lat, data[pos_id].lon);
      return results;
    }  
  }
  
  std::pair<double, double> results(-1, -1);
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
  return editDist(a, b, a.length(), b.length());
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

int TrojanMap::editdistance_recursion(std::string str1, std::string str2, int m, int n){
  // If first string is empty, the only option is to
    // insert all characters of second string into first
    if (m == 0) return n;

    // If second string is empty, the only option is to
    // remove all characters of first string
    if (n == 0) return m;

    // If last characters of two strings are same, nothing
    // much to do. Ignore last characters and get count for
    // remaining strings.
    if (str1[m-1] == str2[n-1])
        return editDist(str1, str2, m-1, n-1);

    // If last characters are not same, consider all three
    // operations on last character of first string, recursively
    // compute minimum cost for all three operations and take
    // minimum of three values.
    return 1 + Min ( editDist(str1,  str2, m, n-1),    // Insert
                     editDist(str1,  str2, m-1, n),   // Remove
                     editDist(str1,  str2, m-1, n-1) // Replace
                   );
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
      std::vector<std::string> path;
      // define a minimum heap.
      std::priority_queue<node, std::vector<node>, std::greater<node> > heap;
      
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

          for(auto neighbor: Data[neigh].neighbors){
          
            if(Data[neighbor].visit == false) continue;
  
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


  std::vector<std::string> path;
  std::string start = GetID(location1_name);
  std::string end = GetID(location2_name);

  // get all edge
  struct edge{
    std::string begin;
    std::string finish;
    double distance;
  };

  std::vector<edge> all_E;
  for (auto &&node : data){
    std::string begin = node.second.id;
    for (int i = 0; i < node.second.neighbors.size(); i++){
      std::string finish = node.second.neighbors[i];
      all_E.push_back({begin, finish, CalculateDistance(begin, finish)});
    }
  }

  // get all verices 
  // all nodes

  //Data
  struct Data{
    double distance;
    std::string prev;
  };
  std::unordered_map<std::string, Data> path_data;
  for (auto it = data.begin(); it != data.end(); it++){
    double dis = it->second.id == start ? 0 : INT_MAX;
    path_data[it->second.id] = {dis, ""};
  }

  //Bellma Ford main Function
  int stop = 0;
  double pre_dis;
  for (int i = 1; i <= data.size() - 1; i++){
    pre_dis = path_data[end].distance;
    for (int j = 0; j < all_E.size(); j++){
      std::string begin = all_E[j].begin;
      std::string finish = all_E[j].finish;
      double dis = all_E[j].distance;
      if (path_data[begin].distance != INT_MAX && path_data[begin].distance + dis < path_data[finish].distance){
        path_data[finish].distance = path_data[begin].distance + dis;
        path_data[finish].prev = begin;
        if (finish == end)
          stop = 0;
      }
    }
    // interrupt
    if (path_data[end].distance != INT_MAX){
      if (path_data[end].distance == pre_dis)
        stop++;
      if (stop == 15)
        break;
    }
  }

  // result
  while (end != ""){
    path.push_back(end);
    end = path_data[end].prev;
  }
  std::reverse(path.begin(), path.end());
  return path;
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

    std::pair<double, std::vector<std::vector<std::string>>> result;
    //for each location, we calculate 
    std::vector<std::string> cur_path;
    cur_path.push_back(location_ids[0]);
    // record each min cost
    double min_cost = INT_MAX;
    double cur_cost = 0;
    // record min path for circle starting from each node
    std::vector<std::string> min_path;
    std::map<double, std::vector<std::string>> record;
    TSP_helper(location_ids[0], location_ids, location_ids[0], cur_cost, cur_path, min_cost, record);
    result.first = min_cost;
    std::map<double, std::vector<std::string>>::iterator it;
    for(it = record.begin(); it != record.end(); it++){
      if(it == record.begin()){
        min_path = it->second;
        continue;
      }
      result.second.push_back(it->second);
    }
    result.second.push_back(min_path);
  return result;
}


void TrojanMap::TSP_helper(std::string start, std::vector<std::string> &locations, std::string cur_node, double cur_cost,
                                   std::vector<std::string> &cur_path, double &min_cost, std::map<double, std::vector<std::string>> &record){
  // if we are at a leaf, update min_cost and min_path;
  if(cur_path.size() == locations.size()){
    double final_cost = cur_cost + CalculateDistance(cur_node, start);
    cur_path.push_back(start);

    if(final_cost < min_cost){
      min_cost = final_cost;
    }
    record[final_cost] = cur_path;
    return;
  }

  // Else evaluate all children.
  // loc is the name of the location
  for(auto loc : locations){
    // if the node has already been added into current path, then we igonre it.
    if(std::find(cur_path.begin(), cur_path.end(), loc) != cur_path.end()){
      continue;
    }
    cur_path.push_back(loc);
    TSP_helper(start, locations, loc, cur_cost + CalculateDistance(loc, cur_node), cur_path, min_cost, record);
    //because we know find a local(or global) optimal, so when we pop, we need to pop start point first;
    if(cur_path.size() == locations.size() + 1) cur_path.pop_back();
    cur_path.pop_back();
  }
}




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
    std::pair<double, std::vector<std::vector<std::string>>> result;
    //for each location, we calculate 
    std::vector<std::string> cur_path;
    cur_path.push_back(location_ids[0]);
    // record each min cost
    double min_cost = INT_MAX;
    double cur_cost = 0;
    // record min path for circle starting from each node
    std::vector<std::string> min_path;
    std::map<double, std::vector<std::string>> record;
    TSP_helper(location_ids[0], location_ids, location_ids[0], cur_cost, cur_path, min_cost, record);
    result.first = min_cost;
    std::map<double, std::vector<std::string>>::iterator it;
    for(it = record.begin(); it != record.end(); it++){
      if(it == record.begin()){
        min_path = it->second;
        continue;
      }
      result.second.push_back(it->second);
    }
    result.second.push_back(min_path);
  return result;
}

void TrojanMap::TSP_helper_early_backtracking(std::string start, std::vector<std::string> &locations, std::string cur_node, double &cur_cost,
                                   std::vector<std::string> &cur_path, double &min_cost, std::map<double, std::vector<std::string>> &record){
  // if we are at a leaf, update min_cost and min_path;
  if(cur_cost > min_cost) return;
  if(cur_path.size() == locations.size()){
    double final_cost = cur_cost + CalculateDistance(cur_node, start);
    cur_path.push_back(start);

    if(final_cost < min_cost){
      min_cost = final_cost;
    }
    record[final_cost] = cur_path;
    return;
  }

  // Else evaluate all children.
  // loc is the name of the location
  for(auto loc : locations){
    // if the node has already been added into current path, then we igonre it.
    if(std::find(cur_path.begin(), cur_path.end(), loc) != cur_path.end()){
      continue;
    }
    cur_path.push_back(loc);
    TSP_helper(start, locations,loc, cur_cost + CalculateDistance(loc, cur_node), cur_path, min_cost, record);
    //because we know find a local(or global) optimal, so when we pop, we need to pop start point first;
    if(cur_path.size() == locations.size() + 1) cur_path.pop_back();
    cur_path.pop_back();
  }
}



std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> locations = location_ids;
  locations.push_back(location_ids.front());
  int length = locations.size();
  int improve = 0;
  while(improve<15)
  {
    start_again: double min_distance = CalculatePathLength(locations);
    for(int i=1; i<length-2; i++)
    {
      for(int j=i+1; j<length-1; j++)
      {
        std::vector<std::string> temp = locations;
        std::reverse(temp.begin()+i,temp.begin()+j+1);
        double distance = CalculatePathLength(temp);
        if(distance < min_distance)
        {
          improve = 0;
          locations.clear();
          locations = temp;
          min_distance = distance;
          results.second.push_back(temp);
          goto start_again;
        }
      }
    }
    improve++;
  }
  results.first = CalculatePathLength(locations);
  return results;
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

//decide whethere there is a cycle in topological sort.
bool TrojanMap::HasCycle(std::unordered_map<std::string, std::vector<std::string>> next, std::string node, std::unordered_map<std::string, bool> &visited){
  bool cycle = false;
  HasCycle_helper(next, node, visited, cycle);
  return (cycle == true);
}

void TrojanMap::HasCycle_helper(std::unordered_map<std::string, std::vector<std::string>> next, std::string node, std::unordered_map<std::string, bool> &visited, bool &cycle){
  // if current node has been visited before means there is a cycle.
  if(visited[node] == true){
    cycle = true;
    return;
  }
  // mark current node.
  visited[node] = true;
  for(auto next_node : next[node]){
    HasCycle_helper(next, next_node, visited, cycle);
  }
  visited[node] = false;
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

  // next is a map that record every nodes that is depended on the current node.
  std::unordered_map<std::string, std::vector<std::string>> next;
  for(auto cur_node : locations){
    for(auto dependency : dependencies){
      if(dependency[0] == cur_node){
        next[cur_node].push_back(dependency[1]);
      }
    }
  }

  // select a node that depend on nothing to detect whethere there exists a cycle.
  // Successor is for recording all nodes that has dependency
  std::set<std::string> Successor;
  for(auto dependency : dependencies){
    Successor.insert(dependency[1]);
  }
  std::string origin = "";
  for(auto location : locations){
    if(Successor.count(location) != 1){
      origin = location;
      break;
    }
  }
  std::unordered_map<std::string, bool> visited;
  if(HasCycle(next, origin, visited) == true){
    return result;
  }

  std::vector<std::string> topo_list;
  std::set<std::string> marks;
  DFS_helper_with_topo(origin, marks, topo_list, next);
  if(topo_list.size() == locations.size()){
    for(int i = 0; i < topo_list.size(); i++){
      result.push_back(topo_list[i]);
    }
  }
  reverse(result.begin(), result.end());
  return result;                                                     
}


void TrojanMap::DFS_helper_with_topo(std::string root, std::set <std::string> &marks, std::vector<std::string> &topo_list, std::unordered_map<std::string, std::vector<std::string>> &next){
  marks.insert(root);

  for(auto child : next[root]){
    if(marks.count(child) == 0){
      DFS_helper_with_topo(child, marks, topo_list, next);
    }
  }
  topo_list.push_back(root);
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
  std::string target_id= GetID(name);

  struct attributes{
    std::string id;
    double dis;
    bool operator<(const attributes &rhs) const{
      return dis < rhs.dis;
    }
  };
  std::priority_queue<attributes> res_temp;

  for (const auto &it : data){
    if (it.second.id != target_id){
      if (it.second.attributes.count(attributesName) > 0){  //count - if there's same string occurance
        double dis = CalculateDistance(it.second.id, target_id);

        if (dis <= r && (res_temp.size() < k || dis < res_temp.top().dis)){
          if (res_temp.size() >= k){
            res_temp.pop();

          }
          res_temp.push({it.second.id, dis});
        }
      }
    }
  }

  while (res_temp.size() != 0){
    auto top = res_temp.top();
    res_temp.pop();
    res.push_back(top.id);
  }

  std::reverse(res.begin(), res.end());
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
