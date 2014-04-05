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
typedef long long ll;
typedef long double ld;

inline int insert(int target, int & init) {
  int c = 0;
  while (init <= target) {
    init = 2 * init - 1;
    c++;
  }
  return c;
}

int resolve(int a, vector<int> & n) {
#ifdef DEBUG
  cout << "resolve ----------------------------------" << endl;
  cout << "a: " << a << endl;
#endif
  if (a == 1)
    return n.size();
  if (n.size() == 1)
    return a > n[0] ? 0 : 1;
  sort(n.begin(), n.end());
#ifdef DEBUG
  cout << "n:" << endl;
  for (int i = 0; i < n.size(); i++)
    cout << ' ' << n[i];
  cout << endl;
#endif
  vector<int> gap;
  for (int i = 0; i < n.size(); i++) {
    gap.push_back(insert(n[i], a));
    a += n[i];
  }
#ifdef DEBUG
  cout << "gap:" << endl;
  for (int i = 0; i < gap.size(); i++)
    cout << ' ' << gap[i];
  cout << endl;
#endif
  vector<int> cand;
  int c = 0;
  for (int i = 0; i < gap.size(); i++) {
    c += gap[i];
    cand.push_back(c + n.size() - (i + 1));
  }
  cand.push_back(n.size());
#ifdef DEBUG
  cout << "cand:" << endl;
  for (int i = 0; i < cand.size(); i++)
    cout << ' ' << cand[i];
  cout << endl;
#endif
  return *min_element(cand.begin(), cand.end());
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int A, N;
    cin >> A >> N;
    vector<int> motes;
    for (int i = 0; i < N; i++) {
      int n;
      cin >> n;
      motes.push_back(n);
    }
    cout << "Case #" << t + 1 << ": " << resolve(A, motes) << endl;
  }
  return 0;
}

