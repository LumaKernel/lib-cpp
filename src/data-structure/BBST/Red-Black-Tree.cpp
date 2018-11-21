// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Red-Black Tree Sequence
// @snippet redblacktree_seq
// @alias rbt_seq seq_rbt persistent_rbt_seq

constexpr int FREE_TYPE = 0; // 0 : nothing, 1 : free, 2 : destroy
constexpr int POOL_SIZE = 1.1e7;

// <BBST Basic Funcs> ( node [, ...] )
// build ( node, first, last )
// Node::rebuildCheck ( <nodes>, threshold = 1e4 )
// mfree( node )
// [Persistent] clone ( node [, <range> ] )
/// --- Red-Black Tree Sequence {{{ ///

#include <cassert>
#include <cstdint>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

namespace RBT {

// MemoryPool {{{

template < int POOL_SIZE >
struct MemoryPool {
  template < class T >
  struct Core {
  private:
    vector< T * > ptr;
    T *start;
    uint_fast32_t idx = 0;

  public:
    Core() : ptr(POOL_SIZE) { expand(); }
    void expand() {
      start = (T *) malloc(sizeof(T) * POOL_SIZE);
      iota(ptr.begin(), ptr.end(), start);
    }
    void clear() {
      idx = 0;
      if(FREE_TYPE) iota(ptr.begin(), ptr.end(), start);
    }
    T *alloc() { return ptr[idx++]; }
    void free(T *p) {
      assert(FREE_TYPE);
      if(p) ptr[--idx] = p;
    }
    void destroy(T *p) {
      assert(FREE_TYPE);
      if(p) {
        p->~T();
        free(p);
      }
    }
    const T *next() { return ptr[idx]; }
    int capacity() const { return ptr.size(); }
    int used() const { return idx; }
    int rest() const { return ptr.size() - idx; }
  };
};

// }}}

// RBTSeq Base {{{

template < class Monoid, class M_act, bool isPersistent,
           template < class > class Allocator >
struct RedBlackTreeSequenceBase {
private:
  using Node = RedBlackTreeSequenceBase;

public:
  static Allocator< Node > alc;

private:
  Node *c[2];
  using X = typename Monoid::T;
  using M = typename M_act::M;
  X accum = Monoid::identity();
  M lazy = M_act::identity();
  uint_fast8_t rev = false;
  int sz;
  enum Color { BLACK, RED };
  uint_fast8_t color;
  uint_fast8_t level;

private:
  // leaf node
  RedBlackTreeSequenceBase(X val = Monoid::identity())
      : c{0, 0}, accum(val), sz(1), color(BLACK), level(0) {}
  // internal node
  RedBlackTreeSequenceBase(Node *l, Node *r, Color color) : c{l, r}, color(color) {
    prop(this);
  }
  static Node *make(Node *l, Node *r, Color color) {
    // assert(l && r && l != alc.next() && r != alc.next()); // explicit
    return new(alc.alloc()) Node(l, r, color);
  }
  static Node *make(const X &x) { return new(alc.alloc()) Node(x); }

  // prop and eval {{{

private:
  // [RBT] a is internal node
  // a is evaled
  // a->c[0], c[1] is proped, evaled
  friend Node *prop(Node *a) {
    a->sz = a->c[0]->sz + a->c[1]->sz;
    a->accum = Monoid::op(a->c[0]->accum, a->c[1]->accum);
    // assert(a->c[0]->level + (a->c[0]->color == BLACK) ==
    //        a->c[1]->level + (a->c[1]->color == BLACK)); // explicit
    a->level = a->c[0]->level + (a->c[0]->color == BLACK);
    return a;
  }
  // call before use val, accum
  friend Node *eval(Node *a) {
    if(a->lazy != M_act::identity()) {
      a->accum = M_act::actInto(a->lazy, -1, a->sz, a->accum);
      for(int i = 0; i < 2; i++)
        if(a->c[i]) {
          a->c[i] = copy(a->c[i]);
          a->c[i]->lazy = M_act::op(a->lazy, a->c[i]->lazy);
        }
      a->lazy = M_act::identity();
    }
    if(a->rev) {
      swap(a->c[0], a->c[1]);
      for(int i = 0; i < 2; i++)
        if(a->c[i]) {
          a->c[i] = copy(a->c[i]);
          a->c[i]->rev ^= 1;
        }
      a->rev = false;
    }
    return a;
  }

