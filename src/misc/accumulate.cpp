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
ll range2D(T &val, int y1, int x1, int y2, int x2, int h, int w) {
  if(y1 < 0) y1 = 0;
  if(x1 < 0) x1 = 0;
  if(y2 >= h) y2 = h - 1;
  if(x2 >= w) x2 = w - 1;
  if(y1 > y2 || x1 > x2) return ll(0);
  ll res(val[y2][x2]);
  if(y1 - 1 >= 0) res -= val[y1 - 1][x2];
  if(x1 - 1 >= 0) res -= val[y2][x1 - 1];
  if(y1 - 1 >= 0 && x1 - 1 >= 0) res += val[y1 - 1][x1 - 1];
  return res;
}

template < class T >
ll range2Dloop(T &val, ll ty1, ll tx1, ll y2, ll x2, int h, int w) {
  if(ty1 > y2 || tx1 > x2) return ll(0);

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

  ll res(0);
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
