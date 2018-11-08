// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick Library
// @snippet     cht
// @alias       convexhulltrick

// CHT<T, x-increasing?, Comp>()
// - maximize : let Comp = greater<T>
// .add(a, b) : f(x) = ax + b
// - minimize : (a) desc
// - maximize : (a) asc
/// --- Convex Hull Trick Library {{{ ///

#include <vector>
#include <functional>
#include <cassert>
#include <utility>

template < class T = long long, bool xIncreasing = false,
           class Comp = less< T > >
struct CHT {
  static T EPS;
  static Comp comp;

private:
  using Line = pair< T, T >;

public:
  vector< Line > lines;
  // is l2 unnecessary ?
  bool check(Line l1, Line l2, Line l3) {
    if(l2.first == l3.first) return 1;
    // cp(l2, l3).x <= cp(l2, l1).x
    return (l2.first - l1.first) * (l3.second - l2.second) + EPS >=
           (l3.first - l2.first) * (l2.second - l1.second);
  }
  T f(int i, const T &x) { return lines[i].first * x + lines[i].second; }
  void add(const T &a, const T &b) {
    assert("add monotonic" && (lines.empty() || !comp(lines.back().first, a)));
    if(lines.size() && lines.back().first == a && !comp(b, lines.back().second))
      return;
    while((int) lines.size() >= 2 &&
          check(lines[lines.size() - 2], lines.back(), Line(a, b)))
      lines.pop_back();
    lines.emplace_back(a, b);
  }
  T query(const T &x) {
    Line p = get(x);
    return p.first * x + p.second;
  }
  pair< T, T > get(const T &x) {
    assert(lines.size());
    if(xIncreasing) {
      static size_t head = 0;
      if(head >= lines.size()) head = lines.size() - 1;
      while(head + 1 < lines.size() && comp(f(head + 1, x), f(head, x))) head++;
      return lines[head];
    } else {
      int ok = lines.size() - 1, ng = -1;
      while(ok - ng > 1) {
        int mid = (ok + ng) >> 1;
        if(comp(f(mid, x), f(mid + 1, x)))
          ok = mid;
        else
          ng = mid;
      }
      return lines[ok];
    }
  }
};

template < class T, bool xIncreasing, class Comp >
T CHT< T, xIncreasing, Comp >::EPS = 1e-19;

template < class T, bool xIncreasing, class Comp >
Comp CHT< T, xIncreasing, Comp >::comp;

/// }}}--- ///

// @new
// @ Dynamic Convex Hull Trick Library
// @snippet     dynamic_cht
// @alias       cht2 dcht

// DynamicCHT<T, Comp>()
// - maximize : let Comp = greater<T>
// === --- ===
// N = no. of f(x)
// .add(a, b) : f(x) = ax + b : amortized O(log N)
// .query(x) : returns f(x), when f minimize f(x) : O(log N)
// .get(x) : returns f that minimize f(x) as (a, b) : O(log N)
// === --- ===
// f can duplicate
/// --- Dynamic Convex Hull Trick Library {{{ ///

#include <functional>
#include <limits>
#include <set>
#include <utility>

// |ab| < LLONG_MAX/4 ???
template < class T = long long, class Comp = less< T > >
struct DynamicCHT {
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
  DynamicCHT() {
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
  friend ostream &operator<<(ostream &os, const DynamicCHT &a) {
    os << "\n";
    os << "lines : " << a.lines.size() << "\n";
    for(auto &p : a.lines)
      os << "(" << p.a << ", " << p.b << ")"
         << "\n";
    os << "cross points : " << a.cps.size() << "\n";
    for(auto &p : a.cps)
      os << "(x = " << p.numer << "/" << p.denom << "; " << p.p.a << ", "
         << p.p.b << ")"
         << "\n";
    return os;
  }

private:
  // erase cp which can be made from lines [a, b]
  void eraseRange(It a, It b) {
    for(It it = a; it != b; ++it) cps.erase(CP(*it, *next(it)));
  }
  // p1 <= p2 <= p3 , p1 < p3
  // p2 is unnecessary?
  bool check(const Line &p1, const Line &p2, const Line &p3) {
    if(p1.a == p2.a) return 1;
    if(p1.a == INF || p1.a == -INF || p3.a == INF || p3.a == -INF) return 0;
    //  cp(p2, p3).x <= cp(p2, p1).x
    return (p2.a - p1.a) * (p3.b - p2.b) + EPS >= (p2.b - p1.b) * (p3.a - p2.a);
  }
};

template < class T, class Comp >
T DynamicCHT< T, Comp >::INF = numeric_limits< T >::has_infinity
                                   ? numeric_limits< T >::infinity()
                                   : numeric_limits< T >::max();

template < class T, class Comp >
T DynamicCHT< T, Comp >::EPS = 1e-19;

template < class T, class Comp >
Comp DynamicCHT< T, Comp >::comp; // only for less and greater

/// }}}--- ///
