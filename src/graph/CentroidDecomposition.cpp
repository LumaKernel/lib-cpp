// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Centroid Decomposition
// @snippet centroid_decomposition
// @alias jusinbunkai
// @alias decomp_centroid

// CentroidDecomposition( <tree> [, process ] )
// .setProcess(func)
// === .build() : returns root id ===
// info about reformed graph (depth is O(log N))
// .par[i] : int
// .child[i] : vector<int>
// .sz[i] : int : subtree size
/// --- Centroid Decomposition {{{ ///
#include <cassert>
#include <functional>
#include <vector>
struct CentroidDecomposition {
  using graph_type = vector< vector< int > >;
  using process_type = function< void(int centroid, const vector< bool > &) >;
  size_t n;
  graph_type tree;
  process_type process;
  CentroidDecomposition() : n(0) {}
  CentroidDecomposition(size_t n, const process_type process =
                                      [&](int, const vector< bool > &) -> void {})
      : n(n), tree(n), process(process) {}
  CentroidDecomposition(const graph_type &tree) : CentroidDecomposition(tree.size()) {
    this->tree = tree;
  }
  void setProcess(const process_type &process) { this->process = process; }
  void addEdge(size_t a, size_t b) {
    assert(a < n && b < n);
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

private:
  vector< bool > processing;
  vector< size_t > sub;
  bool built = 0;

public:
  int root = -1;
  vector< int > par;
  vector< int > sz;
  vector< vector< int > > child;
  int build() {
    assert(!built);
    built = 1;
    processing.resize(n);
    sub.resize(n);
    par.resize(n);
    sz.resize(n);
    child.resize(n);
    return root = decomposite(0, -1);
  }

private:
  int decomposite(int start, int p) {
    dfs(start, -1);
    int centroid = search_centroid(start, -1, sub[start] / 2);
    sz[centroid] = sub[start];
    par[centroid] = p;
    processing[centroid] = 1;
    for(auto &j : tree[centroid])
      if(!processing[j]) child[centroid].push_back(decomposite(j, centroid));
    processing[centroid] = 0;
    process(centroid, processing);
    return centroid;
  }
  void dfs(int i, int p) {
    sub[i] = 1;
    for(auto &j : tree[i])
      if(j != p && !processing[j]) {
        dfs(j, i);
        sub[i] += sub[j];
      }
  }
  int search_centroid(int i, int p, size_t mid) {
    for(auto &j : tree[i])
      if(j != p && !processing[j]) {
        if(sub[j] > mid) return search_centroid(j, i, mid);
      }
    return i;
  }
};
/// }}}--- ///

// do NOT go to vertex v when u[v] is true !!!!
// void process(int c, const vector< bool > &u) {}
