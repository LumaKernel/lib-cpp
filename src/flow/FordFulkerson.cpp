// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     maxflow
// @alias       ford
// @name Max Flow with FordFulkerson Library {{{ ///
/// --- Max Flow with FordFulkerson Library {{{ ///

// Ford-Fulkerson
// O(FV)
struct Ford {
  struct Edge {
    int from, to;
    ll cap, rev;
    int To(int i) { return from == i ? to : from; }
    ll& Cap(int i) { return from == i ? cap : rev; }
    ll& Rev(int i) { return from == i ? rev : cap; }
  };
  int n;
  vector< Edge > edges;
  vector< vector< int > > g;
  ll inf;
  Ford(int n, ll inf = 1e18) : n(n), g(n), inf(inf) {}

  void addEdge(int a, int b, ll cap, int i = -1, bool undirected = false) {
    if(i == -1) i = edges.size();
    edges.resize(max(i + 1, (int) edges.size()));
    edges[i] = (Edge){a, b, cap, undirected ? cap : 0};
    g[a].emplace_back(i);
    g[b].emplace_back(i);
  }

  ll solve(int s, int t) {
    ll flow = 0;
    while(1) {
      vector< int > used(n, 0);
      ll x = dfs(used, s, t, inf);
      if(x == 0) break;
      flow += x;
      if(flow >= inf) return inf;
    }
    return flow;
  }

private:
  ll dfs(vector< int >& used, int i, int t, ll x) {
    if(i == t) return x;
    used[i] = 1;
    for(int idx : g[i])
      if(!used[edges[idx].To(i)] && edges[idx].Cap(i) > 0) {
        Edge& edge = edges[idx];
        ll d = dfs(used, edge.To(i), t, min(x, edge.Cap(i)));
        if(d == 0) continue; ////
        edge.Cap(i) -= d;
        edge.Rev(i) += d;
        return d;
      }
    return 0;
  }
};

/// ---}}} ///

// const int N = 2e6;
// Ford flow(N, 1e18);
