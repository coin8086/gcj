#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Dir {
public:
  Dir(const string & n) : name(n) {}

  string name;
  vector<Dir> children;
};

unsigned int _mk(Dir & dir, const vector<string> & path, int i) {
  if (i == path.size())
    return 0;
  for (int j = 0; j < dir.children.size(); j++) {
    if (dir.children[j].name == path[i])
      return _mk(dir.children[j], path, i + 1);
  }
  dir.children.push_back(Dir(path[i]));
  return _mk(dir.children.back(), path, i + 1) + 1;
}

inline vector<string> split_path(const string & path) {
  vector<string> names;
  istringstream is(path);
  string name;
  while(getline(is, name, '/')) {
    if (!name.empty())
      names.push_back(name);
  }
  return names;
}

inline unsigned int mkdir(Dir & root, const string & path) {
  vector<string> names = split_path(path);
  int i = 0;
  unsigned int count = _mk(root, names, i);
  return count;
}

int main() {
  int T;
  cin >> T;
  string path;
  for (int i = 0; i < T; i++) {
    Dir root("/");
    int N, M;
    cin >> N >> M;
    for (int j = 0; j < N; j++) {
      cin >> path;
      mkdir(root, path);
    }
    unsigned int count = 0;
    for (int k = 0; k < M; k++) {
      cin >> path;
      count += mkdir(root, path);
    }
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << count;
  }
  return 0;
}

