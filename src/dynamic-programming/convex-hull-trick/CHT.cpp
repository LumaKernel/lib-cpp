// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick Library
// @snippet     cht
// @alias       convexhulltrick

// CHT<T, x-increasing?, Comp>
// - maximize : let Comp = greater<T>
// .add(a, b) : f(x) = ax + b
// - minimize : (a) desc
// - maximize : (a) asc
/// --- Convex Hull Trick Library {{{ ///

#include <cassert>
#include <functional>
#include <utility>
#include <vector>

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
