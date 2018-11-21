// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Geometory 3D Library
// @snippet geo3d

// require Geomeotry Library
/// --- Geometory 3D Library {{{ ///
#include <algorithm>
#include <valarray>

inline Scalar dot(const valarray< Scalar > &a, const valarray< Scalar > &b) {
  return (a * b).sum();
}
inline valarray< Scalar > cross(const valarray< Scalar > &a,
                                const valarray< Scalar > &b) {
  return a.cshift(1) * b.cshift(-1) - a.cshift(-1) * b.cshift(1);
}

template < class T >
inline T L1norm(const valarray< T > &a) {
  return abs(a).sum();
}
// L2 norm
template < class T >
inline Float norm(const valarray< T > &a) {
  return sqrt((a * a).sum());
}
template < class T >
inline T LINFnorm(const valarray< T > &a) {
  return abs(a).max();
}
// [0, pi]
Float arg(const valarray< Scalar > &a, const valarray< Scalar > &b) {
  Float val = (Float) dot(a, b) / norm(a) / norm(b);
  return acos(max(min(val, Float(1)), Float(-1)));
}
template < class T >
inline valarray< Float > to_float(const valarray< T > &a) {
  valarray< Float > a2(a.size());
  for(size_t i = 0; i < a.size(); i++) a2[i] = a[i];
  return a2;
}
inline valarray< Float > normalize(const valarray< Float > &a) { return a / norm(a); }

/// }}}--- ///
