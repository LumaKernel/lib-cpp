// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ HL-Decomposition
// @snippet hld
// @alias heavy_light_decomp

// HLD( <tree> , root )
// === build() ===
// .fold(hi, lo, func, inclusive)
//   where func(l, r) proceeds with [l, r)
// .getIn(a) : In-time of Euler Tour
// .getOut(a) : out-time of Euler Tour
// === --- ===
// .getSubtreeSize(a)
// .getDepth(a) : 0-indexed
// .steps(a, b)
// === --- ===
// for subtree : [ getIn(a)          , getOut(a) )
// (exclusive) : [ getInExclusive(a) , getOut(a) )
// HL-Decomposition {{{
#include <functional>
#include <vector>
// based on Euler Tour
struct HLD {
public:
  using size_type = size_t;
  using graph_type = vector< vector< int > >;

private:
  size_type n;
  vector< size_type > head;
  vector< size_type > sub;
  vector< size_type > dep;
  vector< int > par;
  vector< size_type > vid;
  size_type root;
  graph_type tree;

public:
  HLD() : n(0) {}
  HLD(size_type n, size_type root = 0)
      : n(n), head(n), sub(n), dep(n), par(n), vid(n), tree(n) {
    setRoot(root);
  }
  HLD(const graph_type &tree, size_type root) : HLD(tree.size(), root) {
    this->tree = tree;
  }

  void setRoot(size_type root) {
    assert(root < n);
    this->root = root;
  }

private:
  bool built = 0;

public:
  void build() {
    assert(!built && n);
    built = 1;
    head[root] = root;
    dfs0();
    dfs1();
  }

private:
  void dfs0() {
    vector< int > used(n);
    stack< tuple< size_type, int, size_type > > stk;
    stk.emplace(root, -1, 0);
    while(stk.size()) {
      size_type i, d;
      int p;
      tie(i, p, d) = stk.top();
      if(!used[i]) {
        used[i] = 1;
        par[i] = p;
        dep[i] = d;
        for(auto &j : tree[i])
          if(j != p) {
            stk.emplace(j, i, d + 1);
          }
      } else {
        stk.pop();
        sub[i] = 1;
        for(auto &j : tree[i])
          if(j != p) {
            if(sub[j] > sub[tree[i].back()]) {
              swap(tree[i].back(), j);
            }
            sub[i] += sub[j];
          }
      }
    }
  }
  void dfs1() {
    vector< int > used(n);
    stack< tuple< size_type, int > > stk;
    stk.emplace(root, -1);
    size_type id = 0;
    while(stk.size()) {
      size_type i;
      int p;
      tie(i, p) = stk.top(), stk.pop();
      vid[i] = id++;
      for(auto j : tree[i])
        if(j != p) {
          head[j] = j == tree[i].back() ? head[i] : j;
          stk.emplace(j, i);
        }
    }
  }

public:
  size_type getIn(size_type i) {
    assert(built);
    assert(i < n);
    return vid[i];
  }
  size_type getInExclusive(size_type i) { return getIn(i) + 1; }
  size_type getOut(size_type i) {
    assert(built);
    assert(i < n);
    return vid[i] + sub[i];
  }
  size_type getOutExclusive(size_type i) { return getOut(i) - 1; }
  size_type getSubtreeSize(size_type i) { return sub.at(i); }
  size_type getDepth(size_type i) { return dep.at(i); }
  size_type steps(size_type a, size_type b) {
    assert(a < n && b < n);
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
  }
  void addEdge(size_type a, size_type b) {
    assert(built);
    assert(a < n && b < n);
    tree[a].emplace_back(b);
    tree[b].emplace_back(a);
  }
  size_type lca(size_type a, size_type b) {
    assert(built);
    assert(a < n && b < n);
    while(1) {
      if(vid[a] > vid[b]) swap(a, b);
      if(head[a] == head[b]) return a;
      b = par[head[b]];
    }
  }
  void fold(size_type hi, int lo, function< void(int, int) > f, bool inclusive) {
    assert(built);
    assert(hi < n && 0 <= lo && lo < (int) n);
    while(lo != -1 && dep[lo] >= dep[hi]) {
      size_type nex = max(vid[head[lo]], vid[hi]);
      f(nex + (nex == vid[hi] && !inclusive), vid[lo] + 1);
      lo = par[head[lo]];
    }
  }
  size_type size() { return n; }
};
// }}}
