// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ FWT with XOR
// @snippet xor_fwt
// @alias fwt_xor fwht_xor conv_xor adamard_xor

// n must be 2^k
/// --- FWT with XOR {{{ ///
#include <vector>
template < class T >
vector< T > fwtXOR(vector< T > a, bool inverse) {
  int n = a.size();
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j++) {
      if((i & j) == 0) {
        T u = a[j], v = a[j | i];
        a[j] = u + v, a[j | i] = u - v;
      }
    }
  }

  if(inverse) {
    T ninv = T(1) / T(n);
    for(int i = 0; i < n; i++) a[i] *= ninv;
  }

  return a;
}

template < class T >
vector< T > convXOR(vector< T > a, vector< T > b) {
  a = fwtXOR(a, 0);
  b = fwtXOR(b, 0);
  for(size_t i = 0; i < a.size(); i++) a[i] *= b[i];
  return fwtXOR(a, 1);
}
/// }}}--- ///
