// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ DSU on Tree - HLD Style
// @snippet dsu_on_tree

// DSU_on_tree( <tree> , root, add, rem, proceed)
// add, rem, proceed is (vertex) => void
// O(N log N)
// DSU on Tree {{{
#include <cassert>
#include <functional>
#include <stack>
#include <vector>
// HLD style
class DSU_on_tree {
public:
  using size_type = size_t;
  using graph_type = vector< vector< int > >;
  using function_type = function< void(size_type) >;
  size_type n;
  graph_type tree;
  size_type root;
  function_type add, rem, proceed;

  DSU_on_tree() : n(0) {}
  DSU_on_tree(const graph_type &tree, size_type root, const function_type &add,
              const function_type &rem, const function_type &proceed)
      : n(tree.size()), tree(tree), root(root), add(add), rem(rem), proceed(proceed) {
    assert(root < n);
  }

private:
  bool initiated = 0;
  vector< int > heavy;
  vector< size_type > sub;

public:
  int getHeavy(size_type i) {
    assert(initiated);
    assert(i < n);
    return heavy[i];
  }

public:
  void init() {
    assert(!initiated);
    sub.resize(n);
    heavy.resize(n, -1);
    dfs_size();
    initiated = 1;
    dfs();
  }

private:
  void dfs_size() {
    vector< int > used(n);
    stack< pair< size_type, int > > stk;
    stk.emplace(root, -1);
    while(stk.size()) {
      size_type i;
      int p;
      tie(i, p) = stk.top();
      if(!used[i]) {
        used[i] = 1;
        for(auto &j : tree[i])
          if(j != p) {
            stk.emplace(j, i);
          }
      } else {
        stk.pop();
        sub[i] = 1;
        size_type max_size = 0;
        for(auto &j : tree[i])
          if(j != p) {
            sub[i] += sub[j];
            if(heavy[i] == -1 || max_size < sub[j]) max_size = sub[j], heavy[i] = j;
          }
      }
    }
  }
  void dfs() {
    vector< int > used(n);
    stack< tuple< size_type, int, bool > > stk;
    stk.emplace(root, -1, 1);
    while(stk.size()) {
      size_type i;
      int p;
      bool keep;
      tie(i, p, keep) = stk.top();
      if(!used[i]) {
        used[i] = 1;
        if(heavy[i] != -1) stk.emplace(heavy[i], i, 1);
        for(auto &j : tree[i])
          if(j != p && j != heavy[i]) stk.emplace(j, i, 0);
      } else {
        stk.pop();
        dfs_func(i, p, heavy[i], add);
        proceed(i);
        if(!keep) dfs_func(i, p, -1, rem);
      }
    }
  }
  void dfs_func(size_type i, int p, int dontGo, const function_type &func) {
    stack< pair< size_type, int > > stk;
    stk.emplace(i, p);
    while(stk.size()) {
      size_type i;
      int p;
      tie(i, p) = stk.top();
      stk.pop();
      func(i);
      for(auto &j : tree[i])
        if(j != p && j != dontGo) {
          stk.emplace(j, i);
        }
    }
  }
};
// }}}
