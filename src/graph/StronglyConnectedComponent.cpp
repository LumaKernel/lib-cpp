// @import header
// @@
// @name Strongly Connected Component
// @title 強連結成分分解
// @snippet     scc
// SCC(UnWeightedGraph)
// must build(renew)
/// --- Strongly Connected Component {{{ ///

struct SCC {
  int n;
  vector< vector<int> > g, rev;
  vector<int> topo;
  vector<int> used;
  vector<int> comp;
  SCC(int n): n(n), g(n), rev(n) {}
  SCC(UnWeightedGraph ig): n(ig.size()), g(n), rev(n) {
    for(int from = 0; from < n; from++)
      for(int to : ig[from]) addEdge(from, to);
  }
  void addEdge(int a, int b) {
    g[a].emplace_back(b);
    rev[b].emplace_back(a);
  }
  int operator[](int i) {
    return comp[i];
  }
  void build(vector< vector<int> > &renew) {
    used.resize(n, 0);
    comp.resize(n, -1);
    for(int i = 0; i < n; i++) if(!used[i]) dfs1(i);
    reverse(begin(topo), end(topo));
    int k = 0;
    for(int i : topo) if(comp[i] == -1) dfs2(i, k++);

    renew.resize(k);
    set<pair<int, int>> connect;
    for(int i = 0; i < n; i++) {
      for(int j : g[i]) {
        int x = comp[i], y = comp[j];
        if(x == y) continue;
        if(connect.count(make_pair(x, y))) continue;
        connect.emplace(x, y);
        renew[x].emplace_back(y);
      }
    }
  }
private:
  void dfs1(int i) {
    if(used[i]) return;
    used[i] = 1;
    for(int j : g[i]) dfs1(j);
    topo.emplace_back(i);
  }
  void dfs2(int i, int num) {
    if(comp[i] != -1) return;
    comp[i] = num;
    for(int j : rev[i]) dfs2(j, num);
  }
};

/// ---}}} ///
