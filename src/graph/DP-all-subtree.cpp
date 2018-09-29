// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ all tree dp - type luma
// @snippet temp_all_subtree_dp
// @alias dp_all_subtree all_subtree_dp

const int N = 1e5;
vector< vector< int > > g(N);
using Value = int;
map< int, Value > dp[N];
Value dfs(int i, int p, int f) {
  if(dp[i].count(p)) return dp[i][p];
  int deg = g[i].size() - (p != -1);
  Value res = 0;
  if(f || p == -1) {
    // O(deg)
    // go only child
    for(int j : g[i])
      if(j != p) {
        res += dfs(j, i, f);
      }
  } else {
    // O(1)
    dfs(i, -1, f), dfs(p, i, f);
  }
  return dp[i][p] = res;
}

int n;
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  cin >> n;
  for(int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  dfs(0, -1, 1);
  for(int i = 0; i < n; i++) dfs(i, -1, 0);
  return 0;
}
