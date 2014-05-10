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

ull resolve(int A, int B, int K) {
  ull times = 0;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      int c = i & j;
      if (c < K) {
        times++;
      }
    }
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

