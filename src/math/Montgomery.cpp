// @import header
// @@
// @name Montgomery Library
// @title モンゴメリ乗算
// @snippet     montgomery
// @alias       mongome montogome
/// --- Montgomery Library {{{ ///

template<int mod = (int) 1e9 + 7>
struct Montgomery {
  int modlen = 64 - __builtin_clzll(mod);
  long long r2 = (1ll << (modlen * 2)) % mod;
  long long mask = (1 << modlen) - 1;
  long long nr;
  Montgomery() {
    nr = 0;
    int t = 0;
    int vi = 1;
    for(int i = 0; i < modlen; i++) {
      if((t & 1) == 0) {
        t += mod;
        nr += vi;
      }
      t >>= 1;
      vi <<= 1;
    }
  }
  long long reduction(long long t) {
    long long c = t * nr;
    c &= mask;
    c *= mod;
    c += t;
    c >>= modlen;
    if(c >= mod) c -= mod;
    return c;
  }
  // maybe, a * b must not be overflow
  inline long long mul(long long a, long long b) {
    return reduction(reduction(a * b) * r2);
  }
  long long pow(long long a, long long b) {
    long long p = reduction(a * r2);
    long long x = reduction(r2);
    while(b) {
      if(b & 1) x = reduction(x * p);
      p = reduction(p * p);
      b >>= 1;
    }
    return reduction(x);
  }
};

/// }}}--- ///

Montgomery<> montgomery;

