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
template < class M_act >
struct LazySegmentTree {
public:
  using Monoid = typename M_act::Monoid;
  using X = typename Monoid::T;
  using M = typename M_act::M;

private:
  size_t n;
  int h;
  vector< X > data;
  vector< M > lazy;
  vector< size_t > nodeLength;
  // call before use data[i]
  void eval(size_t i) {
    if(lazy[i] == M_act::identity()) return;
    data[i] = M_act::actInto(lazy[i], nodeLength[i], data[i]);
    if(i < n) {
      lazy[i * 2] = M_act::op(lazy[i], lazy[i * 2]);
      lazy[i * 2 + 1] = M_act::op(lazy[i], lazy[i * 2 + 1]);
    }
    lazy[i] = M_act::identity();
  }
  // call before use seg[i] = data[i + n]
  void evalDown(size_t i) {
    i += n;
    for(int j = h - 1; j >= 0; j--) eval(i >> j);
  }
  // call after touch seg[i] = data[i + n]
  void propUp(size_t i) {
    i += n;
    while(i >>= 1)
      eval(i * 2), eval(i * 2 + 1), data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }

public:
  LazySegmentTree() : n(0) {}
  LazySegmentTree(size_t n, X initial = Monoid::identity()) : n(n) {
    if(n > 0) {
      h = 1;
      while(1u << h < n) h++;
      data.resize(2 * n, initial);
      lazy.resize(2 * n, M_act::identity());
      nodeLength.resize(2 * n, 1);
      for(size_t i = n - 1; i > 0; i--) // fill from deep
        data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]),
        nodeLength[i] = nodeLength[i * 2] + nodeLength[i * 2 + 1];
    }
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  LazySegmentTree(InputIter first, InputIter last)
      : LazySegmentTree(distance(first, last)) {
    if(n > 0) {
      copy(first, last, begin(data) + n);
      for(size_t i = n - 1; i > 0; i--) // fill from deep
        data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
    }
  }
  LazySegmentTree(vector< X > v) : LazySegmentTree(v.begin(), v.end()) {}
  LazySegmentTree(initializer_list< X > v) : LazySegmentTree(v.begin(), v.end()) {}
  void act(int l, int r, const M &m) {
    if(l < 0) l = 0;
    if(l >= r) return;
    if(r > (int) n) r = n;
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
  X fold(int l, int r) {
    if(l < 0) l = 0;
    if(l >= r) return Monoid::identity();
    if(r > (int) n) r = n;
    evalDown(l);
    evalDown(r - 1);
    X tmpL = Monoid::identity(), tmpR = Monoid::identity();
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) eval(l), tmpL = Monoid::op(tmpL, data[l]), l++;
      if(r & 1) --r, eval(r), tmpR = Monoid::op(data[r], tmpR);
    }
    return Monoid::op(tmpL, tmpR);
  }
  int size() { return n; }
  inline void dum(int r = -1) {
#ifdef DEBUG
    if(r < 0) r = n;
    DEBUG_OUT << "{";
    for(int i = 0; i < min(r, (int) n); i++) DEBUG_OUT << (i ? ", " : "") << get(i);
    DEBUG_OUT << "}" << endl;
#endif
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

/// --- M_act examples {{{ ///
template < class U = long long, class V = U >
struct RangeMinAdd {
  using X = U;
  using M = V;
  using Monoid = RangeMin< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMaxAdd {
  using X = U;
  using M = V;
  using Monoid = RangeMax< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMinSet {
  using M = U;
  using Monoid = RangeMin< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll, const X &) { return m; }
};

template < class U = long long, class V = U >
struct RangeMaxSet {
  using M = U;
  using Monoid = RangeMax< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll, const X &) { return m; }
};

template < class U = long long, class V = U >
struct RangeSumAdd {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll n, const X &x) { return m * n + x; }
};

template < class U = long long, class V = U >
struct RangeSumSet {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll n, const X &) { return m * n; }
};

template < class U, class V = U >
struct RangeProdMul {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M mpow(M a, ll b) {
    X r(1);
    while(b) {
      if(b & 1) r = r * a;
      a = a * a;
      b >>= 1;
    }
    return r;
  }
  static M op(const M &a, const M &b) { return a * b; }
  static constexpr M identity() { return M(1); }
  static X actInto(const M &m, ll n, const X &x) { return x * mpow(m, n); }
};

template < class U, class V = U >
struct RangeProdSet {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return V::unused; }
  static X actInto(const M &m, ll n, const X &) {
    return RangeProdMul< U, V >::mpow(m, n);
  }
};

template < class U = long long, class V = U >
struct RangeOr2 {
  using X = U;
  using M = V;
  using Monoid = RangeOr< U >;
  static M op(const M &a, const M &b) { return a | b; }
  static constexpr M identity() { return M(0); }
  static X actInto(const M &m, ll, const X &x) { return m | x; }
};

template < class U = long long, class V = U >
struct RangeAnd2 {
  using X = U;
  using M = V;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return M(-1); }
  static X actInto(const M &m, ll, const X &x) { return m & x; }
};

template < class U, size_t N >
struct RangeAnd2< U, std::bitset< N > > {
  using X = U;
  using M = std::bitset< N >;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return std::bitset< N >().set(); }
  static X actInto(const M &m, ll, const X &x) { return m & x; }
};
/// }}}--- ///

using Seg = LazySegmentTree< RangeSumAdd<> >;

Seg seg(N);
