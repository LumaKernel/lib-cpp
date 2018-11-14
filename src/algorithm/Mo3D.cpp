// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Mo3D Library
// @snippet mo3d
// @snippet mo_time

// Mo3D(N, JUST Q, double k)
// favored : k = 6
// 1: insert
// 2: build
/// --- Mo3D Library {{{ ///

struct Mo3D {
  const int width;
  int q = 0;
  vector< int > le, ri, idx, order;
  int nl = 0, nr = 0, time = -1;
  Mo3D(int n, int q, double k = 1)
      : width(int(k* pow(max(n, q), 2.0 / 3.0) + 1.0)),
        le(q),
        ri(q),
        idx(q),
        order(q) {}
  inline void insert(int t, int l, int r) {
    idx[q] = t;
    le[q] = l;
    ri[q] = r;
    order[q] = q;
    q++;
  }
  inline void build() {
    sort(begin(order), begin(order) + q, [&](int a, int b) {
      const int al = le[a] / width, bl = le[b] / width;
      const int ar = ri[a] / width, br = ri[b] / width;
      return al != bl ? al < bl : ar != br ? ar < br : idx[a] < idx[b];
    });
    nl = nr = le[order[0]];
    for(int i = 0; i < q; i++) {
      const int id = order[i];
      while(time < idx[id]) addQuery(++time);
      while(time > idx[id]) remQuery(time--);
      while(nl > le[id]) add(--nl);
      while(nr < ri[id]) add(nr++);
      while(nl < le[id]) rem(nl++);
      while(nr > ri[id]) rem(--nr);
      next(id);
    }
  }
  inline void next(int i);
  inline void addQuery(int i);
  inline void remQuery(int i);
  inline void add(int i);
  inline void rem(int i);
};

/// }}}--- ///

// i is sequential
// idx[i] is absolute
inline void Mo3D::next(int i) {}
inline void Mo3D::addQuery(int i) {}
inline void Mo3D::remQuery(int i) {}
inline void Mo3D::add(int i) {}
inline void Mo3D::rem(int i) {}
