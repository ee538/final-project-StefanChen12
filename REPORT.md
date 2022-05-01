# Report 1

## 1
Implementation of Auto complete: 5 points. (Phase 1)
Time complexity: O (data.size* Name.length)

Time spent: 3 ms

Discussion, conclusion and lesson learned.
- Need to notice that there might exist lower and upper case of alphas, so when we are comparing two string, remember to compare
the lower case type.
---


## 2
Implementation of GetPosition: 5 points. (Phase 1)
Time complexity: O(n)

Time spent: 3 ms

Discussion, conclusion, and lessons learned.
- Need to use id to get the Node. Couldn't use Name because Name didn't point to Naode.


## 3
Implementation of EditDistance: 10 points. (Phase 1)
## overview of the algorithm
because we can use three different method to modify a single word. So when we compare two words, we can compare from the tail.
if the tails are the same, them we can push backward. Using dynamic programing. dp[i][j] means the least numbers of changes that can transform
the i-length word into the j-length word. so as what we said before, if the last alpha is the same. them we can know dp[m][n] = dp[m-1][n-1],
if not, then it either equals to dp[i - 1][j], which means we delete the last alpha of the first word; or it equals dp[i][j - 1], means we 
insert one alpha at the end of the first word. And dp[i][j] = min( dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]), this is the recursion
function.

Time complexity: O (m*n)

Time spend: 232 ms






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
without using stop sign running time took too much time of finding each nodes' neighbors to find the started node. With the help of 
stop sign at diceding if the distance didn't change for a long time, running time reduce a lot.




## 2
Cycledetection:
in this model we first have two little parts, they are:

1. inSquare
  this function checks if a certain node locates within the square.
Runtime complexity: O (n)

2. subgraph
   this function returns a subgraph(which is actually a list of nodes that lays within the square) using the square provided.
Runtime complexity:O (n)

then, we used CycleDetection funtcion and its helper function "isCyclic" to decide whether there exists a cycle in the squra 
provided.

3. CycleDetection function(including main function and its helper )
  
Runtime complexity: O (m + n)
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
Runtime complexity: O (n)

2. ReadDependenciesFromCSVFile
Runtime complexity: O (n)

After using these two function, we can get a string vetcor recording all the locations and a vector of string vector recording all
the depencencies. Then we run the topological sorting funtion. And the topological function includes two part: main part
（DeliveringTrojan)and its helper(DFS_helper_with_topo).

3. DeliveringTrojan(and DFS_helper_with_topo):
Runtime complexity: O (n * ( n + m))

Time spent:
0 ms

Discussion, conclusion, and lessons learned:
Using topological sorting algorithm, because we have several differnt nodes, so starting from a differnt node will give us a 
differnt sorting vector. For example we have three nodes in the example, so we can have 3 differnt topological sorting. But only
the one that has length equals to the number of nodes is the result we expect. So here we go through all the topological results
and choose the one that has the length of number of nodes we have.






# Report 3:
Travelling Trojan

## 1 Brute-force
Runtime complexity: O (n! * n)

Time spend: 49 ms ( places = 8)

## 2 Backtracking
Runtime complexity: O (n! * n)

Time spend: 47 ms ( places = 8)

## 3 2-opt
Runtime complexity: O(n^2 * MAX)

Time spend: 5 ms ( places = 8)


Discussion, conclusion, and lessons learned:
in Brute-force method each time we check if the current path includes current node, if not we add the current node into current
path. Trough this algorithm we can get all the permutations and combinations of locations, but the runtime complexity is bad, which
is O(n! * n). Backtracking has added a early stop in brute-force, which is slightly better than brute-force, but the runtime dosen't
improve much. 2-opt function has largely improved the Runtime complexity. We update the current each time, by choosing i and j, we 
keep the path before i and after j the same, reversing the part between i and j. If the updated version has shorter distance, then
we update the min_path.

