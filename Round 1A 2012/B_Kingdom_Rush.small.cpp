#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <cassert>

using namespace std;

typedef pair<int, int> Level;
typedef pair<bool, bool> State;

int minimum = INT_MAX;

vector<int> candidates(const vector<Level> & levels, const vector<State> & states, int stars) {
  vector<int> cands;
  for (int i = 0; i < levels.size(); i++) {
    if (!states[i].second && levels[i].second <= stars) {
      cands.push_back(i);
      break;
    }
  }
  if (cands.empty()) {
    for (int i = 0; i < levels.size(); i++) {
      if (!states[i].second && !states[i].first && levels[i].first <= stars) {
        cands.push_back(i);
      }
    }
  }
  return cands;
}

void search(const vector<Level> & levels, vector<State> & states, int complete, int times, int stars) {
  if (complete == levels.size()) {
    if (minimum > times)
      minimum = times;
  }
  else {
    vector<int> cands = candidates(levels, states, stars);
    for (int i = 0; i < cands.size(); i++) {
      int l = cands[i];
      if (stars >= levels[l].second) {
        states[l].second = true;
        search(levels, states, complete + 1, times + 1, states[l].first ? stars + 1 : stars + 2);
        states[l].second = false;
      }
      else {
        states[l].first = true;
        search(levels, states, complete, times + 1, stars + 1);
        states[l].first = false;
      }
    }
  }
}

inline void resolve(const vector<Level> & levels) {
  minimum = INT_MAX;
  vector<State> states(levels.size());
  search(levels, states, 0, 0, 0);
  if (minimum == INT_MAX)
    cout << "Too Bad";
  else
    cout << minimum;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    vector<Level> levels;
    levels.reserve(N);
    for (int i = 0; i < N; i++) {
      int a, b;
      cin >> a >> b;
      levels.push_back(make_pair(a, b));
    }
    cout << "Case #" << t + 1 << ": ";
    resolve(levels);
    cout << endl;
  }
  return 0;
}

