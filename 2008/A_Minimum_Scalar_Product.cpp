#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline void read_vector(vector<int> & v, int n) {
  v.reserve(n);
  for (int j = 0; j < n; j++) {
    int x;
    cin >> x;
    v.push_back(x);
  }
}

inline long long resolve(vector<int> & v1, vector<int> & v2) {
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  long long r = 0;
  int n = v1.size();
  for (int i = 0; i < n; i++) {
    r += (long long)v1[i] * v2[n - i - 1];
  }
  return r;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int n;
    cin >> n;
    vector<int> v1, v2;
    read_vector(v1, n);
    read_vector(v2, n);
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << resolve(v1, v2);
  }
  return 0;
}

