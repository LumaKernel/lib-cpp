// @ Modulo Integer
// @snippet modint

/// --- Modulo Integer {{{ ///
#include <ostream>
template < long long mod = static_cast< long long >(1e9 + 7) >
struct ModuloInteger {
  static_assert(mod > 0, "mod must be positive");
  static_assert(mod <= 3037000499, "mod is too big");
  using integer = long long;
  static ModuloInteger unused;
  // math {{{
  static inline integer extgcd(integer a, integer b, integer &x, integer &y) {
    integer d;
    return b == 0 ? (x = a < 0 ? -1 : 1, y = 0, a < 0 ? -a : a)
                  : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
  }
  static inline integer modinv(integer a) {
    integer x = 0, y = 0;
    extgcd(a, mod, x, y);
    if(x < 0)
      x += mod;
    else if(x == mod)
      x = 0;
    return x;
  }
  static inline integer modpow(integer a, long long b) {
    if(b < 0) b = -b, a = modinv(a);
    integer r = 1;
    a %= mod;
    while(b) {
      if(b & 1) r = r * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return r;
  }
  // }}}

  integer val;
  constexpr ModuloInteger() : val(0) {}
  constexpr ModuloInteger(integer t) {
    val = t % mod;
    if(val < 0) val += mod;
  }

private:
  // strict constructor
  constexpr ModuloInteger(integer t, int) : val(t) {}

public:
  template < class T >
  explicit operator T() {
    return T(val);
  }
  // operator bool() { return bool(val); }
  // ModuloInteger <arithmetic-operator>[=] ModuloInteger {{{
  ModuloInteger operator+(ModuloInteger const &rhs) const {
    ModuloInteger tmp = *this;
    tmp += rhs;
    return tmp;
  }
  ModuloInteger operator-(ModuloInteger const &rhs) const {
    ModuloInteger tmp = *this;
    tmp -= rhs;
    return tmp;
  }
  ModuloInteger operator*(ModuloInteger const &rhs) const {
    ModuloInteger tmp = *this;
    tmp *= rhs;
    return tmp;
  }
  ModuloInteger operator/(ModuloInteger const &rhs) const {
    ModuloInteger tmp = *this;
    tmp /= rhs;
    return tmp;
  }
  ModuloInteger &operator+=(ModuloInteger const &rhs) {
    val = val + rhs.val;
    if(val >= mod) val -= mod;
    return *this;
  }
  ModuloInteger &operator-=(ModuloInteger const &rhs) { return *this += -rhs; }
  ModuloInteger &operator*=(ModuloInteger const &rhs) {
    val = val * rhs.val % mod;
    return *this;
  }
  ModuloInteger &operator/=(ModuloInteger const &rhs) { return *this *= rhs.inv(); }
  // }}}
  // increment, decrement {{{
  ModuloInteger operator++(int) {
    ModuloInteger tmp = *this;
    val = val + 1;
    if(val >= mod) val = 0;
    return tmp;
  }
  ModuloInteger operator--(int) {
    ModuloInteger tmp = *this;
    val = val == 0 ? mod - 1 : val - 1;
    return tmp;
  }
  ModuloInteger &operator++() {
    val = val + 1;
    if(val >= mod) val = 0;
    return *this;
  }
  ModuloInteger &operator--() {
    val = val == 0 ? mod - 1 : val - 1;
    return *this;
  }
  // }}}
  ModuloInteger operator-() const { return ModuloInteger(val == 0 ? 0 : mod - val, 0); }
  // ModuloInteger <arithmetic-operator>[=] T {{{
  template < typename T >
  ModuloInteger operator+(T const &rhs) const {
    return ModuloInteger(val + rhs % mod);
  }
  template < typename T >
  ModuloInteger operator-(T const &rhs) const {
    return ModuloInteger(mod + val - rhs % mod);
  }
  template < typename T >
  ModuloInteger operator*(T const &rhs) const {
    return ModuloInteger(val * (rhs % mod));
  }
  template < typename T >
  ModuloInteger operator/(T const &rhs) const {
    return ModuloInteger(val * modinv(rhs));
  }
  template < typename T >
  ModuloInteger &operator+=(T const &rhs) {
    val = (mod + val + rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModuloInteger &operator-=(T const &rhs) {
    val = (mod + val - rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModuloInteger &operator*=(T const &rhs) {
    val = val * (mod + rhs % mod) % mod;
    return *this;
  }
  template < typename T >
  ModuloInteger &operator/=(T const &rhs) {
    val = val * modinv(rhs) % mod;
    return *this;
  }
  // }}}
  ModuloInteger inv() const { return ModuloInteger(modinv(val), 0); }
  ModuloInteger operator~() const { return inv(); }
  friend std::ostream &operator<<(std::ostream &os, ModuloInteger const &mv) {
    os << mv.val;
    return os;
  }
  // equality operator {{{
  ModuloInteger operator==(const ModuloInteger &a) const { return val == a.val; }
  ModuloInteger operator!=(const ModuloInteger &a) const { return val != a.val; }
  ModuloInteger operator==(const integer &a) const { return val == ModuloInteger(a); }
  ModuloInteger operator!=(const integer &a) const { return val != ModuloInteger(a); }
  // }}}
  // T <arithmetic-operator> ModuloInteger {{{
  friend constexpr ModuloInteger operator+(integer a, ModuloInteger const &mv) {
    return ModuloInteger(a % mod + mv.val);
  }
  friend constexpr ModuloInteger operator-(integer a, ModuloInteger const &mv) {
    return ModuloInteger(a % mod - mv.val);
  }
  friend constexpr ModuloInteger operator*(integer a, ModuloInteger const &mv) {
    return ModuloInteger((mod + a % mod) * mv.val % mod, 0);
  }
  friend constexpr ModuloInteger operator/(integer a, ModuloInteger const &mv) {
    return ModuloInteger((mod + a % mod) * modinv(mv.val) % mod, 0);
  }
  // }}}
  // power {{{
  ModuloInteger operator^(integer x) const { return pow(*this, x); }
  ModuloInteger &operator^=(integer x) {
    val = modpow(val, x);
    return *this;
  }
  friend ModuloInteger pow(ModuloInteger x, integer y) {
    return ModuloInteger(modpow(x.val, y), 0);
  }
  // }}}
};
template < long long mod >
ModuloInteger< mod > ModuloInteger< mod >::unused(mod, 0);
/// }}}--- ///

using modint = ModuloInteger<>;
