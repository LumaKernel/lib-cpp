// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ MoTreeVertex Library
// @snippet mo_tree_vertex

// MoTreeVertex(N, JUST Q, double k)
// favored : k = 2
// 1: addEdge
// 2: prebuild
// 3: insert
// 4: build
/// --- MoTreeVertex Library {{{ ///

struct MoTreeVertex {
  const int n, logn, m;
  const int width;
  int q = 0;
  vector< vector< int > > par;
  vector< int > dep;
  vector< int > in, vs;
  vector< vector< int > > g;
  vector< int8_t > flag;
  vector< int > le, ri, lcas, order;
  int nl = 0, nr = 0;
  int log(int x) {
    int h = 1;
    while((1 << h) < x) h++;
    return h;
  }
  MoTreeVertex(int n, int q, double k = 1)
      : n(n),
        logn(log(n)),
        m(2 * n - 1),
        width(int(k* m / sqrt(q) + 1.0)),
        q(q),
        par(logn, vector< int >(n, -1)),
        dep(n),
        in(n),
        g(n),
        flag(n),
        le(q),
        ri(q),
        lcas(q),
        order(q) {
    vs.reserve(m);
  }
  inline void addEdge(int u, int v) {
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  inline void prebuild() {
    dfs(0, -1, 0);
    for(int k = 1; k < logn; k++)
      for(int i = 0; i < n; i++) {
        int p = par[k - 1][i];
        if(p == -1) continue;
        par[k][i] = par[k - 1][p];
      }
  }
  void dfs(int i, int p, int d) {
    dep[i] = d;
    par[0][i] = p;
    in[i] = vs.size();
    vs.emplace_back(i);
    for(int j : g[i])
      if(j != p) {
        dfs(j, i, d + 1);
        vs.emplace_back(j);
      }
  }
  inline int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int k = logn - 1; k >= 0; k--) {
      int nv = par[k][v];
      if(nv != -1 && dep[nv] >= dep[u]) v = nv;
    }
    if(u == v) return u;
    for(int k = logn - 1; k >= 0; k--) {
      int nu = par[k][u], nv = par[k][v];
      if(nu != nv) u = nu, v = nv;
    }
    return par[0][u];
  }
  inline void insert(int u, int v) {
    if(in[u] > in[v]) swap(u, v);
    le[q] = in[u] + 1;
    ri[q] = in[v] + 1;
    lcas[q] = lca(u, v);
    order[q] = q;
    q++;
  }
  inline void build() {
    sort(begin(order), begin(order) + q, [&](int a, int b) {
      const int ab = le[a] / width, bb = le[b] / width;
      return ab != bb ? ab < bb : ab & 1 ? ri[a] < ri[b] : ri[b] < ri[a];
    });
    nl = nr = le[order[0]];
    for(int i = 0; i < q; i++) {
      if(i > 0) rem(lcas[order[i - 1]]);
      const int id = order[i];
      while(nl > le[id]) flip(vs[--nl]);
      while(nr < ri[id]) flip(vs[nr++]);
      while(nl < le[id]) flip(vs[nl++]);
      while(nr > ri[id]) flip(vs[--nr]);
      add(lcas[id]);
      next(id);
    }
  }
  inline void flip(int i) {
    if(flag[i] ^= 1)
      add(i);
    else
      rem(i);
  }
  inline void next(int id);
  inline void add(int i);
  inline void rem(int i);
};

/// }}}--- ///

inline void MoTreeVertex::next(int id) {}
inline void MoTreeVertex::add(int i) {}
inline void MoTreeVertex::rem(int i) {}
