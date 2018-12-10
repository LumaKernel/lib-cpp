// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet ntt
// @ NTT

// MAX_N is max size of OUTPUT, DOUBLED INPUT
// MAX_RES_VALUE = MAX_VALUE^2 * MAX_N
// if MAX_N > 2^20, comment out primes!
// NTT {{{
#include <cassert>
#include <cstdint>
#include <vector>

namespace NTT {
using uint = uint_fast32_t;

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
struct Pool {
  static ll *tmp, *A, *B;
};
template < int MAX_H >
ll *Pool< MAX_H >::tmp = new ll[1 << MAX_H];
template < int MAX_H >
ll *Pool< MAX_H >::A = new ll[1 << MAX_H];
template < int MAX_H >
ll *Pool< MAX_H >::B = new ll[1 << MAX_H];

template < int MAX_H, ll mod, ll primitive >
class Core {
public:
  static_assert((mod & ((1 << MAX_H) - 1)) == 1, "mod is too small; comment out");
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
  void fft(ll *a, uint n, uint nh, bool inverse) const {
    ll *tmp = Pool< MAX_H >::tmp;
    uint mask = n - 1;
    for(uint i = n >> 1, ih = nh - 1; i >= 1; i >>= 1, --ih) {
      ll zeta = inverse ? zetaInvList[nh - 1 - ih] : zetaList[nh - 1 - ih];
      ll powZeta = 1;
      for(uint j = 0; j < n; j += i) {
        for(uint k = 0; k < i; ++k) {
          tmp[j | k] =
              (a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k]) % mod;
        }
        powZeta = powZeta * zeta % mod;
      }
      swap(a, tmp);
    }
    if(nh & 1) {
      swap(a, tmp);
      for(uint i = 0; i < n; ++i) a[i] = tmp[i];
    }
    if(inverse) {
      ll invN = modinv(n, mod);
      for(uint i = 0; i < n; ++i) a[i] = a[i] * invN % mod;
    }
  }
  vector< ll > conv(const vector< ll > &a, const vector< ll > &b) const {
    uint t = a.size() + b.size() - 1;
    uint n = 1, nh = 0;
    while(n < t) n <<= 1, ++nh;
    return convStrict(a, b, n, nh);
  }
  vector< ll > convStrict(const vector< ll > &a, const vector< ll > &b, uint n,
                          uint nh) const {
    ll *A = Pool< MAX_H >::A, *B = Pool< MAX_H >::B;
    for(uint i = 0; i < n; ++i) A[i] = B[i] = 0;
    copy(a.begin(), a.end(), A);
    copy(b.begin(), b.end(), B);
    fft(A, n, nh, 0), fft(B, n, nh, 0);
    for(uint i = 0; i < n; ++i) A[i] = A[i] * B[i] % mod;
    fft(A, n, nh, 1);
    return vector< ll >(A, A + n);
  }
};
// }}}

