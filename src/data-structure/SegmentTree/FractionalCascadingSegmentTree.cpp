// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     fractionalcascadingsegtree
// @alias       segfractionalcascading fcseg
// @name Fractional Cascading SegmentTree Library

// (y, x)
// query(yl, yr, xl, xr)
// only offline
// only one update
/// --- Fractional Cascading SegmentTree Library {{{ ///

template < class T, class U, class Index = ll >
struct FractionalCascadingSegTree {
  int h;
  vector< T > dat;
  vector< vector< Index > > indices;
  vector< vector< int > > L, R;
  U identity;
  function< void(T &, int x, const U &) > setX;
  function< void(T &, vector< Index > &) > initX;
  function< U(T &, int x1, int x2) > queryX;
  function< U(const U &, const U &) > mergeX;
  FractionalCascadingSegTree() {}
  FractionalCascadingSegTree(
      int tempH, function< void(T &, int, const U &) > const &setX,
      function< void(T &, vector< Index > &) > const &initX,
      function< U(T &, int, int) > const &queryX,
      function< U(const U &, const U &) > const &mergeX, U identity = U(),
      T initial = T())
      : identity(identity),
        setX(setX),
        initX(initX),
        queryX(queryX),
        mergeX(mergeX) {
    h = 1;
    while(h < tempH) h <<= 1;
    dat = vector< T >(2 * h, initial);
    indices = vector< vector< Index > >(2 * h);
    L = R = vector< vector< int > >(2 * h);
  }
  void index(int i, Index j) { indices[i + h - 1].emplace_back(j); }
  void init(bool doUnique) {
    for(int i = h * 2 - 2; i >= 0; i--) {
      if(i >= h - 1) {
        sort(begin(indices[i]), end(indices[i]));
        if(doUnique)
          indices[i].erase(
              unique(begin(indices[i]), end(indices[i])), end(indices[i]));
        initX(dat[i], indices[i]);
        continue;
      }
      size_t lsz = indices[i * 2 + 1].size();
      size_t rsz = indices[i * 2 + 2].size();
      size_t nsz = lsz + rsz;
      indices[i].resize(nsz);
      L[i].resize(nsz + 1, lsz);
      R[i].resize(nsz + 1, rsz);
      size_t p1 = 0, p2 = 0;
      while(p1 < lsz || p2 < rsz) {
        L[i][p1 + p2] = p1;
        R[i][p1 + p2] = p2;
        if(p1 < lsz &&
           (p2 == rsz || indices[i * 2 + 1][p1] <= indices[i * 2 + 2][p2])) {
          indices[i][p1 + p2] = indices[i * 2 + 1][p1];
          p1++;
        } else {
          indices[i][p1 + p2] = indices[i * 2 + 2][p2];
          p2++;
        }
      }
      initX(dat[i], indices[i]);
    }
  }
  void set(int i, int j, U const &val) {
    int lower =
        lower_bound(begin(indices[0]), end(indices[0]), j) - begin(indices[0]);
    set(i, lower, val, 0, h, 0);
  }
  void set(int i, int lower, U const &val, int l, int r, int k) {
    if(i + 1 <= l || r <= i) return;
    upd(dat[k], i, lower, val);
    if(i <= l && r <= i + 1) return;
    set(i, L[k][lower], val, l, (l + r) >> 1, k * 2 + 1);
    set(i, R[k][lower], val, (l + r) >> 1, r, k * 2 + 2);
  }
  U query(int a, int b, int l, int r) {
    int lower =
        lower_bound(begin(indices[0]), end(indices[0]), l) - begin(indices[0]);
    int upper =
        lower_bound(begin(indices[0]), end(indices[0]), r) - begin(indices[0]);
    return query(a, b, lower, upper, 0, h, 0);
  }
  U query(int a, int b, int lower, int upper, int l, int r, int k) {
    if(b <= l || r <= a) return identity;
    if(a <= l && r <= b) return queryX(dat[k], lower, upper);
    return mergeX(
        query(a, b, L[k][lower], L[k][upper], l, (l + r) >> 1, k * 2 + 1),
        query(a, b, R[k][lower], R[k][upper], (l + r) >> 1, r, k * 2 + 2));
  }
};

/// }}}--- ///

// fc-seg expamle {{{

// using Under = BIT<>;
// using Data = ll;

using Under = SparseTable< RMQSL >;
using Data = RMQSL::T;

const int N = 1;
FractionalCascadingSegTree< Under, Data > ecas(
    N + 1,
    // set y
    [](Under &dat, int y, Data const &v) -> void {
      dat.set(y, RMQSL::op(dat.get(y), v));
    },
    // init y
    [](Under &dat, vector< ll > indices) -> void {
      dat = Under(indices.size()); // serve initial?
    },
    // [l, r) // WARN : l <= r
    [](Under &dat, int l, int r) -> Data { return dat.query(l, r); },
    // merge y-direction
    [](Data a, Data b) -> Data { return a + b; });

// }}}
