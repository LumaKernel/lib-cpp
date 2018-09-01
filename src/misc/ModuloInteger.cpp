// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name ModInt Library
// @title Modudo Integer
// @snippet     modint
// require math library
/// --- ModInt Library {{{ ///
template < ll mod = (ll) 1e9 + 7 >
struct ModInt {
  ll val;
  ModInt() : val(0) {}
  ModInt(ll val) : val((val % mod + mod) % mod) {}
  operator int() const { return val; }
  operator ll() const { return val; }
  ModInt operator+(ModInt const &rhs) const { return ModInt(val + rhs.val); }
  ModInt operator-(ModInt const &rhs) const { return ModInt(val - rhs.val); }
  ModInt operator*(ModInt const &rhs) const { return ModInt(val * rhs.val); }
  ModInt operator/(ModInt const &rhs) const { return ModInt(val * rhs.inv().val); }
  ModInt &operator+=(ModInt const &rhs) {
    val = ((val + rhs.val) % mod + mod) % mod;
    return *this;
  }
  ModInt &operator-=(ModInt const &rhs) {
    val = ((val - rhs.val) % mod + mod) % mod;
    return *this;
  }
  ModInt &operator*=(ModInt const &rhs) {
    val = (val * rhs.val % mod + mod) % mod;
    return *this;
  }
  ModInt &operator/=(ModInt const &rhs) {
    val = (val * rhs.inv().val % mod + mod) % mod;
    return *this;
  }
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
  template < typename T >
  ModInt operator+(T const &rhs) const {
    return ModInt(val + rhs % mod);
  }
  template < typename T >
  ModInt operator-(T const &rhs) const {
    return ModInt(val - rhs % mod);
  }
  template < typename T >
  ModInt operator*(T const &rhs) const {
    return ModInt(val * (rhs % mod));
  }
  template < typename T >
  ModInt operator/(T const &rhs) const {
    return ModInt(val * modinv(rhs, mod));
  }
  template < typename T >
  ModInt &operator+=(T const &rhs) {
    val = ((val + rhs % mod) % mod + mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator-=(T const &rhs) {
    val = ((val - rhs % mod) % mod + mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator*=(T const &rhs) {
    val = (val * (rhs % mod) % mod + mod) % mod;
    return *this;
  }
  template < typename T >
  ModInt &operator/=(T const &rhs) {
    val = (val * modinv(rhs, mod) % mod + mod) % mod;
    return *this;
  }
  ModInt inv() const { return ModInt(modinv(val, mod)); }
  friend ostream &operator<<(ostream &os, ModInt const &mv) {
    os << mv.val;
    return os;
  }
  friend constexpr ModInt operator+(ll a, ModInt const &mv) {
    return ModInt(a % mod + mv.val);
  }
  friend constexpr ModInt operator-(ll a, ModInt const &mv) {
    return ModInt(a % mod - mv.val);
  }
  friend constexpr ModInt operator*(ll a, ModInt const &mv) {
    return ModInt(a % mod * mv.val);
  }
  friend constexpr ModInt operator/(ll a, ModInt const &mv) {
    return ModInt(a % mod * mv.inv().val);
  }
};
/// }}}--- ///

using Int = ModInt<>;
