// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Fractional Cascading SegmentTree
// @snippet     fractionalcascadingsegtree
// @alias       segfractionalcascading fcseg

// FractionalCascadingSegmentTree
// < Under, Data [, yCompress = 1 [, Index] ] >(H, ...)
// .index(y, x)
// === init(doUnique) ===
// .set(y, x, val)         // index(y, x) must be done
// .fold(yl, yr, xl, xr)
// .fold(y, x)
// === --- ===
// only offline
/// --- Fractional Cascading SegmentTree {{{ ///
#include <algorithm>
#include <cassert>
#include <functional>
#include <map>
#include <vector>

template < class T, class U, bool yCompress = true, class Index = ll >
struct FractionalCascadingSegmentTree {
  size_t h;
  vector< T > dat;
  vector< vector< Index > > indices;
  vector< vector< size_t > > L, R;
  U identity;
  function< void(T &, int x, const U &) > setX;
  function< void(T &, vector< Index > &) > initX;
  function< U(T &, int x1, int x2) > foldX;
  function< U(const U &, const U &) > mergeY;
  FractionalCascadingSegmentTree() {}
  FractionalCascadingSegmentTree(size_t tempH, //
                                 const function< void(T &, int, const U &) > &setX,
                                 const function< void(T &, vector< Index > &) > &initX,
                                 const function< U(T &, int, int) > &foldX,
                                 const function< U(const U &, const U &) > &mergeY,
                                 U identity = U(), T initial = T())
      : identity(identity), setX(setX), initX(initX), foldX(foldX), mergeY(mergeY) {
    h = 1;
    while(h < tempH) h <<= 1;
    dat = vector< T >(2 * h, initial);
    indices = vector< vector< Index > >(2 * h);
    L = R = vector< vector< size_t > >(2 * h);
  }
  vector< Index > ys;
  map< Index, int > ymap;
  vector< pair< Index, Index > > pre_indecies;
  void index(Index i, Index j) {
    if(yCompress) {
      ys.push_back(i);
      pre_indecies.emplace_back(i, j);
    } else {
      size_t i2 = i;
      assert(i2 < h);
      indices[i2 + h].push_back(j);
    }
  }
  void init(bool doUnique) {
    if(yCompress) {
      sort(begin(ys), end(ys));
      ys.erase(unique(begin(ys), end(ys)), end(ys));
      {
        size_t i = 0;
        for(Index &y : ys) ymap[y] = i++;
      }
      for(pair< Index, Index > idx : pre_indecies) {
        indices[ymap[idx.first] + h].push_back(idx.second);
      }
    }
    for(size_t i = h; i < h * 2; i++) {
      sort(begin(indices[i]), end(indices[i]));
      if(doUnique)
        indices[i].erase(unique(begin(indices[i]), end(indices[i])), end(indices[i]));
      initX(dat[i], indices[i]);
    }
    for(size_t i = h - 1; i >= 1; i--) {
      size_t lsz = indices[i * 2].size();
      size_t rsz = indices[i * 2 + 1].size();
      size_t nsz = lsz + rsz;
      indices[i].resize(nsz);
      L[i].resize(nsz + 1, lsz);
      R[i].resize(nsz + 1, rsz);
      size_t p1 = 0, p2 = 0;
      while(p1 < lsz || p2 < rsz) {
        L[i][p1 + p2] = p1;
        R[i][p1 + p2] = p2;
        if(p1 < lsz && (p2 == rsz || indices[i * 2][p1] <= indices[i * 2 + 1][p2])) {
          indices[i][p1 + p2] = indices[i * 2][p1];
          p1++;
        } else {
          indices[i][p1 + p2] = indices[i * 2 + 1][p2];
          p2++;
        }
      }
      initX(dat[i], indices[i]);
    }
  }

public:
  void set(Index y, Index x, const U &val) {
    if(yCompress) {
      assert(ymap.count(y));
      _set(ymap[y], x, val);
    } else {
      size_t y2 = y;
      assert(y2 < h);
      _set(y2, x, val);
    }
  }

private:
  void _set(size_t y, Index x, const U &val) {
    size_t lower = lower_bound(begin(indices[1]), end(indices[1]), x) - begin(indices[1]);
    assert(lower < indices.size());
    size_t k = 1, l = 0, r = h;
    while(k != y + h) {
      setX(dat[k], lower, val);
      size_t mid = (l + r) >> 1;
      if(y < mid) {
        lower = L[k][lower];
        k = k * 2;
        r = mid;
      } else {
        lower = R[k][lower];
        k = k * 2 + 1;
        l = mid;
      }
    }
    setX(dat[k], lower, val);
    assert(indices[k][lower] == x);
  }

public:
  U fold(Index y, Index x) { return fold(y, y + Index(1), x, x + Index(1)); }
  U fold(Index a, Index b, Index l, Index r) {
    if(a >= b || l >= r) return identity;
    size_t lower = lower_bound(begin(indices[1]), end(indices[1]), l) - begin(indices[1]);
    size_t upper = lower_bound(begin(indices[1]), end(indices[1]), r) - begin(indices[1]);
    size_t a2, b2;
    if(yCompress) {
      a2 = lower_bound(begin(ys), end(ys), a) - begin(ys);
      b2 = lower_bound(begin(ys), end(ys), b) - begin(ys);
    } else {
      a2 = a, b2 = b;
      assert(a2 < h && b2 <= h);
    }
    return fold(a2, b2, lower, upper, 0, h, 1);
  }

private:
  U fold(size_t a, size_t b, size_t lower, size_t upper, size_t l, size_t r, size_t k) {
    if(lower == upper) return identity;
    if(b <= l || r <= a) return identity;
    if(a <= l && r <= b) return foldX(dat[k], lower, upper);
    return mergeY(fold(a, b, L[k][lower], L[k][upper], l, (l + r) >> 1, k * 2),
                  fold(a, b, R[k][lower], R[k][upper], (l + r) >> 1, r, k * 2 + 1));
  }
};

