// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ HL-Decomposition
// @snippet hld
// @alias heavy_light_decomp

// HLD( <tree> , root )
// === .build() ===
// .fold(hi, lo, func, inclusive)
//   where func(l, r) proceeds with [l, r)
// .in(a) : in-time of Euler Tour : alias = .[a]
// .out(a) : out-time of Euler Tour
// .rev(a) : rev[in[a]] = a
// .head(a)
// === --- ===
// .subtreeSize(a)
// .depth(a) : 0-indexed
// .climb(a)
// .descendTo(from, to, steps)
// .steps(a, b)
// === --- ===
// for subtree : [ .in(a)          , .out(a) )
// (exclusive) : [ .inExclusive(a) , .out(a) )
// HL-Decomposition {{{
#include <cassert>
#include <functional>
#include <stack>
#include <vector>
// based on Euler Tour
struct HLD {
public:
  using size_type = size_t;
  using graph_type = vector< vector< int > >;

private:
  size_type n;
  vector< size_type > hd;
  vector< size_type > sub;
  vector< size_type > dep;
  vector< int > par;
  vector< size_type > vid;
  size_type root;
  graph_type tree;

public:
  HLD() : n(0) {}
  HLD(size_type n, size_type root = 0)
      : n(n), hd(n), sub(n), dep(n), par(n), vid(n), tree(n) {
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
  vector< size_type > vid_rev;

public:
  void build() {
    assert(!built && n);
    built = 1;

    vid_rev.resize(n);

    hd[root] = root;
    dfs0();
    dfs1();
    for(size_type i = 0; i < n; i++) vid_rev[vid[i]] = i;
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
          hd[j] = j == tree[i].back() ? hd[i] : j;
          stk.emplace(j, i);
        }
    }
  }

public:
  size_type operator[](size_type i) const { return in(i); }
  size_type in(size_type i) const {
    assert(built);
    assert(i < n);
    return vid[i];
  }
  size_type inExclusive(size_type i) const { return in(i) + 1; }
  size_type out(size_type i) const {
    assert(built);
    assert(i < n);
    return vid[i] + sub[i];
  }
  size_type outExclusive(size_type i) const { return out(i) - 1; }
  size_type head(size_type i) const {
    assert(built);
    return hd.at(i);
  }
  size_type rev(size_type i) const {
    assert(built);
    return vid_rev.at(i);
  }
  size_type subtreeSize(size_type i) const {
    assert(built);
    return sub.at(i);
  }
  size_type depth(size_type i) const {
    assert(built);
    return dep.at(i);
  }
  size_type steps(size_type a, size_type b) const {
    assert(built);
    assert(a < n && b < n);
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
  }
  size_type climb(size_type a, long long t) const {
    assert(built);
    assert(a < n && t >= 0);
    while(t) {
      long long c = std::min< long long >(vid[a] - vid[hd[a]], t);
      t -= c;
      a = vid[a] - c;
      if(t && a != root) {
        t--;
        a = par[a];
      }
      if(a == root) break;
    }
    return a;
  }
  size_type descendTo(size_type from, size_type to, long long steps) const {
    assert(built);
    assert(steps >= 0);
    assert(from < n && to < n);
    return climb(to, dep[to] - dep[from] - steps);
  }
  void addEdge(size_type a, size_type b) {
    assert(built);
    assert(a < n && b < n);
    tree[a].emplace_back(b);
    tree[b].emplace_back(a);
  }
  size_type lca(size_type a, size_type b) const {
    assert(built);
    assert(a < n && b < n);
    while(1) {
      if(vid[a] > vid[b]) swap(a, b);
      if(hd[a] == hd[b]) return a;
      b = par[hd[b]];
    }
  }
  void fold(size_type hi, int lo, function< void(int, int) > f, bool inclusive) const {
    assert(built);
    assert(hi < n && 0 <= lo && lo < (int) n);
    while(lo != -1 && dep[lo] >= dep[hi]) {
      size_type nex = max(vid[hd[lo]], vid[hi]);
      f(nex + (nex == vid[hi] && !inclusive), vid[lo] + 1);
      lo = par[hd[lo]];
    }
  }
  size_type size() const { return n; }
};
// }}}
