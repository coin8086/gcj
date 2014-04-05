#include <iostream>
#include <cassert>

using namespace std;

typedef unsigned long long ull;

ull search(ull start, ull end, ull r, ull t) {
  assert(start < end);
  if (start + 1 == end)
    return start;
  ull m = (start + end) / 2;
  /*
   * Note that we can not have
   * if (2 * m * m + (2 * r - 1) * m <= t)
   * here because it will overflow an unsigned long long type when m is big
   * enough. And we also can't have
   * if (a - b <= 0)
   * while a and b are both unsigned values.
   */
  if (2 * m + (2 * r - 1) <= t / m)
    return search(m, end, r, t);
  return search(start, m, r, t);
}

/*
 * The solution is to find out the biggest integer n that satisfies:
 * 2 * n * n + (2 * r - 1) * n <= t
 * But it's not that easy if we want to avoid big integer arithmetics while
 * keeping enough precision. So we use binary search here.
 * Note that although we have:
 * 1 <= 2 * n * n < t
 * thus:
 * 1 <= n < sqrt(t / 2)
 * We can't use sqrt(t / 2) as an upper limit here, for the long double
 * type can only represent 18 decimal digits, while t can have as many
 * as 19 digits. So we have to use t as an upper limit.
 */
inline ull resolve(ull r, ull t) {
  return search(1, t, r, t);
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    ull r, t;
    cin >> r >> t;
    cout << "Case #" << i + 1 << ": " << resolve(r, t) << endl;
  }
  return 0;
}

