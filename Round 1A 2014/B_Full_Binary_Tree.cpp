#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

typedef vector<vector<int> > Graph;

inline vector<int> get_children(const Graph & g, int node, int parent) {
  vector<int> children = g[node];
  if (parent)
    children.erase(find(children.begin(), children.end(), parent));
  return children;
}

//Tell how many nodes to remove to delete a subtree rooted at node.
int del(const Graph & g, int node, int parent) {
  assert(node > 0 && parent > 0);
  int size = g[node].size() - 1;
  if (!size)
    return 1;
  vector<int> children = get_children(g, node, parent);
  assert(size == children.size());
  int r = 1;
  for (int i = 0; i < children.size(); i++) {
    r += del(g, children[i], node);
  }
  return r;
}

bool cmp(const pair<int, int> & a, const pair<int, int> & b) {
  return a.second < b.second;
}

//Select two children so that there is minimum number of nodes to remove.
inline int select(const vector<pair<int, int> > & trees) {
  int m = INT_MAX;
  //For each pair of children i, j, suppose we keep them and remove others.
  //We then calcualte the number of nodes to remove. Among all candidate pairs,
  //we choose the minimum.
  for (int i = 0; i < trees.size() - 1; i++) {
    for (int j = i + 1; j < trees.size(); j++) {
      int v = 0;
      for (int k = 0; k < trees.size(); k++) {
        if (k == i || k == j)
          v += trees[k].first;
        else
          v += trees[k].second;
      }
      if (m > v)
        m = v;
    }
  }
  return m;
}

//Tell how many nodes to remove to make a subtree rooted at node become a full binary tree.
int trim(const Graph & g, int node, int parent = 0) {
  assert(node > 0);
  int size = g[node].size();
  if (parent)
    size--;
  if (!size)
    return 0;
  vector<int> children = get_children(g, node, parent);
  assert(size == children.size());
  if (size == 1)
    return del(g, children[0], node);
  if (size == 2)
    return trim(g, children[0], node) + trim(g, children[1], node);
  //For each child, we compute the trim value and del value so that we can determine
  //the minimum nodes to remove.
  vector<pair<int, int> > trees;
  for (int i = 0; i < children.size(); i++) {
    trees.push_back(make_pair(trim(g, children[i], node), del(g, children[i], node)));
  }
  return select(trees);
}

inline int resolve(const Graph & g) {
  int m = INT_MAX;
  //Try each node as root, then get the minimum.
  for (int i = 1; i < g.size(); i++) {
    int r = trim(g, i);
    if (r < m) {
      m = r;
      if (!m)
        break;
    }
  }
  return m;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N;
    Graph g(N + 1);
    for (int i = 0; i < N - 1; i++) {
      int a, b;
      cin >> a >> b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    cout << "Case #" << t + 1 << ": " << resolve(g) << endl;
  }
  return 0;
}