  // }}}

  // BBST {{{
public:
  friend void mfree(Node *a) {
    if(FREE_TYPE == 1)
      alc.free(a);
    else if(FREE_TYPE == 2)
      alc.destroy(a);
  }
  friend void push_front(Node *&a, const X &x) { a = merge(make(x), a); }
  friend void push_back(Node *&a, const X &x) { a = merge(a, make(x)); }
  friend void insert(Node *&a, int k, const X &x) { insert(a, k, make(x)); }
  friend void insert(Node *&a, int k, Node *b) {
    Node *sl, *sr;
    tie(sl, sr) = split(a, k);
    a = merge(sl, merge(b, sr));
  }
  friend X pop_front(Node *&a) {
    Node *sl, *sr;
    tie(sl, sr) = split(a, 1);
    a = sr;
    X x = getValue(sl);
    mfree(sl);
    return x;
  }
  friend X pop_back(Node *&a) {
    Node *sl, *sr;
    tie(sl, sr) = split(a, size(a) - 1);
    a = sl;
    X x = getValue(sr);
    mfree(sr);
    return x;
  }
  friend X erase(Node *&a, int k) {
    Node *x, *y, *z;
    tie(x, y, z) = split(a, k, k + 1);
    X v = getValue(y);
    mfree(y);
    a = merge(x, z);
    return v;
  }
  friend void erase(Node *&a, int l, int r) {
    Node *x, *y, *z;
    tie(x, y, z) = split(a, l, r);
    mfree(y);
    a = merge(x, z);
  }
  friend tuple< Node *, Node *, Node * > split(Node *a, int l, int r) {
    Node *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, r);
    tie(tl, tr) = split(sl, l);
    return make_tuple(tl, tr, sr);
  }
  friend void mset(Node *&a, int k, const X &v) {
    if(!a) return;
    if(k < 0 || a->sz <= k) return;
    a = eval(a);
    if(isLeaf(a))
      a->accum = v;
    else if(k < a->c[0]->sz)
      mset(a->c[0], k, v);
    else
      mset(a->c[1], k - a->c[0]->sz, v);
    a = prop(a);
  }
  friend X getValue(const Node *a) {
    assert(isLeaf(a));
    return a ? a->lazy != M_act::identity() ? M_act::actInto(a->accum, -1, 1, a->lazy)
                                            : a->accum
             : Monoid::identity();
  }
  friend vector< X > getAll(const Node *a) {
    vector< X > v(size(a));
    auto ite = v.begin();
    getdfs(a, M_act::identity(), ite);
    return v;
  }

  friend X mget(const Node *a, int k) {
    if(!a) return Monoid::identity();
    if(isLeaf(a)) return k == 0 ? getValue(a) : Monoid::identity();
    return k < a->c[0]->sz ? mget(a->c[0], k) : mget(a->c[1], k - a->c[0]->sz);
  }
  friend void act(Node *&a, int l, int r, const M &m) {
    Node *x, *y, *z;
    tie(x, y, z) = split(a, l, r);
    if(y) y->lazy = M_act::op(m, y->lazy);
    a = merge(merge(x, y), z);
  }
  friend X query(Node *a) { return a ? (eval(a), a->accum) : Monoid::identity(); }
  friend X query(Node *&a, int l, int r) {
    Node *x, *y, *z;
    tie(x, y, z) = split(a, l, r);
    X res = query(y);
    a = merge(merge(x, y), z);
    return res;
  }
  friend void reverse(Node *a) {
    if(a) a->rev ^= 1;
  }
  friend void reverse(Node *&a, int l, int r) {
    Node *x, *y, *z;
    tie(x, y, z) = split(a, l, r);
    if(y) y->rev ^= 1;
    a = merge(merge(x, y), z);
  }
  friend int size(const Node *a) { return a ? a->sz : 0; }
  /// }}}--- ///

private:
  static Node *copy(Node *a) {
    // assert(a); // explicit
    if(isPersistent) {
      return new(alc.alloc()) Node(*a);
    } else {
      return a;
    }
  }

