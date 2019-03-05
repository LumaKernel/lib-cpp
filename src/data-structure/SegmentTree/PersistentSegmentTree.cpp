// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Persistent SegmentTree
// @snippet     persistent_seg
// @alias       seg_persistent

// .set( i , time = .lastRoot ) returns new time ( after updating )
// .fold( l, r, time = .lastRoot ) : [l, r)
// .get( i , time = .lastRoot )
/// --- Persistent SegmentTree {{{ ///

#include <vector>

template < class Monoid >
struct PersistentSegTree {
private:
  using T = typename Monoid::T;
  int n;
  vector< T > data;
  vector< int > lch, rch;

public:
  vector< int > roots;
  PersistentSegTree() : n(0) {}
  PersistentSegTree(int n) : n(n), data(1, Monoid::identity()), lch(1, 0), rch(1, 0) {
    roots.push_back(0);
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  PersistentSegTree(InputIter first, InputIter last)
      : PersistentSegTree(distance(first, last)) {
    data.resize(n * 2, Monoid::identity());
    lch.resize(n * 2, 0);
    rch.resize(n * 2, 0);
    copy(first, last, begin(data) + n);
    for(int i = n - 1; i >= 1; i--) {
      data[i] = Monoid::op(data[lch[i] = i * 2], data[rch[i] = i * 2 + 1]);
    }
    roots.push_back(1);
  }
  int set(int i, const T &v, int time = -1) {
    if(time == -1) time = roots.size() - 1;
    int k = make();
    set(i, v, 0, n, k, roots[time]);
    roots.push_back(k);
    return roots.size() - 1;
  }
  void reserve(int qsize) {
    int h = log(n);
    data.reserve(n * 2 + qsize * h);
    lch.reserve(n * 2 + qsize * h);
    rch.reserve(n * 2 + qsize * h);
  }
  void set(int i, const T &v, int l, int r, int k, int prevK) {
    if(r - l == 1) {
      data[k] = v;
      return;
    }
    lch[k] = lch[prevK];
    rch[k] = rch[prevK];
    int x = make();
    if(i < ((l + r) >> 1)) {
      lch[k] = x;
      set(i, v, l, (l + r) >> 1, lch[k], lch[prevK]);
    } else {
      rch[k] = x;
      set(i, v, (l + r) >> 1, r, rch[k], rch[prevK]);
    }
    data[k] = Monoid::op(data[lch[k]], data[rch[k]]);
  }
  T get(int i, int time = -1) { return fold(i, i + 1, time); }
  T fold(int a, int b, int time = -1) {
    if(time == -1) time = roots.size() - 1;
    return fold(a, b, 0, n, roots[time]);
  }
  T fold(int a, int b, int l, int r, int k) {
    if(k == 0) return Monoid::identity();
    if(b <= l || r <= a) return Monoid::identity();
    if(a <= l && r <= b) return data[k];
    return Monoid::op(
        fold(a, b, l, (l + r) >> 1, lch[k]), fold(a, b, (l + r) >> 1, r, rch[k]));
  }

private:
  int make() {
    data.emplace_back(Monoid::identity());
    lch.emplace_back(0);
    rch.emplace_back(0);
    return data.size() - 1;
  }
  int log(int x) {
    int t = 0;
    while(x) x >>= 1, t++;
    return t;
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
  static constexpr X actInto(const M &, long long, const X &x) {
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

using Seg = PersistentSegTree< RangeMin<> >;
