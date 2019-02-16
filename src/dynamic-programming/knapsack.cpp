// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Knapsack
// @snippet knapsack
// @alias napsack

// x : weight
// y : value
// z : limit
// knapsack

// O(min{NW, N \sum {xz}}) < O(N^2 XZ) time
// O(W) space
// knapsack1(<ull>, <ll>, <uint>, uint) {{{
#include <cassert>
#include <deque>
#include <vector>
vector< ll > knapsack1(const vector< unsigned long long >& x, const vector< ll >& y,
                       const vector< unsigned >& z, unsigned W) {
  using ull = unsigned long long;
  size_t n = x.size();
  assert(n == y.size());
  assert(n == z.size());
  if(n == 0) return vector< ll >();
  ull w_max = 0;
  for(size_t i = 0; i < n && w_max < W && (x[i] < W || z[i] == 0); i++) {
    w_max += x[i] * z[i];
    if(i == n - 1 && w_max < W) W = w_max;
  }
  vector< ll > dp(W + 1);
  for(size_t i = 0; i < n; i++)
    if(z[i]) {
      if(x[i]) {
        vector< ll > dp0(W + 1);
        swap(dp, dp0);
        for(size_t r = 0; r < x[i] && r <= W; r++) {
          // k := z[i]
          // a[i][j] := dp[i][j * x[i] + r]
          // dp[i + 1][(j + k) * x[i] + r] ( = a[i + 1][j + k] )
          //  = max{a[i][j] + k * y[i], a[i][j + 1] + (k - 1) * y[i], ...}
          //  = max{a[i][j] + -j * y[i], a[i][j + 1] + -(j + 1) * y[i], ...}
          //      + (j + k) * y[i]
          size_t u = (W - r) / x[i];
          // window sliding technique
          deque< pair< ll, size_t > > deq;
          for(size_t j = 0; j <= u; j++) {
            ll nval = dp0[j * x[i] + r] - j * y[i];
            while(deq.size() && deq.back().first < nval) deq.pop_back();
            deq.emplace_back(nval, j);
            dp[j * x[i] + r] = deq.front().first + j * y[i];
            if(deq.front().second + z[i] == j) deq.pop_front();
          }
        }
      } else {
        for(auto& el : dp) el += y[i] * z[i];
      }
    }
  return dp;
}
// }}}

// check whether \sum {yz} won't overflow
// O(N \sum {yz}) < O(N^2 YZ) time
// knapsack2(<ll>, <uint>, <uint>, ull) {{{
vector< ll > knapsack2(const vector< ll >& x, const vector< unsigned >& y,
                       const vector< unsigned >& z, unsigned long long W) {
  using ull = unsigned long long;
  size_t n = x.size();
  assert(n == y.size());
  assert(n == z.size());
  if(n == 0) return vector< ll >();
  ull value_max = 0;
  for(size_t i = 0; i < n; i++) value_max += y[i] * z[i];
  vector< ll > dp(value_max + 1, W + 1);
  dp[0] = 0;
  for(size_t i = 0; i < n; i++)
    if(y[i] && z[i]) {
      vector< ll > dp0(value_max + 1, W + 1);
      swap(dp, dp0);
      for(size_t r = 0; r < y[i]; r++) {
        // k := z[i]
        // a[i][j] := dp[i][j * y[i] + r]
        // dp[i + 1][(j + k) * y[i] + r] ( = a[i + 1][j + k] )
        //  = min{a[i][j] + k * x[i], a[i][j + 1] + (k - 1) * x[i], ...}
        //  = min{a[i][j] + -j * x[i], a[i][j + 1] + -(j + 1) * x[i], ...}
        //      + (j + k) * x[i]
        size_t u = (value_max - r) / y[i];
        // window sliding technique
        deque< pair< ll, size_t > > deq;
        for(size_t j = 0; j <= u; j++) {
          if((ull) dp0[j * y[i] + r] <= W) {
            ll nval = dp0[j * y[i] + r] - (ll) j * x[i];
            while(deq.size() && deq.back().first > nval) deq.pop_back();
            deq.emplace_back(nval, j);
          }
          if(deq.size()) dp[j * y[i] + r] = deq.front().first + j * x[i];
          if(deq.size() && deq.front().second + z[i] == j) deq.pop_front();
        }
      }
    }
  return dp;
}
// }}}

// check whether \sum {yz} won't overflow
// O(N^2 Y^2)
// knapsack3(<ull>, <uint>, <ull>, ull) {{{
#include <algorithm>
#include <numeric>
unsigned long long knapsack3(const vector< unsigned long long >& x,
                             const vector< unsigned >& y,
                             const vector< unsigned long long >& z,
                             unsigned long long W) {
  using ull = unsigned long long;
  size_t n = x.size();
  assert(n == y.size());
  assert(n == z.size());
  if(n == 0) return 0;
  size_t Y = 0;
  for(size_t i = 0; i < n; i++)
    if(Y < y[i]) Y = y[i];
  if(Y == 0) return 0;
  vector< size_t > ord(n);
  iota(begin(ord), end(ord), 0);
  sort(rbegin(ord), rend(ord),
       [&](size_t a, size_t b) { return (double) y[a] * x[b] < (double) y[b] * x[a]; });

  vector< ll > nx(n);
  vector< unsigned > ny(n);
  vector< unsigned > nz(n);
  vector< ull > zz(n);

  for(size_t i = 0; i < n; i++) {
    nx[i] = x[ord[i]];
    ny[i] = y[ord[i]];

    nz[i] = min(z[ord[i]], (ull) Y - 1);
    zz[i] = z[ord[i]] - nz[i];
  }

  auto sub = knapsack2(nx, ny, nz, W);

  vector< ull > xz_sum(n);
  vector< ull > yz_sum(n);
  for(size_t i = 0; i < n; i++) xz_sum[i] = nx[i] * zz[i];
  for(size_t i = 0; i < n; i++) yz_sum[i] = ny[i] * zz[i];
  for(size_t i = 1; i < n; i++) xz_sum[i] = min(xz_sum[i - 1] + xz_sum[i], W + 1);
  for(size_t i = 1; i < n; i++) yz_sum[i] = yz_sum[i - 1] + yz_sum[i];

  ull res = 0;
  // O(N Y^2 log N)
  for(unsigned v = 0; v < sub.size(); v++) {
    ull use = sub[v];
    if(use > W) continue;
    ull rest = W - use;
    size_t xp = upper_bound(begin(xz_sum), end(xz_sum), rest) - begin(xz_sum);
    ull val = v;
    if(xp >= 1) val += yz_sum[xp - 1], rest -= xz_sum[xp - 1];
    assert(xp == n || nx[xp] != 0); // explicit
    if(xp < n) val += rest / nx[xp] * ny[xp];
    if(res < val) res = val;
  }

  return res;
}
// }}}
