// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Matrix mult pow Library
// @title 行列の積と累乗
// @snippet     matrix
/// --- Matrix mult pow Library {{{ ///

template < class T >
vector< vector< T > > mult(vector< vector< T > > a, vector< vector< T > > b) {
  assert(a[0].size() == b.size());
  vector< vector< T > > res(a.size(), vector< T >(b[0].size(), 0));
  for(int i = 0; i < a.size(); i++) {
    for(int j = 0; j < b[0].size(); j++) {
      for(int k = 0; k < a[0].size(); k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

template < class T >
vector< vector< T > > pow(vector< vector< T > > a, long long k) {
  vector< vector< T > > r(a.size(), vector< T >(a.size(), 0));
  for(size_t i = 0; i < a.size(); i++) r[i][i] = T(1);
  while(k) {
    if(k & 1) r = mult(r, a);
    a = mult(a, a);
    k >>= 1;
  }
  return r;
}

/// }}}--- ///

using Vec = vector< long long >;
using Mat = vector< Vec >;
