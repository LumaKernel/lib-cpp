// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     fractionalcascadingsegtree
// @alias       segfractionalcascading fcseg
// @name Fractional Cascading SegmentTree Library
// データ構造を乗せるためのセグ木の高速版
// オフラインなら予めxごとに求めるyを与える
// クエリはトップダウン
// オンラインならDrivableSegTreeにBITとか乗せるしかない?
/// --- Fractional Cascading SegmentTree Library {{{ ///

template < class T, class U, class Index = ll >
struct FractionalCascadingSegTree {
  int n;
  vector< T > dat;
  vector< vector< Index > > indices;
  vector< vector< int > > L, R;
  U identity;
  function< void(T &, int, int, const U &) > upd;
  function< void(T &, vector< Index > &) > ini;
  function< U(T &, int, int) > f;
  function< U(const U &, const U &) > m;
  FractionalCascadingSegTree() {}
  FractionalCascadingSegTree(int t, function< void(T &, int, int, const U &) > const &upd,
                             function< void(T &, vector< Index > &) > const &ini,
                             function< U(T &, int, int) > const &f,
                             function< U(const U &, const U &) > const &m,
                             U identity = U(), T initial = T())
      : identity(identity), upd(upd), ini(ini), f(f), m(m) {
    n = 1;
    while(n < t) n <<= 1;
    dat = vector< T >(2 * n, initial);
    indices = vector< vector< Index > >(2 * n);
    L = R = vector< vector< int > >(2 * n);
  }
  void index(int i, Index j) { indices[i + n - 1].emplace_back(j); }
  void init(bool doUnique) {
    for(int i = n * 2 - 2; i >= 0; i--) {
      if(i >= n - 1) {
        sort(begin(indices[i]), end(indices[i]));
        if(doUnique)
          indices[i].erase(unique(begin(indices[i]), end(indices[i])), end(indices[i]));
        ini(dat[i], indices[i]);
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
        if(p1 < lsz && (p2 == rsz || indices[i * 2 + 1][p1] <= indices[i * 2 + 2][p2])) {
          indices[i][p1 + p2] = indices[i * 2 + 1][p1];
          p1++;
        } else {
          indices[i][p1 + p2] = indices[i * 2 + 2][p2];
          p2++;
        }
      }
      ini(dat[i], indices[i]);
    }
  }
  void update(int i, int j, U const &val) {
    int lower = lower_bound(begin(indices[0]), end(indices[0]), j) - begin(indices[0]);
    update(i, lower, val, 0, n, 0);
  }
  void update(int i, int lower, U const &val, int l, int r, int k) {
    if(i + 1 <= l || r <= i) return;
    upd(dat[k], i, lower, val);
    if(i <= l && r <= i + 1) return;
    update(i, L[k][lower], val, l, (l + r) >> 1, k * 2 + 1);
    update(i, R[k][lower], val, (l + r) >> 1, r, k * 2 + 2);
  }
  U query(int a, int b, int l, int r) {
    int lower = lower_bound(begin(indices[0]), end(indices[0]), l) - begin(indices[0]);
    int upper = lower_bound(begin(indices[0]), end(indices[0]), r) - begin(indices[0]);
    return query(a, b, lower, upper, 0, n, 0);
  }
  U query(int a, int b, int lower, int upper, int l, int r, int k) {
    if(b <= l || r <= a) return identity;
    if(a <= l && r <= b) return f(dat[k], lower, upper);
    return m(query(a, b, L[k][lower], L[k][upper], l, (l + r) >> 1, k * 2 + 1),
             query(a, b, R[k][lower], R[k][upper], (l + r) >> 1, r, k * 2 + 2));
  }
};

/// }}}--- ///

// fc-seg expamle {{{

// using Under = BIT<>;
// using Data = ll;

// using Under = SparseTable<RMQSL>;
// using Data = ll;

// FractionalCascadingSegTree<Under, Data> ecas(N + 1,
//     // update
//     [](Under &dat, int x, int y, Data const &v) -> void {
//     dat.set(y, RMQSL::op(dat.get(y), v));
//     },
//     // init
//     [](Under &dat, vector<ll> indices) -> void {
//     dat = Under(indices.size()); // serve initial?
//     },
//     // [l, r) // WARN : l <= r
//     [](Under &dat, int l, int r) -> Data {
//       return dat.query(l, r);
//     },
//     // merge
//     [](Data a, Data b) -> Data {
//       return a + b;
//     });

// }}}
