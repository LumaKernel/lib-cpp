// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ XorShift128
// @snippet     xorshift128
// @alias       random_xorshift128

/// --- XorShift128 {{{ ///

#include <cstdint>
struct XorShift128 {
  using result_type = uint_fast32_t;
  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return 0xFFFFFFFF; }
  result_type x = 123456789, y = 362436069, z = 521288629, w = 88675123;
  XorShift128(result_type seed = 0) { z ^= seed; }
  result_type operator()() {
    result_type t = x ^ (x << 11);
    x = y, y = z, z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
};

/// }}}--- ///

// @new
// @ XorShift128 Embeddable
// @snippet     xorshift128_embeddable

#include <cstdint>
/// --- XorShift128 Embeddable {{{ ///

struct XorShift128Embeddable {
  using result_type = uint_fast32_t;
  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return 0xFFFFFFFF; }
  result_type x = 123456789, y = 362436069, z = 521288629, w = 88675123;
  XorShift128Embeddable(result_type seed = 0) { z ^= seed; }
  result_type operator()() {
    result_type t = x ^ (x << 11);
    x = y, y = z, z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
};

/// }}}--- ///
