// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name mp
// @snippet mp

// [i] = size of longest common suffix and prefix in s[0,i-1]
// momentary O(N)
// overall O(N)
// MP {{{

#include <string>
#include <vector>

template < class T >
vector< int > MP(T s) {
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

// }}}

// @new
// @ kmp
// @snippet kmp

// [i] = size of longest common suffix and prefix in s[0,i-1]
// momentary O(log N)
// overall O(N)
// KMP {{{

#include <string>
#include <vector>

template < class T >
vector< int > KMP(T s) {
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

// }}}

// @new
// @ findstr with KMP
// @snippet findsttr

// require kmp
// findstr(a, b [, pos]) == a.find(b [, pos])
// O(N + M)
// findstr with KMP {{{

#include <string>
#include <vector>

template < class T >
int findstr(const T &a, const T &b, int pos = 0) {
  if(a.size() < b.size()) return -1;
  int n = a.size(), m = b.size();
  int j = 0;
  vector< int > kmp = KMP(b);
  for(int i = pos; i < n; i++) {
    while(a[i] != b[j] && j >= 0) j = kmp[j];
    ++j;
    if(j == m) return i - m + 1;
  }
  return -1;
}

// }}}

// @new
// @ cycle
// @snippet cycle

// require kmp
// [i] = min cycle length in [0,i]
// NOTE : not always JUST
// cycle {{{

#include <string>
#include <vector>

template < class T >
vector< int > cycle(T s) {
  auto mp = KMP(s);
  vector< int > len(s.size());
  for(int i = 0; i < (int) s.size(); i++) len[i] = i + 1 - mp[i + 1];
  return len;
}

// }}}
