// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ uniq, compress
// @snippet uniq
// @alias compress

// uniq, compress {{{
#include <algorithm>
#include <map>
#include <vector>
template < class T >
void uniq(vector< T > &v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}
template < class T >
map< T, int > compress(const vector< T > &v) {
  map< T, int > mp;
  int i = -1;
  for(auto &e : v) mp[e] = ++i;
  return mp;
}
// }}}

// @new
// @ smin, smax
// @snippet smin
// @alias smax

// smin, smax {{{
// clang-format off
template < class T, class U > inline void smin(T &a, const U &b) { a = a < (T) b ? a : b; }
template < class T, class U > inline void smax(T &a, const U &b) { a = a < (T) b ? b : a; }
// clang-format on
// }}}

// @new
// @ isInside
// @snippet isinside
// @alias inside outside

bool isInside(int y, int x, int h, int w) { return 0 <= y && 0 <= x && y < h && x < w; }
