#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> Item;
typedef vector<Item> ItemList;

bool item_cmp(const Item & a, const Item & b) {
  int r = a.second - b.second;
  if (!r)
    r = a.first - b.first;
  return r < 0;
}

int bisearch(const ItemList & P, int s, int e, int t) {
  if (s >= e)
    return -1;
  int m = (s + e) / 2;
  if (P[m].second == t)
    return m;
  if (P[m].second < t)
    return bisearch(P, m + 1, e, t);
  return bisearch(P, s, m, t);
}

void resolve(int C, ItemList & P, int & p1, int & p2)
{
  sort(P.begin(), P.end(), item_cmp);
  for (int i = 0; i < P.size(); i++) {
    int target = C - P[i].second;
    assert(target > 0);
    int p = bisearch(P, i + 1, P.size(), target);
    if (p >= 0) {
      p1 = P[i].first;
      p2 = P[p].first;
      if (p1 > p2) {
        int temp = p1;
        p1 = p2;
        p2 = temp;
      }
      return;
    }
  }
  assert(0 && "not here");
}

int main() {
  int N = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int C, I;
    cin >> C >> I;
    ItemList P;
    P.reserve(I);
    for (int j = 0; j < I; j++) {
      int p;
      cin >> p;
      P.push_back(make_pair(j + 1, p));
    }
    int p1, p2;
    resolve(C, P, p1, p2);
    if (i)
      cout << endl;
    cout << "Case #" << i + 1 << ": " << p1 << ' ' << p2;
  }
  return 0;
}

