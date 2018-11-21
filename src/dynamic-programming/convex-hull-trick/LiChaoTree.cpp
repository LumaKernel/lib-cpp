// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Li-Chao Tree
// @snippet lichaotree
// @alias cht_lichaotree

// LiChaoTree<T, Comp>
// - maximize : let Comp = greater<T>
// .x(x)
// === prebuild() ===
// .add(a, b) : f(x) = ax + b
// .add(a, b, l, r) : f(x) = ax + b (x in [l, r])
// .query(x)
/// --- Li-Chao Tree {{{ ///

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template < class T = long long, class Comp = less< T > >
struct LiChaoTree {
  static Comp comp;
  using Line = pair< T, T >;
  static inline T f(const Line &line, T x) {
    return line.first * x + line.second;
  }

  int n;
  vector< Line > dat;
  vector< int > used;
  vector< T > xs;
  void add(T a, T b) { add(0, n, Line(a, b)); }
  // [lx, rx]
  void add(T a, T b, T lx, T rx) {
    int l = lower_bound(xs.begin(), xs.end(), lx) - xs.begin();
    int r = upper_bound(xs.begin(), xs.end(), rx) - xs.begin();
    add(l, r, Line(a, b));
  }

private:
  // [l, r)
  void add(int l, int r, const Line &line) {
    int l0 = l, r0 = r;
    int sz = 1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1, sz <<= 1) {
      if(l & 1) add(l, l0, l0 + sz, line), l0 += sz, l++;
      if(r & 1) --r, r0 -= sz, add(r, r0, r0 + sz, line);
    }
  }
  void add(int k, int l, int r, Line line) {
    if(!used[k]) {
      used[k] = 1, dat[k] = line;
      return;
    }
    T ly = f(line, xs[l]), ry = f(line, xs[r - 1]);
    T nly = f(dat[k], xs[l]), nry = f(dat[k], xs[r - 1]);
    if(comp(nly, ly) && comp(nry, ry)) return;
    if(comp(ly, nly) && comp(ry, nry)) {
      dat[k] = line;
      return;
    }
    if(r - l == 1) return;
    int m = (l + r) >> 1;
    if(comp(nly, ly)) swap(dat[k], line);
    if(comp(f(line, xs[m]), f(dat[k], xs[m]))) {
      swap(dat[k], line);
      add((k << 1) | 1, m, r, line);
    } else {
      add(k << 1, l, m, line);
    }
  }

public:
  void x(T x) { xs.emplace_back(x); }
  void prebuild() {
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int t = xs.size();
    n = 1;
    while(n < t) n <<= 1;
    xs.resize(n, xs.back());

    dat.resize(n << 1);
    used.resize(n << 1);
  }

  T query(T x) { return f(get(x), x); }

  Line get(T x) {
    int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin() + n;
    int res = -1;
    for(; i > 0; i >>= 1)
      if(used[i])
        if(res == -1 || comp(f(dat[i], x), f(dat[res], x))) res = i;
    return dat[res];
  }
};

template < class T, class Comp >
Comp LiChaoTree< T, Comp >::comp;

/// }}}--- ///
