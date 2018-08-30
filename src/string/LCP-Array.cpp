// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ LCP Array Library
// @snippet lcp_array
// require SA
/// --- LCP Array Library {{{ ///

template < class S = SA<> >
struct LCP {
  using T = typename S::T;
  const int n;
  const T &s;
  vector< int > lcp;
  int operator[](int i) const { return lcp[i]; }
  LCP(const S &sa) : n(sa.n), s(sa.s), lcp(n - 1) {
    int h = 0;
    for(int i = 0; i < n; i++) {
      if(h) h--;
      if(sa.rnk[i] == 0) continue;
      int j = sa[sa.rnk[i] - 1];
      while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
      lcp[sa.rnk[i] - 1] = h;
    }
  }
};

/// }}}--- ///
