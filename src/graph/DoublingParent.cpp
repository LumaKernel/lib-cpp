// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     doublingparent
// @title ダブリング (for グラフ)
// @name Doubilng Parent Library
/// --- Doubilng Parent Library {{{ ///

// tree
struct DoublingParent {
  int n, logn;
  vector< vector< int > > &tree;
  vector< int > depth;         // 0-indexed
  vector< vector< int > > par; // for doubling
  DoublingParent(vector< vector< int > > &tree) : n(tree.size()), tree(tree) {
    calc();
  }

private:
  int logbin(int x) {
    int h = 0;
    x = x & 0xFFFF0000 ? (h += 16, x) & 0xFFFF0000 : x;
    x = x & 0xFF00FF00 ? (h += 8, x) & 0xFF00FF00 : x;
    x = x & 0xF0F0F0F0 ? (h += 4, x) & 0xF0F0F0F0 : x;
    x = x & 0xCCCCCCCC ? (h += 2, x) & 0xCCCCCCCC : x;
    x = x & 0xAAAAAAAA ? (h += 1, x) & 0xAAAAAAAA : x;
    return h;
  }
  void calc() {
    logn = logbin(n);
    if(logn == 0) logn++;

    depth.resize(n, 0);
    par.resize(n, vector< int >(logn, -1));
    dfs(0);

    for(int k = 1; k < logn; k++) {
      for(int i = 0; i < n; i++) {
        int p = par[i][k - 1];
        if(p == -1) {
          par[i][k] = -1;
          continue;
        }
        par[i][k] = par[p][k - 1];
      }
    }
  }

  void dfs(int i, int p = -1, int d = 0) {
    depth[i] = d;
    par[i][0] = p;
    for(int j : tree[i])
      if(j != p) {
        dfs(j, i, d + 1);
      }
  }

public:
  int LCA(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = logn - 1; k >= 0; k--) {
      int na = par[a][k];
      if(na == -1) continue;
      if(depth[na] < depth[b]) continue;
      a = na;
    }
    if(a == b) return a;
    for(int k = logn - 1; k >= 0; k--) {
      int na = par[a][k];
      int nb = par[b][k];
      if(na == nb) continue;
      a = na, b = nb;
    }
    return par[a][0];
  }
};

/// }}}--- ///
