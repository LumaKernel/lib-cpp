// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ LazySegmentTree
// @snippet lazysegmenttree
// @alias lazy lazyseg

// LazySegmentTree( size [, initial] )
// LazySegmentTree( <data> )
/// --- LazySegmentTree {{{ ///
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>
template < class Monoid, class M_act >
struct LazySegmentTree {
private:
  using X = typename Monoid::T;
  using M = typename M_act::M;
  int n, h;
  vector< X > data;
  vector< M > lazy;
  vector< int > nodeLeft;
  vector< int > nodeLength;
  // call before use data[i]
  void eval(int i) {
    if(lazy[i] == M_act::identity()) return;
    data[i] = M_act::actInto(lazy[i], nodeLeft[i], nodeLength[i], data[i]);
    if(i < n) {
      lazy[i * 2] = M_act::op(lazy[i], lazy[i * 2]);
      lazy[i * 2 + 1] = M_act::op(lazy[i], lazy[i * 2 + 1]);
    }
    lazy[i] = M_act::identity();
  }
  // call before use seg[i] = data[i + n]
  void evalDown(int i) {
    i += n;
    for(int j = h - 1; j >= 0; j--) eval(i >> j);
  }
  // call after touch seg[i] = data[i + n]
  void propUp(int i) {
    i += n;
    while(i >>= 1)
      eval(i * 2), eval(i * 2 + 1), data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }

public:
  LazySegmentTree() : n(0) {}
  LazySegmentTree(int n, X initial = Monoid::identity()) : n(n) {
    h = 1;
    while(1 << h < n) h++;
    data.resize(2 * n, initial);
    lazy.resize(2 * n, M_act::identity());
    nodeLeft.resize(2 * n);
    nodeLength.resize(2 * n, 1);
    for(int i = 0; i < n; i++) nodeLeft[i + n] = i;
    for(int i = n - 1; i > 0; i--) // fill from deep
      data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]),
      nodeLeft[i] = min(nodeLeft[i * 2], nodeLeft[i * 2 + 1]),
      nodeLength[i] = nodeLength[i * 2] + nodeLength[i * 2 + 1];
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  LazySegmentTree(InputIter first, InputIter last)
      : LazySegmentTree(distance(first, last)) {
    copy(first, last, begin(data) + n);
    for(int i = n - 1; i > 0; i--) // fill from deep
      data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }
  LazySegmentTree(vector< X > v) : LazySegmentTree(v.begin(), v.end()) {}
  LazySegmentTree(initializer_list< X > v) : LazySegmentTree(v.begin(), v.end()) {}
  void act(int l, int r, const M &m) {
    if(l < 0) l = 0;
    if(r >= n) r = n - 1;
    evalDown(l);
    evalDown(r - 1);
    int tl = l, tr = r;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) eval(l), lazy[l] = m, eval(l), l++;
      if(r & 1) --r, eval(r), lazy[r] = m, eval(r);
    }
    propUp(tl);
    propUp(tr - 1);
  }
  void set(size_t i, const X &x) {
    assert(i < n);
    evalDown(i);
    data[i + n] = x;
    propUp(i);
  }
  X get(size_t i) {
    assert(i < n);
    evalDown(i);
    return data[i + n];
  }
  X query(int l, int r) {
    if(l < 0) l = 0;
    if(r >= n) r = n - 1;
    evalDown(l);
    evalDown(r - 1);
    X tmpL = Monoid::identity(), tmpR = Monoid::identity();
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) eval(l), tmpL = Monoid::op(tmpL, data[l]), l++;
      if(r & 1) --r, eval(r), tmpR = Monoid::op(data[r], tmpR);
    }
    return Monoid::op(tmpL, tmpR);
  }
  inline void dum(int r = -1) {
#ifdef DEBUG
    if(r < 0) r = n;
    DEBUG_OUT << "{";
    for(int i = 0; i < min(r, n); i++) DEBUG_OUT << (i ? ", " : "") << get(i);
    DEBUG_OUT << "}" << endl;
#endif
  }
};

/// }}}--- ///

/// --- Monoid, M_act examples {{{ ///

/// --- Monoid examples {{{ ///

#include <algorithm>

constexpr long long inf = 1e18 + 100;

struct Nothing {
  using T = char;
  using M = T;
  static constexpr T op(const T &, const T &) { return T(); }
  static constexpr T identity() { return T(); }
  template < class X >
  static constexpr X actInto(const M &, ll, ll, const X &x) {
    return x;
  }
};

struct RangeMin {
  using T = ll;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return inf; }
};

struct RangeMax {
  using T = ll;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return -inf; }
};

struct RangeSum {
  using T = ll;
  static T op(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return 0; }
};

/// }}}--- ///

// MinAdd m + x
// MinSet m
// SumAdd m * n + x
// SumSet m * n

struct RangeMinAdd {
  using M = ll;
  using X = RangeMin::T;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, ll, const X &x) { return m + x; }
};

struct RangeMinSet {
  using M = ll;
  using X = RangeMin::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -inf; }
  static X actInto(const M &m, ll, ll, const X &) { return m; }
};

struct RangeSumAdd {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, ll n, const X &x) { return m * n + x; }
};

struct RangeSumSet {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -inf; }
  static X actInto(const M &m, ll, ll n, const X &) { return m * n; }
};

/// }}}--- ///

LazySegmentTree< RangeSum, RangeSumAdd > seg(N);
