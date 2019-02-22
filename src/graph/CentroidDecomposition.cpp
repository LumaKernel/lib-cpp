// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Centroid Decomposition
// @snippet centroid_decomposition
// @alias jusinbunkai
// @alias decomp_centroid

// CentroidDecomposition( <tree> [, process_in [, process_out] ] )
// .setProcessIn (func)
// .setProcessOut(func)
// === .build() ===
// .par[i] // parent of i in reformed graph whose depth is O(log N)
/// --- Centroid Decomposition {{{ ///
#include <functional>
#include <cassert>
#include <vector>
struct CentroidDecomposition {
  using graph_type = vector< vector< int > >;
  using process_type = function< void(int centroid, const vector< bool > &) >;
  size_t n;
  graph_type tree;
  process_type process_in, process_out;
  CentroidDecomposition() : n(0) {}
  CentroidDecomposition(
      size_t n,
      const process_type process_in = [&](int, const vector< bool > &) -> void {},
      const process_type process_out = [&](int, const vector< bool > &) -> void {})
      : n(n), process_in(process_in), process_out(process_out) {}
  CentroidDecomposition(const graph_type &tree) : CentroidDecomposition(tree.size()) {}
  void setProcessIn(const process_type &process_in) { this->process_in = process_in; };
  void setProcessOut(const process_type &process_out) { this->process_out = process_out; }
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
  vector< int > par;
  void build() {
    assert(!built);
    built = 1;
    processing.resize(n);
    sub.resize(n);
    par.resize(n);
    decomposite(0, -1);
  }

private:
  void decomposite(int start, int p) {
    dfs(start, -1);
    int centroid = search_centroid(start, -1, sub[start] / 2);
    par[centroid] = p;
    process_in(centroid, processing);
    processing[centroid] = 1;
    for(auto &j : tree[centroid])
      if(!processing[j]) decomposite(j, centroid);
    processing[centroid] = 0;
    process_out(centroid, processing);
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

// void processIn(int c, const vector< bool > &u) {}
// void processOut(int c, const vector< bool > &u) {}

