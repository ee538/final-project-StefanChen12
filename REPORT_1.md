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


Time complexity
- O (data.size* Name.length)

Time spent
- 3 ms



## 2
Implementation of GetPosition: 5 points. (Phase 1)
```cpp
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::string pos_id = GetID(name);                                         //Use GetId get id cause we need use id to get node and get latitud and longitude
  
  std::pair<double, double> results(data[pos_id].lat, data[pos_id].lon);
  return results;
}


Time complexity. 
- O(n)

Time spent
- 3 ms

Discussion, conclusion, and lessons learned.
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

##
overview of the algorithm
because we can use three different method to modify a single word. So when we compare two words, we can compare from the tail.
if the tails are the same, them we can push backward. Using dynamic programing. dp[i][j] means the least numbers of changes that can transform
the i-length word into the j-length word. so as what we said before, if the last alpha is the same. them we can know dp[m][n] = dp[m-1][n-1],
if not, then it either equals to dp[i - 1][j], which means we delete the last alpha of the first word; or it equals dp[i][j - 1], means we 
insert one alpha at the end of the first word. And dp[i][j] = min( dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]), this is the recursion
function.

Time complexity.
- O (m*n)

Time spend:
232 ms
