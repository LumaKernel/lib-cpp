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
template < class T, class U >
inline void smin(T &a, const U &b) {
  a = a < (T) b ? a : b;
}
template < class T, class U >
inline void smax(T &a, const U &b) {
  a = a < (T) b ? b : a;
}
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

// @new
// @ Indexer
// @snippet indexer
// @alias indexed

// Indexer {{{
#include <functional>
#include <ostream>
template < class T, template < class > class Compare = less >
struct Indexer {
  static Compare< int > comp;
  T val;
  int i;
  Indexer(T val = T(), int i = 0) : val(val), i(i) {}
  Indexer &setValue(int val) { this->val = val; }
  Indexer &setIndex(int i) { this->i = i; }
  bool operator<(const Indexer &a) const {
    if(val < a.val) return true;
    if(a.val < val) return false;
    if(i != a.i) return comp(i, a.i);
    return false;
  }
  Indexer &operator+=(const T &a) {
    val += a;
    return *this;
  }
  Indexer &operator-=(const T &a) {
    val -= a;
    return *this;
  }
  Indexer &operator*=(const T &a) {
    val *= a;
    return *this;
  }
  Indexer &operator/=(const T &a) {
    val /= a;
    return *this;
  }
  Indexer operator+() const {
    Indexer tmp = *this;
    tmp.val = +tmp.val;
    return tmp;
  }
  Indexer operator-() const {
    Indexer tmp = *this;
    tmp.val = -tmp.val;
    return tmp;
  }
  Indexer operator+(const T &a) const {
    Indexer tmp = *this;
    tmp += a;
    return tmp;
  }
  Indexer operator-(const T &a) const {
    Indexer tmp = *this;
    tmp -= a;
    return tmp;
  }
  Indexer operator*(const T &a) const {
    Indexer tmp = *this;
    tmp *= a;
    return tmp;
  }
  Indexer operator/(const T &a) const {
    Indexer tmp = *this;
    tmp /= a;
    return tmp;
  }
  friend Indexer operator+(const T &a, const Indexer &b) {
    Indexer tmp = b;
    tmp.val = a + tmp.val;
    return tmp;
  }
  friend Indexer operator-(const T &a, const Indexer &b) {
    Indexer tmp = b;
    tmp.val = a - tmp.val;
    return tmp;
  }
  friend Indexer operator*(const T &a, const Indexer &b) {
    Indexer tmp = b;
    tmp.val = a * tmp.val;
    return tmp;
  }
  friend Indexer operator/(const T &a, const Indexer &b) {
    Indexer tmp = b;
    tmp.val = a / tmp.val;
    return tmp;
  }
  friend ostream &operator<<(ostream &os, const Indexer &a) {
    return os << "(" << a.val << ", i: " << a.i << ")";
  }
};
template < class T, template < class > class Compare >
Compare< int > Indexer< T, Compare >::comp;
// }}}
