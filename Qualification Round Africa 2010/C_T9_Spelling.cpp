#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

const char * key_map[] = {
  "2",
  "22",
  "222",
  "3",
  "33",
  "333",
  "4",
  "44",
  "444",
  "5",
  "55",
  "555",
  "6",
  "66",
  "666",
  "7",
  "77",
  "777",
  "7777",
  "8",
  "88",
  "888",
  "9",
  "99",
  "999",
  "9999"
};

const char * key_map2[] = {
  "bc",
  "c",
  "",
  "ef",
  "f",
  "",
  "hi",
  "i",
  "",
  "kl",
  "l",
  "",
  "no",
  "o",
  "",
  "qrs",
  "rs",
  "s",
  "",
  "uv",
  "v",
  "",
  "xyz",
  "yz",
  "z",
  ""
};

inline bool in_same_key(char a, char b) {
  if (a == b)
    return true;
  if (abs(a - b) > 3)
    return false;
  if (a < b)
    return strchr(key_map2[a - 'a'], b);
  return strchr(key_map2[b - 'a'], a);
}

int main() {
  int N = 0;
  string line;
  cin >> N;
  getline(cin, line); //Skip end \n
  for (int i = 0; i < N; i++) {
    getline(cin, line);
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": ";
    char last = 0;
    for (int j = 0; j < line.size(); j++) {
      char ch = line[j];
      if (in_same_key(ch, last))
        cout << ' ';
      if (ch == ' ')
        cout << '0';
      else
        cout << key_map[ch - 'a'];
      last = ch;
    }
  }
  return 0;
}


