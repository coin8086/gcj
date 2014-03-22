#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char> > Board;

#ifdef DEBUG
void debug_out(const Board & b) {
  int N = b.size();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << b[i][j];
    }
    cout << endl;
  }
}
#endif

void drop(Board & board) {
#ifdef DEBUG
  cout << "Before drop: -----------------" << endl;
  debug_out(board);
#endif

  for (int j = 0; j < board.size(); j++) {
    int i = board.size() - 1;
    int k = -1;
    while (i >= 0) {
      if (board[i][j] == '.') {
        if (k == -1)
          k = i - 1;
        while (k >= 0 && board[k][j] == '.')
          k--;
        if (k >= 0) {
          board[i][j] = board[k][j];
          board[k][j] = '.';
          i--;
        }
        else
          break;
      }
      else
        i--;
    }
  }

#ifdef DEBUG
  cout << "After drop: ++++++++++++++++++" << endl;
  debug_out(board);
#endif
}

inline bool find_row(const Board & board, int i, int j, int K) {
  char ch = board[i][j];
  int count = 1;
  for (int k = j + 1; k < board.size(); k++) {
    if (board[i][k] == ch)
      count++;
    else
      break;
  }
  return count >= K;
}

inline bool find_col(const Board & board, int i, int j, int K) {
  char ch = board[i][j];
  int count = 1;
  for (int k = i - 1; k >= 0; k--) {
    if (board[k][j] == ch)
      count++;
    else
      break;
  }
  return count >= K;
}

inline bool find_cross(const Board & board, int i, int j, int K) {
  char ch = board[i][j];
  int count = 1;
  for (int x = i - 1, y = j + 1; x >= 0 && y < board.size(); x--, y++) {
    if (board[x][y] == ch)
      count++;
    else
      break;
  }
  return count >= K;
}

inline bool find_cross2(const Board & board, int i, int j, int K) {
  char ch = board[i][j];
  int count = 1;
  for (int x = i - 1, y = j - 1; x >= 0 && y >= 0; x--, y--) {
    if (board[x][y] == ch)
      count++;
    else
      break;
  }
  return count >= K;
}

const char * resolve(Board & board, int K) {
  drop(board);
  bool red = false;
  bool blue = false;
  for (int i = board.size() - 1; i >= 0; i--) {
    for (int j = 0; j < board.size(); j++) {
      char ch = board[i][j];
      if ((ch == 'R' && !red) || (ch == 'B' && !blue)) {
        if (find_row(board, i, j, K))
          ch == 'R' ? red = true : blue = true;
        else if (find_col(board, i, j, K))
          ch == 'R' ? red = true : blue = true;
        else if (find_cross(board, i, j, K))
          ch == 'R' ? red = true : blue = true;
        else if (find_cross2(board, i, j, K))
          ch == 'R' ? red = true : blue = true;
        if (red && blue)
          break;
      }
    }
    if (red && blue)
      break;
  }
  if (red && blue)
    return "Both";
  if (red)
    return "Red";
  if (blue)
    return "Blue";
  return "Neither";
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int N, K;
    cin >> N >> K;
    Board board(N, vector<char>(N));
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        char ch;
        cin >> ch;
        board[k][N - j - 1] = ch; //Rotate 90 degree closewise
      }
    }
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << resolve(board, K);
  }
  return 0;
}

