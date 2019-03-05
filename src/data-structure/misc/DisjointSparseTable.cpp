// @ Disjoint Sparse Talbe
// @snippet disjoint_sparse_table
// @alias sparse_table_disjoint

// Disjoint Sparse Table {{{
#include <cassert>
#include <iterator>
#include <vector>
template < class SemiGroup >
struct DisjointSparseTalbe {
public:
  using X = typename SemiGroup::T;
  using size_type = size_t;

private:
  size_type _size, n;
  std::vector< size_type > lg_msb_table;
  std::vector< std::vector< X > > table;

  size_type lg_msb(size_type x) {
    size_type r = 0;
    if(x >> 16) x >>= 16, r ^= 16;
    if(x >> 8) x >>= 8, r ^= 8;
    if(x >> 4) x >>= 4, r ^= 4;
    if(x >> 2) x >>= 2, r ^= 2;
    return r ^ (x >> 1);
  }

private:
  DisjointSparseTalbe(size_type t) : _size(t) {
    n = 1;
    while(n < t) n <<= 1;
    lg_msb_table.resize(n);
    for(size_type i = 1; i < n; i++) lg_msb_table[i] = lg_msb(i);
  }

public:
  DisjointSparseTalbe() : _size(0), n(0) {}
  template < class InputIter,
             class = typename std::iterator_traits< InputIter >::value_type >
  DisjointSparseTalbe(InputIter first, InputIter last)
      : DisjointSparseTalbe(std::distance(first, last)) {
    table.emplace_back(first, last);
    for(size_type i = 2; i < _size; i <<= 1) {
      table.push_back(std::vector< X >());
      table.back().reserve(n);
      for(size_type j = i; j < _size; j += i << 1) {
        std::vector< X > tmp;
        tmp.reserve(i);
        tmp.push_back(table.front()[j - 1]);
        for(size_type k = 2; k <= i; k++)
          tmp.emplace_back(SemiGroup::op(table.front()[j - k], tmp.back()));
        reverse(tmp.begin(), tmp.end());
        table.back().insert(table.back().end(), tmp.begin(), tmp.end());
        table.back().emplace_back(table.front()[j]);
        for(size_type k = 1; k < i; k++)
          table.back().emplace_back(
              SemiGroup::op(table.back().back(), table.front()[j + k]));
      }
    }
  }
  DisjointSparseTalbe(std::initializer_list< X > ilist)
      : DisjointSparseTalbe(ilist.begin(), ilist.end()) {}

public:
  X fold(int l, int r, X identity) {
    if(l < 0) l = 0;
    if(r > (int) _size) r = _size;
    if(l >= r) return identity;
    return fold(l, r);
  }
  X fold(size_type l, size_type r) {
    assert(l < r && r <= _size);
    r--;
    if(l == r) return table.front()[l];
    size_type lgmsb = lg_msb_table[l ^ r];
    return SemiGroup::op(table[lgmsb][l], table[lgmsb][r]);
  }
  size_type size() { return _size; }
};
// }}}

// using SPT = DisjointSparseTalbe<RangeSum<>>;
