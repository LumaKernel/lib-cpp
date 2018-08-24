// @import header
// @@
// @name Modulo Factorial
// @title 階乗の事前計算
// @snippet     fact
// @alias       comb
/// --- Modulo Factorial {{{ ///
template<int N, int mod = (int) 1e9 + 7>
struct Factorial {
  int arr[N+1], inv[N+1];
  long long operator[](int i) const { return arr[i]; }
  constexpr Factorial(): arr(), inv() {
    arr[0] = 1;
    for(int i = 1; i <= N; i++) {
      arr[i] = (long long) i * arr[i - 1] % mod;
    }
    inv[N] = modinv(arr[N], mod);
    for(int i = N-1; i >= 0; i--) {
      inv[i] = (long long) (i + 1) * inv[i + 1] % mod;
    }
  }
  long long C(int n, int r) const {
    if(n < 0 || r < 0 || n < r) return 0;
    return (long long) arr[n] * inv[r] % mod * inv[n - r] % mod;
  }
  long long H(int n, int r) const {
    return C(n + r - 1, r);
  }
};
/// }}}--- ///
  
// constexpr int N = 1e5 + 10;
// constexpr Factorial<N, mod> fact;
