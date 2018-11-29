// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     ntt
// @ NTT

// MAX_N is max size of OUTPUT, DOUBLED INPUT
// MAX_RES_VALUE = MAX_VALUE^2 * MAX_N
// if MAX_N > 2^20, comment out primes!
/// --- NTT {{{ ///
#include <cassert>
#include <cstdint>
#include <vector>

namespace NTT {

// general math {{{
ll extgcd(ll a, ll b, ll &x, ll &y) {
  ll d;
  return b == 0 ? (x = 1, y = 0, a) : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
}
ll modinv(ll a, ll mod) {
  ll x, y;
  extgcd(a, mod, x, y);
  x %= mod;
  return x < 0 ? x + mod : x;
}
ll modpow(ll a, ll b, ll mod) {
  ll r = 1;
  a %= mod;
  while(b) {
    if(b & 1) r = r * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return r;
}
// }}}

// NTT Core {{{
template < int MAX_H >
class Wrapper {
  static ll *tmp;
  static ll *A, *B;

public:
  template < ll mod, ll primitive >
  class Core {
  public:
    static_assert((mod & ((1 << MAX_H) - 1)) == 1, "mod is too small; comment out");
    using uint = uint_fast32_t;
    // ord zetaList[i] = 2^(i + 1)
    ll zetaList[MAX_H], zetaInvList[MAX_H];
    // constexpr
    Core() {
      zetaList[MAX_H - 1] = modpow(primitive, (mod - 1) / (1 << MAX_H), mod);
      zetaInvList[MAX_H - 1] = modinv(zetaList[MAX_H - 1], mod);
      for(int ih = MAX_H - 2; ih >= 0; --ih) {
        zetaList[ih] = zetaList[ih + 1] * zetaList[ih + 1] % mod;
        zetaInvList[ih] = zetaInvList[ih + 1] * zetaInvList[ih + 1] % mod;
      }
    }
    void fft(ll *a, uint n, uint h, bool inv) const {
      uint mask = n - 1;
      for(uint i = n >> 1, ih = h - 1; i >= 1; i >>= 1, --ih) {
        ll zeta = inv ? zetaInvList[h - 1 - ih] : zetaList[h - 1 - ih];
        ll powZeta = 1;
        for(uint j = 0; j < n; j += i) {
          for(uint k = 0; k < i; ++k) {
            tmp[j + k] =
                (a[((j << 1) & mask) + k] + powZeta * a[(((j << 1) + i) & mask) + k]) %
                mod;
          }
          powZeta = powZeta * zeta % mod;
        }
        swap(a, tmp);
      }
      if(h & 1) {
        swap(a, tmp);
        for(uint i = 0; i < n; ++i) a[i] = tmp[i];
      }
      if(inv) {
        ll invN = modinv(n, mod);
        for(uint i = 0; i < n; ++i) a[i] = a[i] * invN % mod;
      }
    }
    vector< ll > conv(const vector< ll > &a, const vector< ll > &b) const {
      assert(a.size() + b.size() - 1 <= (1 << MAX_H));

      if(a.size() == 0) return {};
      if(b.size() == 0) return {};
      return _conv(a, b);
    }
    vector< ll > _conv(const vector< ll > &a, const vector< ll > &b) const {
      uint t = a.size() + b.size() - 1;
      uint h = 0, n = 1;
      while(n < t) n <<= 1, ++h;
      return _convStrict(a, b, n, h);
    }
    vector< ll > _convStrict(const vector< ll > &a, const vector< ll > &b, uint n,
                             uint h) const {
      copy(a.begin(), a.end(), A);
      copy(b.begin(), b.end(), B);
      fft(A, n, h, 0), fft(B, n, h, 0);
      for(uint i = 0; i < n; ++i) A[i] = A[i] * B[i] % mod;
      fft(A, n, h, 1);
      return vector< ll >(A, A + n);
    }
  };
};
template < int MAX_H >
ll *Wrapper< MAX_H >::tmp = new ll[1 << MAX_H];
template < int MAX_H >
ll *Wrapper< MAX_H >::A = new ll[1 << MAX_H];
template < int MAX_H >
ll *Wrapper< MAX_H >::B = new ll[1 << MAX_H];
// }}}

// NTT_PRIMES {{{
constexpr ll NTT_PRIMES[][2] = {
    {1224736769, 3}, // 2^24 * 73 + 1,
    {1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1
    {1051721729, 6}, // 2^20 * 17 * 59 + 1
    {1045430273, 3}, // 2^20 * 997 + 1
    {1012924417, 5}, // 2^21 * 3 * 7 * 23 + 1
    {1007681537, 3}, // 2^20 * 31^2 + 1
    {1004535809, 3}, // 2^21 * 479 + 1
    {998244353, 3},  // 2^23 * 7 * 17 + 1
    {985661441, 3},  // 2^22 * 5 * 47 + 1
    {976224257, 3},  // 2^20 * 7^2 * 19 + 1
    {975175681, 17}, // 2^21 * 3 * 5 * 31 + 1
    {962592769, 7},  // 2^21 * 3^3 * 17 + 1
    {950009857, 7},  // 2^21 * 4 * 151 + 1
    {943718401, 7},  // 2^22 * 3^2 * 5^2 + 1
    {935329793, 3},  // 2^22 * 223 + 1
    {924844033, 5},  // 2^21 * 3^2 * 7^2 + 1
    {469762049, 3},  // 2^26 * 7 + 1
    {167772161, 3},  // 2^25 * 5 + 1
};
// }}}

// Convolution With Garner {{{
template < int MAX_H, int I >
class ConvolutionWithGarnerCore {
public:
  static void conv_for(int n, int h, const vector< ll > &a, const vector< ll > &b,
                       vector< ll > &mods, vector< ll > &coeffs,
                       vector< vector< ll > > &constants) {
    static const typename NTT::Wrapper< MAX_H >::template Core< NTT_PRIMES[I][0],
                                                                NTT_PRIMES[I][1] >
        ntt;
    auto c = ntt._convStrict(a, b, n, h);
    mods[I] = NTT_PRIMES[I][0];
    ConvolutionWithGarnerCore< MAX_H, I - 1 >::conv_for(
        n, h, a, b, mods, coeffs, constants);
    // garner
    for(size_t i = 0; i < c.size(); ++i) {
      ll v = (c[i] - constants[I][i]) * modinv(coeffs[I], mods[I]) % mods[I];
      if(v < 0) v += mods[i];
      for(size_t j = I + 1; j < mods.size(); ++j) {
        constants[j][i] = (constants[j][i] + coeffs[j] * v) % mods[j];
      }
    }
    for(size_t j = I + 1; j < mods.size(); ++j) {
      coeffs[j] = (coeffs[j] * mods[I]) % mods[j];
    }
  }
};

template < int MAX_H >
class ConvolutionWithGarnerCore< MAX_H, -1 > {
public:
  static void conv_for(int, int, const vector< ll > &, const vector< ll > &,
                       vector< ll > &, vector< ll > &, vector< vector< ll > > &) {}
};

template < int MAX_H >
class ConvolutionWithGarner {
public:
  template < int USE >
  static vector< ll > conv(vector< ll > a, vector< ll > b, ll mod) {
    static_assert(USE >= 1, "USE must be positive");
    static_assert(USE <= sizeof(NTT_PRIMES) / sizeof(*NTT_PRIMES), "USE is too big");
    int deg = a.size() + b.size() - 1;
    int n = 1, h = 0;
    while(n < deg) n <<= 1, ++h;
    a.resize(n), b.resize(n);
    vector< ll > coeffs(USE + 1, 1);
    vector< vector< ll > > constants(USE + 1, vector< ll >(n, 0));
    vector< ll > mods(USE + 1, mod);
    ConvolutionWithGarnerCore< MAX_H, USE - 1 >::conv_for(
        n, h, a, b, mods, coeffs, constants);
    return constants.back();
  }
};

// }}}

} // namespace NTT
/// }}}--- ///

// 1st param is MAX_H
// NTT::Wrapper< 18 >::Core< NTT::NTT_PRIMES[0][0], NTT::NTT_PRIMES[0][1] > nttBig;
// NTT::Wrapper< 18 >::Core< 924844033, 5 > ntt;
using nttconv = NTT::ConvolutionWithGarner< 18 >;
// nttconv::conv< USE >(a, b, mod)
