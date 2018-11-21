// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @title HL分解
// @snippet     hldecomp
// @name HL-Decomposition Library
// query(hi, lo, func, inclusive?)
// hld[i] : index on sequence
// WARN : build after adding edges!
/// --- HL-Decomposition Library {{{ ///

struct HLD {
  int n;
  vector< int > head;
  vector< int > sz;
  vector< int > dep;
  vector< int > par;
  vector< int > vid;
  int id = 0;
  vector< vector< int > > g; // tree
  HLD(int n) : n(n), head(n), sz(n), dep(n), par(n), vid(n), g(n) {}
  HLD(vector< vector< int > > g, int root = 0) : HLD(g.size()) {
    this->g = g;
    build(root);
  }
  int operator[](int i) { return vid[i]; }
  void addEdge(int a, int b) {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  void build(int root = 0) {
    head[root] = root;
    dfs0(root, -1, 0);
    dfs1(root, -1);
  }
  int lca(int a, int b) {
    while(1) {
      if(vid[a] > vid[b]) swap(a, b);
      if(head[a] == head[b]) return a;
      b = par[head[b]];
    }
  }
  void query(int hi, int lo, function< void(int, int) > f, bool inclusive = true) {
    while(lo != -1 && dep[lo] >= dep[hi]) {
      int nex = max(vid[head[lo]], vid[hi]);
      f(nex + (nex == vid[hi] && !inclusive), vid[lo] + 1);
      lo = par[head[lo]];
    }
  }

private:
  void dfs0(int i, int p, int d) {
    par[i] = p;
    sz[i] = 1;
    dep[i] = d;
    for(int &j : g[i])
      if(j != p) {
        dfs0(j, i, d + 1);
        sz[i] += sz[j];
        if(sz[j] > sz[g[i][0]]) {
          swap(g[i][0], j);
        }
      }
  }
  void dfs1(int i, int p) {
    vid[i] = id++;
    for(int j : g[i])
      if(j != p) {
        head[j] = j == g[i][0] ? head[i] : j;
        dfs1(j, i);
      }
  }
};

/// }}}--- ///
