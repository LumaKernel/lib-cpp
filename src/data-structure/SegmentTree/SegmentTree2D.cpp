// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     seg2d
// @name 2D SegmentTree Library
// @title 二次元セグメントツリー
// @alias        static_seg_2d 2d_seg
// constructor(int sizex, int sizey, T identity, func merge)
// WARN : query in range by yourself!
/// --- 2D SegmentTree Library {{{ ///

template < class T >
struct SegTree2D {
  vector< T > dat;
  int sizex, sizey;
  T identity;
  function< T(T, T) > merge;
  SegTree2D(int tx, int ty, T identity, function< T(T, T) > merge)
      : identity(identity), merge(merge) {
    sizex = sizey = 1;
    while(tx > sizex) sizex <<= 1;
    while(ty > sizey) sizey <<= 1;
    dat = vector< T >(sizex * sizey * 4, identity);
  }
  void set(int x, int y, T const &val) {
    int kx = x + sizex - 1, ky = y + sizey - 1;
    dat[kx * sizey * 2 + ky] = val;
    sety(kx, y);
    while(kx > 0) {
      kx = (kx - 1) / 2;
      ky = y + sizey - 1;
      dat[kx * sizey * 2 + ky] = merge(dat[(kx * 2 + 1) * sizey * 2 + ky],
                                       dat[(kx * 2 + 2) * sizey * 2 + ky]);
      sety(kx, y);
    }
  }
  void act(int x, int y, T const &val) {
    int kx = x + sizex - 1, ky = y + sizey - 1;
    set(x, y, merge(dat[kx * sizey * 2 + ky], val));
  }

private:
  void sety(int kx, int y) {
    int ky = y + sizey - 1;
    while(ky > 0) {
      ky = (ky - 1) / 2;
      dat[kx * sizey * 2 + ky] = merge(dat[kx * sizey * 2 + ky * 2 + 1],
                                       dat[kx * sizey * 2 + ky * 2 + 2]);
    }
  }

public:
  T query(int xl, int xr, int yl, int yr) {
    return queryx(xl, xr, yl, yr, 0, sizex, 0);
  }

private:
  T queryx(int xl, int xr, int yl, int yr, int sxl, int sxr, int k) {
    if(xr <= sxl || sxr <= xl) return identity;
    if(xl <= sxl && sxr <= xr) return queryy(k, yl, yr, 0, sizey, 0);
    return merge(queryx(xl, xr, yl, yr, sxl, (sxl + sxr) / 2, k * 2 + 1),
                 queryx(xl, xr, yl, yr, (sxl + sxr) / 2, sxr, k * 2 + 2));
  }
  T queryy(int kx, int yl, int yr, int syl, int syr, int k) {
    if(yr <= syl || syr <= yl) return identity;
    if(yl <= syl && syr <= yr) return dat[kx * sizey * 2 + k];
    return merge(queryy(kx, yl, yr, syl, (syl + syr) / 2, k * 2 + 1),
                 queryy(kx, yl, yr, (syl + syr) / 2, syr, k * 2 + 2));
  }
};

/// }}}--- ///
