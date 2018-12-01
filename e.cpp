// includes {{{
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <tuple>
#include <vector>
// }}}
// #include<bits/stdc++.h>
using namespace std;
using ll = long long;

// when Scalar is float-like, let Float = Scalar
using Scalar = double;
using Float = double;
// EPS
const Scalar EPS = 1e-11;
constexpr Float PI = 3.14159265358979323;
/// --- Geometory Library {{{ ///
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>
using Point = complex< Scalar >;
using Polygon = vector< Point >;
struct Line : public pair< Point, Point > {
  Line(const Point &a, const Point &b) : pair< Point, Point >(a, b) {}
};
struct Segment : public pair< Point, Point > {
  Segment(const Point &a, const Point &b) : pair< Point, Point >(a, b) {}
};
inline Scalar dot(const Point &a, const Point &b) { return real(conj(a) * b); };
inline Scalar cross(const Point &a, const Point &b) { return imag(conj(a) * b); };

// L2 norm
inline Float norm(const Point &a) { return abs(a); }

int sign(Scalar x) {
  if(x < -EPS) return -1;
  if(x > +EPS) return +1;
  return 0;
}

// +1 : a->b->c is ccw
// -1 : a->b->c is cw
// +2 : a--b--c
// -2 : b--c--a
//  0 : b--a--c
int ccw(const Point &a, Point b, Point c) {
  b -= a, c -= a;
  if(cross(b, c) > EPS) return +1;
  if(cross(b, c) < -EPS) return -1;
  if(dot(b, c) < 0) return 0;
  if(norm(b) < norm(c)) return +2;
  return -2;
}

inline complex< Float > to_float(const Point &v) {
  return complex< Float >(v.real(), v.imag());
}

inline complex< Float > normalize(const complex< Float > &v) { return v / norm(v); }

inline complex< Float > normal(const complex< Float > &v) {
  return v * complex< Float >(cos(PI / 2), sin(PI / 2));
}

inline Float mclamp(Float x, Float low, Float high) { return max(min(x, high), low); }

// [0, pi]
Float arg(const Point &a, const Point &b) {
  return acos(mclamp((Float) dot(a, b) / norm(a) / norm(b), -1, 1));
}

// triangle, arg a
template < class T >
Float arg(T a, T b, T c) {
  return mclamp(Float(b * b + c * c - a * a) / (2 * b * c), -1, 1);
}

// Sarrus
template < class T >
Float area3(const complex< T > &a, const complex< T > &b) {
  return (Float) abs(a.real() * b.imag() - a.imag() * b.real()) / 2;
}

// Heron's formula
template < class T >
Float area3(T a, T b, T c) {
  Float s = Float(a + b + c) / 2;
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

inline Float dist(const Point &p, const Point &q) { return norm(p - q); }

inline Float dist(const Line &line, const Point &p) {
  return (Float) cross(p - line.first, line.second - line.first) /
         abs(line.second - line.first);
}

inline Float dist(const Point &p, const Line &line) { return dist(line, p); }

inline Float dist(const Segment &segment, const Point &p) {
  if(sign(dot(segment.first - segment.second, p - segment.second)) *
         sign(dot(segment.second - segment.first, p - segment.first)) >=
     0)
    return dist(Line(segment.first, segment.second), p);
  else
    return min(norm(p - segment.first), norm(p - segment.second));
}

inline Float dist(const Point &p, const Segment &segment) { return dist(segment, p); }

inline Float dist(const Segment &a, const Segment &b) {
  return min({
      dist(a, b.first),
      dist(a, b.second),
      dist(b, a.first),
      dist(b, a.second),
  });
}

inline bool isCrossing(const Segment &a, const Segment &b) {
  return ccw(a.first, a.second, b.first) * ccw(a.first, a.second, b.second) <= 0 &&
         ccw(b.first, b.second, a.first) * ccw(b.first, b.second, a.second) <= 0;
}

inline Point intersection(const Line &a, const Line &b) {
  return a.first +              //
         (a.second - a.first) * //
             cross(a.first - b.first, b.second - b.first) *
             cross(a.first - a.second, b.second - b.first);
}

/// }}}--- ///

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  cout << abs(Point(3, 4)) << endl;
  cout << norm(Point(3, 4)) << endl;
  cout << dist(Point(3, 4), Point(0, 0)) << endl;
  cout << norm(Point(3, 4) - Point(0, 0)) << endl;
  cout << (Point(3, 4) - Point(0, 0)) << endl;
  cout << abs(Point(3, 4) - Point(0, 0)) << endl;
  return 0;
}
