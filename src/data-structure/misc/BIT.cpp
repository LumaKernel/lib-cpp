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
  int n, m;
  T identity;
  vector< T > data;
  BIT() : n(0) {}
  BIT(int n, T identity = T()) : n(n), identity(identity), data(n, identity) {
    m = 1;
    while(m < n) m <<= 1;
  }
  void add(int i, T x) {
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
  int lower_bound(T w) {
    int i = 0;
    for(int k = m; k > 0; k >>= 1) {
      if(i + k <= n && data[i + k - 1] < w) w -= data[(i += k) - 1];
    }
    return i;
  }
};

/// }}}--- ///

// BIT<> bit(N);
