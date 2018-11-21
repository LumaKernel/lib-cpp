// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name RBST Sequence Library
// @snippet rbst_seq
/// --- RBST Sequence Library {{{ ///

template < class Monoid, class M_act >
struct RBSTSeq {
private:
  using u32 = uint32_t;
  using X = typename Monoid::T;
  using M = typename M_act::M;
  RBSTSeq *l = nullptr, *r = nullptr;
  X val;
  X accum = Monoid::identity();
  M lazy = M_act::identity();
  bool rev = false;
  int sz = 1;
  // call after touch its child
  // a is not nullptr and is evaled, its child is proped
  friend RBSTSeq *prop(RBSTSeq *a) {
    a->sz = size(a->l) + 1 + size(a->r);
    a->accum =
        Monoid::op(Monoid::op(Accumulated(a->l), a->val), Accumulated(a->r));
    return a;
  }
  // call before use val, accum
  friend void eval(RBSTSeq *a) {
    if(a->lazy != M_act::identity()) {
      a->val = M_act::actInto(a->lazy, -1, 1, a->val);
      a->accum = M_act::actInto(a->lazy, -1, a->sz, a->accum);
      if(a->l != nullptr) a->l->lazy = M_act::op(a->lazy, a->l->lazy);
      if(a->r != nullptr) a->r->lazy = M_act::op(a->lazy, a->r->lazy);
      a->lazy = M_act::identity();
    }
    if(a->rev) {
      swap(a->l, a->r);
      if(a->l != nullptr) a->l->rev ^= 1;
      if(a->r != nullptr) a->r->rev ^= 1;
      a->rev = false;
    }
  }
  friend X Accumulated(RBSTSeq *a) {
    return a == nullptr ? Monoid::identity() : (eval(a), a->accum);
  }
  /// --- XorShift128 {{{ ///
  struct XorShift128 {
    using u32 = uint32_t;
    u32 x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    XorShift128(u32 seed = 0) { z ^= seed; }
    u32 operator()() {
      u32 t = x ^ (x << 11);
      x = y, y = z, z = w;
      return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
  };
  /// }}}--- ///
public:
  RBSTSeq(X val = Monoid::identity()) : val(val) {}
  friend RBSTSeq *merge(RBSTSeq *a, RBSTSeq *b) {
    static XorShift128 xs(__LINE__ * 3 + 5);
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    eval(a);
    eval(b);
    if(xs() % (size(a) + size(b)) < (u32) size(a)) {
      a->r = merge(a->r, b);
      return prop(a);
    } else {
      b->l = merge(a, b->l);
      return prop(b);
    }
  }
  friend int size(RBSTSeq *a) { return a == nullptr ? 0 : a->sz; }
  using PNN = pair< RBSTSeq *, RBSTSeq * >;
  // [0, k), [k, n)
  // 左のグループにk個いれる
  friend PNN split(RBSTSeq *a, int k) {
    if(a == nullptr) return PNN(nullptr, nullptr);
    eval(a);
    RBSTSeq *sl, *sr;
    if(k <= size(a->l)) {
      tie(sl, sr) = split(a->l, k);
      a->l = sr;
      return PNN(sl, prop(a));
    } else {
      tie(sl, sr) = split(a->r, k - size(a->l) - 1);
      a->r = sl;
      return PNN(prop(a), sr);
    }
  }
  friend void insert(RBSTSeq *&a, int k, const X &x) {
    RBSTSeq *sl, *sr;
    tie(sl, sr) = split(a, k);
    a = merge(sl, merge(new RBSTSeq(x), sr));
  }
  friend X erase(RBSTSeq *&a, int k) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, k + 1);
    tie(tl, tr) = split(sl, k);
    a = merge(tl, sr);
    return tr->val;
  }
  friend void erase(RBSTSeq *&a, int l, int r) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, r);
    tie(tl, tr) = split(sl, l);
    a = merge(tl, sr);
  }
  friend void set1(RBSTSeq *&a, int k, X const &x) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, k + 1);
    tie(tl, tr) = split(sl, k);
    if(tr != nullptr) tr->val = tr->accum = x;
    a = merge(merge(tl, tr), sr);
  }
  friend X get(RBSTSeq *&a, int k) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, k + 1);
    tie(tl, tr) = split(sl, k);
    X res = tr == nullptr ? Monoid::identity() : tr->val;
    a = merge(merge(tl, tr), sr);
    return res;
  }
  friend void act(RBSTSeq *&a, int l, int r, M const &m) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, r);
    tie(tl, tr) = split(sl, l);
    if(tr != nullptr) tr->lazy = M_act::op(m, tr->lazy);
    a = merge(merge(tl, tr), sr);
  }
  friend X query(RBSTSeq *&a, int l, int r) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, r);
    tie(tl, tr) = split(sl, l);
    X res = tr == nullptr ? Monoid::identity() : tr->accum;
    a = merge(merge(tl, tr), sr);
    return res;
  }
  friend void reverse(RBSTSeq *&a, int l, int r) {
    RBSTSeq *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, r);
    tie(tl, tr) = split(sl, l);
    if(tr != nullptr) tr->rev ^= 1;
    a = merge(merge(tl, tr), sr);
  }
};

/// }}}--- ///

/// --- Monoid, M_act examples {{{ ///

/// --- Monoid examples {{{ ///

#include <algorithm>
#include <limits>

constexpr long long inf = 1e18 + 100;

struct Nothing {
  using T = char;
  using M = T;
  static constexpr T op(const T &, const T &) { return T(); }
  static constexpr T identity() { return T(); }
  template < class X >
  static constexpr X actInto(const M &, ll, ll, const X &x) {
    return x;
  }
};

