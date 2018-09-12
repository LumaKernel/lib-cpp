// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Kitamasa Library
// @snippet kitamasa

template < class T >
vector< T > kitamasa(const vector< T > &c, const vector< T > &u,
                     const vector< T > &v) {
  int k = c.size();
  vector< T > r(2 * k - 1);
  for(int i = 0; i < k; i++)
    for(int j = 0; j < k; j++) r[i + j] += u[i] * v[j];
  for(int i = 2 * k - 2; i >= k; i--)
    for(int j = 0; j < k; j++) r[i - k + j] += r[i] * c[j];
  r.resize(k);
  return r;
}
