// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Mo with Persistent Data Structure Library
// @snippet mo_ex
// @alias moex mo2

// MoEx(N, JUST Q, double k)
// favored : k = 2
// 1: insert
// 2: build
/// --- Mo with Persistent Data Structure Library {{{ ///

struct MoEx {
  const int width;
  int q = 0;
  vector< int > le, ri, order;
  MoEx(int n, int q, double k = 1)
      : width(int(k* n / sqrt(q) + 1.0)), le(q), ri(q), order(q) {}
  inline void insert(int l, int r) {
    le[q] = l;
    ri[q] = r;
    order[q] = q;
    q++;
  }
  inline void build() {
    for(int i = 0; i < q; i++)
      if(ri[i] - le[i] < width) {
        init();
        for(int j = le[i]; j < ri[i]; j++) add(j);
        next(i);
      }
    sort(begin(order), begin(order) + q, [&](int a, int b) {
      const int ab = le[a] / width, bb = le[b] / width;
      return ab != bb ? ab < bb : ri[a] < ri[b];
    });
    int last = -1;
    int nr;
    for(int i = 0; i < q; i++) {
      int id = order[i];
      if(ri[id] - le[id] < width) continue;
      int b = le[id] / width;
      if(last != b) init(), nr = (b + 1) * width;
      last = b;
      while(nr < ri[id]) add(nr++);
      snapshot();
      for(int j = (b + 1) * width - 1; j >= le[id]; j--) add(j);
      next(id);
      rollback();
    }
  }
  inline void next(int id);
  inline void init();
  inline void snapshot();
  inline void rollback();
  inline void add(int i);
};

/// }}}--- ///

inline void MoEx::next(int id) {}
inline void MoEx::init() {}
inline void MoEx::snapshot() {}
inline void MoEx::rollback() {}
inline void MoEx::add(int i) {}
