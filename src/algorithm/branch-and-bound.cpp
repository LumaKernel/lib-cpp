// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ 01-Knapsack Problem Solver with Branch and bound
// @snippet knapsack01_branch_and_bound
// @alias 01knapsack_branch_and_bound
// @alias bunsigentei_01knapsack

// knapsack01_branch_and_bound(<ull> cost, <ull> value, ull weight) {{{
// 01-knapsack problem solver with branch and bound
#include <stack>
#include <tuple>
#include <vector>
unsigned long long knapsack01_branch_and_bound(const vector< unsigned long long > &cost,
                                               const vector< unsigned long long > &value,
                                               unsigned long long weight) {
  using size_type = size_t;
  using ull = unsigned long long;
  using item_type = pair< ull, ull >;
  using float_type = double;

  size_type _n = cost.size();
  assert(_n == value.size());
  vector< item_type > items(1);

  for(size_type i = 0; i < _n; i++) {
    assert(cost[i] > 0);
    if(cost[i] <= weight) items.emplace_back(value[i], cost[i]);
  }

  size_type n = items.size() - 1;

  sort(begin(items) + 1, end(items), [&](const item_type &a, const item_type &b) {
    return (float_type) a.first / a.second > (float_type) b.first / b.second;
  });

  vector< ull > value_sum(n + 1), cost_sum(n + 1);

  for(size_type i = 1; i <= n; i++)
    value_sum[i] = value_sum[i - 1] + items[i].first,
    cost_sum[i] = cost_sum[i - 1] + items[i].second;

  ull feasible_best = 0; // this satisfies the constraints

  using state_type = tuple< size_type, ull, ull >;
  stack< state_type > stk;
  stk.emplace(1, 0, weight);

  while(stk.size()) {
    size_type i;
    ull now_value, rest;
    tie(i, now_value, rest) = stk.top();
    stk.pop();

    if(rest == 0) continue;

    size_type ok = i - 1, ng = n + 1;
    while(ng - ok > 1) {
      size_type mid = (ng + ok) >> 1;
      ull extra_cost = cost_sum[mid] - cost_sum[i - 1];
      if(extra_cost <= rest)
        ok = mid;
      else
        ng = mid;
    }

    ull extra_cost = cost_sum[ok] - cost_sum[i - 1];
    ull extra_value = value_sum[ok] - value_sum[i - 1];

    feasible_best = max(feasible_best, now_value + extra_value);

    float_type relax_upper_bound = now_value + extra_value;
    if(ok + 1 <= n)
      relax_upper_bound +=
          (float_type) items[ok + 1].first / items[ok + 1].second * (rest - extra_cost);

    if(floor(relax_upper_bound) <= feasible_best) continue;

    if(i < n) {
      // drop
      stk.emplace(i + 1, now_value, rest);
      // adopt
      if(rest >= items[i].second)
        stk.emplace(i + 1, now_value + items[i].first, rest - items[i].second);
    }
  }

  return feasible_best;
}
// }}}
