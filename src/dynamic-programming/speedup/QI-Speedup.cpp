// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Convex QI Speedup
// @snippet convex_qi_speedup
// @alias dp_convex_qi_speedup
// @alias monge_inverse_speedup
// @alias speedup_convex_qi

// D(0) is given
// D(i) = f( min(0 <= j < i,  D(j) + w(j, i)) , i)
// w must satisfy Convex QI
// Convex QI is w[===] + w[-=-] <= w[==-] + w[-==]
// by default, f is identity function
// O(n log n)
// NOTE : w(j, i) is 1-indexed
// Convex QI Speedup {{{
#include <cassert>
#include <functional>
#include <stack>
#include <type_traits>
#include <vector>
template < class T, class W, class F = function< T(const T &) > >
auto ConvexQISpeedup(T d0, size_t n, const W &w,
                     const F &f = [](const T &t) { return t; }) {
#ifdef DEBUG
  static_assert(is_same< T, decltype(w(0, 0)) >::value, "T must equal to typeof w(...)");
  static_assert(is_same< T, decltype(f(d0)) >::value, "T must equal to typeof f(...)");
#endif

  vector< T > D(n + 1);
  D[0] = d0;

  // C(j, i) = D(j) + w(j, i)
  auto C = [&](size_t j, size_t i) { return D[j] + w(j, i); };

  // search the first time to choose l rather than k
  // if w satisfies Closest Zero Property, you can speedup h
  auto h = [&](size_t l, size_t k) {
    assert(l < k && k < n + 1);
    size_t ok = n + 1, ng = k;
    while(ok - ng > 1) {
      size_t mid = (ok + ng) >> 1;
      if(C(l, mid) <= C(k, mid))
        ok = mid;
      else
        ng = mid;
    }
    return ok;
  };

  // (k, h) where k is index and h is the time to die
  stack< pair< size_t, size_t > > S;
  S.emplace(0, n + 1);
  for(size_t i = 1; i <= n; i++) {
    size_t j = S.top().first;
    if(C(i - 1, i) >= C(j, i))
      D[i] = f(C(j, i));
    else {
      D[i] = f(C(i - 1, i));
      while(S.size() &&
            C(i - 1, S.top().second - 1) < C(S.top().first, S.top().second - 1))
        S.pop();
      if(S.empty())
        S.emplace(i - 1, n + 1);
      else
        S.emplace(j, h(S.top().first, i - 1));
    }
    if(S.top().second == i + 1) S.pop();
  }
  return D;
}
// }}}

// @new
// @ Concave QI ( = Monge ) Speedup
// @snippet concave_qi_speedup
// @alias dp_concave_qi_speedup
// @alias monge_speedup
// @alias speedup_concave_qi

// D(0) is given
// D(i) = f( min(0 <= j < i,  D(j) + w(j, i)) , i)
// w must satisfy Concave QI = Monge
// Concave QI is w[===] + w[-=-] >= w[==-] + w[-==]
// by default, f is identity function
// O(n log n)
// NOTE : w(j, i) is 1-indexed
// Concave QI ( = Monge ) Speedup {{{
#include <cassert>
#include <deque>
#include <functional>
#include <type_traits>
#include <vector>
template < class T, class W, class F = function< T(const T &) > >
auto ConcaveQISpeedup(T d0, size_t n, const W &w,
                      const F &f = [](const T &t) { return t; }) {
#ifdef DEBUG
  static_assert(is_same< T, decltype(w(0, 0)) >::value, "T must equal to typeof w(...)");
  static_assert(is_same< T, decltype(f(d0)) >::value, "T must equal to typeof f(...)");
#endif

  vector< T > D(n + 1);
  D[0] = d0;

  // C(j, i) = D(j) + w(j, i)
  auto C = [&](size_t j, size_t i) { return D[j] + w(j, i); };

  // search the first time to choose l rather than k
  // if w satisfies Closest Zero Property, you can speedup h
  auto h = [&](size_t l, size_t k) {
    assert(k < l && l < n + 1);
    size_t ok = n + 1, ng = l;
    while(ok - ng > 1) {
      size_t mid = (ok + ng) >> 1;
      if(C(l, mid) <= C(k, mid))
        ok = mid;
      else
        ng = mid;
    }
    return ok;
  };

  // (k, h) where k is index and h is the time to kill predecessor
  deque< pair< size_t, size_t > > Q;
  Q.emplace_back(0, 1);
  for(size_t i = 1; i <= n; i++) {
    assert(Q.size());
    size_t j = Q.front().first;
    if(C(i - 1, i) <= C(j, i)) {
      D[i] = f(C(i - 1, i));
      Q.clear();
      Q.emplace_back(i - 1, i + 1);
    } else {
      D[i] = f(C(j, i));
      while(Q.size() > 1 &&
            C(i - 1, Q.back().second) <= C(Q.back().first, Q.back().second))
        Q.pop_back();
      size_t k = h(i - 1, Q.back().first);
      if(k < n + 1) Q.emplace_back(i - 1, k);
      if(Q.size() > 1 && i + 1 == Q[1].second)
        Q.pop_front();
      else
        Q.front().second++;
    }
  }
  return D;
}
// }}}
