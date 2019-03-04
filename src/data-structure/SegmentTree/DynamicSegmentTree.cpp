// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Dynamic SegmentTree
// @snippet     dynamicsegmenttree
// @alias       segdynamic

/// --- Dynamic SegmentTree {{{ ///
template < class Monoid >
struct DynamicSegmentTree {
  using T = typename Monoid::T;
  struct Node {
    T value;
    Node *l = nullptr, *r = nullptr;
    Node(T value = Monoid::identity()) : value(value) {}
  };
  Node *top = new Node;
  int n;
  DynamicSegmentTree() {}
  DynamicSegmentTree(int t) {
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
  inline T calc(Node *node) { return node == nullptr ? Monoid::identity() : node->value; }

public:
  T fold(int a, int b) {
    if(a < 0 || b > n || b <= a) return Monoid::identity();
    return fold(a, b, 0, n, top);
  }
  T get(int i) { return fold(i, i + 1); }

private:
  T fold(int a, int b, int l, int r, Node *node) {
    if(node == nullptr) return Monoid::identity();
    if(b <= l || r <= a) return Monoid::identity();
    if(a <= l && r <= b) return node->value;
    return Monoid::op(
        fold(a, b, l, (l + r) / 2, node->l), fold(a, b, (l + r) / 2, r, node->r));
  }
};

/// }}}--- ///

/// --- Monoid examples {{{ ///
constexpr long long inf_monoid = 1e18 + 100;
#include <algorithm>
struct Nothing {
  using T = char;
  using Monoid = Nothing;
  using M = T;
  static constexpr T op(const T &, const T &) { return T(); }
  static constexpr T identity() { return T(); }
  template < class X >
  static constexpr X actInto(const M &, ll, ll, const X &x) {
    return x;
  }
};

template < class U = long long >
struct RangeMin {
  using T = U;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return T(inf_monoid); }
};

template < class U = long long >
struct RangeMax {
  using T = U;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return -T(inf_monoid); }
};

template < class U = long long >
struct RangeSum {
  using T = U;
  static T op(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return T(0); }
};

template < class U >
struct RangeProd {
  using T = U;
  static T op(const T &a, const T &b) { return a * b; }
  static constexpr T identity() { return T(1); }
};

template < class U = long long >
struct RangeOr {
  using T = U;
  static T op(const T &a, const T &b) { return a | b; }
  static constexpr T identity() { return T(0); }
};

#include <bitset>

template < class U = long long >
struct RangeAnd {
  using T = U;
  static T op(const T &a, const T &b) { return a & b; }
  static constexpr T identity() { return T(-1); }
};

template < size_t N >
struct RangeAnd< std::bitset< N > > {
  using T = std::bitset< N >;
  static T op(const T &a, const T &b) { return a & b; }
  static constexpr T identity() { return std::bitset< N >().set(); }
};

/// }}}--- ///

using Seg = DynamicSegmentTree< RangeMin<> >;
