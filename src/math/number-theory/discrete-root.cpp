// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Discrete Root
// @snippet modroot

// require modlog, modpow
// b^(1/a)
// modroot(a, b, p, primitiveRoot) {{{
ll modroot(ll a, ll b, ll p, ll primitiveRoot) {
  // x^a = b
  // x = g^y
  // (g^a)^y=b
  ll y = modlog(modpow(primitiveRoot, a, p), b, p);
  return y == -1 ? -1 : modpow(primitiveRoot, y, p);
}
// }}}

