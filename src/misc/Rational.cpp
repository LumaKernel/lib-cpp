// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Rational Library
// @snippet rational
// @alias fraction

/// --- Rational Library {{{ ///
#include <iostream>
#include <utility>
template < class Integer = long long >
struct Rational {
  static Integer gcd(Integer a, Integer b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    Integer res = 1;
    while(a != b) {
      if(a < b) swap(a, b);
      if(b == 0) break;
      if(!(a % 2) && !(b % 2))
        res *= 2, a /= 2, b /= 2;
      else if(!(a % 2))
        a /= 2;
      else if(!(b % 2))
        b /= 2;
      else
        a = (a - b) / 2;
    }
    return res * a;
  }
  Integer numer, denom;
  Rational(Integer numer = 0) : numer(numer), denom(1) {}
  Rational(Integer numer, Integer denom) : numer(numer), denom(denom) { reduce(); }

private:
  Rational(Integer numer, Integer denom, int) : numer(numer), denom(denom) {}

public:
  void reduce() {
    assert(denom != 0);
    Integer g = gcd(numer, denom);
    numer /= g, denom /= g;
    if(denom < 0) numer = -numer, denom = -denom;
  }
  template < class T >
  explicit operator T() {
    return T(T(numer) / T(denom));
  }
  Rational operator+() const { return *this; }
  Rational operator-() const { return Rational(-numer, denom, 0); }
  // Rational <arithmetic operator> Rational {{{
  Rational operator+(const Rational &a) const {
    return Rational(a.numer * denom + numer * a.denom, denom * a.denom);
  }
  Rational operator-(const Rational &a) const { return *this + -a; }
  Rational operator*(const Rational &a) const {
    return Rational(numer * a.numer, denom * a.denom);
  }
  Rational operator/(const Rational &a) const {
    return Rational(numer * a.denom, denom * a.numer);
  }
  Rational &operator+=(const Rational &a) {
    *this = *this + a;
    return *this;
  }
  Rational &operator-=(const Rational &a) {
    *this = *this - a;
    return *this;
  }
  Rational &operator*=(const Rational &a) {
    *this = *this * a;
    return *this;
  }
  Rational &operator/=(const Rational &a) {
    *this = *this / a;
    return *this;
  }
  // }}}
  // Rational <arithmetic operator> Integer {{{
  Rational operator+(Integer a) const { return *this + Rational(a); }
  Rational operator-(Integer a) const { return *this + Rational(-a); }
  Rational operator*(Integer a) const { return *this * Rational(a); }
  Rational operator/(Integer a) const { return *this * Rational(1, a, 0); }
  Rational &operator+=(Integer a) {
    *this = *this + a;
    return *this;
  }
  Rational &operator-=(Integer a) {
    *this = *this - a;
    return *this;
  }
  Rational &operator*=(Integer a) {
    *this = *this * a;
    return *this;
  }
  Rational &operator/=(Integer a) {
    *this = *this / a;
    return *this;
  }
  // }}}
  Rational inverse() const {
    assert(numer != 0);
    return Rational(denom, numer);
  }
  /// Rational <comparison operator> Rational {{{
  bool operator==(const Rational &a) const {
    return numer == a.numer && denom == a.denom;
  }
  bool operator<(const Rational &a) const { return numer * a.denom < a.numer * denom; }
  bool operator!=(const Rational &a) const { return rel_ops::operator!=(*this, a); }
  bool operator>(const Rational &a) const { return rel_ops::operator>(*this, a); }
  bool operator<=(const Rational &a) const { return rel_ops::operator<=(*this, a); }
  bool operator>=(const Rational &a) const { return rel_ops::operator>=(*this, a); }
  // }}}
  /// Rational <comparison operator> Integer {{{
  bool operator==(Integer a) const { return *this == Rational(a); }
  bool operator<(Integer a) const { return *this < Rational(a); }
  bool operator!=(Integer a) const { return *this != Rational(a); }
  bool operator>(Integer a) const { return *this > Rational(a); }
  bool operator<=(Integer a) const { return *this <= Rational(a); }
  bool operator>=(Integer a) const { return *this >= Rational(a); }
  // }}}
  friend ostream &operator<<(ostream &os, const Rational &a) {
    os << a.numer << "/" << a.denom;
    return os;
  }
  Integer bunsi() const { return numer; }
  Integer bunbo() const { return denom; }
};
/// }}}--- ///
using rational = Rational<>;
