// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name PersistentSegmentTree Library
// @snippet     persistent_seg
// @alias       seg_persistent
// @ PersistentSegmentTree Library
// NOTE : query in range!
/// --- PersistentSegmentTree Library {{{ ///

// struct Monoid {
//   using T = _underlying_set_;
//   static T op(const T& a, const T& b) { return _a_op_b_; }
//   static constexpr T identity() { return _identity_element_; }
// };

template < class Monoid >
struct PersistentSegTree {
private:
  using T = typename Monoid::T;
  int n;
  vector< T > data;
  vector< int > lch, rch;
  int lastRoot = 0;

public:
  PersistentSegTree() : n(0) {}
  PersistentSegTree(int t) : data(1, Monoid::identity()), lch(1, 0), rch(1, 0) {
    n = 1;
    while(n < t) n <<= 1;
  }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  PersistentSegTree(InputIter first, InputIter last)
      : PersistentSegTree(distance(first, last)) {
    assign(first, last);
  }
  int set(int i, const T& v, int root = 0) {
    if(root == 0) root = lastRoot;
    int k = make();
    set(i, v, 0, n, k, root);
    lastRoot = k;
    return k;
  }
  template < class InputIter,
             class = typename iterator_traits< InputIter >::value_type >
  void assign(InputIter first, InputIter last) {
    assert(n >= distance(first, last));
    data.resize(n * 2 - 1, Monoid::identity());
    lch.resize(n * 2 - 1, 0);
    rch.resize(n * 2 - 1, 0);
    copy(first, last, begin(data) + n - 1);
    for(int i = n - 2; i >= 0; i--) {
      data[i] = Monoid::op(data[lch[i] = i * 2 + 1], data[rch[i] = i * 2 + 2]);
    }
  }
  void reserve(int qsize) {
    int h = log(n);
    data.reserve(n * 2 - 1 + qsize * h);
    lch.reserve(n * 2 - 1 + qsize * h);
    rch.reserve(n * 2 - 1 + qsize * h);
  }
  void set(int i, const T& v, int l, int r, int k, int prevK) {
    if(r - l == 1) {
      data[k] = v;
      return;
    }
    lch[k] = lch[prevK];
    rch[k] = rch[prevK];
    int x = make(); //// important where to calc
    if(i < ((l + r) >> 1)) {
      lch[k] = x;
      set(i, v, l, (l + r) >> 1, lch[k], lch[prevK]);
    } else {
      rch[k] = x;
      set(i, v, (l + r) >> 1, r, rch[k], rch[prevK]);
    }
    data[k] = Monoid::op(data[lch[k]], data[rch[k]]);
  }
  T get(int i, int root = 0) { return query(i, i + 1, root); }
  T query(int a, int b, int root = 0) {
    if(root == 0) root = lastRoot;
    return query(a, b, 0, n, root);
  }
  T query(int a, int b, int l, int r, int k) {
    if(k == 0) return Monoid::identity();
    if(b <= l || r <= a) return Monoid::identity();
    if(a <= l && r <= b) return data[k];
    return Monoid::op(query(a, b, l, (l + r) >> 1, lch[k]),
                      query(a, b, (l + r) >> 1, r, rch[k]));
  }

private:
  int make() {
    data.emplace_back(Monoid::identity());
    lch.emplace_back(0);
    rch.emplace_back(0);
    return data.size() - 1;
  }
  int log(int x) {
    int t = 0;
    while(x) x >>= 1, t++;
    return t;
  }
};

/// }}}--- ///

// persistent-seg examples {{{

struct RMQMonoid {
  using T = ll;
  static T op(const T& a, const T& b) { return min(a, b); }
  static constexpr T identity() { return numeric_limits< T >::max(); }
};
struct RSQMonoid {
  using T = ll;
  static T op(const T& a, const T& b) { return a + b; }
  static constexpr T identity() { return 0; }
};
struct RMaxQMonoid {
  using T = ll;
  static T op(const T& a, const T& b) { return max(a, b); }
  static constexpr T identity() { return numeric_limits< T >::min(); }
};

using RMQ = PersistentSegTree< RMQMonoid >;
using RSQ = PersistentSegTree< RSQMonoid >;
using RMaxQ = PersistentSegTree< RMaxQMonoid >;

// }}}
