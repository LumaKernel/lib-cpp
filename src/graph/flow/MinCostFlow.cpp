// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     mincostflow
// @name MinCostFlow Library
/// --- MinCostFlow Library {{{ ///
struct MinCostFlow {
  struct Edge {
    int to;
    ll cap, cost;
    size_t rev;
  };
  int n;
  vector< vector< Edge > > graph;
  vector< ll > dist;
  vector< int > prevv, previ;
  ll inf;
  MinCostFlow(int n, ll inf)
      : n(n), graph(n), dist(n), prevv(n), previ(n), inf(inf) {}
  void addEdge(int a, int b, ll cap, ll cost, int undirected = 0) {
    graph[a].emplace_back((Edge){b, cap, cost, graph[b].size()});
    graph[b].emplace_back(
        (Edge){a, undirected ? cap : 0, -cost, graph[a].size() - 1});
  }
  ll solve(int s, int t, ll f) {
    ll res = 0;
    while(f > 0) {
      fill(begin(dist), end(dist), inf);
      dist[s] = 0;
      bool update = 1;
      // Bellman-Ford
      while(update) {
        update = 0;
        for(int v = 0; v < n; v++) {
          if(dist[v] == inf) continue;
          for(size_t i = 0; i < graph[v].size(); i++) {
            Edge &edge = graph[v][i];
            if(edge.cap > 0 && dist[edge.to] > dist[v] + edge.cost) {
              dist[edge.to] = dist[v] + edge.cost;
              prevv[edge.to] = v;
              previ[edge.to] = i;
              update = 1;
            }
          }
        }
      }
      //
      if(dist[t] == inf) return -1;
      ll d = f;
      for(int v = t; v != s; v = prevv[v]) {
        d = min(d, graph[prevv[v]][previ[v]].cap);
      }
      f -= d;
      res += d * dist[t];
      for(int v = t; v != s; v = prevv[v]) {
        Edge &edge = graph[prevv[v]][previ[v]];
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
