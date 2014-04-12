#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef vector<int> Row;

inline void resolve(const Row & r1, const Row & r2) {
  int s = 0;
  int n;
  for (int i = 0; i < 4; i++) {
    if (find(r2.begin(), r2.end(), r1[i]) != r2.end()) {
      if (!s) {
        s = 1;
        n = r1[i];
      }
      else if (s == 1) {
        s = 2;
        break;
      }
    }
  }
  if (s == 1)
    cout << n;
  else if (s == 2)
    cout << "Bad magician!";
  else
    cout << "Volunteer cheated!";
}

inline Row get_row() {
  int ir;
  cin >> ir;
  Row row;
  for (int i = 1; i <= 4; i++) {
    int j, n;
    if (i == ir) {
      for (j = 0; j < 4; j++) {
        cin >> n;
        row.push_back(n);
      }
    }
    else {
      for (j = 0; j < 4; j++)
        cin >> n;
    }
  }
  return row;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    Row r1 = get_row();
    Row r2 = get_row();
    cout << "Case #" << t + 1 << ": ";
    resolve(r1, r2);
    cout << endl;
  }
  return 0;
}

