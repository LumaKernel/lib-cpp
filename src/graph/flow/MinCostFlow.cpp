// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     mincostflow
// @name MinCostFlow

// MinCostFlow(size, inf)
// MinCostFlow(size, inf, int& s, int& t)
// addEdge(from, to, capacity, cost, undirected = false)
// === build(s, t, flow) ===
// O(FE log V)
// return mincost
// return -1 if impossible
/// --- MinCostFlow {{{ ///
#include <cassert>
#include <queue>
#include <tuple>
#include <vector>
// with Dijkstra with Potential
struct MinCostFlow {
  struct Edge {
    int to;
    ll cap, cost;
    size_t rev;
  };
  int n;
  vector< vector< Edge > > graph;
  vector< ll > h; // potential
  vector< ll > dist;
  vector< int > prevv, preve;
  ll inf;
  MinCostFlow(int n, ll inf)
      : n(n), graph(n), h(n), dist(n), prevv(n), preve(n), inf(inf) {}
  MinCostFlow(int n, ll inf, int &s, int &t) : MinCostFlow(n + 2, inf) {
    s = n, t = n + 1;
  }
  void addEdge(int a, int b, ll cap, ll cost, int undirected = 0) {
    assert(cost >= 0);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    graph[a].emplace_back((Edge){b, cap, cost, graph[b].size()});
    graph[b].emplace_back((Edge){a, undirected ? cap : 0, -cost, graph[a].size() - 1});
  }
  ll build(int s, int t, ll f) {
    h.assign(n, 0);
    ll res = 0;
    while(f > 0) {
      dist.assign(n, inf);
      dist[s] = 0;
      // Dijkstra with potential
      using P = pair< ll, int >;
      priority_queue< P, vector< P >, greater< P > > pq;
      pq.emplace(0, s);
      while(pq.size()) {
        ll d;
        int v;
        tie(d, v) = pq.top();
        pq.pop();
        if(dist[v] < d) continue;
        for(size_t i = 0; i < graph[v].size(); i++) {
          Edge &edge = graph[v][i];
          ll nd = dist[v] + edge.cost + h[v] - h[edge.to];
          if(edge.cap > 0 && dist[edge.to] > nd) {
            dist[edge.to] = nd;
            pq.emplace(nd, edge.to);
            prevv[edge.to] = v;
            preve[edge.to] = i;
          }
        }
      }
      //
      if(dist[t] == inf) return -1;
      for(int v = 0; v < n; v++) h[v] += dist[v];

      ll d = f;
      for(int v = t; v != s; v = prevv[v]) {
        d = min(d, graph[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for(int v = t; v != s; v = prevv[v]) {
        Edge &edge = graph[prevv[v]][preve[v]];
        edge.cap -= d;
        graph[v][edge.rev].cap += d;
      }
    }
    return res;
  }
};
/// }}}--- ///

// const int N = 100000;
// ll inf = 1e18;
// MinCostFlow ecas(N, inf);
