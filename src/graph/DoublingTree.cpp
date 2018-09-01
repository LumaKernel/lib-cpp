// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet doubling_tree
// @name Doubilng Tree Library

// DoublingTree ( <graph> , initial? )
// set (i, val) or assign ( <data> )
// WARN : build() !!!
// lca (a, b)
// query(hi, a, hi_inclusive?)
/// --- Doubilng Tree Library {{{ ///

template < class Monoid >
struct DoublingTree {
  using T = typename Monoid::T;
  int n, logn;
  vector< vector< int > > tree;
  vector< int > depth; // 0-indexed
  // [logn][n]
  vector< vector< int > > par;
  vector< vector< T > > dat;
  int log(int n) {
    int h = 1;
    while((1 << h) < n) h++;
    return h;
  }
  DoublingTree(int n, const T &initial = Monoid::identity())
      : n(n), logn(log(n)), tree(n), dat(logn, vector< T >(n, initial)) {}
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  DoublingTree(InputIter first, InputIter last,
               const T &initial = Monoid::identity())
      : DoublingTree(distance(first, last), initial) {
    copy(first, last, begin(tree));
  }
  DoublingTree(const vector< vector< int > > &tree,
               const T &initial = Monoid::identity())
      : DoublingTree(begin(tree), end(tree), initial) {}
  void set(int i, const T &val) { dat[0][i] = val; }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  void assign(InputIter first, InputIter last) {
    assert(distance(first, last) <= n);
    copy(first, last, begin(dat[0]));
  }
  void build() {
    depth.resize(n);
    par.resize(logn, vector< int >(n));
    dfs(0);
    for(int k = 1; k < logn; k++) {
      for(int i = 0; i < n; i++) {
        int p = par[k - 1][i];
        if(p == -1) {
          par[k][i] = -1;
          continue;
        }
        dat[k][i] = Monoid::op(dat[k - 1][p], dat[k - 1][i]);
        par[k][i] = par[k - 1][p];
      }
    }
  }

private:
  void dfs(int i, int p = -1, int d = 0) {
    depth[i] = d;
    par[0][i] = p;
    for(int j : tree[i])
      if(j != p) {
        dfs(j, i, d + 1);
      }
  }

public:
  int lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = logn - 1; k >= 0; k--) {
      int na = par[k][a];
      if(na == -1 || depth[na] < depth[b]) continue;
      a = na;
    }
    if(a == b) return a;
    for(int k = logn - 1; k >= 0; k--) {
      int na = par[k][a];
      int nb = par[k][b];
      if(na == nb) continue;
      a = na, b = nb;
    }
    return par[0][a];
  }
  T query(int hi, int a, bool inclusive = true) {
    T res = Monoid::identity();
    for(int k = logn - 1; k >= 0; k--) {
      int na = par[k][a];
      if(na == -1 || depth[na] < depth[hi]) continue;
      res = Monoid::op(dat[k][a], res);
      a = na;
    }
    if(inclusive) res = Monoid::op(dat[0][hi], res);
    return res;
  }
};

/// }}}--- ///

/// --- Monoid examples {{{ ///

struct Nothing {
  using T = char;
  using M = char;
  static constexpr T op(const T &, const T &) { return 0; }
  static constexpr T identity() { return 0; }
  template < class X >
  static constexpr X actInto(const M &, ll, ll, const X &x) {
    return x;
  }
};

struct RangeMin {
  using T = ll;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return numeric_limits< T >::max(); }
};

struct RangeMax {
  using T = ll;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return numeric_limits< T >::min(); }
};

struct RangeSum {
  using T = ll;
  static T op(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return 0; }
};

/// }}}--- ///

DoublingTree< RangeSum > eca(N);
