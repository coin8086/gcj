#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long ull;

inline ull pow(int base, int exp) {
  if (!exp)
    return 1;
  ull n = (ull)base;
  for (int i = 2; i <= exp; i++) {
    n *= base;
  }
  return n;
}

ull resolve(const string & word) {
  vector<int> v;
  map<char, int> m;
  int avail = 1;
  int i;
  for (i = 0; i < word.size(); i++) {
    char ch = word[i];
    map<char, int>::iterator it = m.find(ch);
    if (it != m.end()) {
      v.push_back(it->second);
    }
    else {
      v.push_back(avail);
      m[ch] = avail;
      if (avail >= 2)
        avail++;
      else if (avail == 1)
        avail = 0;
      else
        avail = 2;
    }
  }
  int base = avail >= 2 ? avail : 2;
  ull n = 0;
  for (i = 0; i < v.size(); i++) {
    n += v[i] * pow(base, v.size() - i - 1);
  }
  return n;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    string word;
    cin >> word;
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << resolve(word);
  }
  return 0;
}

