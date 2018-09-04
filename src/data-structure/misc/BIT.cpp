// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name BIT Library
// @snippet bit
// @title Binary Indexed Tree (Fenwick Tree)
// NOTE : there's get and sum method.
/// --- BIT Library {{{ ///

template < class T = ll >
struct BIT {
  vector< T > data;
  int n;
  T identity;
  function< T(const T &, const T &) > merge;
  BIT() : n(0) {}
  BIT(int n, T identity = T(),
      function< T(const T &, const T &) > merge =
          [](T const &a, T const &b) { return a + b; })
      : n(n), identity(identity), merge(merge) {
    data.resize(n, identity);
  }
  void add(int i, T x) {
    i++;
    while(i <= n) {
      data[i - 1] = merge(data[i - 1], x);
      i += i & -i;
    }
  }
  T sum(int i) {
    if(i < 0) return identity;
    if(i >= n) i = n - 1;
    i++;
    T s = identity;
    while(i > 0) {
      s = merge(s, data[i - 1]);
      i -= i & -i;
    }
    return s;
  }
  T get(int i, function< T(const T &) > const &inverse = [](T const &a) {
    return -a;
  }) {
    return merge(sum(i), inverse(sum(i - 1)));
  }
  T range(int a, int b,
          function< T(const T &) > const &inverse = [](T const &a) {
            return -a;
          }) {
    return merge(sum(b), inverse(sum(a - 1)));
  }
};

/// }}}--- ///

// BIT<> bit(N);
