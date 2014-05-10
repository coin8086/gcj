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

int change(const string & s1, const string & s2, string * result = 0) {
  string a = s1;
  string b = s2;
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
  if (result)
    *result = a;
  return times;
}

string slim(const string & a) {
  string r = a;
  string::iterator p = r.begin();
  for (; *p; p++) {
    while (*p && *p == *(p + 1))
      r.erase(p);
  }
  return r;
}

inline void resolve(const vector<string> & strs) {
  string s = slim(strs[0]);
  vector<int> dist;
  for (int i = 0; i < strs.size(); i++) {
    int c = change(strs[i], s);
    if (c < 0) {
      cout << "Fegla Won";
      return;
    }
    dist.push_back(c);
  }
  sort(dist.begin(), dist.end());
  int mid;
  if (dist.size() % 2)
    mid = dist[dist.size() / 2];
  else {
    int m = dist.size() / 2;
    mid = (dist[m - 1] + dist[m]) / 2;
  }
  int minimum = 0;
  for (int i = 0; i < dist.size(); i++) {
    minimum += abs(dist[i] - mid);
  }
  cout << minimum;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    vector<string> strs;
    strs.reserve(N);
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      strs.push_back(s);
    }
    cout << "Case #" << t + 1 << ": ";
    resolve(strs);
    cout << endl;
  }
  return 0;
}