struct RangeMin {
  using T = ll;
  static T op(const T &a, const T &b) { return min(a, b); }
  static constexpr T identity() { return inf; }
};

struct RangeMax {
  using T = ll;
  static T op(const T &a, const T &b) { return max(a, b); }
  static constexpr T identity() { return -inf; }
};

struct RangeSum {
  using T = ll;
  static T op(const T &a, const T &b) { return (a + b) % mod; }
  static constexpr T identity() { return 0; }
};

/// }}}--- ///

// MinAdd m + x
// MinSet m
// SumAdd m * n + x
// SumSet m * n

#include <limits>

struct RangeMinAdd {
  using M = ll;
  using X = RangeMin::T;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, ll, const X &x) { return m + x; }
};

struct RangeMinSet {
  using M = ll;
  using X = RangeMin::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -inf; }
  static X actInto(const M &m, ll, ll, const X &) { return m; }
};

struct RangeSumAdd {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, ll n, const X &x) { return m * n + x; }
};

struct RangeSumSet {
  using M = ll;
  using X = RangeSum::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -inf; }
  static X actInto(const M &m, ll, ll n, const X &) { return m * n; }
};

/// }}}--- ///

RBSTSeq< RangeMin, RangeMinAdd > *seq = nullptr;

// @new
// @name RBST Multiset Library
// @snippet rbst_multiset
/// --- RBST Multiset Library {{{ ///

template < class Key >
struct RBSTMultiset {
public:
  const Key key;

private:
  using u32 = uint32_t;
  using PNN = pair< RBSTMultiset*, RBSTMultiset* >;
  RBSTMultiset *l = nullptr, *r = nullptr;
  int sz = 1;
  friend RBSTMultiset* prop(RBSTMultiset* a) {
    a->sz = size(a->l) + 1 + size(a->r);
    return a;
  }
  /// --- XorShift128 {{{ ///
  struct XorShift128 {
    using u32 = uint32_t;
    u32 x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    XorShift128(u32 seed = 0) { z ^= seed; }
    u32 operator()() {
      u32 t = x ^ (x << 11);
      x = y, y = z, z = w;
      return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
  };
  /// }}}--- ///
public:
  RBSTMultiset(Key key) : key(key) {}
  friend RBSTMultiset* merge(RBSTMultiset* a, RBSTMultiset* b) {
    static XorShift128 xs(__LINE__ * 3 + 5);
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(xs() % (size(a) + size(b)) < (u32) size(a)) {
      a->r = merge(a->r, b);
      return prop(a);
    } else {
      b->l = merge(a, b->l);
      return prop(b);
    }
  }
  // lower (-inf, key), [key, inf)
  // upper (-inf, key], (key, inf)
  friend PNN split(RBSTMultiset* a, Key key, bool upper) {
    if(a == nullptr) return PNN(nullptr, nullptr);
    RBSTMultiset *sl, *sr;
    if(upper ? key < a->key : !(a->key < key)) {
      tie(sl, sr) = split(a->l, key, upper);
      a->l = sr;
      return PNN(sl, prop(a));
    } else {
      tie(sl, sr) = split(a->r, key, upper);
      a->r = sl;
      return PNN(prop(a), sr);
    }
  }
  friend PNN lower_split(RBSTMultiset* a, const Key& key) {
    return split(a, key, false);
  }
  friend PNN upper_split(RBSTMultiset* a, const Key& key) {
    return split(a, key, true);
  }
  friend int size(RBSTMultiset* a) { return a == nullptr ? 0 : a->sz; }
  friend void insert(RBSTMultiset*& a, Key key) {
    RBSTMultiset *sl, *sr;
    tie(sl, sr) = lower_split(a, key);
    a = merge(sl, merge(new RBSTMultiset(key), sr));
  }
  friend void erase(RBSTMultiset*& a, Key key) {
    RBSTMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = upper_split(a, key);
    tie(tl, tr) = lower_split(sl, key);
    a = merge(tl, sr);
  }
  friend void erase(RBSTMultiset*& a, Key keyL, Key keyR,
                    bool inclusive = false) {
    RBSTMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, keyR, inclusive);
    tie(tl, tr) = lower_split(sl, keyL);
    a = merge(tl, sr);
  }
  friend void erase1(RBSTMultiset*& a, Key key) {
    if(a == nullptr) return;
    if(key < a->key) {
      erase1(a->l, key);
    } else {
      if(!(a->key < key)) {
        a = merge(a->l, a->r);
        return;
      }
      erase1(a->r, key);
    }
    prop(a);
  }
  friend Key getKth(RBSTMultiset*& a, int k) {
    static const struct CannotGetKthOfNullptr {} ex;
    if(a == nullptr) throw ex;
    if(k <= size(a->l)) {
      if(k == size(a->l)) return a->key;
      return getKth(a->l, k);
    } else {
      return getKth(a->r, k - size(a->l) - 1);
    }
  }
  friend int count(RBSTMultiset*& a, Key key) {
    RBSTMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = upper_split(a, key);
    tie(tl, tr) = lower_split(sl, key);
    int cnt = size(tr);
    a = merge(merge(tl, tr), sr);
    return cnt;
  }
  friend int count(RBSTMultiset*& a, Key keyL, Key keyR,
                   bool inclusive = false) {
    RBSTMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, keyR, inclusive);
    tie(tl, tr) = lower_split(sl, keyL);
    int cnt = size(tr);
    a = merge(merge(tl, tr), sr);
    return cnt;
  }
};

/// }}}--- ///

RBSTMultiset< ll >* ms = nullptr;
