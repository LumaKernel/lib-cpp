// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Sparse Table
// @snippet     sparsetable
// @title Sparse Table
// @alias       rmq
// NOTE : query in range!

// SparseTable( <data> , identity ? )
// .query(l, r) : [l, r)
/// --- Sparse Table {{{ ///
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <vector>
template < class SemiLattice >
struct SparseTable {
  using T = typename SemiLattice::T;
  size_t n;
  vector< size_t > log2;
  vector< vector< T > > t;
  T identity;
  SparseTable() : n(0) {}
  SparseTable(size_t n, T identity = T()) : n(n), log2(n + 1), identity(identity) {
    for(size_t i = 2; i <= n; i++) log2[i] = log2[i >> 1] + 1;
    t.resize(log2[n] + 1, vector< T >(n, identity));
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  SparseTable(InputIter first, InputIter last, T identity = T())
      : SparseTable(distance(first, last), identity) {
    copy(first, last, begin(t[0]));
    build();
  }
  SparseTable(vector< T > v, T identity = T())
      : SparseTable(v.begin(), v.end(), identity) {}
  SparseTable(initializer_list< T > v, T identity = T())
      : SparseTable(v.begin(), v.end(), identity) {}
  void set(size_t i, T val) {
    assert(i < n);
    t[0][i] = val;
  }
  T get(size_t i) {
    assert(i < n);
    return t[0][i];
  }
  void build() {
    for(size_t j = 0; j < log2[n]; j++) {
      size_t w = 1 << j;
      for(size_t i = 0; i + (w << 1) <= n; i++) {
        t[j + 1][i] = SemiLattice::op(t[j][i], t[j][i + w]);
      }
    }
  }
  T query(int l, int r) {
    if(r - l < 1) return identity;
    assert(r <= n);
    int j = log2[r - l];
    return SemiLattice::op(t[j][l], t[j][r - (1 << j)]);
  }
};
/// }}}--- ///

// SemiLattice examples {{{
struct RMQSL {
  using T = ll;
  static T op(T const &a, T const &b) { return a < b ? a : b; }
};
// }}}

SparseTable< RMQSL > rmq(N, inf);
