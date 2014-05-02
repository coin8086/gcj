#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

typedef vector<string> Flows;

//Count how many '1's there are in the k-th column of flows.
inline int count_one(const Flows & f, int k) {
  int cnt = 0;
  for (int i = 0; i < f.size(); i++) {
    if (f[i][k] == '1')
      cnt++;
  }
  return cnt;
}

//Flip the k-th column of flows.
inline void change(Flows & f, int k) {
  for (int i = 0; i < f.size(); i++) {
    f[i][k] = f[i][k] == '0' ? '1' : '0';
  }
}

//Tell if first k characters of string s and t match.
inline bool match(const string & s, const string & t, int k) {
  for (int i = 0; i <= k; i++) {
    if (s[i] != t[i])
      return false;
  }
  return true;
}

//Tell if first k columns of flows s and t match.
bool match(const Flows & s, const Flows & t, int k) {
  set<int> matched;
  int N = s.size();
  for (int i = 0; i < N; i++) {
    bool found = false;
    for (int j = 0; j < N; j++) {
      if (!matched.count(j) && match(s[i], t[j], k)) {
        matched.insert(j);
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return true;
}

bool search(int N, int L, Flows & s, Flows & t, int i, int & times) {
  if (i == L) {
    //Since we always try no-change match first, this is the minimum times of change.
    return true;
  }

  int ones_s = count_one(s, i);
  int ones_t = count_one(t, i);
  bool changable = false;
  //Need to change at first
  if (ones_s != ones_t) {
    if (ones_s + ones_t != N) {
      return false; //Impossible anyway
    }
    times++;
    change(s, i);
    if (match(s, t, i) && search(N, L, s, t, i + 1, times)) {
      return true;
    }
    times--;
    change(s, i);
    return false;
  }
  else if (ones_s + ones_t == N) {
    changable = true;
  }

  //No need to change at first
  if (match(s, t, i) && search(N, L, s, t, i + 1, times)) {
    return true;
  }

  if (!changable)
    return false;

  //If ones_s == ones_t, then we have second chance to make change and match.
  times++;
  change(s, i);
  if (match(s, t, i) && search(N, L, s, t, i + 1, times)) {
    return true;
  }
  times--;
  change(s, i);
  return false;
}

inline void resolve(int N, int L, Flows & s, Flows & t) {
  int times = 0;
  if (search(N, L, s, t, 0, times))
    cout << times;
  else
    cout << "NOT POSSIBLE";
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N, L;
    cin >> N >> L;
    Flows s, tar;
    for (int i = 0; i < N; i++) {
      string f;
      cin >> f;
      s.push_back(f);
    }
    for (int i = 0; i < N; i++) {
      string f;
      cin >> f;
      tar.push_back(f);
    }
    cout << "Case #" << t + 1 << ": ";
    resolve(N, L, s, tar);
    cout << endl;
  }
  return 0;
}

