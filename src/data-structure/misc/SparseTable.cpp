// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Sparse Table
// @snippet sparsetable
// @alias rmq_sparsetable

// SparseTable( <data> [, default_value] )
// .fold(l, r) : [l, r)
/// --- Sparse Table {{{ ///
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <vector>
template < class SemiLattice >
struct SparseTable {
public:
  using T = typename SemiLattice::T;
  using size_type = size_t;

private:
  size_type n;
  vector< size_type > log2;
  vector< vector< T > > t;
  T default_value;

public:
  SparseTable() : n(0) {}
  SparseTable(size_type n, T default_value = T())
      : n(n), log2(n + 1), default_value(default_value) {
    for(size_type i = 2; i <= n; i++) log2[i] = log2[i >> 1] + 1;
    t.resize(log2[n] + 1, vector< T >(n, default_value));
  }
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  SparseTable(InputIter first, InputIter last, T default_value = T())
      : SparseTable(distance(first, last), default_value) {
    copy(first, last, begin(t[0]));
    build();
  }
  SparseTable(vector< T > v, T default_value = T())
      : SparseTable(v.begin(), v.end(), default_value) {}
  SparseTable(initializer_list< T > v, T default_value = T())
      : SparseTable(v.begin(), v.end(), default_value) {}
  void set(size_type i, T val) {
    assert(i < n);
    t[0][i] = val;
  }
  T get(size_type i) {
    assert(i < n);
    return t[0][i];
  }
  void build() {
    for(size_type j = 0; j < log2[n]; j++) {
      size_type w = 1 << j;
      for(size_type i = 0; i + (w << 1) <= n; i++) {
        t[j + 1][i] = SemiLattice::op(t[j][i], t[j][i + w]);
      }
    }
  }
  T fold(size_type l, size_type r) {
    if(r - l < 1) return default_value;
    assert(l < n && r <= n);
    size_type j = log2[r - l];
    return SemiLattice::op(t[j][l], t[j][r - (1 << j)]);
  }
  size_type size() { return n; }
};
/// }}}--- ///

// SemiLattice examples {{{
struct RMQSL {
  using T = ll;
  static T op(T const &a, T const &b) { return a < b ? a : b; }
};
// }}}

using SPT = SparseTable< RMQSL >;
SPT rmq(N, inf);
