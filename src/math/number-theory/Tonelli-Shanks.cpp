// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ modsqrt with Tonelli-Shanks algorithm
// @snippet modsqrt
// @alias sqrt_mod legendre is_quadratic_residue heihoujouyo rujandoru

// require math library
// modsqrt {{{

inline int legendre(ll a, ll p) {
  a %= p;
  if(a < 0) a += p;
  // a ^ ((p - 1) / 2) mod p
  return a == 0 ? 0 : modpow(a, p >> 1, p) == 1 ? 1 : -1;
}

#include <random>

// simplified Tonelli-Shanks algorithm
// a : quadratic residue (if not, return -1)
// p : odd prime
ll modsqrt(ll a, ll p) {
  a = a % p;
  if(a < 0) a += p;

  if(a == 0) return 0;

  if(legendre(a, p) == -1) return -1;

  if(p % 4 == 3) return modpow(a, (p + 1) / 4, p);
  if(p % 8 == 5)
    return modpow(a, (p - 1) / 4, p) == 1
               ? modpow(a, (p + 3) / 8, p)
               : modpow(2, (p - 1) / 4, p) * modpow(a, (p + 3) / 8, p) % p;

  int s = 1;
  ll q = p >> 1;
  while((q & 1) == 0) q >>= 1, ++s;

  static mt19937 mt;
  ll z;
  do {
    // (2/p) == 1
    z = 3 + mt() % (p - 3);
  } while(modpow(z, p >> 1, p) == 1);

  int m = s;
  ll c = modpow(z, q, p);
  ll t = modpow(a, q, p);
  ll r = modpow(a, (q + 1) >> 1, p);

  for(; m > 1; --m) {
    ll b = modpow(t, ll(1) << (m - 2), p);
    if(b != 1) r = r * c % p, t = c * c % p * t % p;
    c = c * c % p;
  }
  return r;
}

ll modsqrt(ll a, ll p, ll y) {
  ll x = modsqrt(a, p);
  ll py = 1;
  for(ll i = 0; i < y; i++) py *= p;
  return modpow(x, py / p, py) * modpow(a, (py + 1) / 2 - py / p, py) % py;
}

// }}}

// @new TEST tonnelli-shanks algorithm

// {{{
int main() {
  ll mods[] = {
      3, 5, 7, 11, 10007, ll(1e9 + 7), ll(1e9 + 9), 199181, 95009, 92179};
  ll nums[] = {1234,    1234567, 14567, 7654, 2345,   2381, 4823, 58184,
               3838431, 38482,   23832, 4283, 384194, 49,   2312, 1124};

  for(ll p : mods) {
    assert(isPrime(p));
    dump(p, p % 8);
    for(ll num : nums) {
      if(legendre(num, p) == 1) {
        ll py = 1;
        for(int i = 1; i <= 2; i++) {
          py *= p;
          ll x = modsqrt(num, p, i);
          assert(x * x % py == num % py);
        }
      }
    }
  }

  return 0;
}
// }}}
