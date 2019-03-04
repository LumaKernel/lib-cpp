// @ Suffix Array with Manber & Myers
// @snippet sa_manber_myers
/// --- Suffix Array with Manber & Myers {{{ ///
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
template < class _T = std::string >
struct SA {
  using T = _T;
  using size_type = size_t;
  const size_type n;
  const T &s;
  std::vector< size_type > rnk;
  std::vector< size_type > sa;
  size_type operator[](size_type i) const { return sa[i]; }
  SA(const T &s) : n(s.size()), s(s), rnk(n), sa(n) {
    iota(begin(sa), end(sa), 0);
    sort(begin(sa), end(sa), [&](size_type a, size_type b) { return s[a] < s[b]; });
    for(size_type i = 0; i < n; i++) rnk[i] = s[i];
    for(size_type i = 1; i < n; i <<= 1) {
      auto comp = [&](size_type a, size_type b) {
        if(rnk[a] != rnk[b]) return rnk[a] < rnk[b];
        a = a + i < n ? rnk[a + i] : -1;
        b = b + i < n ? rnk[b + i] : -1;
        return a < b;
      };
      sort(begin(sa), end(sa), comp);
      auto tmp = rnk;
      tmp[sa[0]] = 0;
      for(size_type j = 1; j < n; j++)
        tmp[sa[j]] = tmp[sa[j - 1]] + comp(sa[j - 1], sa[j]); ///
      rnk = tmp;
    }
  }
};
/// }}}--- ///
