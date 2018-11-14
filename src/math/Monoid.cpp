// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Monoid examples
// @snippet monoid_expamples
/// --- Monoid examples {{{ ///

#include <algorithm>
#include <limits>

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