/// }}}--- ///

// never forget to init SparseTable by yourself
// WARNING : DO DOUBLE-CHECK !
// FC-SegmentTree Example {{{

using Under = SparseTable< RMQSL >;
using Value = RMQSL;
using Data = Value::T;

FractionalCascadingSegmentTree< Under, Data, 1 > ecas(
    N + 1,
    // set x
    [](Under &dat, int x, const Data &val) -> void {
      dat.set(x, Value::op(dat.get(x), val));
    },
    // init x
    [](Under &dat, const vector< ll > &indices) -> void {
      dat = Under(indices.size()); // serve initial?
    },
    // fold [l, r) // l < r
    [](Under &dat, int l, int r) -> Data { return dat.fold(l, r); },
    // merge y-direction
    [](Data a, Data b) -> Data { return a + b; }
    // optional identity
    // , identity
    );
// }}}

// @new
// @ BIT on FC-SegmentTree
// @snippet fc_seg_bit
// @alias   bit_on_fc_seg

// one add // range sum
// WARNING : DO DOUBLE-CHECK !
// BIT on FC-SegmentTree {{{

using Under = BIT<>;
using Data = ll;

FractionalCascadingSegmentTree< Under, Data > qina(
    N + 10,
    // set x
    [](Under &dat, int x, const Data &val) -> void { dat.add(x, val); },
    // init x
    [](Under &dat, const vector< ll > &indices) -> void {
      dat = Under(indices.size()); // serve initial?
    },
    // fold [l, r) // l < r
    [](Under &dat, int l, int r) -> Data { return dat.range(l, r - 1); },
    // merge y-direction
    [](Data a, Data b) -> Data { return a + b; }
    // optional identity
    // , identity
    );

// }}}

// @new
// @ SegmentTree on FC-SegmentTree
// @snippet fc_seg_seg
// @alias   seg_on_fc_seg

// WARNING : DO DOUBLE-CHECK !
// SegmentTree on FC-SegmentTree {{{

using Under = Seg;
using Value = RangeMin<>;
using Data = Value::T;

FractionalCascadingSegmentTree< Under, Data, 1 > ecas(
    N + 1,
    // set x
    [](Under &dat, int x, const Data &val) -> void {
      // dat.set(x, Value::op(dat.get(x), val));
      dat.set(x, val);
    },
    // init x
    [](Under &dat, const vector< ll > &indices) -> void {
      dat = Under(indices.size(), inf_monoid?); // serve initial?
    },
    // fold [l, r) // l < r
    [](Under &dat, int l, int r) -> Data { return dat.fold(l, r); },
    // merge y-direction
    [](Data a, Data b) -> Data { return min(a, b); }
    // optional identity
    ,
    inf_monoid);
// }}}
