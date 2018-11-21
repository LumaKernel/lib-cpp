// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     mstarborescence
// @name MSTArborescence Library
// @title 最小全域有向部分木
// require SCC Library!
// int MSTArborescence(WeightedDirectedGraph, int root)
/// --- MSTArborescence Library {{{ ///

ll MSTArborescence(vector< vector< pair< int, int > > > &graph, int start, ll sum = 0) {
  int n = graph.size();

  vector< int > rev(n, -1);
  vector< ll > weight(n, INF);
  for(int idx = 0; i < n; i++) {
    for(auto &e : graph[idx]) {
      if(se(e) < weight[fi(e)]) {
        weight[fi(e)] = se(e);
        rev[fi(e)] = idx;
      }
    }
  }

  SCC scc(n);
  for(int i = 0; i < n; i++) {
    if(start == i) continue;
    scc.addEdge(rev[i], i);
    sum += weight[i];
  }
  vector< vector< int > > renew;
  scc.decomposite(renew);
  if(renew.size() == n) return sum;
  vector< vector< pair< int, int > > > fixed(renew.size());
  for(int i = 0; i < n; i++) {
    for(P &e : graph[i]) {
      if(scc[i] == scc[fi(e)]) continue;
      fixed[scc[i]].emplace_back(scc[fi(e)], se(e) - weight[fi(e)]);
    }
  }
  return MSTArborescence(fixed, scc[start], sum);
}

/// }}}--- ///
