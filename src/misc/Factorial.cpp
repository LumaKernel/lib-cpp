// @name Modulo Factorial
// @snippet     fact
// @alias       comb

// NOTE : use H with larger N
/// --- Modulo Factorial {{{ ///
#include <cassert>
#include <cstddef>
template < std::size_t N, int mod = static_cast< int >(1e9 + 7) >
struct Factorial {
  using integer = long long;
  constexpr integer extgcd(integer a, integer b, integer &x, integer &y) {
    integer d = 0;
    return b == 0 ? (x = a < 0 ? -1 : 1, y = 0, a < 0 ? -a : a)
                  : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
  }
  constexpr integer modinv(integer a) {
    integer x = 0, y = 0;
    extgcd(a, mod, x, y);
    if(x < 0)
      x += mod;
    else if(x == mod)
      x = 0;
    return x;
  }
  int arr[N + 1], inv[N + 1];
  integer operator[](int i) const { return arr[i]; }
  Factorial() : arr(), inv() {
    arr[0] = 1;
    for(std::size_t i = 1; i <= N; i++) {
      arr[i] = (integer) i * arr[i - 1] % mod;
    }
    inv[N] = modinv(arr[N]);
    for(int i = N - 1; i >= 0; i--) {
      inv[i] = (integer)(i + 1) * inv[i + 1] % mod;
    }
  }
  integer C(int n, int r) const {
    if(n < 0 || r < 0 || n < r) return 0;
    assert(n <= N);
    return (integer) arr[n] * inv[r] % mod * inv[n - r] % mod;
  }
  integer H(int n, int r) const { return C(n + r - 1, r); }
};
/// }}}--- ///

constexpr int mod = 1e9 + 7;
const int N = 1e5 + 10;
Factorial< N * 2, mod > fact;
