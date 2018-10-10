// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ CRT
// @snippet crt

// require math, modmul
/// --- CRT {{{ ///
ll CRT(ll x1, ll x2, ll m1, ll m2) {
  ll y1, y2;
  extgcd(m1, m2, y1, y2);
  ll m = m1 * m2;
  ll res = (modmul(x2 * m1, y1, m) + modmul(x1 * m2, y2, m)) % m;
  if(res < 0) res += m;
  return res;
}
/// }}}--- ///
