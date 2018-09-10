// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name 2D BIT Library
// @snippet     bit2d
// @alias       2dbit

// NOTE : query in range and x1 <= x2, y is same
/// --- 2D BIT Library {{{ ///

template < class T = ll, class V = function< T(T, T) > >
struct BIT2D {
  int h, w;
  T identity;
  vector< T > dat;
  BIT2D(int h, int w, T identity = T())
      : h(h), w(w), identity(identity), dat(h * w, identity) {}
  void add(int y, int x, T const &val) {
    for(++y; y <= h; y += y & -y) addX(y, x, val);
  }
  void addRange(int y1, int x1, int y2, int x2, T const &val) {
    add(y1, x1, val);
    if(y2 + 1 < h) add(y2 + 1, x1, -val);
    if(x2 + 1 < w) add(y1, x2 + 1, -val);
    if(y2 + 1 < h && x2 + 1 < w) add(y2 + 1, x2 + 1, val);
  }
  void set(int y, int x, T val) { add(y, x, val - get(y, x)); }
  T sum(int y, int x) {
    if(y < 0 || x < 0) return 0;
    T r = identity;
    for(++y; y > 0; y -= y & -y) r += sumX(y, x);
    return r;
  }
  T get(int y, int x) { return range(y, x, y, x); }
  T range(int y1, int x1, int y2, int x2) {
    return sum(y2, x2) - sum(y1 - 1, x2) - sum(y2, x1 - 1) +
           sum(y1 - 1, x1 - 1);
  }

private:
  inline int id(int y, int x) { return (y - 1) * w + (x - 1); }
  void addX(int y, int x, T const &val) {
    for(++x; x <= w; x += x & -x) dat[id(y, x)] += val;
  }
  T sumX(int y, int x) {
    T r = identity;
    for(++x; x > 0; x -= x & -x) r += dat[id(y, x)];
    return r;
  }
};

/// }}}--- ///
