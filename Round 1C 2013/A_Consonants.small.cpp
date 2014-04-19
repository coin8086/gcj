#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

class Pair {
public:
  Pair(int a, int b) : i(a), j(b) {}
  int i;
  int j;
};

inline bool is_vowel(char ch) {
  return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

vector<Pair> parse(const string & name, int n) {
  vector<Pair> pairs;
  pairs.push_back(Pair(-1, -1));
  int i = 0;
  while (true) {
    while (i < name.size() && is_vowel(name[i]))
      i++;
    if (i == name.size())
      break;
    int sub = i;
    int count = 0;
    while (i < name.size() && !is_vowel(name[i])) {
      i++;
      count++;
    }
    if (count >= n) {
      int last = sub + (count - n);
      while (sub <= last) {
        pairs.push_back(Pair(sub, sub + n));
        sub++;
      }
    }
    if (i == name.size())
      break;
    i++;
  }
  pairs.push_back(Pair(name.size() + 1, name.size() + 1));
  return pairs;
}

inline ll count(int ia, int ja, int ik, int jk) {
  //assert(ia <= ik && jk <= ja && ik < jk);
  ll p = ik - ia;
  ll t = ja - jk;
  return 1 + p + t + p * t;
}

ll resolve(const string & name, int n) {
  vector<Pair> sub = parse(name, n);
  ll m = 0;
  for (int k = 1; k < sub.size() - 1; k++) {
    for (int p = 1; p <= k; p++) {
      m += count(sub[k - p].i + 1, sub[k + 1].j - 1, sub[k - p + 1].i, sub[k].j);
    }
  }
  return m;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    string name;
    int n;
    cin >> name >> n;
    cout << "Case #" << t + 1 << ": " << resolve(name, n) << endl;
  }
  return 0;
}

