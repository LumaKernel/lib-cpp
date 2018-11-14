// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Sparse Table Library
// @snippet     sparsetable
// @title Sparse Table
// @alias       rmq
// NOTE : query in range!
/// --- Sparse Table Library {{{ ///

template < class SemiLattice >
struct SparseTable {
  using T = typename SemiLattice::T;
  size_t n;
  vector< size_t > log2;
  vector< vector< T > > t;
  T identity;
  SparseTable() : n(0) {}
  SparseTable(size_t n, T identity = T())
      : n(n), log2(n + 1), identity(identity) {
    for(size_t i = 2; i <= n; i++) log2[i] = log2[i >> 1] + 1;
    t.resize(log2[n] + 1, vector< T >(n, identity));
  }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  SparseTable(InputIter first, InputIter last, T identity = T())
      : SparseTable(distance(first, last), identity) {
    copy(first, last, begin(t[0]));
    build();
  }
  void set(size_t i, T val) { t[0][i] = val; }
  T get(size_t i) { return t[0][i]; }
  void build() {
    for(size_t j = 0; j < log2[n]; j++) {
      size_t w = 1 << j;
      for(size_t i = 0; i + (w << 1) <= n; i++) {
        t[j + 1][i] = SemiLattice::op(t[j][i], t[j][i + w]);
      }
    }
  }
  T query(size_t l, size_t r) {
    if(r - l < 1) return identity;
    size_t j = log2[r - l];
    return SemiLattice::op(t[j][l], t[j][r - (1 << j)]);
  }
};

/// }}}--- ///

// SemiLattice examples {{{

struct RMQSL {
  using T = int;
  static T op(T const &a, T const &b) { return a < b ? a : b; }
};

// }}}

SparseTable< RMQSL > rmq(N, inf);
