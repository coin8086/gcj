#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Wire : public pair<int, int> {
public:
  Wire(int a, int b) : pair<int, int>(a, b) {}

  bool operator<(const Wire & rhs) const {
    return this->first < rhs.first;
  }
};

int resolve(vector<Wire> & wires) {
  int count = 0;
  sort(wires.begin(), wires.end());
  for (int i = 0; i < wires.size(); i++) {
    int b = wires[i].second;
    for (int j = i + 1; j < wires.size(); j++) {
      if (wires[j].second < b)
        count++;
    }
  }
  return count;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int N;
    cin >> N;
    vector<Wire> wires;
    for (int j = 0; j < N; j++) {
      int a, b;
      cin >> a >> b;
      wires.push_back(Wire(a, b));
    }
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << resolve(wires);
  }
  return 0;
}

