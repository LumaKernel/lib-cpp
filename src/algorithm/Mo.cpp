// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Mo Library
// @snippet mo

// Mo(N, JUST Q, double k)
// favored : k = 2
// 1: insert
// 2: build
/// --- Mo Library {{{ ///

struct Mo {
  const int width;
  int q = 0;
  vector< int > le, ri, order;
  int nl = 0, nr = 0;
  Mo(int n, int q, double k = 1)
      : width(int(k* n / sqrt(q) + 1.0)), le(q), ri(q), order(q) {}
  inline void insert(int l, int r) {
    le[q] = l;
    ri[q] = r;
    order[q] = q;
    q++;
  }
  inline void build() {
    sort(begin(order), begin(order) + q, [&](int a, int b) {
      const int ab = le[a] / width, bb = le[b] / width;
      return ab != bb ? ab < bb : ab & 1 ? ri[a] < ri[b] : ri[b] < ri[a];
    });
    nl = nr = le[order[0]];
    for(int i = 0; i < q; i++) {
      const int id = order[i];
      while(nl > le[id]) add(--nl);
      while(nl < le[id]) rem(nl++);
      while(nr < ri[id]) add(nr++);
      while(nr > ri[id]) rem(--nr);
      next(id);
    }
  }
  inline void next(int i);
  inline void add(int i);
  inline void rem(int i);
};

/// }}}--- ///

inline void Mo::next(int i) {}
inline void Mo::add(int i) {}
inline void Mo::rem(int i) {}
