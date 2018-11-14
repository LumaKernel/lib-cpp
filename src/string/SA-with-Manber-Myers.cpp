// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Suffix Array with Manber & Myers
// @snippet sa_manber_myers
/// --- Suffix Array with Manber & Myers {{{ ///

template < class _T = string >
struct SA {
  using T = _T;
  const int n;
  const T &s;
  vector< int > rnk;
  vector< int > sa;
  int operator[](int i) const { return sa[i]; }
  SA(const T &s) : n(s.size()), s(s), rnk(n), sa(n) {
    iota(begin(sa), end(sa), 0);
    sort(begin(sa), end(sa), [&](int a, int b) { return s[a] < s[b]; });
    for(int i = 0; i < n; i++) rnk[i] = s[i];
    for(int i = 1; i < n; i <<= 1) {
      auto comp = [&](int a, int b) {
        if(rnk[a] != rnk[b]) return rnk[a] < rnk[b];
        a = a + i < n ? rnk[a + i] : -1;
        b = b + i < n ? rnk[b + i] : -1;
        return a < b;
      };
      sort(begin(sa), end(sa), comp);
      auto tmp = rnk;
      tmp[sa[0]] = 0;
      for(int j = 1; j < n; j++)
        tmp[sa[j]] = tmp[sa[j - 1]] + comp(sa[j - 1], sa[j]); ///
      rnk = tmp;
    }
  }
};

/// }}}--- ///
