// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     bipartiteMatching
// @alias       flowBipariteMatching
// @name BipartiteMatching Library

// constructor(n)
// addEdge(a, b) // bipartite graph (undirected)
// === build() returns max flow ===
// O(VE) but very fast
// match[i] = some or -1
// === restoreMinVertexCover() ===
// O(V + E)
// vertexCovered[i] = 1 or 0
// === restoreMaxStableSet() ===
// alias of previous
// stable[i] = 1 or 0
// === restoreMinEdgeCover() ===
// O(V + E)
// isolated cannot be covered
// match2[i] = 1 or 0
/// --- BipartiteMatching Library {{{ ///
struct BipartiteMatching {
  int n;
  vector< vector< int > > g;
  BipartiteMatching(int n) : n(n), g(n) {}
  void addEdge(int a, int b) {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  vector< int > match;

private:
  vector< int > used;

public:
  int build() {
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
  vector< int > vertexCovered;
  vector< int > stable;
  inline void restoreMaxStableSet() { restoreMinVertexCover(); }
  void restoreMinVertexCover() {
    vertexCovered = vector< int >(n);
    stable = vector< int >(n, 1);
    vector< int > used0(n), used1(n);
    vector< int > color(n);
    vector< int > red(n);
    for(int i = 0; i < n; i++)
      if(!used0[i]) {
        // bfs
        queue< int > q0;
        queue< int > q1;
        q0.emplace(i);
        used0[i] = 1;
        while(q0.size()) {
          int j = q0.front();
          q0.pop();
          if(color[j] == 0 && match[j] == -1) q1.emplace(j);
          for(int k : g[j])
            if(!used0[k]) {
              used0[k] = 1;
              color[k] = color[j] ^ 1;
              q0.emplace(k);
            }
        }
        used1[i] = 1;
        while(q1.size()) {
          int j = q1.front();
          q1.pop();
          red[j] = 1;
          if(color[j] == 1) {
            if(match[j] != -1) q1.emplace(match[j]);
          } else {
            for(int k : g[j])
              if(!used1[k] && k != match[j]) {
                used1[k] = 1;
                q1.emplace(k);
              }
          }
        }
      }
    for(int i = 0; i < n; i++)
      if(color[i] ^ red[i] ^ 1) vertexCovered[i] = 1, stable[i] = 0;
  }
  vector< int > match2;
  void restoreMinEdgeCover() {
    match2 = match;
    for(int i = 0; i < n; i++)
      if(match2[i] == -1) {
        for(int j : g[i])
          if(match2[j] == -1) {
            match2[i] = j;
            match2[j] = i;
            break;
          }
      }
  }

private:
  bool dfs(int v) {
    if(used[v]) return false; ///
    used[v] = 1;
    for(int u : g[v])
      if(match[u] < 0 || dfs(match[u])) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    return false;
  }
};
/// }}}--- ///
