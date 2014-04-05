#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

inline int insert(int target, int & init) {
  int c = 0;
  while (init <= target) {
    init = 2 * init - 1;
    c++;
  }
  return c;
}

int resolve(int a, vector<int> & n) {
  if (a == 1)
    return n.size();
  if (n.size() == 1)
    return a > n[0] ? 0 : 1;
  sort(n.begin(), n.end());
  vector<int> gap;
  for (int i = 0; i < n.size(); i++) {
    gap.push_back(insert(n[i], a));
    a += n[i];
  }
  vector<int> cand;
  int c = 0;
  for (int i = 0; i < gap.size(); i++) {
    c += gap[i];
    cand.push_back(c + n.size() - (i + 1));
  }
  cand.push_back(n.size());
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

