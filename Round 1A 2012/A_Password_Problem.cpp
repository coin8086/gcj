#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long double ld;

ld resolve(int A, int B, const vector<ld> & P) {
  ld expect = 1 + B + 1;
  for (int to_del = 0; to_del <= A; to_del++) {
    ld p = 1;
    for (int i = 0; i < A - to_del; i++)
      p *= P[i];

    ld e = (to_del * 2 + B - A + 1) * p;
    e += (to_del * 2 + B - A + 1 + B + 1) * (1 - p);

    if (e < expect)
      expect = e;
  }
  return expect;
}

int main() {
  cout.precision(6);
  cout << fixed;
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int A, B;
    cin >> A >> B;
    vector<ld> P;
    P.reserve(A);
    for (int i = 0; i < A; i++) {
      ld p;
      cin >> p;
      P.push_back(p);
    }
    cout << "Case #" << t + 1 << ": " << resolve(A, B, P) << endl;
  }
  return 0;
}

