// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     dynamicsegtree
// @alias       segdynamic
// @name DynamicSegTree
// Note : to get faster, use map by yourself
// .entity : number of materialized leaves
/// --- DynamicSegTree {{{ ///

template < class Monoid >
struct DynamicSegTree {
  using T = typename Monoid::T;
  struct Node {
    T value;
    Node *l = nullptr, *r = nullptr;
    Node(T value = Monoid::identity()) : value(value) {}
  };
  Node *top = new Node;
  int n;
  DynamicSegTree() {}
  DynamicSegTree(int t) {
    n = 1;
    while(t > n) n <<= 1;
  }
  void set(int i, T const &val) { set(i, val, 0, n, top); }

private:
  void set(int i, T const &val, int l, int r, Node *&node) {
    if(i + 1 <= l || r <= i) return;
    if(node == nullptr) node = new Node();
    if(i <= l && r <= i + 1) {
      node->value = val;
      return;
    }
    set(i, val, l, (l + r) / 2, node->l);
    set(i, val, (l + r) / 2, r, node->r);
    node->value = Monoid::op(calc(node->l), calc(node->r));
  }
  inline T calc(Node *node) {
    return node == nullptr ? Monoid::identity() : node->value;
  }

public:
  T query(int a, int b) {
    if(a < 0 || b > n || b <= a) return Monoid::identity();
    return query(a, b, 0, n, top);
  }
  T get(int i) { return query(i, i + 1); }

private:
  T query(int a, int b, int l, int r, Node *node) {
    if(node == nullptr) return Monoid::identity();
    if(b <= l || r <= a) return Monoid::identity();
    if(a <= l && r <= b) return node->value;
    return Monoid::op(query(a, b, l, (l + r) / 2, node->l),
                      query(a, b, (l + r) / 2, r, node->r));
  }
};

/// }}}--- ///

// examples {{{

struct RMQMonoid {
  using T = ll;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return numeric_limits< T >::max(); }
};
struct RSQMonoid {
  using T = Int;
  static T op(const T &a, const T &b) { return a + b; }
  static T identity() { return T(); }
};
struct RMaxQMonoid {
  using T = ll;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return numeric_limits< T >::min(); }
};

// using RMQ = DynamicSegTree<RMQMonoid>;
using RSQ = DynamicSegTree< RSQMonoid >;
// using RMaxQ = DynamicSegTree<RMaxQMonoid>;

// }}}
