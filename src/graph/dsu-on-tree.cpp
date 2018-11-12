// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ DSU on Tree template type HLD
// @snippet dsu_on_tree
// @alias   temp_dsu_on_tree

// HLD style
const int N = 1e5;

int dep[N];
int sz[N];
void dfs0(int i, int p = -1, int d = 0) {
  dep[i] = d;
  sz[i] = 1;
  for(int j : g[i])
    if(j != p) {
      dfs0(j, i, d + 1);
      sz[i] += sz[j];
    }
}

int value[N];
void add(int i, int x, int p, int heavy) {
  value[i] += x;
  for(int j : g[i])
    if(j != p && j != heavy) {
      add(j, x, i, heavy);
    }
}

void dfs1(int i, int p = -1, int keep = 1) {
  int heavy = -1;
  for(int j : g[i])
    if(j != p)
      if(heavy == -1 || sz[heavy] < sz[j]) heavy = j;
  for(int j : g[i])
    if(j != p && j != heavy) dfs1(j, i);
  if(heavy != -1) dfs1(heavy, i, 1);
  add(i, 1, p, heavy);
  // do something
  //
  if(!keep) add(i, -1, p, -1);
}
