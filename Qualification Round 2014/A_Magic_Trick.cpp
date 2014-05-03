#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> Row;

inline void resolve(const Row & a, const Row & b) {
  int found = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (a[i] == b[j]) {
        if (!found) {
          found = a[i];
        }
        else {
          found = -1;
          break;
        }
      }
    }
  }
  if (found > 0)
    cout << found;
  else if (found < 0)
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

