#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

bool big_first(const int * a, const int * b) {
  return *a > *b;
}

inline ld calc(int sum, const vector<const int *> & SI, int start, int n) {
  assert(n - start > 1);
  int sum2 = 0;
  for (int i = start; i < n; i++)
    sum2 += *SI[i];
  return (sum + sum2) * 1.0L / (n - start);
}

vector<ld> resolve(const vector<int> S) {
  int n = S.size();
  vector<const int *> SI;
  SI.reserve(n);
  for (int i = 0; i < n; i++)
    SI.push_back(&S[i]);
  sort(SI.begin(), SI.end(), big_first);

  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += S[i];
  }

  int start = -1;
  ld A;
  do {
    start++;
    A = calc(sum, SI, start, n);
  } while (*SI[start] > A);

  vector<ld> M(n);
  const int * base = &S[0];
  for (int i = start; i < n; i++) {
    int idx = SI[i] - base;
    M[idx] = (A - S[idx]) * 100 / sum;
  }
  return M;
}

int main() {
  cout.precision(6);
  cout << fixed;
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    vector<int> S;
    S.reserve(N);
    for (int i = 0; i < N; i++) {
      int s;
      cin >> s;
      S.push_back(s);
    }
    cout << "Case #" << t + 1 << ":";
    vector<ld> M = resolve(S);
    for (int i = 0; i < M.size(); i++) {
      cout << ' ' << M[i];
    }
    cout << endl;
  }
  return 0;
}

