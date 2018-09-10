// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ MoEx UF example

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
