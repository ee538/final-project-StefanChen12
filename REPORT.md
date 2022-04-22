# Report 1

## 1
Implementation of Auto complete: 5 points. (Phase 1)
```cpp
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  std::unordered_map<std::string, Node>::iterator it;
 
  for ( it = data.begin(); it != data.end(); it++){     // run throught all data to find data's that fit.
    std::string Node_name = it->second.name;            // get id's name
    if(Node_name.length() < name.length()) continue;
    for(int i = 0; i < name.length(); i++){             // trun throught each alphabet in a word.
      if(tolower(Node_name[i]) == tolower(name[i])){    // make sure we can find whether is upper letter or lower letter
        if(i == name.length() - 1){
          results.push_back(Node_name);                 //we got the same alphabet.
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
```

Time complexity
- O (data.size* Name.length)

Time spent
- 3 ms

---

## 2

Implementation of GetPosition: 5 points. (Phase 1)
```cpp
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::string pos_id = GetID(name);                                         //Use GetId get id cause we need use id to get node and get latitud and longitude
  
  std::pair<double, double> results(data[pos_id].lat, data[pos_id].lon);
  return results;
}
```

Time complexity. 
- O(n)

Time spent
- 3 ms

Discussion, conclusion, and lessons learned.
- Need to use id to get the Node. Couldn't use Name because Name didn't point to Naode.

---

## 3

Implementation of EditDistance: 10 points. (Phase 1)
```cpp
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
```

## overview of the algorithm
because we can use three different method to modify a single word. So when we compare two words, we can compare from the tail.
if the tails are the same, them we can push backward. Using dynamic programing. dp[i][j] means the least numbers of changes that can transform
the i-length word into the j-length word. so as what we said before, if the last alpha is the same. them we can know dp[m][n] = dp[m-1][n-1],
if not, then it either equals to dp[i - 1][j], which means we delete the last alpha of the first word; or it equals dp[i][j - 1], means we 
insert one alpha at the end of the first word. And dp[i][j] = min( dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]), this is the recursion
function.

Time complexity.
- O (m*n)

Time spend
- 232 ms



# Report 2:

## 1
Implementation of  CalculateShortestPath_Dijkstra

Time complexity:
because we are using heap, so the runtime complexity is O(m + nlogn). m is the total number of edges and n is the total
number of nodes.

Time spent:
374 ms

Discussion, conclusion, and lessons learned:
using a heap can help us find the node to deal with in every turn. And it can largely save us time. in this Algorithm, we create a
unordered map called Data. And we create a new class called node, through which we can record the previous node in the shortest
path from begining to current node as well as and the shrotest distance. Now we know how to find the shortest distance from start
to end and we can save a lot of time using heap.



Implementation of  CalculateShortestPath_Bellman

Time complexity:
because we have to runs through all nodes to find the path, the time complexity would be O(m*n). m is the number of vertices and n in the total edages that the graph could have. If we set a stop sign, we didn't have to run through all nodes to get the result.

Time spent:
38058ms ms

Discussion, conclusion, and lessons learned:
without using stop sign running time took too much time of finding each nodes' neighbors to find the started node. With the help of stop sign at diceding if the distance didn't change for a long time, running time reduce a lot.




## 2
Cycledetection:
in this model we first have two little parts, they are:

1. inSquare
  this function checks if a certain node locates within the square.
Runtime complexity: O(n)

2. subgraph
   this function returns a subgraph(which is actually a list of nodes that lays within the square) using the square provided.
Runtime complexity:O(n)

then, we used CycleDetection funtcion and its helper function "isCyclic" to decide whether there exists a cycle in the squra 
provided.

3. CycleDetection function(including main function and its helper )
  
Runtime complexity: O(m + n)
because we have to go through all the nodes and all the edges to find out whether there exists a cycle or not. 

Time spent:
0 ms

Discussion, conclusion, and lessons learned:
because now in the graph, all the roads are bi-directional, so everytime when we are at a node, we first mark it as visited,
then we use DFS going through all its neighbors. when we arrive a node whose neighbor has one neighber being visited, and the 
visited neighbor is not the current node, then we know there is a cycle in the graph.


## 3
Topological sort:
first we have two functions reading and parsing csv files, and they are:
1. ReadDependenciesFromCSVFile
Runtime complexity:O(n)

2. ReadDependenciesFromCSVFile
Runtime complexity: O(n)

After using these two function, we can get a string vetcor recording all the locations and a vector of string vector recording all
the depencencies. Then we run the topological sorting funtion. And the topological function includes two part: main part
（DeliveringTrojan)and its helper(DFS_helper_with_topo).

3. DeliveringTrojan(and DFS_helper_with_topo):
Runtime complexity: O(n(n + m))

Time spent:
0 ms

Discussion, conclusion, and lessons learned:
Using topological sorting algorithm, because we have several differnt nodes, so starting from a differnt node will give us a 
differnt sorting vector. For example we have three nodes in the example, so we can have 3 differnt topological sorting. But only
the one that has length equals to the number of nodes is the result we expect. So here we go through all the topological results
and choose the one that has the length of number of nodes we have.




