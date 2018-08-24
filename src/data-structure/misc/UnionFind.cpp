// @import header
// @@
// @snippet     unionfind
// @alias       uf
// @name Union Find Library
/// --- Union Find Library {{{ ///

struct UF {
  int n;
  vector<int> par, rank;
  UF(int n): n(n), par(n, -1), rank(n, 0) {}
  int find(int x) {
    return par[x] < 0 ? x : par[x] = find(par[x]);
  }
  int size(int x) {
    return -par[find(x)];
  }
  bool same(int a, int b) {
    return find(a) == find(b);
  }
  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(rank[a] > rank[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    if(rank[a] == rank[b]) rank[b]++;
  }
};

/// }}}--- ///

