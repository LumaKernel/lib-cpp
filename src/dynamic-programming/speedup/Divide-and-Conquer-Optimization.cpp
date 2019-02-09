// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Divide and Conquer Optimization
// @snippet dac
// @alias daq divide_a_c_opt opt_dac

// require Monotone Minima
// f(i, j) = min(0 <= k < j, g(i, j, k))
// f(0, j) = w_i[0, j]
// where g(i, j, k) = f(i - 1, k) + w_i[k + 1, j]
// A[i][j] := min argmin(0 <= k < j, g(i, j, k))
// NOTE : f(i, j) = g(i, j, A[i][j])
// A must satisfy A[i][j] <= A[i][j + 1]
// That w satisfies Convex QI is sufficient
// Convex QI is w[|===|] + w[|-=-|] >= w[|-==|] + w[|==-|]
// time : O(n m log m)
// space : O(nm)
// return f[n][m] vector
/// --- Divide and Conquer Optimization {{{ ///
#include <type_traits>
#include <vector>
template < class T, class F >
auto DACOptimization(size_t n, size_t m, T identity, const F &w) {
#ifdef DEBUG
  static_assert(
      is_same< T, decltype(w(0, 0, 0)) >::value, "T must equal to typeof w(...)");
#endif
  vector< vector< T > > f(n, vector< T >(m));
  for(size_t i = 0; i < m; i++) f[0][i] = w(0, 0, i);
  for(size_t i = 1; i < n; i++) {
    // 0 <= k < j
    auto h = [&](int j, int k) {
      auto val = w(i, k + 1, j);
      if(i > 0) val += f[i - 1][k];
      return val;
    };
    auto argmin = MonotoneMinima< T >(m, m, h, identity, LOWER_EXCLUSIVE);
    for(size_t j = 0; j < m; j++) f[i][j] = argmin[j].second;
  }
  return f;
}
/// }}}--- ///
