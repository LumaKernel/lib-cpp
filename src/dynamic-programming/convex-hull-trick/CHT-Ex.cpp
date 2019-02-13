// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick Extended
// @snippet     chtex
// @alias       cht2 dcht dynamic_cht convexhulltrick_ex

// CHTEx<T, Comp>()
// - maximize : let Comp = greater<T>
// === --- ===
// N = no. of f(x)
// .add(a, b, id?) : f(x) = ax + b : amortized O(log N)
// .query(x) : returns f(x), when f minimize f(x) : O(log N)
// .get(x) : line : O(log N)
// line.a, line.b, line.id
// line.calc(x)
// === --- ===
// f can duplicate
/// --- Convex Hull Trick Extended {{{ ///
#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <utility>

template < class T = long long, class Comp = less< T >, class D = T >
struct CHTEx {
  static T INF;
  static T EPS;
  static Comp comp;

private:
  struct Line { // ax + b
    T a, b;
    int id;
    Line(const T &a, const T &b, int id = 0) : a(a), b(b), id(id) {}
    bool operator<(const Line &rhs) const { // (a, b)
      return a != rhs.a ? comp(rhs.a, a) : comp(b, rhs.b);
    }
    T calc(const T &x) { return a * x + b; }
    friend ostream& operator<<(ostream& os, const Line& line) {
      os << "(" << line.a << ", " << line.b;
      return os;
    }
  };
  struct CP {
    T numer, denom; // x-coordinate; denom is non-negative for comparison
    Line p;
    CP(const T &n) : numer(n), denom(1), p(T(0), T(0)) {}
    // p1 < p2
    CP(const Line &p1, const Line &p2) : p(p2) {
      if(p1.a == INF || p1.a == -INF)
        numer = -INF, denom = T(1);
      else if(p2.a == INF || p2.a == -INF)
        numer = INF, denom = T(1);
      else {
        numer = p1.b - p2.b, denom = p2.a - p1.a;
        if(denom < 0) numer = -numer, denom = -denom;
      }
    }
    bool operator<(const CP &rhs) const {
      if(numer == INF || rhs.numer == -INF) return false;
      if(numer == -INF || rhs.numer == INF) return true;
      return (D) numer * rhs.denom < (D) rhs.numer * denom;
    }
  };
  set< Line > lines;
  set< CP > cps;
  typedef typename set< Line >::iterator It;

public:
  CHTEx() { clear(); }
  void add(const T &a, const T &b, int id = 0) {
    const Line p(a, b, id);
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
  T query(const T &x) const { return get(x).calc(x); }
  Line get(const T &x) const {
    assert(cps.size());
    return (--cps.lower_bound(CP(x)))->p;
  }
  void clear() {
    cps.clear();
    lines.clear();

    // sentinel
    lines.insert({Line(INF, 0), Line(-INF, 0)});
    cps.insert(CP(Line(INF, 0), Line(-INF, 0)));
  }
  friend ostream &operator<<(ostream &os, const CHTEx &a) {
    os << "CHT-Ex\n";
    os << a.lines.size() << "lines\n";
    for(auto &p : a.lines)
      os << p << "\n";
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
    return (D)(p2.a - p1.a) * (p3.b - p2.b) + EPS >= (D)(p2.b - p1.b) * (p3.a - p2.a);
  }
};

template < class T, class Comp, class D >
T CHTEx< T, Comp, D >::INF = numeric_limits< T >::has_infinity
                                 ? numeric_limits< T >::infinity()
                                 : numeric_limits< T >::max();

template < class T, class Comp, class D >
T CHTEx< T, Comp, D >::EPS = 1e-19;

template < class T, class Comp, class D >
Comp CHTEx< T, Comp, D >::comp; // only for less or greater
/// }}}--- ///
