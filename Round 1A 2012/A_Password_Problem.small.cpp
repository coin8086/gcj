#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long double ld;

class Pattern {
public:
  Pattern(int idx, ld prob) : first_err(idx), p(prob) {}
  int first_err;
  ld p;
};

void enum_all(const vector<ld> & P, vector<bool> & curr, vector<Pattern> & patterns) {
  if (P.size() == curr.size()) {
    int first = P.size();
    ld p = 1;
    for (int i = 0; i < curr.size(); i++) {
      if (curr[i]) {
        p *= P[i];
      }
      else {
        p *= (1 - P[i]);
        if (i < first)
          first = i;
      }
    }
    patterns.push_back(Pattern(first, p));
  }
  else {
    bool cands[] = {false, true};
    for (int i = 0; i < 2; i++) {
      curr.push_back(cands[i]);
      enum_all(P,  curr, patterns);
      curr.pop_back();
    }
  }
}

inline vector<Pattern> all_patterns(const vector<ld> & P) {
  vector<Pattern> patterns;
  vector<bool> curr;
  enum_all(P, curr, patterns);
  return patterns;
}

ld resolve(int A, int B, const vector<ld> & P) {
  ld expect = 1 + B + 1;
  vector<Pattern> patterns = all_patterns(P);
  for (int to_del = 0; to_del <= A; to_del++) {
    ld e = 0;
    for (int i = 0; i < patterns.size(); i++) {
      if (A - to_del <= patterns[i].first_err)
        e += (to_del * 2 + B - A + 1) * patterns[i].p;
      else
        e += (to_del * 2 + B - A + 1 + B + 1) * patterns[i].p;
    }
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

