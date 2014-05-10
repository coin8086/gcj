#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

inline int align(vector<string> & strs) {
  int m = 0;
  for (int i = 0; i < strs.size(); i++) {
    if (strs[i].size() > m)
      m = strs[i].size();
  }
  m *= 2; //NOTE here!
  for (int i = 0; i < strs.size(); i++) {
    strs[i].resize(m);
  }
  return m;
}

inline void resolve(vector<string> & strs) {
  int n = strs.size();
  char ch = strs[0][0];
  for (int k = 1; k < n; k++) {
    if (ch != strs[k][0]) {
      cout << "Fegla Won";
      return;
    }
  }

  int m = align(strs);
  int times = 0;
  for (int i = 1; i < m; i++) {
    char a_ch = strs[0][i];
    char b_ch = 0;
    int a_cnt = 1;
    int b_cnt = 0;
    for (int k = 1; k < n; k++) {
      char ch = strs[k][i];
      if (ch == a_ch) {
        a_cnt++;
      }
      else {
        if (!b_cnt) {
          b_ch = ch;
          b_cnt++;
        }
        else if (ch == b_ch) {
          b_cnt++;
        }
        else {
          cout << "Fegla Won";
          return;
        }
      }
    }
    char t_ch = a_cnt >= b_cnt ? a_ch : b_ch;
    for (int k = 0; k < n; k++) {
      if (strs[k][i] != t_ch) {
        if (strs[k][i - 1] == t_ch) {
          strs[k].insert(i, 1, t_ch);
          times++;
        }
        else {
          while (strs[k][i] != t_ch) {
            if (strs[k][i - 1] == strs[k][i]) {
              strs[k].erase(i, 1);
              times++;
            }
            else
              break;
          }
          if (strs[k][i] != t_ch) {
            cout << "Fegla Won";
            return;
          }
        }
      }
    }
  }
  cout << times;
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

