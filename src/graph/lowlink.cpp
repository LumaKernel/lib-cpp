// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Lowlink Library
// @title LowLink
// @snippet     lowlink
// Lowlink(UndirectedGraph)
// or use addEdge
// must build()
/// --- Lowlink Library {{{ ///

struct Lowlink {
  struct Edge {
    int to, idx;
  };
  int n;
  int edgeSize = 0;
  vector< vector< Edge > > g;
  vector< int > ord, low;

  vector< int > used;
  vector< int > isBridge, isArticulation;
  Lowlink(int n) : n(n), g(n), ord(n), low(n) {}
  Lowlink(vector< vector< int > > ig) : n(ig.size()), g(n), ord(n), low(n) {
    for(int from = 0; from < n; from++)
      for(int to : ig[from])
        if(from < to) addEdge(from, to);
  }

  void addEdge(int a, int b) {
    g[a].emplace_back((Edge){b, edgeSize});
    g[b].emplace_back((Edge){a, edgeSize});
    edgeSize++;
  }

  void build() {
    used.resize(n, 0);
    isBridge.resize(edgeSize, 0);
    isArticulation.resize(n, 0);

    int k = 0;
    dfs(0, -1, k);
  }

private:
  void dfs(int i, int p, int &k) {
    used[i] = 1;
    ord[i] = low[i] = k++;
    isArticulation[i] = 0;
    int DFSTreeDegree = 0;
    for(Edge edge : g[i]) {
      int j = edge.to;
      int idx = edge.idx;
      if(j == p) continue;
      if(!used[j]) {
        // on dfs-tree
        DFSTreeDegree++;
        dfs(j, i, k);
        low[i] = min(low[i], low[j]);
        isBridge[idx] = ord[i] < low[j];
        if(p != -1 && ord[i] <= low[j]) {
          isArticulation[i] = 1;
        }
      } else {
        low[i] = min(low[i], ord[j]);
      }
    }
    if(p == -1 && DFSTreeDegree > 1) {
      isArticulation[i] = 1;
    }
  }
};

/// }}}--- ///
