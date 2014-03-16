#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  int N = 0;
  string line;
  cin >> N;
  getline(cin, line); //skip trailing '\n'
  for (int i = 0; i < N; i++) {
    getline(cin, line);
    istringstream is(line);
    vector<string> words;
    string word;
    while (is >> word) {
      words.push_back(word);
    }
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ":";
    for (int j = words.size() - 1; j >= 0; j--) {
      cout << ' ' << words[j];
    }
  }
  return 0;
}

