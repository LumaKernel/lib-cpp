// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Accumulation 2D Utility
// @snippet range2d
// @alias acum2d 2d_range_accum

// range2D accum2D {{{

template < class T, class U = ll >
U range2D(T &val, int y1, int x1, int y2, int x2, int h, int w) {
  if(y1 < 0) y1 = 0;
  if(x1 < 0) x1 = 0;
  if(y2 >= h) y2 = h - 1;
  if(x2 >= w) x2 = w - 1;
  if(y1 > y2 || x1 > x2) return U(0);
  U res = val[y2][x2];
  if(y1 - 1 >= 0) res -= val[y1 - 1][x2];
  if(x1 - 1 >= 0) res -= val[y2][x1 - 1];
  if(y1 - 1 >= 0 && x1 - 1 >= 0) res += val[y1 - 1][x1 - 1];
  return res;
}

template < class T >
void accum2D(T &val, int h, int w) {
  for(int i = 1; i < h; i++)
    for(int j = 0; j < w; j++) val[i][j] += val[i - 1][j];
  for(int i = 0; i < h; i++)
    for(int j = 1; j < w; j++) val[i][j] += val[i][j - 1];
}

// }}}
