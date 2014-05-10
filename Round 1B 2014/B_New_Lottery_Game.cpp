#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

inline ll foo(ll A, ll B, ll K) {
#ifdef DEBUG
  clog << A - K << ", " << B - K << ", " << (A - K) * (B - K) << endl;
#endif
  ll times = 0;
  ll N = min(A, B);
  for (ll i = K; i < N; i++) {
    for (ll j = i + 1; j < N; j++) {
      if ((i & j) < K)
        times += 2;
    }
  }
  if (A != B) {
    ll M = max(A, B);
    for (ll i = N; i < M; i++)
      for (ll j = K; j < N; j++)
        if ((i & j) < K)
          times++;
  }
  return times;
}

inline ll resolve(ll A, ll B, ll K) {
  ll times = 0;
  if (A <= K || B <= K) {
    times = A * B;
  }
  else {
    times = K * (A + B - K);
    times += foo(A, B, K);
  }
  return times;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int A, B, K;
    cin >> A >> B >> K;
    cout << "Case #" << t + 1 << ": " << resolve(A, B, K) << endl;
  }
  return 0;
}

