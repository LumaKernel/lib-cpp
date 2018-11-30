// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ FastZetaTransform
// @snippet fzt
// @alias zeta fast_zeta_transform

// fzt {{{
#include <vector>

// to upper : b[j] = sum(i: j in i, a[i])
// n is power of 2
template < class T >
vector< T > fzt(vector< T > a, bool toUpper) {
  int n = a.size();
  for(int i = 1; i < n; i <<= 1)
    for(int j = 0; j < n; j++)
      if((j & i) == 0) {
        if(toUpper) {
          a[j] += a[j | i];
        } else {
          a[j | i] += a[j];
        }
      }
  return a;
}
// }}}

// @new
// @ FastMobiusTransform
// @snippet fmt
// @alias mebius_fmt mobius_fmt fast_mobius_transform

// fmt {{{
#include <vector>
// to upper : b[j] = sum(i: j in i, (-1)^|i\j| * a[i])
// n is power of 2
template < class T >
vector< T > fmt(vector< T > a, bool toUpper) {
  int n = a.size();
  for(int i = 1; i < n; i <<= 1)
    for(int j = 0; j < n; j++)
      if((j & i) == 0) {
        if(toUpper) {
          a[j] -= a[j | i];
        } else {
          a[j | i] -= a[j];
        }
      }
  return a;
}
// }}}

// @new
// @ FWT with AND
// @snippet and_conv
// @alias fwt_and fwht_and conv_and hadamard_and

// n must be 2^k
// require FZT, FMT
// Convolution with AND {{{
#include <vector>
template < class T >
vector< T > convAND(vector< T > a, vector< T > b) {
  a = fzt(a, 1);
  b = fzt(b, 1);
  for(size_t i = 0; i < a.size(); i++) a[i] *= b[i];
  return fmt(a, 1);
}
// }}}

// @new
// @ FWT with OR
// @snippet or_conv
// @alias fwt_or fwht_or conv_or hadamard_or

// n must be 2^k
// require FZT, FMT
//  Convolution with OR {{{
#include <vector>
template < class T >
vector< T > convOR(vector< T > a, vector< T > b) {
  a = fzt(a, 0);
  b = fzt(b, 0);
  for(size_t i = 0; i < a.size(); i++) a[i] *= b[i];
  return fmt(a, 0);
}
// }}}
