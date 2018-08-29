// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name LazySegmentTree Library
// @snippet     lazysegmenttree
// @alias       lazy lazyseg
// NOTE : query in range!
/// --- LazySegmentTree Library {{{ ///

template < class Monoid, class M_act >
struct LazySegTree {
private:
  using X = typename Monoid::T;
  using M = typename M_act::M;
  int n, h;
  vector< X > data;
  vector< M > lazy;
  // call before use data[i]
  void eval(int i, int sz) {
    if(lazy[i] == M_act::identity()) return;
    data[i] = M_act::actInto(lazy[i], sz, data[i]);
    if(i < n) {
      lazy[i * 2] = M_act::op(lazy[i], lazy[i * 2]);
      lazy[i * 2 + 1] = M_act::op(lazy[i], lazy[i * 2 + 1]);
    }
    lazy[i] = M_act::identity();
  }
  // call before use seg[i] = data[i + n]
  void evalDown(int i) {
    i += n;
    for(int j = h - 1; j >= 0; j--) eval(i >> j, 1 << j);
  }
  // call after touch seg[i] = data[i + n]
  void propUp(int i) {
    i += n;
    int sz = 1;
    while(i >>= 1)
      eval(i * 2, sz), eval(i * 2 + 1, sz),
          data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]), sz <<= 1;
  }
  int logbin(int x) {
    int h = 0;
    x = x & 0xFFFF0000 ? (h += 16, x) & 0xFFFF0000 : x;
    x = x & 0xFF00FF00 ? (h += 8, x) & 0xFF00FF00 : x;
    x = x & 0xF0F0F0F0 ? (h += 4, x) & 0xF0F0F0F0 : x;
    x = x & 0xCCCCCCCC ? (h += 2, x) & 0xCCCCCCCC : x;
    x = x & 0xAAAAAAAA ? (h += 1, x) & 0xAAAAAAAA : x;
    return h;
  }

public:
  LazySegTree() : n(0) {}
  LazySegTree(int n) : n(n) {
    h = logbin(n) + 1;
    data.resize(2 * n, Monoid::identity());
    lazy.resize(2 * n, M_act::identity());
  }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  LazySegTree(InputIter first, InputIter last)
      : LazySegTree(distance(first, last)) {
    copy(first, last, begin(data) + n);
    for(int i = n - 1; i > 0; i--) // fill from deep
      data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }
  void act(int l, int r, const M &m) {
    evalDown(l);
    evalDown(r - 1);
    int tl = l, tr = r;
    int sz = 1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1, sz <<= 1) {
      if(l & 1) eval(l, sz), lazy[l] = m, eval(l, sz), l++;
      if(r & 1) --r, eval(r, sz), lazy[r] = m, eval(r, sz);
    }
    propUp(tl);
    propUp(tr - 1);
  }
  void set(int i, const X &x) {
    evalDown(i);
    data[i + n] = x;
    propUp(i);
  }
  X get(int i) {
    evalDown(i);
    return data[i + n];
  }
  X query(int l, int r) {
    evalDown(l);
    evalDown(r - 1);
    X tmpL = Monoid::identity(), tmpR = Monoid::identity();
    int sz = 1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1, sz <<= 1) {
      if(l & 1) eval(l, sz), tmpL = Monoid::op(tmpL, data[l++]);
      if(r & 1) eval(--r, sz), tmpR = Monoid::op(data[r], tmpR);
    }
    return Monoid::op(tmpL, tmpR);
  }
  inline void dum(int r = -1) {
#ifdef DEBUG
    ostream &o =
#ifdef USE_COUT
        cout
#else
        cerr
#endif
        ;
    if(r < 0) r = n;
    o << "{";
    for(int i = 0; i < min(r, n); i++) o << (i ? ", " : "") << get(i);
    o << "}" << endl;
#endif
  }
};

/// }}}--- ///

/// --- Monoid, M_act examples {{{ ///

/// --- Monoid examples {{{ ///

struct Nothing {
  using T = char;
  using M = char;
  static constexpr T op(const T &, const T &) { return 0; }
  static constexpr T identity() { return 0; }
  template < class X >
  static constexpr X actInto(const M &, ll, const X &x) {
    return x;
  }
};

struct RangeMin {
  using T = ll;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return numeric_limits< T >::max(); }
};

struct RangeMax {
  using T = ll;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return numeric_limits< T >::min(); }
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
  static X actInto(const M &m, ll, const X &x) { return m + x; }
};

struct RangeMinSet {
  using M = ll;
  using X = RangeMin::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return numeric_limits< M >::min(); }
  static X actInto(const M &m, ll, const X &) { return m; }
};

struct RangeSumAdd {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll n, const X &x) { return m * n + x; }
};

struct RangeSumSet {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return numeric_limits< M >::min(); }
  static X actInto(const M &m, ll n, const X &) { return m * n; }
};

/// }}}--- ///

// LazySegTree<RangeSum, RangeSumAdd> seg(N);
