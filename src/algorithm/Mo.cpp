// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Mo Library
// @snippet mo

// Mo(N, JUST Q, double k)
// WARN : write "int id = mo.next();"
// 1: insert
// 2: build
// 3: next...
/// --- Mo Library {{{ ///

struct Mo {
  const int width;
  vector< int > le, ri, order;
  int nl = 0, nr = 0;
  Mo(int n, int q, double k = 1)
      : width(int(k* n / sqrt(q) + 1.0)), le(q), ri(q), order(q) {}
  inline void insert(int l, int r) {
    static int i = 0;
    le[i] = l;
    ri[i] = r;
    order[i] = i;
    i++;
  }
  inline void build() {
    sort(begin(order), end(order), [&](int a, int b) {
      const int ab = le[a] / width, bb = le[b] / width;
      return ab != bb ? ab < bb : ab & 1 ? ri[a] < ri[b] : ri[b] < ri[a];
    });
  }
  inline int next() {
    static int i = 0;
#ifdef DEBUG
    assert(i < (int) order.size());
#endif
    const int id = order[i++];
    while(nl > le[id]) add(--nl);
    while(nr < ri[id]) add(nr++);
    while(nl < le[id]) rem(nl++);
    while(nr > ri[id]) rem(--nr);
    return id;
  }
  inline void add(int i);
  inline void rem(int i);
};

/// }}}--- ///

inline void Mo::add(int i) {}

inline void Mo::rem(int i) {}
