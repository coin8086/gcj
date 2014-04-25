#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

class Subset {
public:
  Subset() : sum(0) {}
  int sum;
  vector<int> num;
};

void enum_all(const vector<int> & num, vector<bool> & curr, vector<Subset> & sets) {
  if (curr.size() == num.size()) {
    sets.resize(sets.size() + 1);
    Subset & s = sets.back();
    for (int i = 0; i < curr.size(); i++) {
      if (curr[i]) {
        s.sum += num[i];
        s.num.push_back(num[i]);
      }
    }
  }
  else {
    bool cands[] = {false,  true};
    for (int i = 0; i < 2; i++) {
      curr.push_back(cands[i]);
      enum_all(num, curr, sets);
      curr.pop_back();
    }
  }
}

bool cmp(const Subset & a, const Subset & b) {
  return a.sum < b.sum;
}

vector<vector<int> > resolve(vector<int> & num) {
  vector<bool> curr;
  vector<Subset> sets;
  enum_all(num, curr, sets);
  sort(sets.begin(), sets.end(), cmp);
  vector<vector<int> > r;
  for (int i = 0; i < sets.size() - 1; i++) {
    if (sets[i].sum == sets[i + 1].sum) {
      r.push_back(sets[i].num);
      r.push_back(sets[i + 1].num);
      break;
    }
  }
  return r;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    vector<int> num;
    num.reserve(N);
    for (int i = 0; i < N; i++) {
      int n;
      cin >> n;
      num.push_back(n);
    }
    cout << "Case #" << t + 1 << ":" << endl;
    vector<vector<int> > subsets = resolve(num);
    for (int i = 0; i < subsets.size(); i++) {
      for (int j = 0; j < subsets[i].size(); j++) {
        if (j)
          cout << ' ';
        cout << subsets[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}

