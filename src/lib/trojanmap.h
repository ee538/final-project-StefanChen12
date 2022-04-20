#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cfloat>
#include <math.h>
#include <fstream>
#include <sstream>
#include <climits>
#include <cmath>
#include <set>
#include <chrono>


// A Node is the location of one point in the map.
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors; attributes = n.attributes;};
    Node(std::string Id, double Lat, double Lon, std::string Name, std::vector<std::string> Neighbors, std::unordered_set<std::string> Attributes){
      id = Id;
      lat = Lat;
      Lon = lon;
      name = Name;
      neighbors = Neighbors;
      attributes = Attributes;
    }
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
    std::unordered_set<std::string> attributes;  // List of the attributes of the location.
};

// this node struct is for calculating the shrotest distance between two different places
class node{
    public:
    node(){};
    node(bool v, long d, std::string Id, std::string pre, std::string backward, std::vector<std::string> neig){
        visit = v;
        distance = d;
        id = Id;
        prev = pre;
        back = backward;
        for(int i = 0; i < neig.size(); i++){
            neighbors.push_back(neig[i]);
        }
        //stop = s;
    };
    bool visit; // check if the node has been visited, false represents not visited and true represents visited.
    double distance; // the distance between this node and the start node, the default value is infinity.
    std::string id; // A unique id assign to each point
    std::string prev; // the previous node in the shortest path.
    std::string back; // the previous node in the shortest path.
    std::vector<std::string> neighbors; // the neighbors of the node.
    //int stop;
    // Returns true if distance is smaller than the distance of other node object
    // and false otherwise.
    bool operator<(const node& rhs) const;

    // Returns true if grade is greater than the grade of other Student objects
    // and false otherwise.
    bool operator>(const node& rhs) const;

    // Returns true if grade is equal to the grade of other Student objects and
    // false otherwise.
    bool operator==(const node& rhs) const;

};

class TrojanMap {
 public:
  // Constructor
  TrojanMap(){CreateGraphFromCSVFile();};
  
  // A map of ids to Nodes.
  std::unordered_map<std::string, Node> data;  
  std::unordered_map<std::string, Node> Data;  
  std::unordered_map<std::string, Node> top_data;  
  //-----------------------------------------------------
  // Read in the data
  void CreateGraphFromCSVFile();

  //-----------------------------------------------------
  // TODO: Implement these functions and create unit tests for them:
  // Get the Latitude of a Node given its id.
  double GetLat(const std::string& id);

  // Get the Longitude of a Node given its id.
  double GetLon(const std::string& id);

  // Get the smallest number of 3 variables, for finding the closest name.
  int Min(int x, int y, int z);

  // get editDistance of two string.
  int editDist(std::string str1, std::string str2, int m, int n);

  // Get the name of a Node given its id.
  std::string GetName(const std::string& id);

  // Get the id given its name.
  std::string GetID(const std::string& name);

  // Get the neighbor ids of a Node.
  std::vector<std::string> GetNeighborIDs(const std::string& id);

  // Returns a vector of names given a partial name.
  std::vector<std::string> Autocomplete(std::string name);

  // Returns lat and lon of the given the name.
  std::pair<double, double> GetPosition(std::string name);

  // Calculate location names' edit distance
  int CalculateEditDistance(std::string, std::string);

  // Find the closest name
  std::string FindClosestName(std::string name);  

  // Get the distance between 2 nodes.
  double CalculateDistance(const std::string &a, const std::string &b);

  // Calculates the total path length for the locations inside the vector.
  double CalculatePathLength(const std::vector<std::string> &path);

  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  std::vector<std::string> CalculateShortestPath_Dijkstra(std::string location1_name,
                                                 std::string location2_name);
  std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string location1_name,
                                                 std::string location2_name);
  double CalculateShortestPath_Bellman_Ford_Helper(std::string s, int i, std::string v, std::unordered_map<std::string, node> &Data);

  // Given CSV filename, it read and parse locations data from CSV file,
  // and return locations vector for topological sort problem.
  std::vector<std::string> ReadLocationsFromCSVFile(std::string locations_filename);
  
  // Given CSV filenames, it read and parse dependencise data from CSV file,
  // and return dependencies vector for topological sort problem.
  std::vector<std::vector<std::string>> ReadDependenciesFromCSVFile(std::string dependencies_filename);

  // Given a vector of location names, it should return a sorting of nodes
  // that satisfies the given dependencies.
  std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
      std::vector<std::string> location_ids);
  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Backtracking(
      std::vector<std::string> location_ids);
  
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> location_ids);

  // Check whether the id is in square or not
  bool inSquare(std::string id, std::vector<double> &square);

  // Get the subgraph based on the input
  std::vector<std::string> GetSubgraph(std::vector<double> &square);
  
  // Given a subgraph specified by a square-shape area, determine whether there is a
  // cycle or not in this subgraph.
  bool CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square);


  bool isCyclic(std::string node, std::set<std::string> &visited, std::string parent, std::vector<double> &square);


  // Given a location id and k, find the k closest points on the map
  std::vector<std::string> FindNearby(std::string, std::string, double, int);
  
  //----------------------------------------------------- User-defined functions

};

// A global variable that stores the start time.
std::chrono::time_point<std::chrono::system_clock> g_start_time;
// A function that stores the current time into g_start_time;
void StoreStartTime() { g_start_time = std::chrono::system_clock::now(); }
// A function that returns the difference from the current time to
// g_start_time in seconds.
double PrintAndGetDuration() {
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - g_start_time);
  std::cout << "Operation took: " << diff.count() << " milliseconds"
            << std::endl;

  return diff.count();
}


#endif
