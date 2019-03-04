// @import header
// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// @@
// @ LCP Array Library
// @snippet lcp_array
// require SA
/// --- LCP Array Library {{{ ///
#include<vector>
template < class S = SA<> >
struct LCP {
  using T = typename S::T;
  using size_type = size_t;
  const size_type n;
  const T &s;
  std::vector< size_type > lcp;
  int operator[](int i) const { return lcp[i]; }
  LCP(const S &sa) : n(sa.n), s(sa.s), lcp(n - 1) {
    size_type h = 0;
    for(size_type i = 0; i < n; i++) {
      if(h) h--;
      if(sa.rnk[i] == 0) continue;
      size_type j = sa[sa.rnk[i] - 1];
      while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
      lcp[sa.rnk[i] - 1] = h;
    }
  }
};
/// }}}--- ///
