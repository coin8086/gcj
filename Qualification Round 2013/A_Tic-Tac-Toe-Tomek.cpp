#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef vector<vector<char> > Board;

inline void count(char ch, int & cx, int & co, int & ct) {
  if (ch == 'X')
    cx++;
  else if (ch == 'O')
    co++;
  else if (ch == 'T')
    ct++;
}

inline bool check(int cx, int co, int ct, bool & x, bool & o, bool & over) {
  if (cx + co + ct < 4) {
    over = false;
  }
  else if (cx * co == 0) {
    !cx ? o = true : x = true;
  }
  return o || x;
}

const char * resolve(const Board & b) {
  bool x = false;
  bool o = false;
  bool over = true;
  int cx, co, ct;

  //Check columnes
  for (int j = 0; j < 4; j++) {
    cx = co = ct = 0;
    for (int i = 0; i < 4; i++) {
      count(b[i][j], cx, co, ct);
    }
    if (check(cx, co, ct, x, o, over))
      return x ? "X won" : "O won";
  }

  //Check rows
  for (int i = 0; i < 4; i++) {
    cx = co = ct = 0;
    for (int j = 0; j < 4; j++) {
      count(b[i][j], cx, co, ct);
    }
    if (check(cx, co, ct, x, o, over))
      return x ? "X won" : "O won";
  }

  //Check cross
  cx = co = ct = 0;
  for (int i = 0, j = 0; i < 4; i++, j++) {
    count(b[i][j], cx, co, ct);
  }
  if (check(cx, co, ct, x, o, over))
    return x ? "X won" : "O won";

  cx = co = ct = 0;
  for (int i = 0, j = 3; i < 4; i++, j--) {
    count(b[i][j], cx, co, ct);
  }
  if (check(cx, co, ct, x, o, over))
    return x ? "X won" : "O won";

  return over ? "Draw" : "Game has not completed";
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    Board b(4, vector<char>(4));
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        char ch;
        cin >> ch;
        b[i][j] = ch;
      }
    }
    cout << "Case #" << t + 1 << ": " << resolve(b) << endl;
  }
  return 0;
}

