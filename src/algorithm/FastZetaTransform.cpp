// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ FastZetaTransform
// @snippet fzt
// @alias zeta fast_zeta_transform

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

// @new
// @ FastMobiusTransform
// @snippet fmt
// @alias mebius_fmt mobius_fmt fast_mobius_transform

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
