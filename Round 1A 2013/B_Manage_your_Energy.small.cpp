#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int E, R, m;

void search(const vector<int> & n, vector<int> & d, int a) {
  if (d.size() == n.size()) {
    int c = 0;
    for (int i = 0; i < d.size(); i++) {
      c += d[i] * n[i];
    }
    if (c > m)
      m = c;
    return;
  }
  for (int c = 0; c <= a; c++) {
    d.push_back(c);
    int na = a - c + R;
    if (na > E)
      na = E;
    search(n, d, na);
    d.pop_back();
  }
}

int resolve(int e, int r, const vector<int> & n) {
  if (e <= r) {
    int c = 0;
    for (int i = 0; i < n.size(); i++) {
      c += n[i];
    }
    return c * e;
  }
  E = e;
  R = r;
  m = 0;
  vector<int> d;
  search(n, d, e);
  return m;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int e, r, n;
    cin >> e >> r >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      int vi;
      cin >> vi;
      v.push_back(vi);
    }
    cout << "Case #" << t + 1 << ": " << resolve(e, r, v) << endl;
  }
  return 0;
}

