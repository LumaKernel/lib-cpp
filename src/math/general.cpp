// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     isprime
// @name isPrime
/// --- isPrime {{{ ///

bool isPrime(ll n) {
  if(n < 2) return false;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) return false;
  }
  return true;
}

/// }}}--- ///

// @new
// @snippet     divisor
// @name divisor
// O(N^.5)
/// --- divisor {{{ ///
vector< ll > divisor(ll n) {
  vector< ll > res;
  for(ll i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      res.emplace_back(i);
      if(i != n / i) res.emplace_back(n / i);
    }
  }
  return res;
}
/// }}}--- ///

// @new
// @name primeFactors
// @snippet     primefactors
// @alias       insuubunkai soinsuubunkai
// O(N^.5)
/// --- primeFactors {{{ ///
map< ll, int > primeFactors(ll n) {
  map< ll, int > res;
  for(ll i = 2; i * i <= n; i++) {
    while(n % i == 0) n /= i, res[i]++;
  }
  if(n != 1) res[n] = 1;
  return res;
}
/// }}}--- ///

// @new
// @name phi
// @snippet     phi
// @alias       euler
// O(N^.5)
/// --- phi {{{ ///
ll phi(ll n) {
  ll res = n;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      res = res / i * (i - 1);
      while(n % i == 0) n /= i;
    }
  }
  if(n != 1) res = res / n * (n - 1);
  return res;
}
/// }}}--- ///

// @new
// @name phi2
// @snippet     philist
// @alias       phi2 eulerlist euler2
// O(N log log N)
/// --- phi2 {{{ ///
vector< int > phi2(int n) {
  n++;
  vector< int > euler(n);
  for(int i = 0; i < n; i++) euler[i] = i;
  for(int i = 2; i < n; i++) {
    if(euler[i] == i) {
      for(int j = i; j < n; j += i) euler[j] = euler[j] / i * (i - 1);
    }
  }
  return euler;
}
/// }}}--- ///

// @new
// @name primes
// @snippet     primes
/// --- primes {{{ ///
vector< int > primes(int n) {
  vector< int > res;
  for(int i = 2; i <= n; ++i) {
    bool isp = 1;
    for(int p : res) {
      if((ll) p * p > i) break;
      if(i % p == 0) {
        isp = 0;
        break;
      }
    }
    if(isp) res.emplace_back(i);
  }
  return res;
}
/// }}}--- ///

// @new
// @name math
// @snippet     math
// @alias       gcd lcm extgcd modinv modpow
/// --- math {{{ ///
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll extgcd(ll a, ll b, ll &x, ll &y) {
  ll d;
  return b == 0 ? (x = 1, y = 0, a)
                : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
}
ll modinv(ll a, ll mod) {
  ll x, y;
  extgcd(a, mod, x, y);
  if(x < 0) x += mod;
  return x;
}
ll modpow(ll a, ll b, ll mod) {
  ll r = 1;
  a %= mod;
  while(b) {
    if(b & 1) r = r * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return r;
}
/// }}}--- ///

// @new isPrimitive
// @snippet     is_primitive
/// --- isPrimitive {{{ ///
bool isPrimitive(ll x, ll mod) {
  auto ds = divisor(mod - 1);
  for(ll d : ds)
    if(d != mod - 1) {
      if(modpow(x, d, mod) == 1) return false;
    }
  return true;
}
/// }}}--- ///

// @new modmul
// @snippet     modmul
// @alias       mulmod
/// --- modmul {{{ ///
ll modmul(ll x, ll y, ll mod) {
  ll res = (x * y - (ll)((long double) x * y / mod) * mod) % mod;
  return res < 0 ? res + mod : res;
}
/// }}}--- ///
