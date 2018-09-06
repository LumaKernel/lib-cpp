// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Modulo Factorial
// @title 階乗の事前計算
// @snippet     fact
// @alias       comb
// WARN : use H with larger N
/// --- Modulo Factorial {{{ ///
template < int N, int mod = (int) 1e9 + 7 >
struct Factorial {
  constexpr ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll d = 0;
    return b == 0 ? (x = 1, y = 0, a)
                  : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
  }
  constexpr ll modinv(ll a) {
    ll x = 0, y = 0;
    extgcd(a, mod, x, y);
    return (x + mod) % mod;
  }
  int arr[N + 1], inv[N + 1];
  ll operator[](int i) const { return arr[i]; }
  constexpr Factorial() : arr(), inv() {
    arr[0] = 1;
    for(int i = 1; i <= N; i++) {
      arr[i] = (ll) i * arr[i - 1] % mod;
    }
    inv[N] = modinv(arr[N]);
    for(int i = N - 1; i >= 0; i--) {
      inv[i] = (ll)(i + 1) * inv[i + 1] % mod;
    }
  }
  ll C(int n, int r) const {
    if(n < 0 || r < 0 || n < r) return 0;
    return (ll) arr[n] * inv[r] % mod * inv[n - r] % mod;
  }
  ll H(int n, int r) const { return C(n + r - 1, r); }
};
/// }}}--- ///

const int N = 1e5 + 10;
constexpr Factorial < N * 2 ?, mod > fact;
