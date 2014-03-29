#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

#define UPPER 10000000
//#define UPPER 31

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;

vector<ull> fs;

inline bool is_fair(ull n) {
  vector<char> digits;
  digits.reserve(20);
  while (n) {
    digits.push_back(n % 10);
    n /= 10;
  }
  for (uint i = 0; i < digits.size(); i++) {
    if (digits[i] != digits[digits.size() - i - 1])
      return false;
  }
  return true;
}

void init() {
  fs.reserve(1000);
  fs.push_back(1);
  for (uint i = 2; i <= UPPER; i++) {
    if (is_fair(i)) {
      ull i2 = (ull)i * i;
      if (is_fair(i2))
        fs.push_back(i2);
    }
  }
  //cout << "Size: " << fs.size() << endl;
}

inline ull resolve(ull A, ull B) {
  typedef vector<ull>::const_iterator It;
  It lower = lower_bound(fs.begin(), fs.end(), A);
  It upper = upper_bound(fs.begin(), fs.end(), B);
  return upper - lower;
}

int main() {
  init();

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    ull A, B;
    cin >> A >> B;
    cout << "Case #" << t + 1 << ": " << resolve(A, B) << endl;
  }
  return 0;
}

