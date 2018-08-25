// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name mp
// @snippet     mp
// [i] = size of longest common suffix and prefix in s[0:i-1]
// 瞬間最悪計算量 O(N)
// 均し計算量 O(N)
vector< int > MP(string s) {
  int n = s.size();
  vector< int > A(n + 1);
  A[0] = -1;
  int j = -1;
  for(int i = 0; i < n; i++) {
    while(j >= 0 && s[i] != s[j]) j = A[j];
    A[i + 1] = ++j;
  }
  return A;
}

// @new kmp
// @snippet     kmp
// [i] = size of longest common suffix and prefix in s[0:i-1]
// 瞬間最悪計算量 O(log N)
// 均し計算量 O(N)
vector< int > KMP(string s) {
  int n = s.size();
  vector< int > kmp(n + 1), mp(n + 1);
  kmp[0] = mp[0] = -1;
  int j = -1;
  for(int i = 0; i < n; i++) {
    while(j >= 0 && s[i] != s[j]) j = kmp[j];
    kmp[i + 1] = mp[i + 1] = ++j;
    if(i + 1 < n && s[i + 1] == s[j]) kmp[i + 1] = kmp[j];
  }
  return mp;
}

// @new cycle
// @snippet     cycle
// [i] = min cycle length in [0:i-1]
// 最小周期長
// NOTE : justである必要なし
vector< int > cycle(string s) {
  auto mp = MP(s);
  vector< int > len(s.size());
  for(int i = 0; i < (int) s.size(); i++) len[i] = i + 1 - mp[i + 1];
  return len;
}
