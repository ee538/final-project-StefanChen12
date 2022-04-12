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
1. High-level overview of your design (Use diagrams and pictures for your data structures).

Time complexity
- O (data.size* Name.length)

Time spent
- 3 ms

4. Discussion, conclusion, and lessons learned.


## 2
Implementation of GetPosition: 5 points. (Phase 1)
```cpp
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::string pos_id = GetID(name);                                         //Use GetId get id cause we need use id to get node and get latitud and longitude
  
  std::pair<double, double> results(data[pos_id].lat, data[pos_id].lon);
  return results;
}
```
Structure
- Get the information inside the Node.

Time complexity. 
- O(1)

Time spent
- 3 ms

Lessons learned.
- Need to use id to get the Node. Couldn't use Name because Name didn't point to Naode.

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
1. High-level overview of your design (Use diagrams and pictures for your data structures).
Time complexity.
- O (m*n)
3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.



