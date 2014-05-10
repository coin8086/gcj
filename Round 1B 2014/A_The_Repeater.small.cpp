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

int change(string & a, string & b) {
  a.reserve(200);
  b.reserve(200);
  string::iterator p = a.begin();
  string::iterator q = b.begin();
  int times = 0;

  if (*p != *q)
    return -1;

  while (true) {
    while (*p && *q && *p == *q)
      p++, q++;
    if (!*p && !*q)
      break;
    if (*(p - 1) == *q) {
      a.insert(p, *q);
      times++;
    }
    else if (*p == *(q - 1)) {
      a.erase(p);
      times++;
    }
    else
      return -1;
  }
  return times;
}

inline void resolve(string & a, string & b) {
  int times = change(a, b);
  if (times >= 0)
    cout << times;
  else
    cout << "Fegla Won";
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    string a, b;
    cin >> a >> b;
    cout << "Case #" << t + 1 << ": ";
    resolve(a, b);
    cout << endl;
  }
  return 0;
}

