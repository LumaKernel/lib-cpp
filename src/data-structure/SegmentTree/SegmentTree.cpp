// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ SegmentTree
// @snippet segmenttree
// @alias seg

// SegmentTree( size [, initial] )
// SegmentTree( <data> )
/// --- SegmentTree {{{ ///
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>
template < class Monoid >
struct SegmentTree {
private:
  using T = typename Monoid::T;
  int n;
  vector< T > data;
  // call after touch data[i]
  void prop(int i) { data[i] = Monoid::op(data[2 * i], data[2 * i + 1]); }

public:
  SegmentTree() : n(0) {}
  SegmentTree(int n, T initial = Monoid::identity()) : n(n) {
    data.resize(n * 2, initial);
    for(int i = n - 1; i > 0; i--) data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  SegmentTree(InputIter first, InputIter last) : SegmentTree(distance(first, last)) {
    copy(first, last, begin(data) + n);
    // fill from deep
    for(int i = n - 1; i > 0; i--) prop(i);
  }
  SegmentTree(vector< T > v) : SegmentTree(v.begin(), v.end()) {}
  SegmentTree(initializer_list< T > v) : SegmentTree(v.begin(), v.end()) {}
  void set(size_t i, const T &v) {
    assert(i < n);
    data[i += n] = v;
    while(i >>= 1) prop(i); // propUp
  }
  T get(size_t i) {
    assert(i < n);
    return data[i + n];
  }
  T fold(int l, int r) {
    if(l < 0) l = 0;
    if(l >= r) return Monoid::identity();
    if(r > n) r = n;
    T tmpL = Monoid::identity(), tmpR = Monoid::identity();
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) tmpL = Monoid::op(tmpL, data[l++]);
      if(r & 1) tmpR = Monoid::op(data[--r], tmpR);
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

using Seg = SegmentTree< RangeMin<> >;
Seg seg(N);
