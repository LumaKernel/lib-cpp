// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick Extended Library
// @snippet     chtex
// @alias       cht2 dcht dynamic_cht

// CHTEx<T, Comp>()
// - maximize : let Comp = greater<T>
// === --- ===
// N = no. of f(x)
// .add(a, b) : f(x) = ax + b : amortized O(log N)
// .query(x) : returns f(x), when f minimize f(x) : O(log N)
// .get(x) : returns f that minimize f(x) as (a, b) : O(log N)
// === --- ===
// f can duplicate
/// --- Convex Hull Trick Extended Library {{{ ///

#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <utility>

// |ab| < LLONG_MAX/4 ???
template < class T = long long, class Comp = less< T > >
struct CHTEx {
  static T INF;
  static T EPS;
  static Comp comp;

private:
  struct Line { // ax + b
    T a, b;
    Line(const T &a, const T &b) : a(a), b(b) {}
    bool operator<(const Line &rhs) const { // (a, b)
      return a != rhs.a ? comp(rhs.a, a) : comp(b, rhs.b);
    }
  };
  struct CP {
    T numer, denom; // x-coordinate; denom is non-negative for comparison
    Line p;
    CP(const T &n) : numer(n), denom(1), p(0, 0) {}
    // p1 < p2
    CP(const Line &p1, const Line &p2) : p(p2) {
      if(p1.a == INF || p1.a == -INF)
        numer = -INF, denom = 1;
      else if(p2.a == INF || p2.a == -INF)
        numer = INF, denom = 1;
      else {
        numer = p1.b - p2.b, denom = p2.a - p1.a;
        if(denom < 0) numer = -numer, denom = -denom;
      }
    }
    bool operator<(const CP &rhs) const {
      if(numer == INF || rhs.numer == -INF) return 0;
      if(numer == -INF || rhs.numer == INF) return 1;
      return numer * rhs.denom < rhs.numer * denom;
    }
  };
  set< Line > lines;
  set< CP > cps;
  typedef typename set< Line >::iterator It;

public:
  CHTEx() {
    // sentinel
    lines.insert({Line(INF, 0), Line(-INF, 0)});
    cps.insert(CP(Line(INF, 0), Line(-INF, 0)));
  }
  void add(const T &a, const T &b) {
    const Line p(a, b);
    It pos = lines.insert(p).first;
    if(check(*prev(pos), p, *next(pos))) {
      // ax + b is unnecessary
      lines.erase(pos);
      return;
    }
    cps.erase(CP(*prev(pos), *next(pos)));
    {
      It it = prev(pos);
      while(it != lines.begin() && check(*prev(it), *it, p)) --it;
      // lines (it, pos) is unnecessary
      // [it, pos - 1] : [pos - 1, pos] is still not added
      eraseRange(it, prev(pos));
      // [it + 1, pos - 1]
      lines.erase(++it, pos);
      pos = lines.find(p);
    }
    {
      It it = next(pos);
      while(next(it) != lines.end() && check(p, *it, *next(it))) ++it;
      // lines (pos, it) is unnecessary
      // [pos + 1, it] : [pos, pos + 1] is still not added
      eraseRange(++pos, it);
      // [pos + 1, it - 1]
      lines.erase(pos, it);
      pos = lines.find(p);
    }
    cps.insert(CP(*prev(pos), *pos));
    cps.insert(CP(*pos, *next(pos)));
  }
  T query(const T &x) const {
    pair< T, T > p = get(x);
    return p.first * x + p.second;
  }
  pair< T, T > get(const T &x) const {
    const Line &p = (--cps.lower_bound(CP(x)))->p;
    return make_pair(p.a, p.b);
  }
  friend ostream &operator<<(ostream &os, const CHTEx &a) {
    os << "\n";
    os << "lines : " << a.lines.size() << "\n";
    for(auto &p : a.lines)
      os << "(" << p.a << ", " << p.b << ")"
         << "\n";
    os << "cross points : " << a.cps.size() << "\n";
    for(auto &p : a.cps)
      os << "(x = " << p.numer << "/" << p.denom << "; " << p.p.a << ", " << p.p.b << ")"
         << "\n";
    return os;
  }

private:
  // erase cp which can be made from lines [a, b]
  void eraseRange(It a, It b) {
    for(It it = a; it != b; ++it) cps.erase(CP(*it, *next(it)));
  }
  // p2 is unnecessary?
  bool check(const Line &p1, const Line &p2, const Line &p3) {
    if(p1.a == p2.a) return 1;
    if(p1.a == INF || p1.a == -INF || p3.a == INF || p3.a == -INF) return 0;
    //  cp(p2, p3).x <= cp(p2, p1).x
    return (p2.a - p1.a) * (p3.b - p2.b) + EPS >= (p2.b - p1.b) * (p3.a - p2.a);
  }
};

template < class T, class Comp >
T CHTEx< T, Comp >::INF = numeric_limits< T >::has_infinity
                              ? numeric_limits< T >::infinity()
                              : numeric_limits< T >::max();

template < class T, class Comp >
T CHTEx< T, Comp >::EPS = 1e-19;

template < class T, class Comp >
Comp CHTEx< T, Comp >::comp; // only for less and greater

/// }}}--- ///
