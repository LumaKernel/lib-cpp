// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     bipartiteMatching
// @alias       flowBipariteMatching
// @name BipartiteMatching Library
/// --- BipartiteMatching Library {{{ ///
struct BipartiteMatching {
  int n;
  vector< vector< int > > graph;

  BipartiteMatching(int n) : n(n), graph(n) {}
  void addEdge(int a, int b) {
    graph[a].emplace_back(b);
    graph[b].emplace_back(a);
  }

  vector< int > used;
  vector< int > match;

  // max flow
  int solve() {
    match = vector< int >(n, -1);
    int flow = 0;
    for(int i = 0; i < n; i++) {
      if(match[i] < 0) {            ///
        used = vector< int >(n, 0); ///
        if(dfs(i)) flow++;
      }
    }
    return flow;
  }

private:
  bool dfs(int v) {
    if(used[v]) return false; ///
    used[v] = 1;
    for(int u : graph[v])
      if(match[u] < 0 || dfs(match[u])) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    return false;
  }
};
/// }}}--- ///
