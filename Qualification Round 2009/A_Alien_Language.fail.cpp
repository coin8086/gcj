#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> parse_into_tokens(const string & word) {
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
  return tokens;
}

//typedef void (* Callback)(const string & word);
template<class Callback>
void permute(const vector<string> & pattern, string & word, Callback & f) {
  if (pattern.size() == word.size())
    f(word);
  else {
    const string & cand = pattern[word.size()];
    for (int i = 0; i < cand.size(); i++) {
      word.push_back(cand[i]);
      permute(pattern, word, f);
      //word.pop_back();
      word.resize(word.size() - 1);
    }
  }
}

class Counter {
public:
  Counter(const vector<string> & dict) : _dict(dict), _count(0) {}

  void operator()(const string & word) {
    if (binary_search(_dict.begin(), _dict.end(), word))
      _count++;
  }

  int count() { return _count; }

private:
  const vector<string> & _dict;
  int _count;
};

inline int resolve(const vector<string> & dict, const vector<string> & pattern) {
  Counter counter(dict);
  string word;
  permute(pattern, word, counter);
  return counter.count();
}

int main() {
  int L, D, N;
  cin >> L >> D >> N;
  vector<string> dict;
  dict.reserve(D);
  string word;
  int i;
  for (i = 0; i < D; i++) {
    cin >> word;
    dict.push_back(word);
  }
  sort(dict.begin(), dict.end());
  for (i = 0; i < N; i++) {
    cin >> word;
    vector<string> pattern = parse_into_tokens(word);
    int k = resolve(dict, pattern);
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << k;
  }
  return 0;
}

