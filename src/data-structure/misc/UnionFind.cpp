// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     unionfind
// @alias       uf
// @ Union Find

/// --- Union Find {{{ ///
#include <vector>
struct UF {
  int n;
  vector< int > par;
  UF(int n) : n(n), par(n, -1) {}
  int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
  int size(int x) { return -par[find(x)]; }
  bool same(int a, int b) { return find(a) == find(b); }
  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
  }
  void clear() { par.assign(n, -1); }
};
/// }}}--- ///
