// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick
// @snippet     cht
// @alias       convexhulltrick

// CHT<a-increasing, T, x-type = 0, is-minimize = true>
// maximatoin : let is-minimize = true
// x-type : [0 : random, +1 : asc, -1 : desc]
// .add(a, b, id?) : f(x) = ax + b
// .query(x)
// .get(x) : line
// line.a, line.b, line.id
// line.calc(x)
/// --- Convex Hull Trick {{{ ///
#include <cassert>
#include <functional>
#include <ostream>
#include <utility>
#include <vector>
template < bool aIncreasing, class T = long long, int xType = 0, bool isMinimize = true,
           class D = T >
struct CHT {
  static_assert(xType == 0 || xType == 1 || xType == -1, "xType must be in {0, +1, -1}");
  static T EPS;
  constexpr static bool headIncreasing = aIncreasing ^ (xType == -1) ^ isMinimize;

private:
  // a is better
  static inline bool comp(const T &a, const T &b) {
    if(isMinimize)
      return a < b;
    else
      return a > b;
  }

  static inline bool comp2(const D &a, const D &b) {
    if(isMinimize ^ aIncreasing)
      return a < b;
    else
      return a > b;
  }

  struct Line {
    T a, b;
    int id;
    Line(T a, T b, int id = 0) : a(a), b(b), id(id) {}
    T calc(const T &x) { return x * a + b; }
    friend ostream &operator<<(ostream &os, Line line) {
      os << "(" << line.a << ", " << line.b << ")";
      return os;
    }
  };

public:
  vector< Line > lines;
  // is l2 unnecessary ?
  bool check(Line l1, Line l2, Line l3) {
    if(l2.a == l3.a) return 1;
    // cp(l2, l3).x <= cp(l2, l1).x
    return !comp2(
        (D)(l2.a - l1.a) * (l3.b - l2.b) + D(EPS), (D)(l3.a - l2.a) * (l2.b - l1.b));
  }

  T f(int i, const T &x) { return lines[i].a * x + lines[i].b; }
  void add(const T &a, const T &b, int id = 0) {
    if(aIncreasing) {
      assert("add a-asc" && (lines.empty() || !(a < lines.back().a)));
    } else {
      assert("add a-desc" && (lines.empty() || !(lines.back().a < a)));
    }
    if(lines.size() && lines.back().a == a && !comp(b, lines.back().b)) return;
    Line line(a, b, id);
    while((int) lines.size() >= 2 && check(lines[lines.size() - 2], lines.back(), line)) {
      lines.pop_back();
      if(!headIncreasing)
        if(head > 0) head--;
    }
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
    if(xType == 0) {
      int ok = lines.size() - 1, ng = -1;
      while(ok - ng > 1) {
        int mid = (ok + ng) >> 1;
        if(comp(f(mid, x), f(mid + 1, x)))
          ok = mid;
        else
          ng = mid;
      }
      return lines[ok];
    } else if(xType == 1) {
      assert("query increasingly!" && (!used || !(x < last)));
    } else if(xType == -1) {
      assert("query decreasingly!" && (!used || !(last < x)));
    }
    used = true;
    last = x;
    if(head >= lines.size()) head = lines.size() - 1;
    if(headIncreasing) {
      while(head + 1 < lines.size() && comp(f(head + 1, x), f(head, x))) head++;
      return lines[head];
    } else {
      while(head + 1 < lines.size() &&
            comp(f(lines.size() - 1 - (head + 1), x), f(lines.size() - 1 - head, x)))
        head++;
      return lines[lines.size() - 1 - head];
    }
  }
  void clear() {
    head = 0;
    used = false;
    lines.clear();
  }
  friend ostream &operator<<(ostream &os, CHT cht) {
    os << "CHT[";
    os << "a-" << (aIncreasing ? "asc" : "desc") << "; ";
    os << "x-" << (xType != 0 ? xType == -1 ? "desc" : "asc" : "random") << "; ";
    os << (isMinimize ? "min" : "max") << "; ";
    os << "internal-head-" << (headIncreasing ? "asc" : "desc");
    os << "]\n";
    os << cht.lines.size() << " lines\n";
    for(auto &p : cht.lines) os << p << "\n";
    return os;
  }
};

template < bool aIncreasing, class T, int xType, bool isMinimize, class D >
T CHT< aIncreasing, T, xType, isMinimize, D >::EPS = 1e-19;

/// }}}--- ///
