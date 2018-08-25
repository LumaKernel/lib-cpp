// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name XorShift128
// @snippet     xorshift128
// @alias       random_xorshift128
/// --- XorShift128 {{{ ///
struct XorShift128 {
  using u32 = uint32_t;
  u32 x = 123456789, y = 362436069, z = 521288629, w = 88675123;
  XorShift128(u32 seed = 0) { z ^= seed; }
  u32 operator()() {
    u32 t = x ^ (x << 11);
    x = y, y = z, z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
};
/// }}}--- ///
