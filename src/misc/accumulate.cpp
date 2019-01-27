// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Accumulation 2D Utility
// @snippet range2d
// @alias accum2d 2d_range_accum loop_range2d

// accum2D range2D range2Dloop {{{
template < class T >
void accum2D(T &val, int h, int w) {
  for(int i = 1; i < h; i++)
    for(int j = 0; j < w; j++) val[i][j] += val[i - 1][j];
  for(int i = 0; i < h; i++)
    for(int j = 1; j < w; j++) val[i][j] += val[i][j - 1];
}

template < class T >
auto range2D(T &val, int y1, int x1, int y2, int x2, int h, int w) {
  using V = decltype(val[0][0]);
  if(y2 >= h) y2 = h - 1;
  if(x2 >= w) x2 = w - 1;
  if(y1 > y2 || x1 > x2) return V(0);
  V res(val[y2][x2]);
  if(y1 - 1 >= 0) res -= val[y1 - 1][x2];
  if(x1 - 1 >= 0) res -= val[y2][x1 - 1];
  if(y1 - 1 >= 0 && x1 - 1 >= 0) res += val[y1 - 1][x1 - 1];
  return res;
}

template < class T >
auto range2Dloop(T &val, ll ty1, ll tx1, ll y2, ll x2, int h, int w) {
  using V = decltype(val[0][0]);
  if(ty1 > y2 || tx1 > x2) return V(0);

  ll y1 = ty1 % h;
  if(y1 < 0) y1 += h;
  ll x1 = tx1 % w;
  if(x1 < 0) x1 += w;

  y2 += y1 - ty1;
  x2 += x1 - tx1;

  ll gy = y2 / h;
  ll gx = x2 / w;
  y2 %= h;
  x2 %= w;

  V res(0);
  if(gy == 0 && gx == 0) {
    res += range2D< T >(val, y1, x1, y2, x2, h, w);
  } else if(gy == 0) {
    res += range2D< T >(val, y1, x1, y2, w - 1, h, w);
    res += range2D< T >(val, y1, 0, y2, x2, h, w);
    res += range2D< T >(val, y1, 0, y2, w - 1, h, w) * (gx - 1);
  } else if(gx == 0) {
    res += range2D< T >(val, y1, x1, h - 1, x2, h, w);
    res += range2D< T >(val, 0, x1, y2, x2, h, w);
    res += range2D< T >(val, 0, x1, h - 1, x2, h, w) * (gy - 1);
  } else {
    res += range2D< T >(val, y1, x1, h - 1, w - 1, h, w);                     // UL
    res += range2D< T >(val, 0, x1, y2, w - 1, h, w);                         // DL
    res += range2D< T >(val, y1, 0, h - 1, x2, h, w);                         // UR
    res += range2D< T >(val, 0, 0, y2, x2, h, w);                             // DR
    res += range2D< T >(val, y1, 0, h - 1, w - 1, h, w) * (gx - 1);           // U
    res += range2D< T >(val, 0, 0, y2, w - 1, h, w) * (gx - 1);               // D
    res += range2D< T >(val, 0, x1, h - 1, w - 1, h, w) * (gy - 1);           // L
    res += range2D< T >(val, 0, x1, h - 1, x2, h, w) * (gy - 1);              // R
    res += range2D< T >(val, 0, 0, h - 1, w - 1, h, w) * (gy - 1) * (gx - 1); // C
  }
  return res;
}
// }}}

// @new
// @ Accumulation 1D Utility
// @snippet range1d
// @alias accum1d 1d_range_accum loop_range1d

// accum1D, range1D, range1Dloop {{{
#include<vector>
template<class T>
void accum1D(T &a, int n) {
  for(int i = 1; i < n; i++) a[i] += a[i-1];
}
template<class T>
void accum1D(vector<T> &a) {
  accum1D(a, a.size());
}
template<class T, int N>
void accum1D(T a[N]) {
  accum1D(a, N);
}

template<class T>
auto range1D(const T &a, int l, int r, int n) {
  if(r >= n) r = n - 1;
  auto res(a[r]);
  if(l - 1 >= 0) res -= a[l - 1];
  return res;
}
template<class T>
auto range1D(vector<T> &a, int l, int r) {
  return range1D(a, l, r, a.size());
}
template<class T, int N>
auto range1D(T a[N], int l, int r) {
  return range1D(a, l, r, N);
}

template<class T>
auto range1Dloop(const T &a, ll tl, ll r, int n) {
  decltype(a[0]) res(0);
  if(tl > r) return res;
  assert(n >= 1);
  ll l = tl % n;
  if(l < 0) l += n;
  r += l - tl;
  ll gr = r / n;
  if(gr == 0) {
    res += range1D<T>(a, l, r, n);
  } else {
    res += range1D<T>(a, l, n - 1, n);
    res += range1D<T>(a, 0, r % n, n);
    res += range1D<T>(a, 0, n - 1, n) * (gr - 1);
  }
  return res;
}
template<class T>
T range1Dloop(vector<T> &a, ll l, ll r) {
  return range1Dloop(a, l, r, a.size());
}
template<class T, int N>
T range1Dloop(T a[N], ll l, ll r) {
  return range1Dloop(a, l, r, N);
}
// }}}
