// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name SegmentTree Library
// @snippet     segmenttree
// @ SegmentTree Library
// @alias       seg
// NOTE : query in range!
/// --- SegmentTree Library {{{ ///

template < class Monoid >
struct SegTree {
private:
  using T = typename Monoid::T;
  int n;
  vector< T > data;
  // call after touch data[i]
  void prop(int i) { data[i] = Monoid::op(data[2 * i], data[2 * i + 1]); }

public:
  SegTree() : n(0) {}
  SegTree(int n) : n(n) { data.resize(n * 2, Monoid::identity()); }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  SegTree(InputIter first, InputIter last) : SegTree(distance(first, last)) {
    copy(first, last, begin(data) + n);
    // fill from deep
    for(int i = n - 1; i > 0; i--) prop(i);
  }
  void set(int i, const T &v) {
    data[i += n] = v;
    while(i >>= 1) prop(i); // propUp
  }
  T get(int i) { return data[i + n]; }
  T query(int l, int r) {
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

struct Nothing {
  using T = char;
  using M = char;
  static constexpr T op(const T &, const T &) { return 0; }
  static constexpr T identity() { return 0; }
  template < class X >
  static constexpr X actInto(const M &, ll, ll, const X &x) {
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

using RMQ = SegTree< RangeMin >;
RMQ rmq(N);
