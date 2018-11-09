// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ moebius
// @snippet     moebius_func
// @alias mebius_func
// O(N^.5)
unordered_map< ll, int > moebius(ll n) {
  unordered_map< ll, int > res;
  vector< ll > primes;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) primes.emplace_back(i);
  }
  if(n != 1) primes.emplace_back(n);
  int m = primes.size();
  for(int i = 0; i < (1 << m); i++) {
    int mu = 1;
    ll num = 1;
    for(int j = 0; j < m; j++)
      if(i & (1 << j)) {
        mu *= -1;
        num *= primes[j];
      }
    res[num] = mu;
  }
  return res;
}
