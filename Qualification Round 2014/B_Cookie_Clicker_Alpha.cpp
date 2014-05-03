#include <iostream>
#include <cassert>

using namespace std;

typedef unsigned long long ull;
typedef long double ld;

/*
 * Let t(n) be the time need for buying n-th farm, then
 * t(0) = 0
 * t(1) = C / 2
 * t(2) = C / (2 + F)
 * ...
 * t(n) = C / (2 + (n - 1) * F)
 * Let T(n) be the time for collecting X cookies if we have n farms, then
 * T(n) = t(0) + t(1) + ... + t(n) + X / (2 + n * F)
 * Suppose T(n) will get a minimum value at some n, and a bigger value at n + 1,
 * then we can get it by increasing n from 0 and calculating T(n).
 * But before we do it brutally, we found some cheaper way in calculation:
 * Let
 * P(n) = 1/2 + ... + 1 /(2 + (n - 1) * F)
 * and
 * Q(n) = 1 / (2 + n * F)
 * then
 * T(n) = C * P(n) + X * Q(n)
 * and
 * P(n) = P(n - 1) + Q(n - 1)
 */
ld resolve(ld C, ld F, ld X) {
  ld s = 0;
  ld x = 1.0L / 2;
  ld last = X / 2;
  ull n = 1;
  while (true) {
    s += x;
    x = 1 / (2 + n * F);
    ld t = C * s + X * x;
    if (last < t)
      break;
    last = t;
    n++;
  }
  return last;
}

int main() {
  cout.precision(7);
  cout << fixed;
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    ld C, F, X;
    cin >> C >> F >> X;
    cout << "Case #" << t + 1 << ": " << resolve(C, F, X) << endl;
  }
  return 0;
}

