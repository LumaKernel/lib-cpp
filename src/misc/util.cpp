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

// @new
// @ Unique Overlaps
// @snippet unique_overlaps
// @alias remove_overlaps
// @alias overlaps_remove

// uniqueOverlaps {{{
template < class T >
vector< pair< T, T > > uniqueOverlaps(const vector< pair< T, T > > &v) {
  sort(v.begin(), v.end());
  vector< pair< T, T > > w;
  pair< T, T > now = v[0];
  for(size_t i = 1; i < v.size(); i++) {
    if(v[i].first <= now.second && now.second <= v[i].second)
      now.second = v[i].second;
    else
      w.push_back(now), now = v[i];
  }
  w.push_back(now);
  return w;
}
// }}}

// @new
// @ construct modinv
// @snippet construct_modinvs
// @alias modinvs_construct
// @comment TODO : maintenance it

// construct_modinvs {{{
vector< ll > construct_modinvs(int n, ll mod = ll(1e9 + 7)) {
  vector< ll > res(n + 1);
  res[1] = 1;
  for(int i = 2; i <= n; i++) res[i] = mod - res[mod % i] * (mod / i) % mod;
  return res;
}
// }}}
