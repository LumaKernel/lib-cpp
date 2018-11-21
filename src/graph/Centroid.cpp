// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Enumurate Centroid
// @snippet centroid_enum

vector<int> centroid;
int c[N];
void dfs(int i, int p) {
  c[i] = 1;
  int f = 1;
  for(int j : g[i]) if(j != p) {
    dfs(j, i);
    c[i] += c[j];
    f &= c[j] <= n / 2;
  }
  f &= (n - c[i]) <= n / 2;
  if(f) centroid.emplace_back(i);
}
