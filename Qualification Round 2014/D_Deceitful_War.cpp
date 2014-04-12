#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

inline int score(const vector<double> & a, const vector<double> & b) {
  int i = 0;
  int j = 0;
  int s = 0;
  while (i < a.size()) {
    if (a[i] > b[j]) {
      s++;
      j++;
    }
    i++;
  }
  return s;
}

inline vector<double> get_blocks(int N) {
  vector<double> a;
  a.reserve(N);
  for (int i = 0; i < N; i++) {
    double m;
    cin >> m;
    a.push_back(m);
  }
  sort(a.begin(), a.end());
  return a;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    vector<double> a = get_blocks(N);
    vector<double> b = get_blocks(N);
    cout << "Case #" << t + 1 << ": " << score(a, b) << ' ' << N - score(b, a) << endl;
  }
  return 0;
}

