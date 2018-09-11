// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Mo with UF
// @snippet mo_ex_unionfind
// @alias mo_unionfind

/// --- Mo with Persistent Data Structure Library {{{ ///

struct MoEx {
  const int width;
  int q = 0;
  vector< int > le, ri, order;
  MoEx(int n, int q, double k = 1)
      : width(int(k* n / sqrt(q) + 1.0)), le(q), ri(q), order(q) {}
  inline void insert(int l, int r) {
    le[q] = l;
    ri[q] = r;
    order[q] = q;
    q++;
  }
  inline void build() {
    for(int i = 0; i < q; i++)
      if(ri[i] - le[i] < width) {
        init();
        for(int j = le[i]; j < ri[i]; j++) add(j);
        next(i);
      }
    sort(begin(order), begin(order) + q, [&](int a, int b) {
      const int ab = le[a] / width, bb = le[b] / width;
      return ab != bb ? ab < bb : ri[a] < ri[b];
    });
    int last = -1;
    int nr;
    for(int i = 0; i < q; i++) {
      int id = order[i];
      if(ri[id] - le[id] < width) continue;
      int b = le[id] / width;
      if(last != b) init(), nr = (b + 1) * width;
      last = b;
      while(nr < ri[id]) add(nr++);
      snapshot();
      for(int j = (b + 1) * width - 1; j >= le[id]; j--) add(j);
      next(id);
      rollback();
    }
  }
  inline void next(int id);
  inline void init();
  inline void snapshot();
  inline void rollback();
  inline void add(int i);
};

/// }}}--- ///

/// --- MoEx UF example {{{ ///

const int N = 1e5;

int par[N * 2];
int col = 1;
int used[N * 2];
int ans[N];
using P = pair< int, int >;
vector< P > history;

void reset(int i) {
  if(used[i] != col) used[i] = col, par[i] = -1;
}
int find(int a) {
  reset(a);
  return par[a] < 0 ? a : find(par[a]);
}
bool same(int a, int b) { return find(a) == find(b); }
void unite(int a, int b) {
  a = find(a), b = find(b);
  if(a == b) return;
  if(par[a] < par[b]) swap(a, b);
  history.emplace_back(b, par[b]);
  history.emplace_back(a, par[a]);
  par[b] += par[a];
  par[a] = b;
}

inline void MoEx::next(int id) { ans[id]; /* */ }
inline void MoEx::init() {
  //
  history.clear();
  col++;
}
inline void MoEx::snapshot() {
  oldNow = now;
  history.clear();
}
inline void MoEx::rollback() {
  now = oldNow;
  while(history.size()) {
    int i, x;
    tie(i, x) = history.back();
    par[i] = x;
    history.pop_back();
  }
}
inline void MoEx::add(int i) {
  unite(a[i] + N, b[i]);
  unite(a[i], b[i] + N);
  //
}

/// }}}--- ///
