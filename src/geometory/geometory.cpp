// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Geometory Library
// @snippet     geometory
// @alias       geo

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

// @new
// @snippet     circle
// @alias       geo_circle
// @name Geometory Circle Library

// Scalar must be Float
/// --- Geometory Circle Library {{{ ///
// center, radius
using Circle = pair< Point, Scalar >;

// -1 : 0 share (outside)
//  1 : 0 share (B in A)
//  2 : 0 share (A in B)
// -3 : 1 share (outside)
//  3 : 1 share (B in A)
//  4 : 1 share (A in B)
//  0 : 2 share
int cpr(const Circle &a, const Circle &b) {
  Scalar d = norm(a.first - b.first);
  if(a.second + b.second + EPS < d) return -1;
  if(b.second + d + EPS < a.second) return 1;
  if(a.second + d + EPS < b.second) return 2;
  if(abs(a.second + b.second - d) < EPS) return -3;
  if(abs(b.second + d - a.second) < EPS) return 3;
  if(abs(a.second + d - b.second) < EPS) return 4;
  return 0;
}

vector< Point > intersections(const Circle &a, const Circle &b) {
  vector< Point > res;
  // normalize(b-a) * R_A
  Point x = a.second * normalize(b.first - a.first);
  if(abs(cpr(a, b)) >= 3) {
    res.emplace_back(a.first + x);
  } else if(cpr(a, b) == 0) {
    Scalar s = arg(b.second, norm(b.first - a.first), a.second);
    res.emplace_back(a.first + x * Point(cos(s), sin(s)));
    res.emplace_back(a.first + x * Point(cos(-s), sin(-s)));
  }
  return res;
}

vector< Point > intersections(const Circle &a, const Line &line) {
  vector< Point > res;
  Point n = normal(line.first - line.second);
  Point p = intersection(line, Line(a.first, a.first + n));
  Scalar d = norm(a.first - p);
  if(abs(d - a.second) < EPS) {
    res.emplace_back(p);
  } else if(abs(d) < a.second) {
    Scalar len = sqrt(a.second * a.second - d * d);
    Point share = len * normalize(line.first - line.second);
    res.emplace_back(p + share);
    res.emplace_back(p - share);
  }
  return res;
}

inline Scalar area(const Circle &a) { return PI * a.second * a.second; }

Scalar shareArea(Circle a, Circle b) {
  Scalar d = norm(a.first - b.first);
  if(a.second + b.second < d + EPS) return 0;
  if(a.second < b.second) swap(a, b);
  if(b.second + d < a.second + EPS) return area(b);
  Scalar s1 = arg(b.second, a.second, d), s2 = arg(a.second, b.second, d);
  Scalar tri2 =
      (a.second * a.second * sin(s1 * 2) + b.second * b.second * sin(s2 * 2)) / 2;
  return a.second * a.second * s1 + b.second * b.second * s2 - tri2;
}

inline Line ajacentLine(const Circle &c, const Point &p) {
  return Line(p, p + normal(p - c.first));
}

// the tangentLine of c passing p
vector< Line > tangentLines(const Circle &c, const Point &p) {
  vector< Line > res;
  Scalar d = norm(p - c.first);
  if(abs(d - c.second) < EPS)
    res.emplace_back(ajacentLine(c, p));
  else if(c.second < d) {
    Point a = c.first + c.second * normalize(p - c.first);
    vector< Point > b = intersections(
        Circle(c.first, norm(c.first - p)), Line(a, a + normal(c.first - p)));
    for(size_t i = 0; i < b.size(); i++) {
      res.emplace_back(p, c.first + c.second * normalize(b[i] - c.first));
    }
  }
  return res;
}

vector< Line > commonTangentLines(Circle a, Circle b) {
  vector< Line > res;
  if(a.second + EPS < b.second) swap(a, b);
  if(norm(a.first - b.first) < EPS) return res;

  Point p = a.first + (b.first - a.first) * a.second / (a.second + b.second);
  if(norm(a.first - p) + EPS > a.second) res = tangentLines(a, p);
  if(abs(a.second - b.second) < EPS) {
    Point n = normal(normalize(b.first - a.first) * a.second);
    res.emplace_back(a.first + n, b.first + n);
    res.emplace_back(a.first - n, b.first - n);
  } else {
    Point q = a.first + (b.first - a.first) * a.second / (a.second - b.second);
    if(abs(a.first - q) + EPS > a.second) {
      vector< Line > tmp = tangentLines(a, q);
      res.insert(begin(res), begin(tmp), end(tmp));
    }
  }
  return res;
}

/// }}}--- ///

// @new
// @snippet     polygon
// @alias       geo_polygon caliper
// @name Geometory Polygon Library

/// --- Geometory Polygon Library {{{ ///
// ok for either ccw or cw
Scalar area(const Polygon &poly) {
  if(poly.size() < 3) return 0;
  Scalar res = cross(poly[poly.size() - 1], poly[0]);
  for(size_t i = 0; i < poly.size() - 1; i++) {
    res += cross(poly[i], poly[i + 1]);
  }
  return abs(res) / 2;
}

//  0 : outside
//  1 : inside
// -1 : on vertex
// -2 : on line
int inside(const Polygon &poly, const Point &p) {
  int cnt = 0;
  for(size_t i = 0; i < poly.size(); i++) {
    size_t ii = i, jj = (i + 1) % poly.size();
    if(norm(poly[i] - p) < EPS) return -1;
    if(poly[ii].imag() > poly[jj].imag()) swap(ii, jj);
    if(poly[ii].imag() - EPS < p.imag() && p.imag() < poly[jj].imag() + EPS) {
      if(abs(poly[ii].imag() - poly[jj].imag()) < EPS) { // parallel
        if(poly[ii].real() > poly[jj].real()) swap(ii, jj);
        if(poly[ii].real() - EPS < p.real() && p.real() < poly[jj].real() + EPS)
          return -2;
      } else {
        Point q = intersection(Line(poly[ii], poly[jj]), Line(p, p + Point(1, 0)));
        if(p.real() < q.real() && p.imag() > poly[ii].imag() + EPS)
          cnt++; // count only upside
      }
    }
  }
  return cnt & 1;
}

// param ccwConvex must be ccw and convex
Scalar caliper(const Polygon &ccwConvex) {
  constexpr auto comp = [](Point a, Point b) {
    return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();
  };
  size_t i, j;
  for(size_t k = 0; k < ccwConvex.size(); k++) {
    if(comp(ccwConvex[i], ccwConvex[k])) j = k;
    if(!comp(ccwConvex[j], ccwConvex[k])) i = k;
  }
  Scalar res = 0;
  size_t si = i, sj = j;
  while(i != si || j != sj) {
    res = max(res, norm(ccwConvex[i] - ccwConvex[j]));
    if(cross(ccwConvex[(i + 1) % ccwConvex.size()] - ccwConvex[i],
             ccwConvex[(j + 1) % ccwConvex.size()] - ccwConvex[j]) < 0)
      i = (i + 1) % ccwConvex.size();
    else
      j = (j + 1) % ccwConvex.size();
  }
  return res;
}
/// }}}--- ///

// @new TEST-GEOMETORY
#include <cassert>
#include <iostream>
// TODO : いずれremoveに変える
int main() {
  assert(cross(Point(0, 1) + Point(2, 3), Point(1, 1) + Point(2, 3)) == -4);
  cout << "ok" << endl;
}