  // [RBT] rotate, submerge {{{
private:
  // [RBT]
  // a is evaled, NOT proped
  // a->c[_] is unique, evaled;
  // a->c[!R] is internal node
  // a->c[!R]->c[!R] is unique, evaled
  friend Node *rotate(Node *a, bool R) {
    Node *l = a->c[!R];
    a->c[!R] = eval(copy(l->c[R]));
    l->c[R] = prop(a);
    return prop(l);
  }
  // [RBT]
  // a is internal node, evaled, NOT proped
  // a->[_] is unique, evaled
  // return proped, evaled
  friend Node *check(Node *a, bool R) {
    if(a->color == BLACK && a->c[!R]->color == RED && a->c[!R]->c[!R]->color == RED) {
      // assert(a->c[!R]->c[R]->color == BLACK); // explicit
      a->color = RED;
      a->c[!R]->color = BLACK;
      if(a->c[R]->color == BLACK) return rotate(a, R);
      a->c[R]->color = BLACK;
    }
    return prop(a);
  }
  // return proped, evaled
  friend Node *submerge(Node *a, Node *b) {
    if(a->level < b->level) {
      // b is NOT leaf node
      // assert(b->c[0] && b->c[1]); // explicit
      b = eval(b);
      b->c[0] = submerge(a, copy(b->c[0]));
      b->c[1] = eval(copy(b->c[1]));
      return check(b, 1);
    } else if(a->level > b->level) {
      // a is NOT leaf node
      // assert(a->c[0] && a->c[1]); // explicit
      a = eval(a);
      a->c[1] = submerge(copy(a->c[1]), b);
      a->c[0] = eval(copy(a->c[0]));
      return check(a, 0);
    } else {
      // assert(a->color == BLACK && b->color == BLACK); // explicit
      return make(eval(a), eval(b), RED);
    }
  }
  // }}}

  // [RBT] {{{
public:
  // return evaled
  friend Node *merge(Node *a, Node *b) {
    if(!a) return b;
    if(!b) return a;
    Node *c = submerge(a, b);
    c->color = BLACK;
    return c;
  }

  // [0, k), [k, n)
  friend pair< Node *, Node * > split(Node *a, int k) {
    if(!a) return {0, 0};
    if(k == 0) return {0, a};
    if(k >= a->sz) return {a, 0};
    a = eval(a);
    // a is internal
    // assert(a->c[0] && a->c[1]); // explicit

    Node *sl, *sr;
    Node *l = copy(a->c[0]), *r = copy(a->c[1]);
    mfree(a);
    if(k < l->sz) {
      tie(sl, sr) = split(l, k);
      return {sl, merge(sr, r)};
    }
    if(k > l->sz) {
      tie(sl, sr) = split(r, k - l->sz);
      return {merge(l, sl), sr};
    }
    l->color = r->color = BLACK;
    return {l, r};
  }
  friend Node *clone(Node *a) {
    assert(isPersistent);
    if(!a) return 0;
    return new(alc.alloc()) Node(*a);
  }
  friend Node *clone(Node *&a, int l, int r) {
    assert(isPersistent);
    if(!a) return 0;
    Node *x, *y, *z;
    tie(x, y, z) = split(a, l, r);
    Node *res = clone(y);
    a = merge(merge(x, y), z);
    return res;
  }

