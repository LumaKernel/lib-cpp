// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name ModInt Library
// @snippet modint

/// --- ModInt Library {{{ ///
#include <ostream>
template < ll mod = (ll) 1e9 + 7 >
struct ModInt {
  // math {{{
  static inline ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll d;
    return b == 0 ? (x = a < 0 ? -1 : 1, y = 0, a < 0 ? -a : a)
                  : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
  }
  static inline ll modinv(ll a) {
    ll x = 0, y = 0;
    extgcd(a, mod, x, y);
    if(x < 0) x += mod;
    return x;
  }
  static inline ll modpow(ll a, ll b) {
    if(b < 0) b = -b, a = modinv(a);
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

  ll val;
  constexpr ModInt() : val(0) {}
  constexpr ModInt(ll t) {
    val = t % mod;
    if(val < 0) val += mod;
  }

private:
  // strict constructor
  constexpr ModInt(ll t, int) : val(t) {}

public:
  template < class T >
  explicit operator T() {
    return T(val);
  }
  // ModInt <arithmetic-operator>[=] ModInt {{{
  ModInt operator+(ModInt const &rhs) const {
    ModInt tmp = *this;
    tmp += rhs;
    return tmp;
  }
  ModInt operator-(ModInt const &rhs) const {
    ModInt tmp = *this;
    tmp -= rhs;
    return tmp;
  }
  ModInt operator*(ModInt const &rhs) const {
    ModInt tmp = *this;
    tmp *= rhs;
    return tmp;
  }
  ModInt operator/(ModInt const &rhs) const {
    ModInt tmp = *this;
    tmp /= rhs;
    return tmp;
  }
  ModInt &operator+=(ModInt const &rhs) {
    val = val + rhs.val;
    if(val >= mod) val -= mod;
    return *this;
  }
  ModInt &operator-=(ModInt const &rhs) { return *this += -rhs; }
  ModInt &operator*=(ModInt const &rhs) {
    val = val * rhs.val % mod;
    return *this;
  }
  ModInt &operator/=(ModInt const &rhs) { return *this *= rhs.inv(); }
  // }}}
  // increment, decrement {{{
  ModInt operator++(int) {
    ModInt tmp = *this;
    val = val + 1;
    if(val >= mod) val = 0;
    return tmp;
  }
  ModInt operator--(int) {
    ModInt tmp = *this;
    val = val == 0 ? mod - 1 : val - 1;
    return tmp;
  }
  ModInt &operator++() {
    val = val + 1;
    if(val >= mod) val = 0;
    return *this;
  }
  ModInt &operator--() {
    val = val == 0 ? mod - 1 : val - 1;
    return *this;
  }
  // }}}
  ModInt operator-() const { return ModInt(val == 0 ? 0 : mod - val, 0); }
  // ModInt <arithmetic-operator>[=] T {{{
  template < typename T >
  ModInt operator+(T const &rhs) const {
    return ModInt(val + rhs % mod);
  }
  template < typename T >
  ModInt operator-(T const &rhs) const {
    return ModInt(mod + val - rhs % mod);
  }
  template < typename T >
  ModInt operator*(T const &rhs) const {
    return ModInt(val * (rhs % mod));
  }
  template < typename T >
  ModInt operator/(T const &rhs) const {
    return ModInt(val * modinv(rhs));
  }
  template < typename T >
  ModInt &operator+=(T const &rhs) {
    val = (mod + val + rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator-=(T const &rhs) {
    val = (mod + val - rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator*=(T const &rhs) {
    val = val * (mod + rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator/=(T const &rhs) {
    val = val * modinv(rhs, mod) % mod;
    return *this;
  }
  // }}}
  ModInt inv() const { return ModInt(modinv(val), 0); }
  ModInt operator~() const { return inv(); }
  friend ostream &operator<<(ostream &os, ModInt const &mv) {
    os << mv.val;
    return os;
  }
  // equality operator {{{
  ModInt operator==(const ModInt &a) const { return val == a.val; }
  ModInt operator!=(const ModInt &a) const { return val != a.val; }
  ModInt operator==(const ll &a) const { return val == ModInt(a); }
  ModInt operator!=(const ll &a) const { return val != ModInt(a); }
  // }}}
  // T <arithmetic-operator> ModInt {{{
  friend constexpr ModInt operator+(ll a, ModInt const &mv) {
    return ModInt(a % mod + mv.val);
  }
  friend constexpr ModInt operator-(ll a, ModInt const &mv) {
    return ModInt(a % mod - mv.val);
  }
  friend constexpr ModInt operator*(ll a, ModInt const &mv) {
    return ModInt((mod + a % mod) * mv.val % mod, 0);
  }
  friend constexpr ModInt operator/(ll a, ModInt const &mv) {
    return ModInt((mod + a % mod) * modinv(mv.val) % mod, 0);
  }
  // }}}
  // power {{{
  ModInt operator^(ll x) const { return pow(*this, x); }
  ModInt &operator^=(ll x) {
    val = modpow(val, x);
    return *this;
  }
  friend ModInt pow(ModInt x, ll y) { return ModInt(modpow(x.val, y), 0); }
  // }}}
};
/// }}}--- ///

using modint = ModInt<>;
