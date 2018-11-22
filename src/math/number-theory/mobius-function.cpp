// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ mobius-function
// @snippet     mobius_func
// @alias mebius_func

// O(N^.5)
// mu_enum(n) - mu[all divisors]
// mu_enum {{{

#include <unordered_map>
#include <vector>

unordered_map< ll, int > mu_enum(ll n) {
  unordered_map< ll, int > res;
  vector< ll > primes;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) primes.emplace_back(i);
  }
  if(n != 1) primes.emplace_back(n);
  int m = primes.size();
  for(int i = 0; i < (1 << m); i++) {
    int v = 1;
    ll num = 1;
    for(int j = 0; j < m; j++)
      if(i & (1 << j)) {
        v *= -1;
        num *= primes[j];
      }
    res[num] = v;
  }
  return res;
}
// }}}
