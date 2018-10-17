// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     dinic
// @abbr        Dinic(int size, ll flow = 1e18)
// @ Dinic Library
/// --- Dinic Library {{{ ///
// solve max flow

struct Dinic {
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
  Dinic(int n, ll inf = 1e18) : n(n), g(n), inf(inf) {}

  void addEdge(int a, int b, ll cap, int i = -1, bool undirected = false) {
    if(i == -1) i = edges.size();
    edges.resize(max(i + 1, (int) edges.size()));
    edges[i] = (Edge){a, b, cap, undirected ? cap : 0};
    g[a].emplace_back(i);
    g[b].emplace_back(i);
  }

  ll solve(int s, int t) {
    vector< int > level(n);
    ll flow = 0;
    while(bfs(s, level), level[t] > 0) {
      ll newflow = dfs(s, t, inf, level);
      if(newflow == 0) break;
      flow += newflow;
      if(flow >= inf) return inf;
    }
    return flow;
  }

private:
  void bfs(int s, vector< int >& level) {
    fill(begin(level), end(level), -1);
    queue< int > q;
    q.emplace(s);
    level[s] = 0;
    while(q.size()) {
      int i = q.front();
      q.pop();
      for(int idx : g[i]) {
        Edge edge = edges[idx];
        if(level[edge.To(i)] == -1 && edge.Cap(i) > 0) {
          level[edge.To(i)] = level[i] + 1;
          q.emplace(edge.To(i));
        }
      }
    }
  }

  ll dfs(int i, int t, ll flow, vector< int > const& level) {
    if(i == t) return flow;
    for(int idx : g[i]) {
      Edge& edge = edges[idx];
      if(edge.Cap(i) > 0 && level[edge.To(i)] > level[i]) {
        ll newflow = dfs(edge.To(i), t, min(flow, edge.Cap(i)), level);
        if(newflow == 0) continue;
        edge.Cap(i) -= newflow;
        edge.Rev(i) += newflow;
        return newflow;
      }
    }
    return 0;
  }
};

/// }}}--- ///
