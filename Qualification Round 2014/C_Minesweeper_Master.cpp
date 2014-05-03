#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<vector<char> > Board;

class Pair {
public:
  Pair() : x(0), y(0) {}
  Pair(int i, int j) : x(i), y(j) {}
  int x;
  int y;
};

#ifdef DEBUG
inline void debug(const Board & b) {
  int R = b.size();
  int C = b[0].size();
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (b[i][j])
        clog << b[i][j];
      else
        clog << 'U';
    }
    clog << endl;
  }
  clog << endl;
}
#endif

inline void output(const Board & b) {
  int R = b.size();
  int C = b[0].size();
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (!b[i][j])
        cout << '*';
      else if (!i && !j)
        cout << 'c';
      else
        cout << '.';
    }
    cout << endl;
  }
}

inline vector<Pair> candidates(const Board & b, int i, int j) {
  int R = b.size();
  int C = b[0].size();
  vector<Pair> n;
  n.reserve(8);
  if (i > 0 && !b[i - 1][j])
    n.push_back(Pair(i - 1, j));

  if (i > 0 && j != C - 1 && !b[i - 1][j + 1])
    n.push_back(Pair(i - 1, j + 1));

  if (j != C - 1 && !b[i][j + 1])
    n.push_back(Pair(i, j + 1));

  if (i != R - 1 && j != C - 1 && !b[i + 1][j + 1])
    n.push_back(Pair(i + 1, j + 1));

  if (i != R - 1 && !b[i + 1][j])
    n.push_back(Pair(i + 1, j));

  if (i != R - 1 && j > 0 && !b[i + 1][j - 1])
    n.push_back(Pair(i + 1, j - 1));

  if (j > 0 && !b[i][j - 1])
    n.push_back(Pair(i, j - 1));

  if (i > 0 && j > 0 && !b[i - 1][j - 1])
    n.push_back(Pair(i - 1, j - 1));

  return n;
}

inline void mark(Board & b, const vector<Pair> & pairs, char ch) {
  for (int i = 0; i < pairs.size(); i++) {
    const Pair & p = pairs[i];
    b[p.x][p.y] = ch;
  }
}

bool search(Board & b, int x, int y, int t, int s) {
  bool r = false;
  b[x][y] = 'z';
  vector<Pair> cands = candidates(b, x, y);
  mark(b, cands, 'e');
#ifdef DEBUG
  debug(b);
#endif
  s += cands.size();
  if (s == t) {
    r = true;
  }
  else if (s < t) {
    for (int i = 0; i < cands.size(); i++) {
      if (search(b, cands[i].x, cands[i].y, t, s)) {
        r = true;
        break;
      }
    }
  }
  if (!r) {
    mark(b, cands, 0);
    b[x][y] = 'e';
  }
  return r;
}

/*
 * The general idea is: a cell of 0 determines the other empty cells around it.
 * We start with an empty cell, mark it as zero and extend its neighbours as emtpy cells.
 * Then from one of its empty neighbours we repeat the procedure, until we have exactly
 * the number of empty spaces we want. Back trace is used to make it.
 *
 * Note that if we turn on DEBUG, we may find there're many unnecessary(but not repeated)
 * searches, for example, when R = 2, C = 50, M = 3. In this case, the back trace will take
 * endless time(roughly O(2^50)), So I add a prejudge for it(when R = 2 or C = 2). Alghough
 * I doubt such an ugly "patch" doesn't cover all cases perfectly, it works.
 */
inline void resolve(int R, int C, int M) {
  if ((R == 2 || C == 2) && M % 2) {
    cout << "Impossible" << endl;
    return;
  }
  Board b(R, vector<char>(C));
  b[0][0] = 'e';
  int t = R * C - M;
  if (t == 1 || search(b, 0, 0, t, 1))
    output(b);
  else
    cout << "Impossible" << endl;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int R, C, M;
    cin >> R >> C >> M;
    cout << "Case #" << t + 1 << ":" << endl;
    resolve(R, C, M);
  }
  return 0;
}