  // it must be guaranteed that there's enough memory in pool
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  friend Node *build(Node *&a, InputIter first, InputIter last) {
    mfree(a);
    int n = distance(first, last);
    if(n == 0) return 0;
    vector< Node * > v(n), tmp(n);
    InputIter ite = first;
    for(int i = 0; i < n; ++i, ++ite) v[i] = make(*ite);
    while(v.size() != 1) {
      tmp.resize(v.size() >> 1);
      for(size_t i = 0; i < tmp.size(); i++) tmp[i] = merge(v[i << 1], v[(i << 1) | 1]);
      if(v.size() & 1) tmp.emplace_back(v.back());
      swap(v, tmp);
    }
    return a = v[0];
  }

  friend inline bool isLeaf(const Node *a) { return !bool(a->c[0]); }

private:
  static void getdfs(const Node *a, M m, typename vector< X >::iterator &ite) {
    if(a->lazy != M_act::identity()) m = M_act::op(m, a->lazy);
    if(isLeaf(a)) {
      *ite++ = m != M_act::identity() ? M_act::actInto(a->accum, -1, 1, m) : a->accum;
    } else {
      getdfs(a->c[0], m, ite);
      getdfs(a->c[1], m, ite);
    }
  }

public:
  static void rebuild(vector< Node * > &roots) {
    vector< vector< X > > vals(roots.size());
    for(size_t i = 0; i < roots.size(); i++) {
      vals[i] = (getAll(roots[i]));
    }
    alc.clear();
    for(size_t i = 0; i < roots.size(); i++) {
      build(roots[i] = 0, vals[i].begin(), vals[i].end());
    }
  }

  static inline void rebuildCheck(Node *&a, int threshold = 10000) {
    if(Node::alc.rest() < threshold) {
      vector< Node * > v{a};
      Node::rebuild(v);
      a = v[0];
    }
  }

  static inline void rebuildCheck(vector< Node * > &v, int threshold = 10000) {
    if(Node::alc.rest() < threshold) Node::rebuild(v);
  }

  friend string to_string(const Node *a) {
    if(!a) return "";
    return "(" + to_string(a->c[0]) +          //
           ", accum: " + to_string(a->accum) + //
           // " isBlack: " + to_string(a->color == BLACK) + //
           " sz: " + to_string(a->sz) + //
           ", " + to_string(a->c[1]) + ")";
  }

  // }}}
};

template < class Monoid, class M_act, bool isPersistent,
           template < class > class Allocator >
Allocator< RedBlackTreeSequenceBase< Monoid, M_act, isPersistent, Allocator > >
    RedBlackTreeSequenceBase< Monoid, M_act, isPersistent, Allocator >::alc;

// }}}

template < class Monoid, class M_act >
using RBTSeq =
    RedBlackTreeSequenceBase< Monoid, M_act, false, MemoryPool< POOL_SIZE >::Core >;

template < class Monoid, class M_act >
using PersistentRBTSeq =
    RedBlackTreeSequenceBase< Monoid, M_act, true, MemoryPool< POOL_SIZE >::Core >;

} // namespace RBT

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
  static T op(const T &a, const T &b) { return a + b; }
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

using RBT::PersistentRBTSeq;
using RBT::RBTSeq;

// using Node = RBTSeq< RangeSum, RangeSumAdd >; // FREE_TYPE = 1
using Node = PersistentRBTSeq< RangeSum, RangeSumAdd >; // FREE_TYPE = 0

Node *seq = 0;

// @new TEST-RBT-SEQUENCE
// {{{
int main() {
  if(0) {
    push_back(seq, 0);
    pop_back(seq);
    insert(seq, 1, 10);
    erase(seq, 1);
    erase(seq, 1, 10);
    split(seq, 1, 10);
    mget(seq, 1);
    mset(seq, 4, 10);
    act(seq, 0, 10, 10);
    query(seq, 0, 10);
    reverse(seq, 0, 10);
    // [RBT]
    clone(seq);
    clone(seq, 0, 10);
    to_string(seq);
    isLeaf(seq);
    getAll(seq);
    vector< Node* > v{seq};
    Node::rebuild(v);
    Node::rebuildCheck(v, 10000);
    Node::rebuildCheck(seq, 10000);
  }
}
// }}}
