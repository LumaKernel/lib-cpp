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
// .add(a, b, id?) : f(x) = ax + b
// - minimize : (a) desc
// - maximize : (a) asc
// .query(x)
// .get(x) : line
// line.id
// line.calc(x)
/// --- Convex Hull Trick Library {{{ ///
#include <cassert>
#include <functional>
#include <utility>
#include <vector>
template < class T = long long, bool xIncreasing = false, class Comp = less< T >,
           class D = T >
struct CHT {
  static T EPS;
  static Comp comp;

private:
  struct Line : pair< T, T > {
    int id;
    Line(T a, T b, int id = 0) : pair< T, T >(a, b), id(id) {}
    T calc(const T &x) { return x * pair< T, T >::first + pair< T, T >::second; }
  };

public:
  vector< Line > lines;
  // is l2 unnecessary ?
  bool check(Line l1, Line l2, Line l3) {
    if(l2.first == l3.first) return 1;
    // cp(l2, l3).x <= cp(l2, l1).x
    return (D)(l2.first - l1.first) * (l3.second - l2.second) + EPS >=
           (D)(l3.first - l2.first) * (l2.second - l1.second);
  }
  T f(int i, const T &x) { return lines[i].first * x + lines[i].second; }
  void add(const T &a, const T &b, int id = 0) {
    assert("add monotonically" && (lines.empty() || !comp(lines.back().first, a)));
    if(lines.size() && lines.back().first == a && !comp(b, lines.back().second)) return;
    Line line(a, b, id);
    while((int) lines.size() >= 2 && check(lines[lines.size() - 2], lines.back(), line))
      lines.pop_back();
    lines.push_back(line);
  }
  T query(const T &x) { return get(x).calc(x); }

private:
  size_t head = 0;
  bool used = false;
  T last;

public:
  Line get(const T &x) {
    assert(lines.size());
    if(xIncreasing) {
      assert("query increasingly!" && (!used || last <= x));
      used = true;
      last = x;
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
  void clear() {
    head = 0;
    used = false;
    lines.clear();
  }
};

template < class T, bool xIncreasing, class Comp, class D >
T CHT< T, xIncreasing, Comp, D >::EPS = 1e-19;

template < class T, bool xIncreasing, class Comp, class D >
Comp CHT< T, xIncreasing, Comp, D >::comp;

/// }}}--- ///
