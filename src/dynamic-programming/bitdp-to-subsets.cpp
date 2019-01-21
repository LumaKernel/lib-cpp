// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ bitdp subsets non-zero
// @snippet bitdp_subsets_nonzero
// @alias dp_bitdp_subsets_nonzero
// @alias sanjou_bitdp_subsets_nonzero
// @alias subsets_nonzero_bitdp

int dp[1 << S] = {};
dp[0] = 0;
for(int i = 1; i < 1 << S; i++) {
  for(int j = i; j > 0; j = (j - 1) & i) {
  }
}

// @new
// @ bitdp subsets zero
// @snippet bitdp_subsets_zero
// @alias dp_bitdp_subsets_zero
// @alias sanjou_bitdp_subsets_zero
// @alias subsets_zero_bitdp

int dp[1 << S] = {};
dp[0] = 0;
for(int i = 1; i < 1 << S; i++) {
  for(int j = i, f = 1; f; j = (j - 1) & i, f = j != 0) {
  }
}

// @new
// @ bitdp supset
// @snippet bitdp_supset
// @alias dp_bitdp_supset
// @alias sanjou_bitdp_supset
// @alias supset_bitdp

int dp[1 << S] = {};
dp[(1 << S) - 1] = 0;
for(int i = (1 << S) - 2; i >= 0; i--) {
  for(int j = i; j < 1 << S; j = (j + 1) | i) {
  }
}

