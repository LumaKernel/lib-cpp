// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     ntt
// @name NTT Library

// require math library
/// --- NTT Library {{{ ///
struct NTT {
  ll mod, primitive;
  NTT() {}
  NTT(ll mod, ll primitive) : mod(mod), primitive(primitive) {}
  vector< ll > fft(vector< ll > a, bool inv = 0) {
    int n = a.size();
    int h = 32 - __builtin_clz(n);
    h--;
    // bitの反転
    for(int i = 0; i < n; i++) {
      int j = 0;
      for(int k = 0; k < h; k++) j |= (i >> k & 1) << (h - 1 - k);
      if(i < j) swap(a[i], a[j]);
    }
    // i : 今考えている多項式の次数 / 2
    for(int i = 1; i < n; i *= 2) {
      ll zeta = modpow(primitive, (mod - 1) / (i * 2), mod);
      if(inv) zeta = modinv(zeta, mod);
      ll tmp = 1;
      // j : 指数
      for(int j = 0; j < i; j++) {
        // k : 何個目の多項式か
        for(int k = 0; k < n; k += i * 2) {
          ll s = a[k + j + 0];
          ll t = a[k + j + i] * tmp % mod;
          a[k + j + 0] = (s + t) % mod;
          a[k + j + i] = (s - t) % mod;
        }
        tmp = tmp * zeta % mod;
      }
    }
    int invn = modinv(n, mod);
    if(inv)
      for(int i = 0; i < n; i++) a[i] = a[i] * invn % mod;
    for(int i = 0; i < n; i++) a[i] = (a[i] + mod) % mod;
    return a;
  }
  template < typename T >
  vector< ll > conv(vector< T > aa, vector< T > bb) {
    int deg = aa.size() + bb.size();
    int n = 1;
    while(n < deg) n <<= 1;
    vector< ll > a(n), b(n);
    for(int i = 0; i < (int) aa.size(); i++) a[i] = aa[i] % mod;
    for(int i = 0; i < (int) bb.size(); i++) b[i] = bb[i] % mod;
    a = fft(a);
    b = fft(b);
    vector< ll > c(n);
    for(int i = 0; i < n; i++) c[i] = a[i] * b[i] % mod;
    return fft(c, 1);
  }
};
/// }}}--- ///

vector< NTT > ntts{
    NTT((1 << 24) * 73 + 1, 3),
    NTT((1 << 21) * 3 * 7 * 23 + 1, 5),
    NTT((1 << 25) * 5 + 1, 3),
    NTT((1 << 26) * 7 + 1, 3),
    NTT((1 << 21) * 3 * 3 * 7 * 7 + 1, 5),
};

/// --- Garner Library {{{ ///
ll garner(const vector< ll > &x, vector< ll > mods, ll mod) {
  mods.emplace_back(mod);
  vector< ll > coeffs(x.size() + 1, 1); // coeffs[i]v_i
  vector< ll > constants(x.size() + 1, 0);
  for(size_t i = 0; i < x.size(); i++) {
    // x[i] - constants[i] == coeffs[i] * v_i (mod mods[i])
    ll v = (x[i] - constants[i]) * modinv(coeffs[i], mods[i]) % mods[i];
    if(v < 0) v += mods[i];
    for(size_t j = i + 1; j < x.size() + 1; j++) {
      // coeffs[j] is (mod mods[j])
      constants[j] = (constants[j] + coeffs[j] * v) % mods[j];
      coeffs[j] = (coeffs[j] * mods[i]) % mods[j];
    }
  }
  return constants.back();
}
/// }}}--- ///

template < class T >
// convolution with NTT {{{
vector< ll > conv(vector< T > a, vector< T > b, int use = 1, ll mod = 1e9 + 7) {
  vector< vector< ll > > cs;
  auto nlist = ntts;
  nlist.resize(use);
  for(auto ntt : nlist) {
    cs.emplace_back(ntt.conv(a, b));
  }
  if(use == 1) return cs[0];
  int n = cs[0].size();
  vector< ll > c(n);
  for(int i = 0; i < n; i++) {
    vector< ll > vals(use), mods(use);
    for(int j = 0; j < use; j++) {
      vals[j] = cs[j][i];
      mods[j] = nlist[j].mod;
    }
    c[i] = garner(vals, mods, mod);
  }
  return c;
}
// }}}
