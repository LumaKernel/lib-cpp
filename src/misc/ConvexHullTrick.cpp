// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex Hull Trick Library
// @snippet     cht
// @alias       convexhulltrick
// CHT(bool increasing, Compare comp);
// increasing : is query monotonic-increasing ?
// comp : rhs is better
// add(pair<T, T> line) : add deacrinsgly!!
/// --- Convex Hull Trick Library {{{ ///

struct CHT {
  using Line = pair< ll, ll >;
  vector< Line > lines;
  bool increasing;
  function< bool(ll, ll) > comp;
  CHT(bool increasing = false, function< bool(ll, ll) > comp =
                                   [&](ll lhs, ll rhs) { return lhs >= rhs; })
      : increasing(increasing), comp(comp) {}
  // is l2 unnecessary ?
  bool check(Line l1, Line l2, Line l3) {
    return comp((l1.second - l2.second) * (l3.first - l2.first),
                (l3.second - l2.second) * (l1.first - l2.first));
  }
  ll f(int i, ll x) { return lines[i].first * x + lines[i].second; }
  // add decreasingly
  void add(ll a, ll b) { add(Line(a, b)); }
  void add(Line line) {
    while((int) lines.size() >= 2 &&
          check(lines[lines.size() - 2], lines.back(), line))
      lines.pop_back();
    lines.emplace_back(line);
  }
  ll query(ll x) {
    if(increasing) {
      static int head = 0;
      while((int) lines.size() - 1 > head && comp(f(head, x), f(head + 1, x)))
        head++;
      return f(head, x);
    } else {
      int low = -1, high = lines.size() - 1;
      while(high - low > 1) {
        int mid = (low + high) >> 1;
        (comp(f(mid, x), f(mid + 1, x)) ? low : high) = mid;
      }
      return f(high, x);
    }
  }
};

/// }}}--- ///

// @new
// @ Dynamic Convex Hull Trick Library
// @snippet     dynamic_cht
// @alias       cht2

// DynamicCHT<T, Comp>() : if maximize, use greater<T> for Comp
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
#include <tuple>

// |ab| < LLONG_MAX/4 ???
template < class T = long long, class Comp = less< T > >
struct DynamicCHT {
  static T inf;
  static Comp comp;

private:
  struct Line { // ax + b
    T a, b;
    Line(const T &a, const T &b) : a(a), b(b) {}
    bool operator<(const Line &rhs) const { // (-a, b)
      return a != rhs.a ? comp(rhs.a, a) : comp(b, rhs.b);
    }
  };
  struct CP {
    T numer, denom; // x-coordinate
    const Line &p;
    CP(const T &n, const T &d, const Line &p) : numer(n), denom(d), p(p) {}
    CP(const Line &p1, const Line &p2) : p(p2) {
      if(p1.a == inf)
        numer = -inf, denom = 1;
      else if(p2.a == -inf)
        numer = inf, denom = 1;
      else
        numer = p1.b - p2.b, denom = p2.a - p1.a;
    }
    bool operator<(const CP &rhs) const {
      if(numer == inf || rhs.numer == -inf) return 0;
      if(numer == -inf || rhs.numer == inf) return 1;
      return numer * rhs.denom < rhs.numer * denom;
    }
  };
  set< Line > lines;
  set< CP > cps;
  typedef typename set< Line >::iterator It;

public:
  DynamicCHT() {
    // sentinel
    lines.insert({Line(inf, 0), Line(-inf, 0)});
    cps.insert(CP(Line(inf, 0), Line(-inf, 0)));
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
  T query(const T &x) {
    const Line &p = (--cps.lower_bound(CP(x, 1, Line(0, 0))))->p;
    return p.a * x + p.b;
  }
  tuple< T, T > get(const T &x) {
    const Line &p = (--cps.lower_bound(CP(x, 1, Line(0, 0))))->p;
    return make_tuple(p.a, p.b);
  }
  void dum() {
#ifdef DEBUG
    DEBUG_OUT << "lines : " << lines.size() << "\n";
    for(auto p : lines)
      DEBUG_OUT << "(" << p.a << ", " << p.b << ")"
                << "\n";
    DEBUG_OUT << "cross points : " << cps.size() << "\n";
    for(auto p : cps)
      DEBUG_OUT << "(x = " << p.numer << "/" << p.denom << ")"
                << "\n";
    DEBUG_OUT << flush;
#endif
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
    if(p1.a == inf || p3.a == -inf) return 0;
    return (p2.a - p1.a) * (p3.b - p2.b) >= (p2.b - p1.b) * (p3.a - p2.a);
  }
};
template < class T, class Comp >
T DynamicCHT< T, Comp >::inf = numeric_limits< T >::has_infinity
                                   ? numeric_limits< T >::infinity()
                                   : numeric_limits< T >::max();
template < class T, class Comp >
Comp DynamicCHT< T, Comp >::comp = Comp(); // only for less and greater

/// }}}--- ///
