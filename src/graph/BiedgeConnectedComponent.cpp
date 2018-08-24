// @import header
// @@
// @name Biedge Component Decomposition Libary
// @title 二辺連結成分分解
// @snippet     biedge
// @alias       bridge twoedge nihen
// !! require Lowlink !!
// NOTE : 二辺連結成分分解
// Biedge(built-lowlink)
// Biedge(graph)
// NOTE : Biedge.tree, .comp
/// --- Biedge Component Decomposition Libary {{{ ///

struct Biedge {
  Lowlink lowlink;
  vector<int> comp;
  vector< vector<int> > tree;

  Biedge(Lowlink lowlink): lowlink(lowlink){ decomposite(); }
  Biedge(UnWeightedGraph g): lowlink(g){
    lowlink.build();
    decomposite();
  }

  vector<int> used;

private:
  void decomposite() {
    int n = lowlink.n;

    tree.resize(n);
    used.resize(n, 0);
    comp.resize(n, -1);

    int gid = 0;
    for(int i = 0; i < n; i++) if(!used[i]) dfs(gid++, i, -1);

    tree.resize(gid);
  }

  void dfs(int gid, int i, int p) {
    used[i] = 1;
    comp[i] = gid;
    for(auto edge : lowlink.g[i]) {
      int j = edge.to;
      int idx = edge.idx;
      if(j == p) continue;
      if(lowlink.isBridge[idx]) {
        if(used[j]) {
          tree[gid].emplace_back(comp[j]);
          tree[comp[j]].emplace_back(gid);
        }
      }else if(!used[j]){
        dfs(gid, j, i);
      }
    }
  }
};

/// }}}--- ///

