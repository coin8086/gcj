#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;

class Chest {
public:
  Chest() : type(0), open(false) {}
  int type;
  vector<int> keys;
  bool open;
};

inline vector<int> candidates(const vector<Chest> & chests, const multiset<int> & avail_keys) {
  vector<int> cands;
  if (!avail_keys.empty()) {
    for (int i = 1; i < chests.size(); i++) {
      if (!chests[i].open) {
        if (avail_keys.find(chests[i].type) != avail_keys.end())
          cands.push_back(i);
      }
    }
  }
  return cands;
}

bool search(vector<Chest> & chests, multiset<int> & avail_keys, vector<int> & path) {
  if (path.size() == chests.size() - 1)
    return true;

#ifdef DEBUG
  cout << "Path:";
  for (int i = 0; i < path.size(); i++) {
    cout << ' ' << path[i];
  }
  cout << endl;
#endif
  vector<int> cands = candidates(chests, avail_keys);
#ifdef DEBUG
  cout << "Candidates:";
  for (int i = 0; i < cands.size(); i++) {
    cout << ' ' << cands[i];
  }
  cout << endl;
#endif
  for (int i = 0; i < cands.size(); i++) {
    Chest & c = chests[cands[i]];
    c.open = true;
    avail_keys.erase(avail_keys.find(c.type));
    avail_keys.insert(c.keys.begin(), c.keys.end());
    path.push_back(cands[i]);
    if (search(chests, avail_keys, path))
      return true;
    c.open = false;
    for (int j = 0; j < c.keys.size(); j++) {
      avail_keys.erase(avail_keys.find(c.keys[j]));
    }
    avail_keys.insert(c.type);
    path.pop_back();
  }
  return false;
}

bool impossible0(vector<Chest> & chests, multiset<int> & avail_keys) {
  map<int, int> required;
  multiset<int> all;
  for (int i = 1; i < chests.size(); i++) {
    Chest & c = chests[i];
    required[c.type] += 1;
    all.insert(c.keys.begin(), c.keys.end());
  }
  all.insert(avail_keys.begin(), avail_keys.end());
  typedef map<int, int>::iterator It;
  for (It it = required.begin(); it != required.end(); it++) {
    if (all.count(it->first) < it->second)
      return true;
  }
  return false;
}

void dfs(vector<Chest> & chests, int idx) {
  Chest & c = chests[idx];
  c.open = true;
  for (int i = 0; i < c.keys.size(); i++) {
    for (int j = 1; j < chests.size(); j++) {
      if (!chests[j].open && chests[j].type == c.keys[i])
        dfs(chests, j);
    }
  }
}

bool impossible(vector<Chest> & chests, multiset<int> & avail_keys) {
  if (impossible0(chests, avail_keys))
    return true;

  bool ret = false;
  chests[0].keys.insert(chests[0].keys.end(), avail_keys.begin(), avail_keys.end());
  dfs(chests, 0);
  for (int i = 0; i < chests.size(); i++) {
    if (!chests[i].open)
      ret = true;
    else
      chests[i].open = false;
  }
  chests[0].keys.clear();
  return ret;
}

inline vector<int> resolve(vector<Chest> & chests, multiset<int> & avail_keys) {
#ifdef DEBUG
  cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
#endif
  vector<int> path;
  if (impossible(chests, avail_keys))
    return path;

  if (!search(chests, avail_keys, path))
    path.clear();

#ifdef DEBUG
  cout << "----------------------------------------" << endl;
#endif
  return path;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    vector<Chest> chests(1); //Skip #0
    multiset<int> avail_keys;
    int K, N;
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
      int k;
      cin >> k;
      assert(k > 0);
      avail_keys.insert(k);
    }
    for (int i = 0; i < N; i++) {
      Chest c;
      int T, K;
      cin >> T >> K;
      c.type = T;
      for (int j = 0; j < K; j++) {
        int k;
        cin >> k;
        if (k > 0)
          c.keys.push_back(k);
      }
      chests.push_back(c);
    }
    vector<int> path = resolve(chests, avail_keys);
    cout << "Case #" << t + 1 << ":";
    if (path.empty())
      cout << " IMPOSSIBLE";
    else
      for (int i = 0; i < path.size(); i++)
        cout << ' ' << path[i];
    cout << endl;
  }
  return 0;
}

