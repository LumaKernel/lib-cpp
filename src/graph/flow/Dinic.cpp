// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     dinic
// @ Max Flow with Dinic Library

// constructor(n, inf?) // be careful !
// addEdge(from, to, capacity, isDirected? = false) returns edgeID
// === build(s, t) - returns max flow (or inf) ===
// === restoreMinCut(s) ===
// .isCut[edgeID]
// === --- ===
// inf * 2 < LL_MAX
/// --- Max Flow with Dinic Library {{{ ///

struct Dinic {
  struct Edge {
    int from, to;
    ll cap, rev;
    int To(int i) const { return from == i ? to : from; }
    ll& Cap(int i) { return from == i ? cap : rev; }
    ll& Rev(int i) { return from == i ? rev : cap; }
  };

  int n;
  vector< Edge > edges;
  vector< vector< int > > g;
  ll inf;
  Dinic(int n, ll inf = 1e18) : n(n), g(n), inf(inf) {}
  int addEdge(int a, int b, ll cap, bool undirected = false) {
    edges.emplace_back((Edge){a, b, cap, undirected ? cap : 0});
    g[a].emplace_back(edges.size() - 1);
    g[b].emplace_back(edges.size() - 1);
    return edges.size() - 1;
  }
  ll build(int s, int t) {
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
  vector< int > isCut;
  void restoreMinCut(int s) {
    isCut = vector< int >(edges.size());
    // bfs
    vector< int > used(n);
    queue< int > q;
    q.emplace(s);
    used[s] = 1;
    while(q.size()) {
      int i = q.front();
      q.pop();
      for(int idx : g[i]) {
        Edge& edge = edges[idx];
        if(!used[edge.To(i)] && edge.Cap(i) > 0) {
          q.emplace(edge.To(i));
          used[edge.To(i)] = 1;
        }
      }
    }
    for(size_t i = 0; i < edges.size(); i++) {
      if(used[edges[i].from] != used[edges[i].to]) isCut[i] = 1;
    }
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

const int N = 2e6;
const ll inf = 1e18;
Dinic flow(N, inf);
