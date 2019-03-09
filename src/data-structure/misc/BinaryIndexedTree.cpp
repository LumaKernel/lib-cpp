// @ Binary Indexed Tree
// @snippet bit

// .add(i, v)   : bit[i] += v
// .get(i)      : bit[i]
// .sum(i)      : bit[0] + ... + bit[i]
// .range(l, r) : bit[l] + ... + bit[r]
// .lower_bound(T v) : min i that satisfies .sum(i) >= v
//    - use only when bit[i] >= 0 for all i > 0
/// --- Binary Indexed Tree {{{ ///
#include <cassert>
#include <vector>
template < class T = long long >
struct BinaryIndexedTree {
  using size_type = std::size_t;
  size_type n, m;
  T identity;
  std::vector< T > data;
  BinaryIndexedTree() : n(0) {}
  BinaryIndexedTree(int n, T identity = T())
      : n(n), identity(identity), data(n, identity) {
    m = 1;
    while(m < n) m <<= 1;
  }
  void add(size_type i, T x) {
    assert(i < n);
    i++;
    while(i <= n) {
      data[i - 1] = data[i - 1] + x;
      i += i & -i;
    }
  }
  T sum(int i) {
    if(i < 0) return identity;
    if(i >= n) i = n - 1;
    i++;
    T s = identity;
    while(i > 0) {
      s = s + data[i - 1];
      i -= i & -i;
    }
    return s;
  }
  T get(int i) { return sum(i) - sum(i - 1); }
  T range(int a, int b) { return sum(b) - sum(a - 1); }
  size_type lower_bound(T w) {
    size_type i = 0;
    for(size_type k = m; k > 0; k >>= 1) {
      if(i + k <= n && data[i + k - 1] < w) w -= data[(i += k) - 1];
    }
    return i;
  }
};
/// }}}--- ///

template < class T = long long >
using BIT = BinaryIndexedTree< T >;
