#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<char> Data;

class Word : public Data {
public:
  Word(const string & w) {
    resize(26 * w.size());
    for (int i = 0; i < w.size(); i++) {
      (*this)[i * 26 + (w[i] - 'a')] = true;
    }
  }
};

typedef vector<Word> Dict;

class Pattern : public Data {
public:
  Pattern(const vector<string> & p) {
    resize(26 * p.size());
    for (int i = 0; i < p.size(); i++) {
      for (int j = 0; j < p[i].size(); j++) {
        (*this)[i * 26 + (p[i][j] - 'a')] = true;
      }
    }
  }

  inline bool match(const Data & d) const {
    assert(size() == d.size());
    Data::const_iterator it1 = begin(), it2 = d.begin();
    for (; it1 != end(); it1++, it2++) {
      if (*it2 && !*it1)
        return false;
    }
    return true;
  }
};

Pattern parse_into_pattern(const string & word) {
  vector<string> tokens;
  bool group = false;
  string token;
  string::const_iterator p = word.begin();
  while (p != word.end()) {
    if (*p == '(')
      group = true;
    else if (*p == ')') {
      group = false;
      tokens.push_back(token);
      token.clear();
    }
    else {
      if (group)
        token.push_back(*p);
      else
        tokens.push_back(string(1, *p));
    }
    p++;
  }
  return Pattern(tokens);
}

inline int resolve(const Dict & dict, const Pattern & pattern) {
  int count = 0;
  for (int i = 0; i < dict.size(); i++) {
    if (pattern.match(dict[i]))
      count++;
  }
  return count;
}

int main() {
  int L, D, N;
  cin >> L >> D >> N;
  Dict dict;
  dict.reserve(D);
  string word;
  int i;
  for (i = 0; i < D; i++) {
    cin >> word;
    dict.push_back(Word(word));
  }
  for (i = 0; i < N; i++) {
    cin >> word;
    Pattern pattern = parse_into_pattern(word);
    int k = resolve(dict, pattern);
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << k;
  }
  return 0;
}

