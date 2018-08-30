// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name FastZetaTransform
// @snippet fzt
// @alias zeta fast_zeta_transform
// a'[i] = sum(j は i を含む, a[j])
template < class T >
void zeta(vector< T > &a,
          function< T(T, T) > const &op = [](T a, T b) { return a + b; }) {
  int n = a.size();
  for(int i = 0; i < n; i++)
    for(int b = 0; b < (1 << n); b++)
      if(!(b & (1 << i))) a[b] = op(a[b], a[b | (1 << i)]);
}

// @new
// @name FastMoebiusTransform
// @snippet fmt
// @alias mebius_fmt moebius_fmt fast_moebius_transform
// zetaの逆操作
template < class T >
void moebius(vector< T > &a,
             function< T(T, T) > const &op = [](T a, T b) { return a - b; }) {
  int n = a.size();
  for(int i = 0; i < n; i++)
    for(int b = 0; b < (1 << n); b++)
      if(b & (1 << i)) a[b] = op(a[b], a[b | (1 << i)]);
}