// Convolution With Garner {{{
template < int MAX_H, int I >
class ConvolutionWithGarnerCore {
public:
  static void conv_for(uint n, uint nh, const vector< ll > &a, const vector< ll > &b,
                       vector< ll > &mods, vector< ll > &coeffs,
                       vector< vector< ll > > &constants) {
    static const Core< MAX_H, NTT_PRIMES[I][0], NTT_PRIMES[I][1] > ntt;
    auto c = ntt.convStrict(a, b, n, nh);
    mods[I] = NTT_PRIMES[I][0];
    ConvolutionWithGarnerCore< MAX_H, I - 1 >::conv_for(
        n, nh, a, b, mods, coeffs, constants);
    // garner
    for(size_t i = 0; i < c.size(); ++i) {
      ll v = (c[i] - constants[I][i]) * modinv(coeffs[I], mods[I]) % mods[I];
      if(v < 0) v += mods[I];
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
  static void conv_for(uint, uint, const vector< ll > &, const vector< ll > &,
                       vector< ll > &, vector< ll > &, vector< vector< ll > > &) {}
};

template < int MAX_H >
class ConvolutionWithGarner {
public:
  template < int USE >
  static vector< ll > conv(const vector< ll > &a, const vector< ll > &b, ll mod) {
    static_assert(USE >= 1, "USE must be positive");
    static_assert(USE <= sizeof(NTT_PRIMES) / sizeof(*NTT_PRIMES), "USE is too big");
    uint nt = a.size() + b.size() - 1;
    uint n = 1, nh = 0;
    while(n < nt) n <<= 1, ++nh;
    vector< ll > coeffs(USE + 1, 1);
    vector< vector< ll > > constants(USE + 1, vector< ll >(n));
    vector< ll > mods(USE + 1, mod);
    ConvolutionWithGarnerCore< MAX_H, USE - 1 >::conv_for(
        n, nh, a, b, mods, coeffs, constants);
    return constants.back();
  }
};

// }}}

} // namespace NTT
// }}}

// 1st param is MAX_H
NTT::Core< 18, NTT::NTT_PRIMES[0][0], NTT::NTT_PRIMES[0][1] > nttBig;
NTT::Core< 18, 998244353, 5 > ntt;
using nttconv = NTT::ConvolutionWithGarner< 18 >;
// nttconv::conv< USE >(a, b, mod)

// @new
// @ NTT2
// @snippet ntt2

// require NTT
// NTT2 {{{
namespace NTT {

// NTT2 Core {{{
template < int MAX_NM >
struct Pool2 {
  static ll *tmp, *A, *B;
};
template < int MAX_NM >
ll *Pool2< MAX_NM >::tmp = new ll[MAX_NM];
template < int MAX_NM >
ll *Pool2< MAX_NM >::A = new ll[MAX_NM];
template < int MAX_NM >
ll *Pool2< MAX_NM >::B = new ll[MAX_NM];

// transpose {{{
// semi-private
template < int MAX_NM, class T >
static void transpose(T *a, size_t n, size_t m, size_t mh) {
  // assert(m == (1u << mh));
  ll *tmp = Pool2< MAX_NM >::tmp;
  if(n == m) {
    for(size_t i = 0; i < n - 1; ++i)
      for(size_t j = i + 1; j < m; ++j) swap(a[(i << mh) | j], a[(j << mh) | i]);
  } else {
    for(size_t i = 0; i < n * m; ++i) tmp[i] = a[i];
    for(size_t i = 0; i < n; ++i)
      for(size_t j = 0; j < m; ++j) a[(i << mh) | j] = tmp[(j << mh) | i];
  }
}
// }}}

template < int MAX_H, int MAX_NM, ll mod, ll primitive >
class Core2 {
public:
  void fft2(ll *a, uint n, uint nh, uint m, uint mh, bool inverse) const {
    static const Core< MAX_H, mod, primitive > ntt;
    // assert(n == (1u << nh));
    // assert(m == (1u << mh));
    for(int t = 0; t < 2; ++t) {
      for(uint i = 0; i < n * m; i += m) ntt.fft(a + i, m, mh, inverse);
      transpose< MAX_NM >(a, n, m, mh);
      swap(n, m);
      swap(nh, mh);
    }
  }
  vector< vector< ll > > conv2(const vector< vector< ll > > &a,
                               const vector< vector< ll > > &b) const {
    uint nt = a.size() + b.size() - 1, mt = a[0].size() + b[1].size() - 1;
    assert(nt <= (1 << MAX_H) && mt <= (1 << MAX_H));
    uint n = 1, m = 1, nh = 0, mh = 0;
    while(n < nt) n <<= 1, ++nh;
    while(m < mt) m <<= 1, ++mh;
    return conv2Strict(a, b, n, nh, m, mh);
  }
  vector< vector< ll > > conv2Strict(const vector< vector< ll > > &a,
                                     const vector< vector< ll > > &b, uint n, uint nh,
                                     uint m, uint mh) const {
    ll *A = Pool2< MAX_NM >::A, *B = Pool2< MAX_NM >::B;
    for(uint i = 0; i < n * m; ++i) A[i] = B[i] = 0;
    for(uint i = 0; i < a.size(); ++i) copy(a[i].begin(), a[i].end(), A + (i << mh));
    for(uint i = 0; i < b.size(); ++i) copy(b[i].begin(), b[i].end(), B + (i << mh));
    fft2(A, n, nh, m, mh, 0), fft2(B, n, nh, m, mh, 0);
    for(uint i = 0; i < n * m; ++i) A[i] = A[i] * B[i] % mod;
    fft2(A, n, nh, m, mh, 1);
    vector< vector< ll > > c(n, vector< ll >(m));
    for(uint i = 0; i < n; ++i)
      for(uint j = 0; j < m; ++j) c[i][j] = A[(i << mh) | j];
    return c;
  }
};
// }}}

// Convolution2 With Garner {{{
template < int MAX_H, int MAX_NM, int I >
class Convolution2WithGarnerCore {
public:
  static void conv2_for(uint n, uint nh, uint m, uint mh, const vector< vector< ll > > &a,
                        const vector< vector< ll > > &b, vector< ll > &mods,
                        vector< ll > &coeffs,
                        vector< vector< vector< ll > > > &constants) {
    static const Core2< MAX_H, MAX_NM, NTT_PRIMES[I][0], NTT_PRIMES[I][1] > ntt2;
    auto c = ntt2.conv2Strict(a, b, n, nh, m, mh);
    mods[I] = NTT_PRIMES[I][0];
    Convolution2WithGarnerCore< MAX_H, MAX_NM, I - 1 >::conv2_for(
        n, nh, m, mh, a, b, mods, coeffs, constants);
    // garner
    for(size_t i = 0; i < c.size(); ++i)
      for(size_t j = 0; j < c[0].size(); ++j) {
        ll v = (c[i][j] - constants[I][i][j]) * modinv(coeffs[I], mods[I]) % mods[I];
        if(v < 0) v += mods[I];
        for(size_t k = I + 1; k < mods.size(); ++k) {
          constants[k][i][j] = (constants[k][i][j] + coeffs[k] * v) % mods[k];
        }
      }
    for(size_t j = I + 1; j < mods.size(); ++j) {
      coeffs[j] = (coeffs[j] * mods[I]) % mods[j];
    }
  }
};

template < int MAX_H, int MAX_NM >
class Convolution2WithGarnerCore< MAX_H, MAX_NM, -1 > {
public:
  static void conv2_for(uint, uint, uint, uint, const vector< vector< ll > > &,
                        const vector< vector< ll > > &, vector< ll > &, vector< ll > &,
                        vector< vector< vector< ll > > > &) {}
};

template < int MAX_H, int MAX_NM >
class Convolution2WithGarner {
public:
  template < int USE >
  static vector< vector< ll > > conv2(const vector< vector< ll > > &a,
                                      const vector< vector< ll > > &b, ll mod) {
    static_assert(USE >= 1, "USE must be positive");
    static_assert(USE <= sizeof(NTT_PRIMES) / sizeof(*NTT_PRIMES), "USE is too big");
    uint nt = a.size() + b.size() - 1, mt = a[0].size() + b[0].size() - 1;
    uint n = 1, m = 1, nh = 0, mh = 0;
    while(n < nt) n <<= 1, ++nh;
    while(m < mt) m <<= 1, ++mh;
    vector< ll > coeffs(USE + 1, 1);
    vector< vector< vector< ll > > > constants(
        USE + 1, vector< vector< ll > >(n, vector< ll >(m)));
    vector< ll > mods(USE + 1, mod);
    Convolution2WithGarnerCore< MAX_H, MAX_NM, USE - 1 >::conv2_for(
        n, nh, m, mh, a, b, mods, coeffs, constants);
    return constants.back();
  }
};

// }}}

} // namespace NTT
// }}}

NTT::Core2< 18, 1 << 22, NTT::NTT_PRIMES[0][0], NTT::NTT_PRIMES[0][1] > ntt2Big;
NTT::Core2< 18, 1 << 22, 998244353, 5 > ntt2;
using nttconv2 = NTT::Convolution2WithGarner< 11, 1 << 22 >;
// nttconv2::conv2< USE >(a, b, mod)
